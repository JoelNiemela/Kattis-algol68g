//! @file bits.c
//! @author J. Marcel van der Veer
//
//! @section Copyright
//
// This file is part of Algol68G - an Algol 68 compiler-interpreter.
// Copyright 2001-2022 J. Marcel van der Veer <algol68g@xs4all.nl>.
//
//! @section License
//
// This program is free software; you can redistribute it and/or modify it 
// under the terms of the GNU General Public License as published by the 
// Free Software Foundation; either version 3 of the License, or 
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
// more details. You should have received a copy of the GNU General Public 
// License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "a68g.h"
#include "a68g-prelude.h"
#include "a68g-mp.h"
#include "a68g-genie.h"
#include "a68g-postulates.h"
#include "a68g-parser.h"
#include "a68g-options.h"
#include "a68g-optimiser.h"
#include "a68g-listing.h"

#if defined (HAVE_MATHLIB)
#include <Rmath.h>
#endif

#if defined (BUILD_WIN32)
#include <windows.h>
#endif

// libgen selects Posix versions of dirname/basename in stead of GNU versions.

#include <libgen.h> 

#define WRITE_TXT(fn, txt) ASSERT (write ((fn), (txt), 1 + strlen (txt)) != -1)

#if defined (BUILD_LINUX)

#include <execinfo.h>

void genie_sigsegv (NODE_T *p)
{
  (void) p;
  raise (SIGSEGV);
}

//! @brief Provide a rudimentary backtrace.

void stack_backtrace (void)
{
#define DEPTH 16
  void *array[DEPTH];
  WRITE_TXT (2, "\n++++ Top of call stack:");
  int size = backtrace (array, DEPTH);
  if (size > 0) {
    WRITE_TXT (2, "\n");
    backtrace_symbols_fd (array, size, 2);
  }
#undef DEPTH
}

void genie_backtrace (NODE_T *p)
{
  (void) p;
  stack_backtrace ();
}

#else

void stack_backtrace (void)
{
  WRITE_TXT (2, "\n++++ Stack backtrace is linux-only");
}

void genie_backtrace (NODE_T *p)
{
  (void) p;
  stack_backtrace ();
}
#endif

//! @brief Open a file in ~/.a68g, if possible.

FILE *a68_fopen (char *fn, char *mode, char *new_fn)
{
#if defined (BUILD_WIN32) || !defined (HAVE_DIRENT_H)
  ASSERT (snprintf (new_fn, SNPRINTF_SIZE, "%s", fn) >= 0);
  return fopen (new_fn, mode);
#else
  char dn[BUFFER_SIZE];
  int rc;
  errno = 0;
  ASSERT (snprintf (dn, SNPRINTF_SIZE, "%s/%s", getenv ("HOME"), A68_DIR) >= 0);
  rc = mkdir (dn, (mode_t) (S_IRUSR | S_IWUSR | S_IXUSR));
  if (rc == 0 || (rc == -1 && errno == EEXIST)) {
    struct stat status;
    if (stat (dn, &status) == 0 && S_ISDIR (ST_MODE (&status)) != 0) {
      FILE *f;
      ASSERT (snprintf (new_fn, SNPRINTF_SIZE, "%s/%s", dn, fn) >= 0);
      f = fopen (new_fn, mode);
      if (f != NO_FILE) {
        return f;
      }
    }
  }
  ASSERT (snprintf (new_fn, SNPRINTF_SIZE, "%s", fn) >= 0);
  return fopen (new_fn, mode);
#endif
}

//! @brief Get terminal size.

void a68_getty (int *h, int *c)
{
// Default action first.
  (*h) = MAX_TERM_HEIGTH;
  (*c) = MAX_TERM_WIDTH;
#if (defined (HAVE_SYS_IOCTL_H) && defined (TIOCGWINSZ))
  {
    struct winsize w;
    if (ioctl (0, TIOCGWINSZ, &w) == 0) {
      (*h) = w.ws_row;
      (*c) = w.ws_col;
    }
  }
#elif (defined (HAVE_SYS_IOCTL_H) && defined (TIOCGSIZE))
  {
    struct ttysize w;
    (void) ioctl (0, TIOCGSIZE, &w);
    if (w.ts_lines > 0) {
      (*h) = w.ts_lines;
    }
    if (w.ts_cols > 0) {
      (*c) = w.ts_cols;
    }
  }
#elif (defined (HAVE_SYS_IOCTL_H) && defined (WIOCGETD))
  {
    struct uwdata w;
    (void) ioctl (0, WIOCGETD, &w);
    if (w.uw_heigth > 0 && w.uw_vs != 0) {
      (*h) = w.uw_heigth / w.uw_vs;
    }
    if (w.uw_width > 0 && w.uw_hs != 0) {
      (*c) = w.uw_width / w.uw_hs;
    }
  }
#endif
}

