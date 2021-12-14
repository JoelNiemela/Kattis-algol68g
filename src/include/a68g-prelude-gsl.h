//! @file a68g-prelude-gsl.h
//! @author J. Marcel van der Veer
//
//! @section Copyright
//
// This file is part of Algol68G - an Algol 68 compiler-interpreter.
// Copyright 2001-2021 J. Marcel van der Veer <algol68g@xs4all.nl>.
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

#if !defined (__A68G_PRELUDE_GSL_H__)
#define __A68G_PRELUDE_GSL_H__

#if defined (HAVE_GSL)

extern void stand_gsl (void);

extern GPROC genie_airy_ai_deriv_real;
extern GPROC genie_airy_ai_deriv_scaled_real;
extern GPROC genie_airy_ai_real;
extern GPROC genie_airy_ai_scaled_real;
extern GPROC genie_airy_bi_deriv_real;
extern GPROC genie_airy_bi_deriv_scaled_real;
extern GPROC genie_airy_bi_real;
extern GPROC genie_airy_bi_scaled_real;
extern GPROC genie_airy_zero_ai_deriv_real;
extern GPROC genie_airy_zero_ai_real;
extern GPROC genie_airy_zero_bi_deriv_real;
extern GPROC genie_airy_zero_bi_real;
extern GPROC genie_angle_restrict_pos_real;
extern GPROC genie_angle_restrict_symm_real;
extern GPROC genie_atanint_real;
extern GPROC genie_bessel_il0_scaled_real;
extern GPROC genie_bessel_il1_scaled_real;
extern GPROC genie_bessel_il2_scaled_real;
extern GPROC genie_bessel_il_scaled_real;
extern GPROC genie_bessel_in0_real;
extern GPROC genie_bessel_in0_scaled_real;
extern GPROC genie_bessel_in1_real;
extern GPROC genie_bessel_in1_scaled_real;
extern GPROC genie_bessel_in_real;
extern GPROC genie_bessel_in_scaled_real;
extern GPROC genie_bessel_inu_real;
extern GPROC genie_bessel_inu_scaled_real;
extern GPROC genie_bessel_jl0_real;
extern GPROC genie_bessel_jl1_real;
extern GPROC genie_bessel_jl2_real;
extern GPROC genie_bessel_jl_real;
extern GPROC genie_bessel_jn0_real;
extern GPROC genie_bessel_jn1_real;
extern GPROC genie_bessel_jn_real;
extern GPROC genie_bessel_jnu_real;
extern GPROC genie_bessel_kl0_scaled_real;
extern GPROC genie_bessel_kl1_scaled_real;
extern GPROC genie_bessel_kl2_scaled_real;
extern GPROC genie_bessel_kl_scaled_real;
extern GPROC genie_bessel_kn0_real;
extern GPROC genie_bessel_kn0_scaled_real;
extern GPROC genie_bessel_kn1_real;
extern GPROC genie_bessel_kn1_scaled_real;
extern GPROC genie_bessel_kn_real;
extern GPROC genie_bessel_kn_scaled_real;
extern GPROC genie_bessel_knu_real;
extern GPROC genie_bessel_knu_scaled_real;
extern GPROC genie_bessel_knu_scaled_real;
extern GPROC genie_bessel_ln_knu_real;
extern GPROC genie_bessel_yl0_real;
extern GPROC genie_bessel_yl1_real;
extern GPROC genie_bessel_yl2_real;
extern GPROC genie_bessel_yl_real;
extern GPROC genie_bessel_yn0_real;
extern GPROC genie_bessel_yn1_real;
extern GPROC genie_bessel_yn_real;
extern GPROC genie_bessel_ynu_real;
extern GPROC genie_bessel_zero_jnu0_real;
extern GPROC genie_bessel_zero_jnu1_real;
extern GPROC genie_bessel_zero_jnu_real;
extern GPROC genie_beta_inc_gsl_real;
extern GPROC genie_beta_inc_real;
extern GPROC genie_chi_real;
extern GPROC genie_ci_real;
extern GPROC genie_clausen_real;
extern GPROC genie_conicalp_0_real;
extern GPROC genie_conicalp_1_real;
extern GPROC genie_conicalp_cyl_reg_real;
extern GPROC genie_conicalp_half_real;
extern GPROC genie_conicalp_mhalf_real;
extern GPROC genie_conicalp_sph_reg_real;
extern GPROC genie_dawson_real;
extern GPROC genie_debye_1_real;
extern GPROC genie_debye_2_real;
extern GPROC genie_debye_3_real;
extern GPROC genie_debye_4_real;
extern GPROC genie_debye_5_real;
extern GPROC genie_debye_6_real;
extern GPROC genie_dilog_real;
extern GPROC genie_doublefact_real;
extern GPROC genie_ellint_d_real;
extern GPROC genie_ellint_d_real;
extern GPROC genie_ellint_e_comp_real;
extern GPROC genie_ellint_e_real;
extern GPROC genie_ellint_f_real;
extern GPROC genie_ellint_k_comp_real;
extern GPROC genie_ellint_p_comp_real;
extern GPROC genie_ellint_p_real;
extern GPROC genie_ellint_rc_real;
extern GPROC genie_ellint_rd_real;
extern GPROC genie_ellint_rf_real;
extern GPROC genie_ellint_rj_real;
extern GPROC genie_etaint_real;
extern GPROC genie_eta_real;
extern GPROC genie_expint_3_real;
extern GPROC genie_expint_e1_real;
extern GPROC genie_expint_e2_real;
extern GPROC genie_expint_ei_real;
extern GPROC genie_expint_en_real;
extern GPROC genie_expm1_real;
extern GPROC genie_exprel_2_real;
extern GPROC genie_exprel_n_real;
extern GPROC genie_exprel_real;
extern GPROC genie_fact_real;
extern GPROC genie_fermi_dirac_0_real;
extern GPROC genie_fermi_dirac_1_real;
extern GPROC genie_fermi_dirac_2_real;
extern GPROC genie_fermi_dirac_3half_real;
extern GPROC genie_fermi_dirac_half_real;
extern GPROC genie_fermi_dirac_inc_0_real;
extern GPROC genie_fermi_dirac_int_real;
extern GPROC genie_fermi_dirac_m1_real;
extern GPROC genie_fermi_dirac_mhalf_real;
extern GPROC genie_gamma_inc_real;
extern GPROC genie_gamma_inc_p_real;
extern GPROC genie_gamma_inc_q_real;
extern GPROC genie_gammainv_real;
extern GPROC genie_gammastar_real;
extern GPROC genie_gegenpoly_1_real;
extern GPROC genie_gegenpoly_2_real;
extern GPROC genie_gegenpoly_3_real;
extern GPROC genie_gegenpoly_n_real;
extern GPROC genie_hermite_func_real;
extern GPROC genie_hypot_real;
extern GPROC genie_hzeta_real;
extern GPROC genie_laguerre_1_real;
extern GPROC genie_laguerre_2_real;
extern GPROC genie_laguerre_3_real;
extern GPROC genie_laguerre_n_real;
extern GPROC genie_lambert_w0_real;
extern GPROC genie_lambert_wm1_real;
extern GPROC genie_legendre_h3d_0_real;
extern GPROC genie_legendre_h3d_1_real;
extern GPROC genie_legendre_H3d_real;
extern GPROC genie_legendre_p1_real;
extern GPROC genie_legendre_p2_real;
extern GPROC genie_legendre_p3_real;
extern GPROC genie_legendre_pl_real;
extern GPROC genie_legendre_q0_real;
extern GPROC genie_legendre_q1_real;
extern GPROC genie_legendre_ql_real;
extern GPROC genie_lncosh_real;
extern GPROC genie_lndoublefact_real;
extern GPROC genie_lnfact_real;
extern GPROC genie_lnpoch_real;
extern GPROC genie_lnsinh_real;
extern GPROC genie_log_1plusx_mx_real;
extern GPROC genie_log_1plusx_real;
extern GPROC genie_log_abs_real;
extern GPROC genie_poch_real;
extern GPROC genie_pochrel_real;
extern GPROC genie_psi_1_int_real;
extern GPROC genie_psi_1piy_real;
extern GPROC genie_psi_1_real;
extern GPROC genie_psi_int_real;
extern GPROC genie_psi_n_real;
extern GPROC genie_psi_real;
extern GPROC genie_shi_real;
extern GPROC genie_sinc_real;
extern GPROC genie_si_real;
extern GPROC genie_synchrotron_1_real;
extern GPROC genie_synchrotron_2_real;
extern GPROC genie_taylorcoeff_real;
extern GPROC genie_transport_2_real;
extern GPROC genie_transport_3_real;
extern GPROC genie_transport_4_real;
extern GPROC genie_transport_5_real;
extern GPROC genie_zeta_int_real;
extern GPROC genie_zetam1_int_real;
extern GPROC genie_zetam1_real;
extern GPROC genie_zeta_real;