// Signal handlers.

//! @brief Signal for window resize.

#if defined (SIGWINCH)
void sigwinch_handler (int i)
{
  (void) i;
  ABEND (signal (SIGWINCH, sigwinch_handler) == SIG_ERR, ERROR_ACTION, __func__);
  a68_getty (&A68 (term_heigth), &A68 (term_width));
  return;
}
#endif

//! @brief Signal reading for segment violation.

void sigsegv_handler (int i)
{
  (void) i;
// write () is asynchronous-safe and may be called here.
  WRITE_TXT (2, "\nFatal");
  if (FILE_INITIAL_NAME (&A68_JOB) != NO_TEXT) {
    WRITE_TXT (2, ": ");
    WRITE_TXT (2, FILE_INITIAL_NAME (&A68_JOB));
  }
  WRITE_TXT (2, ": memory access violation\n");
  stack_backtrace ();
  exit (EXIT_FAILURE);
  return;
}

//! @brief Raise SYSREQUEST so you get to a monitor.

void sigint_handler (int i)
{
  (void) i;
  ABEND (signal (SIGINT, sigint_handler) == SIG_ERR, ERROR_ACTION, __func__);
  if (!(STATUS_TEST (TOP_NODE (&A68_JOB), BREAKPOINT_INTERRUPT_MASK) || A68 (in_monitor))) {
    STATUS_SET (TOP_NODE (&A68_JOB), BREAKPOINT_INTERRUPT_MASK);
    genie_break (TOP_NODE (&A68_JOB));
  }
}

#if defined (BUILD_UNIX)

//! @brief Signal reading from disconnected terminal.

void sigttin_handler (int i)
{
  (void) i;
  ABEND (A68_TRUE, ERROR_ACTION, __func__);
}

//! @brief Signal broken pipe.

void sigpipe_handler (int i)
{
  (void) i;
  ABEND (A68_TRUE, ERROR_ACTION, __func__);
}

//! @brief Signal alarm - time limit check.

void sigalrm_handler (int i)
{
  (void) i;
  if (A68 (in_execution) && !A68 (in_monitor)) {
    REAL_T _m_t = (REAL_T) OPTION_TIME_LIMIT (&A68_JOB);
    if (_m_t > 0 && (seconds () - A68 (cputime_0)) > _m_t) {
      diagnostic (A68_RUNTIME_ERROR, (NODE_T *) A68 (f_entry), ERROR_TIME_LIMIT_EXCEEDED);
      exit_genie ((NODE_T *) A68 (f_entry), A68_RUNTIME_ERROR);
    }
  }
  (void) alarm (1);
}

#endif

//! @brief Install_signal_handlers.

void install_signal_handlers (void)
{
  ABEND (signal (SIGINT, sigint_handler) == SIG_ERR, ERROR_ACTION, __func__);
  ABEND (signal (SIGSEGV, sigsegv_handler) == SIG_ERR, ERROR_ACTION, __func__);
#if defined (SIGWINCH)
  ABEND (signal (SIGWINCH, sigwinch_handler) == SIG_ERR, ERROR_ACTION, __func__);
#endif
#if defined (BUILD_UNIX)
  ABEND (signal (SIGALRM, sigalrm_handler) == SIG_ERR, ERROR_ACTION, __func__);
  ABEND (signal (SIGPIPE, sigpipe_handler) == SIG_ERR, ERROR_ACTION, __func__);
  ABEND (signal (SIGTTIN, sigttin_handler) == SIG_ERR, ERROR_ACTION, __func__);
#endif
}

//! @brief Time versus arbitrary origin.

REAL_T seconds (void)
{
  return (REAL_T) clock () / (REAL_T) CLOCKS_PER_SEC;
}

//! @brief Safely append to buffer.

void bufcat (char *dst, char *src, int len)
{
  if (src != NO_TEXT) {
    char *d = dst, *s = src;
    int n = len, dlen;
// Find end of dst and left-adjust; do not go past end 
    for (; n-- != 0 && d[0] != NULL_CHAR; d++) {
      ;
    }
    dlen = (int) (d - dst);
    n = len - dlen;
    if (n > 0) {
      while (s[0] != NULL_CHAR) {
        if (n != 1) {
          (d++)[0] = s[0];
          n--;
        }
        s++;
      }
      d[0] = NULL_CHAR;
    }
// Better sure than sorry 
    dst[len - 1] = NULL_CHAR;
  }
}

//! @brief Safely copy to buffer.

void bufcpy (char *dst, char *src, int len)
{
  if (src != NO_TEXT) {
    char *d = dst, *s = src;
    int n = len;
// Copy as many as fit 
    if (n > 0 && --n > 0) {
      do {
        if (((d++)[0] = (s++)[0]) == NULL_CHAR) {
          break;
        }
      } while (--n > 0);
    }
    if (n == 0 && len > 0) {
// Not enough room in dst, so terminate 
      d[0] = NULL_CHAR;
    }
// Better sure than sorry 
    dst[len - 1] = NULL_CHAR;
  }
}

//! @brief Safely get dir name from path.

char *a68_dirname (char *src)
{
  int len = (int) strlen (src) + 1;
  char *cpy = (char *) get_fixed_heap_space (len + 1);
  char *dst = (char *) get_fixed_heap_space (len + 1);
  ABEND (cpy == NO_TEXT, ERROR_OUT_OF_CORE, __func__);
  ABEND (dst == NO_TEXT, ERROR_OUT_OF_CORE, __func__);
  bufcpy (cpy, src, len);
  bufcpy (dst, dirname (cpy), len);
  return dst;
}

//! @brief Safely get basename from path.

char *a68_basename (char *src)
{
  int len = (int) strlen (src) + 1;
  char *cpy = (char *) get_fixed_heap_space (len + 1);
  char *dst = (char *) get_fixed_heap_space (len + 1);
  ABEND (cpy == NO_TEXT, ERROR_OUT_OF_CORE, __func__);
  ABEND (dst == NO_TEXT, ERROR_OUT_OF_CORE, __func__);
  bufcpy (cpy, src, len);
  bufcpy (dst, basename (cpy), len);
  return dst;
}

//! @brief Compute relative path.

#if defined (BUILD_WIN32)

static char *win32_slash (char *p)
{
  char *q = p;
  while (*p != '\0') {
    if (*p == '\\') {
      *p = '/';
    }
    p++;
  }
  return q;
}

static char *win32_realpath (char *name, char *resolved)
{
  char *res = NO_TEXT;
  if (name == NO_TEXT || name[0] == '\0') {
    return NO_TEXT;
  }
  if (resolved == NO_TEXT) {
    res = (char *) get_fixed_heap_space (PATH_MAX + 1);
    if (res == NO_TEXT) {
      return NO_TEXT;
    }
  } else {
    res = resolved;
  }
  int rc = GetFullPathName (name, PATH_MAX, res, (char **) NO_TEXT);
  if (rc == 0) {
    return NO_TEXT;
  } else {
    win32_slash (res);
    struct stat st;
    if (stat (res, &st) < 0) { // Should be 'lstat', but mingw does not have that.
      if (resolved == NO_TEXT) {
        free (res);
        return NO_TEXT;
      }
    }
  }
  return res;
}

#endif

char *a68_relpath (char *p1, char *p2, char *fn)
{
  char q[PATH_MAX + 1];
  bufcpy (q, p1, PATH_MAX);
  bufcat (q, "/", PATH_MAX);
  bufcat (q, p2, PATH_MAX);
  bufcat (q, "/", PATH_MAX);
  bufcat (q, fn, PATH_MAX);
// Home directory shortcut ~ is a shell extension.
  if (strchr (q, '~') != NO_TEXT) {
    return NO_TEXT;
  }
  char *r = (char *) get_fixed_heap_space (PATH_MAX + 1);
  ABEND (r == NO_TEXT, ERROR_OUT_OF_CORE, __func__);
// Error handling in the caller!
#if defined (BUILD_WIN32)
  r = win32_realpath (q, NO_TEXT);
#else
  r = realpath (q, NO_TEXT);
#endif
  return r;
}

//! @brief PROC (STRING) STRING realpath

void genie_realpath (NODE_T * p)
{
  A68_REF str;
  char in[PATH_MAX + 1];
  char * out;
  POP_REF (p, &str);
  if (a_to_c_string (p, in, str) == NO_TEXT) {
    PUSH_REF (p, empty_string (p));
  } else {
// Note that ~ is not resolved since that is the shell, not libc.
#if defined (BUILD_WIN32)
    out = win32_realpath (in, NO_TEXT);
#else
    out = realpath (in, NO_TEXT);
#endif
    if (out == NO_TEXT) {
      PUSH_REF (p, empty_string (p));
    } else {
      PUSH_REF (p, c_to_a_string (p, out, PATH_MAX));
    }
  }
}