extern GPROC genie_complex_scale_matrix_complex;
extern GPROC genie_complex_scale_vector_complex;
extern GPROC genie_fft_backward;
extern GPROC genie_fft_complex_backward;
extern GPROC genie_fft_complex_forward;
extern GPROC genie_fft_complex_inverse;
extern GPROC genie_fft_forward;
extern GPROC genie_fft_inverse;
extern GPROC genie_laplace;
extern GPROC genie_matrix_add;
extern GPROC genie_matrix_ch;
extern GPROC genie_matrix_ch_solve;
extern GPROC genie_matrix_complex_add;
extern GPROC genie_matrix_complex_det;
extern GPROC genie_matrix_complex_div_complex;
extern GPROC genie_matrix_complex_div_complex_ab;
extern GPROC genie_matrix_complex_echo;
extern GPROC genie_matrix_complex_eq;
extern GPROC genie_matrix_complex_inv;
extern GPROC genie_matrix_complex_lu;
extern GPROC genie_matrix_complex_lu_det;
extern GPROC genie_matrix_complex_lu_inv;
extern GPROC genie_matrix_complex_lu_solve;
extern GPROC genie_matrix_complex_minus;
extern GPROC genie_matrix_complex_minusab;
extern GPROC genie_matrix_complex_ne;
extern GPROC genie_matrix_complex_plusab;
extern GPROC genie_matrix_complex_scale_complex;
extern GPROC genie_matrix_complex_scale_complex_ab;
extern GPROC genie_matrix_complex_sub;
extern GPROC genie_matrix_complex_times_matrix;
extern GPROC genie_matrix_complex_times_vector;
extern GPROC genie_matrix_complex_trace;
extern GPROC genie_matrix_complex_transpose;
extern GPROC genie_matrix_det;
extern GPROC genie_matrix_div_real;
extern GPROC genie_matrix_div_real_ab;
extern GPROC genie_matrix_echo;
extern GPROC genie_matrix_eq;
extern GPROC genie_matrix_inv;
extern GPROC genie_matrix_lu;
extern GPROC genie_matrix_lu_det;
extern GPROC genie_matrix_lu_inv;
extern GPROC genie_matrix_lu_solve;
extern GPROC genie_matrix_minus;
extern GPROC genie_matrix_minusab;
extern GPROC genie_matrix_ne;
extern GPROC genie_matrix_plusab;
extern GPROC genie_matrix_qr;
extern GPROC genie_matrix_qr_ls_solve;
extern GPROC genie_matrix_qr_solve;
extern GPROC genie_matrix_scale_real;
extern GPROC genie_matrix_scale_real_ab;
extern GPROC genie_matrix_sub;
extern GPROC genie_matrix_svd;
extern GPROC genie_matrix_svd_solve;
extern GPROC genie_matrix_times_matrix;
extern GPROC genie_matrix_times_vector;
extern GPROC genie_matrix_trace;
extern GPROC genie_matrix_transpose;
extern GPROC genie_prime_factors;
extern GPROC genie_real_scale_matrix;
extern GPROC genie_real_scale_vector;
extern GPROC genie_vector_add;
extern GPROC genie_vector_complex_add;
extern GPROC genie_vector_complex_div_complex;
extern GPROC genie_vector_complex_div_complex_ab;
extern GPROC genie_vector_complex_dot;
extern GPROC genie_vector_complex_dyad;
extern GPROC genie_vector_complex_echo;
extern GPROC genie_vector_complex_eq;
extern GPROC genie_vector_complex_minus;
extern GPROC genie_vector_complex_minusab;
extern GPROC genie_vector_complex_ne;
extern GPROC genie_vector_complex_norm;
extern GPROC genie_vector_complex_plusab;
extern GPROC genie_vector_complex_scale_complex;
extern GPROC genie_vector_complex_scale_complex_ab;
extern GPROC genie_vector_complex_sub;
extern GPROC genie_vector_complex_times_matrix;
extern GPROC genie_vector_div_real;
extern GPROC genie_vector_div_real_ab;
extern GPROC genie_vector_dot;
extern GPROC genie_vector_dyad;
extern GPROC genie_vector_echo;
extern GPROC genie_vector_eq;
extern GPROC genie_vector_minus;
extern GPROC genie_vector_minusab;
extern GPROC genie_vector_ne;
extern GPROC genie_vector_norm;
extern GPROC genie_vector_plusab;
extern GPROC genie_vector_scale_real;
extern GPROC genie_vector_scale_real_ab;
extern GPROC genie_vector_sub;
extern GPROC genie_vector_times_matrix;
extern GPROC genie_beta_inc_real;
extern GPROC genie_gamma_inc_real;
extern GPROC genie_poch_real;
extern GPROC genie_digamma_real;

#endif

#endif
