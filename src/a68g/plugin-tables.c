//! @file compiler-tables.c
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
#include "a68g-genie.h"
#include "a68g-listing.h"
#include "a68g-mp.h"
#include "a68g-optimiser.h"
#include "a68g-compiler.h"
#include "a68g-parser.h"
#include "a68g-transput.h"

TRANSLATION *monadics, *dyadics, *functions;

TRANSLATION monadics_nocheck[] = {
  {genie_minus_int, "-"},
  {genie_minus_real, "-"},
  {genie_abs_int, "labs"},
  {genie_abs_real, "fabs"},
  {genie_sign_int, "SIGN"},
  {genie_sign_real, "SIGN"},
  {genie_entier_real, "a68_entier"},
  {genie_round_real, "a68_round"},
  {genie_not_bool, "!"},
  {genie_abs_bool, "(int) "},
  {genie_abs_bits, "(INT_T) "},
  {genie_bin_int, "(UNSIGNED_T) "},
  {genie_not_bits, "~"},
  {genie_abs_char, "TO_UCHAR"},
  {genie_repr_char, ""},
  {genie_re_complex, "a68_re_complex"},
  {genie_im_complex, "a68_im_complex"},
  {genie_minus_complex, "a68_minus_complex"},
  {genie_abs_complex, "a68_abs_complex"},
  {genie_arg_complex, "a68_arg_complex"},
  {genie_conj_complex, "a68_conj_complex"},
  {genie_idle, ""},
  {NO_GPROC, NO_TEXT}
};

TRANSLATION monadics_check[] = {
  {genie_minus_int, "-"},
  {genie_minus_real, "-"},
  {genie_abs_int, "labs"},
  {genie_abs_real, "fabs"},
  {genie_sign_int, "SIGN"},
  {genie_sign_real, "SIGN"},
  {genie_not_bool, "!"},
  {genie_abs_bool, "(int) "},
  {genie_abs_bits, "(INT_T) "},
  {genie_bin_int, "(UNSIGNED_T) "},
  {genie_not_bits, "~"},
  {genie_abs_char, "TO_UCHAR"},
  {genie_repr_char, ""},
  {genie_re_complex, "a68_re_complex"},
  {genie_im_complex, "a68_im_complex"},
  {genie_minus_complex, "a68_minus_complex"},
  {genie_abs_complex, "a68_abs_complex"},
  {genie_arg_complex, "a68_arg_complex"},
  {genie_conj_complex, "a68_conj_complex"},
  {genie_idle, ""},
  {NO_GPROC, NO_TEXT}
};

TRANSLATION dyadics_nocheck[] = {
  {genie_add_int, "+"},
  {genie_sub_int, "-"},
  {genie_mul_int, "*"},
  {genie_over_int, "/"},
  {genie_mod_int, "a68_mod_int"},
  {genie_div_int, "a68_div_int"},
  {genie_eq_int, "=="},
  {genie_ne_int, "!="},
  {genie_lt_int, "<"},
  {genie_gt_int, ">"},
  {genie_le_int, "<="},
  {genie_ge_int, ">="},
  {genie_plusab_int, "a68_plusab_int"},
  {genie_minusab_int, "a68_minusab_int"},
  {genie_timesab_int, "a68_timesab_int"},
  {genie_overab_int, "a68_overab_int"},
  {genie_add_real, "+"},
  {genie_sub_real, "-"},
  {genie_mul_real, "*"},
  {genie_div_real, "/"},
  {genie_pow_real, "a68_x_up_y"},
  {genie_pow_real_int, "a68_x_up_n"},
  {genie_eq_real, "=="},
  {genie_ne_real, "!="},
  {genie_lt_real, "<"},
  {genie_gt_real, ">"},
  {genie_le_real, "<="},
  {genie_ge_real, ">="},
  {genie_plusab_real, "a68_plusab_real"},
  {genie_minusab_real, "a68_minusab_real"},
  {genie_timesab_real, "a68_timesab_real"},
  {genie_divab_real, "a68_divab_real"},
  {genie_eq_char, "=="},
  {genie_ne_char, "!="},
  {genie_lt_char, "<"},
  {genie_gt_char, ">"},
  {genie_le_char, "<="},
  {genie_ge_char, ">="},
  {genie_eq_bool, "=="},
  {genie_ne_bool, "!="},
  {genie_and_bool, "&&"},
  {genie_or_bool, "||"},
  {genie_and_bits, "&"},
  {genie_or_bits, "|"},
  {genie_eq_bits, "=="},
  {genie_ne_bits, "!="},
  {genie_shl_bits, "<<"},
  {genie_shr_bits, ">>"},
  {genie_i_complex, "a68_i_complex"},
  {genie_i_int_complex, "a68_i_complex"},
  {genie_abs_complex, "a68_abs_complex"},
  {genie_arg_complex, "a68_arg_complex"},
  {genie_add_complex, "a68_add_complex"},
  {genie_sub_complex, "a68_sub_complex"},
  {genie_mul_complex, "a68_mul_complex"},
  {genie_div_complex, "a68_div_complex"},
  {genie_eq_complex, "a68_eq_complex"},
  {genie_ne_complex, "a68_ne_complex"},
  {NO_GPROC, NO_TEXT}
};

TRANSLATION dyadics_check[] = {
  {genie_add_int, "a68_add_int"},
  {genie_sub_int, "a68_sub_int"},
  {genie_mul_int, "a68_mul_int"},
  {genie_over_int, "a68_over_int"},
  {genie_mod_int, "a68_mod_int"},
  {genie_div_int, "a68_div_int"},
  {genie_add_real, "+"},
  {genie_sub_real, "-"},
  {genie_mul_real, "*"},
  {genie_div_real, "/"},
  {genie_pow_real, "a68_x_up_y"},
  {genie_pow_real_int, "a68_x_up_n"},
  {genie_eq_int, "=="},
  {genie_ne_int, "!="},
  {genie_lt_int, "<"},
  {genie_gt_int, ">"},
  {genie_le_int, "<="},
  {genie_ge_int, ">="},
  {genie_eq_real, "=="},
  {genie_ne_real, "!="},
  {genie_lt_real, "<"},
  {genie_gt_real, ">"},
  {genie_le_real, "<="},
  {genie_ge_real, ">="},
  {genie_eq_char, "=="},
  {genie_ne_char, "!="},
  {genie_lt_char, "<"},
  {genie_gt_char, ">"},
  {genie_le_char, "<="},
  {genie_ge_char, ">="},
  {genie_eq_bool, "=="},
  {genie_ne_bool, "!="},
  {genie_and_bool, "&&"},
  {genie_or_bool, "||"},
  {genie_and_bits, "&"},
  {genie_or_bits, "|"},
  {genie_eq_bits, "=="},
  {genie_ne_bits, "!="},
  {genie_i_complex, "a68_i_complex"},
  {genie_i_int_complex, "a68_i_complex"},
  {genie_abs_complex, "a68_abs_complex"},
  {genie_arg_complex, "a68_arg_complex"},
  {genie_add_complex, "a68_add_complex"},
  {genie_sub_complex, "a68_sub_complex"},
  {genie_mul_complex, "a68_mul_complex"},
  {genie_div_complex, "a68_div_complex"},
  {genie_eq_complex, "a68_eq_complex"},
  {genie_ne_complex, "a68_ne_complex"},
  {NO_GPROC, NO_TEXT}
};

TRANSLATION functions_nocheck[] = {
  {genie_sqrt_real, "sqrt"},
  {genie_curt_real, "cbrt"},
  {genie_exp_real, "a68_exp"},
  {genie_ln_real, "log"},
  {genie_log_real, "log10"},
  {genie_sin_real, "sin"},
  {genie_cos_real, "cos"},
  {genie_tan_real, "tan"},
  {genie_asin_real, "asin"},
  {genie_acos_real, "acos"},
  {genie_atan_real, "atan"},
  {genie_sinh_real, "sinh"},
  {genie_cosh_real, "cosh"},
  {genie_tanh_real, "tanh"},
  {genie_erfc_real, "erfc"},
  {genie_erf_real, "erf"},
  {genie_gamma_real, "tgamma"},
  {genie_ln_gamma_real, "lgamma"},
  {genie_sindg_real, "a68_sindg"},
  {genie_cosdg_real, "a68_cosdg"},
  {genie_tandg_real, "a68_tandg"},
  {genie_asindg_real, "a68_asindg"},
  {genie_acosdg_real, "a68_acosdg"},
  {genie_atandg_real, "a68_atandg"},
  {genie_sqrt_complex, "a68_sqrt_complex"},
  {genie_exp_complex, "a68_exp_complex"},
  {genie_ln_complex, "a68_ln_complex"},
  {genie_sin_complex, "a68_sin_complex"},
  {genie_cos_complex, "a68_cos_complex"},
  {genie_tan_complex, "a68_tan_complex"},
  {genie_asin_complex, "a68_asin_complex"},
  {genie_acos_complex, "a68_acos_complex"},
  {genie_atan_complex, "a68_atan_complex"},
  {genie_sinh_complex, "a68_sinh_complex"},
  {genie_cosh_complex, "a68_cosh_complex"},
  {genie_tanh_complex, "a68_tanh_complex"},
  {genie_asinh_complex, "a68_asinh_complex"},
  {genie_acosh_complex, "a68_acosh_complex"},
  {genie_atanh_complex, "a68_atanh_complex"},
  {genie_asinh_real, "a68_asinh"},
  {genie_acosh_real, "a68_acosh"},
  {genie_atanh_real, "a68_atanh"},
  {genie_inverfc_real, "a68_inverfc"},
  {genie_inverf_real, "a68_inverf"},
  {NO_GPROC, NO_TEXT}
};

TRANSLATION functions_check[] = {
  {genie_sqrt_real, "sqrt"},
  {genie_curt_real, "cbrt"},
  {genie_exp_real, "a68_exp"},
  {genie_ln_real, "log"},
  {genie_log_real, "log10"},
  {genie_sin_real, "sin"},
  {genie_cos_real, "cos"},
  {genie_tan_real, "tan"},
  {genie_asin_real, "asin"},
  {genie_acos_real, "acos"},
  {genie_atan_real, "atan"},
  {genie_sinh_real, "sinh"},
  {genie_cosh_real, "cosh"},
  {genie_tanh_real, "tanh"},
  {genie_erfc_real, "erfc"},
  {genie_erf_real, "erf"},
  {genie_gamma_real, "tgamma"},
  {genie_ln_gamma_real, "lgamma"},
  {genie_sindg_real, "a68_sindg"},
  {genie_cosdg_real, "a68_cosdg"},
  {genie_tandg_real, "a68_tandg"},
  {genie_asindg_real, "a68_asindg"},
  {genie_acosdg_real, "a68_acosdg"},
  {genie_atandg_real, "a68_atandg"},
  {genie_asinh_real, "a68_asinh"},
  {genie_acosh_real, "a68_acosh"},
  {genie_atanh_real, "a68_atanh"},
  {genie_inverfc_real, "a68_inverfc"},
  {genie_inverf_real, "a68_inverf"},
  {NO_GPROC, NO_TEXT}
};

TRANSLATION constants[] = {
  {genie_int_lengths, "3"},
  {genie_int_shorths, "1"},
  {genie_real_lengths, "3"},
  {genie_real_shorths, "1"},
  {genie_complex_lengths, "3"},
  {genie_complex_shorths, "1"},
#if (A68_LEVEL >= 3)
  {genie_bits_lengths, "2"},
#else
  {genie_bits_lengths, "3"},
#endif
  {genie_bits_shorths, "1"},
  {genie_bytes_lengths, "2"},
  {genie_bytes_shorths, "1"},
  {genie_int_width, "INT_WIDTH"},
  {genie_long_int_width, "LONG_INT_WIDTH"},
  {genie_long_mp_int_width, "LONG_LONG_INT_WIDTH"},
  {genie_real_width, "REAL_WIDTH"},
  {genie_long_real_width, "LONG_REAL_WIDTH"},
  {genie_long_mp_real_width, "LONG_LONG_REAL_WIDTH"},
  {genie_exp_width, "EXP_WIDTH"},
  {genie_long_exp_width, "LONG_EXP_WIDTH"},
  {genie_long_mp_exp_width, "LONG_LONG_EXP_WIDTH"},
  {genie_bits_width, "BITS_WIDTH"},
  {genie_bytes_width, "BYTES_WIDTH"},
  {genie_long_bytes_width, "LONG_BYTES_WIDTH"},
  {genie_max_abs_char, "UCHAR_MAX"},
  {genie_max_int, "A68_MAX_INT"},
  {genie_max_real, "REAL_MAX"},
  {genie_min_real, "REAL_MIN"},
  {genie_null_char, "NULL_CHAR"},
  {genie_small_real, "REAL_EPSILON"},
  {genie_pi, "A68_PI"},
  {genie_cgs_acre, "GSL_CONST_CGSM_ACRE"},
  {genie_cgs_angstrom, "GSL_CONST_CGSM_ANGSTROM"},
  {genie_cgs_astronomical_unit, "GSL_CONST_CGSM_ASTRONOMICAL_UNIT"},
  {genie_cgs_bar, "GSL_CONST_CGSM_BAR"},
  {genie_cgs_barn, "GSL_CONST_CGSM_BARN"},
  {genie_cgs_bohr_magneton, "GSL_CONST_CGSM_BOHR_MAGNETON"},
  {genie_cgs_bohr_radius, "GSL_CONST_CGSM_BOHR_RADIUS"},
  {genie_cgs_boltzmann, "GSL_CONST_CGSM_BOLTZMANN"},
  {genie_cgs_btu, "GSL_CONST_CGSM_BTU"},
  {genie_cgs_calorie, "GSL_CONST_CGSM_CALORIE"},
  {genie_cgs_canadian_gallon, "GSL_CONST_CGSM_CANADIAN_GALLON"},
  {genie_cgs_carat, "GSL_CONST_CGSM_CARAT"},
  {genie_cgs_cup, "GSL_CONST_CGSM_CUP"},
  {genie_cgs_curie, "GSL_CONST_CGSM_CURIE"},
  {genie_cgs_day, "GSL_CONST_CGSM_DAY"},
  {genie_cgs_dyne, "GSL_CONST_CGSM_DYNE"},
  {genie_cgs_electron_charge, "GSL_CONST_CGSM_ELECTRON_CHARGE"},
  {genie_cgs_electron_magnetic_moment, "GSL_CONST_CGSM_ELECTRON_MAGNETIC_MOMENT"},
  {genie_cgs_electron_volt, "GSL_CONST_CGSM_ELECTRON_VOLT"},
  {genie_cgs_erg, "GSL_CONST_CGSM_ERG"},
  {genie_cgs_faraday, "GSL_CONST_CGSM_FARADAY"},
  {genie_cgs_fathom, "GSL_CONST_CGSM_FATHOM"},
  {genie_cgs_fluid_ounce, "GSL_CONST_CGSM_FLUID_OUNCE"},
  {genie_cgs_foot, "GSL_CONST_CGSM_FOOT"},
  {genie_cgs_footcandle, "GSL_CONST_CGSM_FOOTCANDLE"},
  {genie_cgs_footlambert, "GSL_CONST_CGSM_FOOTLAMBERT"},
  {genie_cgs_gauss, "GSL_CONST_CGSM_GAUSS"},
  {genie_cgs_gram_force, "GSL_CONST_CGSM_GRAM_FORCE"},
  {genie_cgs_grav_accel, "GSL_CONST_CGSM_GRAV_ACCEL"},
  {genie_cgs_gravitational_constant, "GSL_CONST_CGSM_GRAVITATIONAL_CONSTANT"},
  {genie_cgs_hectare, "GSL_CONST_CGSM_HECTARE"},
  {genie_cgs_horsepower, "GSL_CONST_CGSM_HORSEPOWER"},
  {genie_cgs_hour, "GSL_CONST_CGSM_HOUR"},
  {genie_cgs_inch, "GSL_CONST_CGSM_INCH"},
  {genie_cgs_inch_of_mercury, "GSL_CONST_CGSM_INCH_OF_MERCURY"},
  {genie_cgs_inch_of_water, "GSL_CONST_CGSM_INCH_OF_WATER"},
  {genie_cgs_joule, "GSL_CONST_CGSM_JOULE"},
  {genie_cgs_kilometers_per_hour, "GSL_CONST_CGSM_KILOMETERS_PER_HOUR"},
  {genie_cgs_kilopound_force, "GSL_CONST_CGSM_KILOPOUND_FORCE"},
  {genie_cgs_knot, "GSL_CONST_CGSM_KNOT"},
  {genie_cgs_lambert, "GSL_CONST_CGSM_LAMBERT"},
  {genie_cgs_light_year, "GSL_CONST_CGSM_LIGHT_YEAR"},
  {genie_cgs_liter, "GSL_CONST_CGSM_LITER"},
  {genie_cgs_lumen, "GSL_CONST_CGSM_LUMEN"},
  {genie_cgs_lux, "GSL_CONST_CGSM_LUX"},
  {genie_cgs_mass_electron, "GSL_CONST_CGSM_MASS_ELECTRON"},
  {genie_cgs_mass_muon, "GSL_CONST_CGSM_MASS_MUON"},
  {genie_cgs_mass_neutron, "GSL_CONST_CGSM_MASS_NEUTRON"},
  {genie_cgs_mass_proton, "GSL_CONST_CGSM_MASS_PROTON"},
  {genie_cgs_meter_of_mercury, "GSL_CONST_CGSM_METER_OF_MERCURY"},
  {genie_cgs_metric_ton, "GSL_CONST_CGSM_METRIC_TON"},
  {genie_cgs_micron, "GSL_CONST_CGSM_MICRON"},
  {genie_cgs_mil, "GSL_CONST_CGSM_MIL"},
  {genie_cgs_mile, "GSL_CONST_CGSM_MILE"},
  {genie_cgs_miles_per_hour, "GSL_CONST_CGSM_MILES_PER_HOUR"},
  {genie_cgs_minute, "GSL_CONST_CGSM_MINUTE"},
  {genie_cgs_molar_gas, "GSL_CONST_CGSM_MOLAR_GAS"},
  {genie_cgs_nautical_mile, "GSL_CONST_CGSM_NAUTICAL_MILE"},
  {genie_cgs_newton, "GSL_CONST_CGSM_NEWTON"},
  {genie_cgs_nuclear_magneton, "GSL_CONST_CGSM_NUCLEAR_MAGNETON"},
  {genie_cgs_ounce_mass, "GSL_CONST_CGSM_OUNCE_MASS"},
  {genie_cgs_parsec, "GSL_CONST_CGSM_PARSEC"},
  {genie_cgs_phot, "GSL_CONST_CGSM_PHOT"},
  {genie_cgs_pint, "GSL_CONST_CGSM_PINT"},
  {genie_cgs_planck_constant_h, "6.6260693e-27"},
  {genie_cgs_planck_constant_hbar, "1.0545717e-27"},
  {genie_cgs_point, "GSL_CONST_CGSM_POINT"},
  {genie_cgs_poise, "GSL_CONST_CGSM_POISE"},
  {genie_cgs_pound_force, "GSL_CONST_CGSM_POUND_FORCE"},
  {genie_cgs_pound_mass, "GSL_CONST_CGSM_POUND_MASS"},
  {genie_cgs_poundal, "GSL_CONST_CGSM_POUNDAL"},
  {genie_cgs_proton_magnetic_moment, "GSL_CONST_CGSM_PROTON_MAGNETIC_MOMENT"},
  {genie_cgs_psi, "GSL_CONST_CGSM_PSI"},
  {genie_cgs_quart, "GSL_CONST_CGSM_QUART"},
  {genie_cgs_rad, "GSL_CONST_CGSM_RAD"},
  {genie_cgs_roentgen, "GSL_CONST_CGSM_ROENTGEN"},
  {genie_cgs_rydberg, "GSL_CONST_CGSM_RYDBERG"},
  {genie_cgs_solar_mass, "GSL_CONST_CGSM_SOLAR_MASS"},
  {genie_cgs_speed_of_light, "GSL_CONST_CGSM_SPEED_OF_LIGHT"},
  {genie_cgs_standard_gas_volume, "GSL_CONST_CGSM_STANDARD_GAS_VOLUME"},
  {genie_cgs_std_atmosphere, "GSL_CONST_CGSM_STD_ATMOSPHERE"},
  {genie_cgs_stilb, "GSL_CONST_CGSM_STILB"},
  {genie_cgs_stokes, "GSL_CONST_CGSM_STOKES"},
  {genie_cgs_tablespoon, "GSL_CONST_CGSM_TABLESPOON"},
  {genie_cgs_teaspoon, "GSL_CONST_CGSM_TEASPOON"},
  {genie_cgs_texpoint, "GSL_CONST_CGSM_TEXPOINT"},
  {genie_cgs_therm, "GSL_CONST_CGSM_THERM"},
  {genie_cgs_ton, "GSL_CONST_CGSM_TON"},
  {genie_cgs_torr, "GSL_CONST_CGSM_TORR"},
  {genie_cgs_troy_ounce, "GSL_CONST_CGSM_TROY_OUNCE"},
  {genie_cgs_uk_gallon, "GSL_CONST_CGSM_UK_GALLON"},
  {genie_cgs_uk_ton, "GSL_CONST_CGSM_UK_TON"},
  {genie_cgs_unified_atomic_mass, "GSL_CONST_CGSM_UNIFIED_ATOMIC_MASS"},
  {genie_cgs_us_gallon, "GSL_CONST_CGSM_US_GALLON"},
  {genie_cgs_week, "GSL_CONST_CGSM_WEEK"},
  {genie_cgs_yard, "GSL_CONST_CGSM_YARD"},
  {genie_mks_acre, "GSL_CONST_MKS_ACRE"},
  {genie_mks_angstrom, "GSL_CONST_MKS_ANGSTROM"},
  {genie_mks_astronomical_unit, "GSL_CONST_MKS_ASTRONOMICAL_UNIT"},
  {genie_mks_bar, "GSL_CONST_MKS_BAR"},
  {genie_mks_barn, "GSL_CONST_MKS_BARN"},
  {genie_mks_bohr_magneton, "GSL_CONST_MKS_BOHR_MAGNETON"},
  {genie_mks_bohr_radius, "GSL_CONST_MKS_BOHR_RADIUS"},
  {genie_mks_boltzmann, "GSL_CONST_MKS_BOLTZMANN"},
  {genie_mks_btu, "GSL_CONST_MKS_BTU"},
  {genie_mks_calorie, "GSL_CONST_MKS_CALORIE"},
  {genie_mks_canadian_gallon, "GSL_CONST_MKS_CANADIAN_GALLON"},
  {genie_mks_carat, "GSL_CONST_MKS_CARAT"},
  {genie_mks_cup, "GSL_CONST_MKS_CUP"},
  {genie_mks_curie, "GSL_CONST_MKS_CURIE"},
  {genie_mks_day, "GSL_CONST_MKS_DAY"},
  {genie_mks_dyne, "GSL_CONST_MKS_DYNE"},
  {genie_mks_electron_charge, "GSL_CONST_MKS_ELECTRON_CHARGE"},
  {genie_mks_electron_magnetic_moment, "GSL_CONST_MKS_ELECTRON_MAGNETIC_MOMENT"},
  {genie_mks_electron_volt, "GSL_CONST_MKS_ELECTRON_VOLT"},
  {genie_mks_erg, "GSL_CONST_MKS_ERG"},
  {genie_mks_faraday, "GSL_CONST_MKS_FARADAY"},
  {genie_mks_fathom, "GSL_CONST_MKS_FATHOM"},
  {genie_mks_fluid_ounce, "GSL_CONST_MKS_FLUID_OUNCE"},
  {genie_mks_foot, "GSL_CONST_MKS_FOOT"},
  {genie_mks_footcandle, "GSL_CONST_MKS_FOOTCANDLE"},
  {genie_mks_footlambert, "GSL_CONST_MKS_FOOTLAMBERT"},
  {genie_mks_gauss, "GSL_CONST_MKS_GAUSS"},
  {genie_mks_gram_force, "GSL_CONST_MKS_GRAM_FORCE"},
  {genie_mks_grav_accel, "GSL_CONST_MKS_GRAV_ACCEL"},
  {genie_mks_gravitational_constant, "GSL_CONST_MKS_GRAVITATIONAL_CONSTANT"},
  {genie_mks_hectare, "GSL_CONST_MKS_HECTARE"},
  {genie_mks_horsepower, "GSL_CONST_MKS_HORSEPOWER"},
  {genie_mks_hour, "GSL_CONST_MKS_HOUR"},
  {genie_mks_inch, "GSL_CONST_MKS_INCH"},
  {genie_mks_inch_of_mercury, "GSL_CONST_MKS_INCH_OF_MERCURY"},
  {genie_mks_inch_of_water, "GSL_CONST_MKS_INCH_OF_WATER"},
  {genie_mks_joule, "GSL_CONST_MKS_JOULE"},
  {genie_mks_kilometers_per_hour, "GSL_CONST_MKS_KILOMETERS_PER_HOUR"},
  {genie_mks_kilopound_force, "GSL_CONST_MKS_KILOPOUND_FORCE"},
  {genie_mks_knot, "GSL_CONST_MKS_KNOT"},
  {genie_mks_lambert, "GSL_CONST_MKS_LAMBERT"},
  {genie_mks_light_year, "GSL_CONST_MKS_LIGHT_YEAR"},
  {genie_mks_liter, "GSL_CONST_MKS_LITER"},
  {genie_mks_lumen, "GSL_CONST_MKS_LUMEN"},
  {genie_mks_lux, "GSL_CONST_MKS_LUX"},
  {genie_mks_mass_electron, "GSL_CONST_MKS_MASS_ELECTRON"},
  {genie_mks_mass_muon, "GSL_CONST_MKS_MASS_MUON"},
  {genie_mks_mass_neutron, "GSL_CONST_MKS_MASS_NEUTRON"},
  {genie_mks_mass_proton, "GSL_CONST_MKS_MASS_PROTON"},
  {genie_mks_meter_of_mercury, "GSL_CONST_MKS_METER_OF_MERCURY"},
  {genie_mks_metric_ton, "GSL_CONST_MKS_METRIC_TON"},
  {genie_mks_micron, "GSL_CONST_MKS_MICRON"},
  {genie_mks_mil, "GSL_CONST_MKS_MIL"},
  {genie_mks_mile, "GSL_CONST_MKS_MILE"},
  {genie_mks_miles_per_hour, "GSL_CONST_MKS_MILES_PER_HOUR"},
  {genie_mks_minute, "GSL_CONST_MKS_MINUTE"},
  {genie_mks_molar_gas, "GSL_CONST_MKS_MOLAR_GAS"},
  {genie_mks_nautical_mile, "GSL_CONST_MKS_NAUTICAL_MILE"},
  {genie_mks_newton, "GSL_CONST_MKS_NEWTON"},
  {genie_mks_nuclear_magneton, "GSL_CONST_MKS_NUCLEAR_MAGNETON"},
  {genie_mks_ounce_mass, "GSL_CONST_MKS_OUNCE_MASS"},
  {genie_mks_parsec, "GSL_CONST_MKS_PARSEC"},
  {genie_mks_phot, "GSL_CONST_MKS_PHOT"},
  {genie_mks_pint, "GSL_CONST_MKS_PINT"},
  {genie_mks_planck_constant_h, "6.6260693e-34"},
  {genie_mks_planck_constant_hbar, "1.0545717e-34"},
  {genie_mks_point, "GSL_CONST_MKS_POINT"},
  {genie_mks_poise, "GSL_CONST_MKS_POISE"},
  {genie_mks_pound_force, "GSL_CONST_MKS_POUND_FORCE"},
  {genie_mks_pound_mass, "GSL_CONST_MKS_POUND_MASS"},
  {genie_mks_poundal, "GSL_CONST_MKS_POUNDAL"},
  {genie_mks_proton_magnetic_moment, "GSL_CONST_MKS_PROTON_MAGNETIC_MOMENT"},
  {genie_mks_psi, "GSL_CONST_MKS_PSI"},
  {genie_mks_quart, "GSL_CONST_MKS_QUART"},
  {genie_mks_rad, "GSL_CONST_MKS_RAD"},
  {genie_mks_roentgen, "GSL_CONST_MKS_ROENTGEN"},
  {genie_mks_rydberg, "GSL_CONST_MKS_RYDBERG"},
  {genie_mks_solar_mass, "GSL_CONST_MKS_SOLAR_MASS"},
  {genie_mks_speed_of_light, "GSL_CONST_MKS_SPEED_OF_LIGHT"},
  {genie_mks_standard_gas_volume, "GSL_CONST_MKS_STANDARD_GAS_VOLUME"},
  {genie_mks_std_atmosphere, "GSL_CONST_MKS_STD_ATMOSPHERE"},
  {genie_mks_stilb, "GSL_CONST_MKS_STILB"},
  {genie_mks_stokes, "GSL_CONST_MKS_STOKES"},
  {genie_mks_tablespoon, "GSL_CONST_MKS_TABLESPOON"},
  {genie_mks_teaspoon, "GSL_CONST_MKS_TEASPOON"},
  {genie_mks_texpoint, "GSL_CONST_MKS_TEXPOINT"},
  {genie_mks_therm, "GSL_CONST_MKS_THERM"},
  {genie_mks_ton, "GSL_CONST_MKS_TON"},
  {genie_mks_torr, "GSL_CONST_MKS_TORR"},
  {genie_mks_troy_ounce, "GSL_CONST_MKS_TROY_OUNCE"},
  {genie_mks_uk_gallon, "GSL_CONST_MKS_UK_GALLON"},
  {genie_mks_uk_ton, "GSL_CONST_MKS_UK_TON"},
  {genie_mks_unified_atomic_mass, "GSL_CONST_MKS_UNIFIED_ATOMIC_MASS"},
  {genie_mks_us_gallon, "GSL_CONST_MKS_US_GALLON"},
  {genie_mks_vacuum_permeability, "GSL_CONST_MKS_VACUUM_PERMEABILITY"},
  {genie_mks_vacuum_permittivity, "GSL_CONST_MKS_VACUUM_PERMITTIVITY"},
  {genie_mks_week, "GSL_CONST_MKS_WEEK"},
  {genie_mks_yard, "GSL_CONST_MKS_YARD"},
  {genie_num_atto, "GSL_CONST_NUM_ATTO"},
  {genie_num_avogadro, "GSL_CONST_NUM_AVOGADRO"},
  {genie_num_exa, "GSL_CONST_NUM_EXA"},
  {genie_num_femto, "GSL_CONST_NUM_FEMTO"},
  {genie_num_fine_structure, "GSL_CONST_NUM_FINE_STRUCTURE"},
  {genie_num_giga, "GSL_CONST_NUM_GIGA"},
  {genie_num_kilo, "GSL_CONST_NUM_KILO"},
  {genie_num_mega, "GSL_CONST_NUM_MEGA"},
  {genie_num_micro, "GSL_CONST_NUM_MICRO"},
  {genie_num_milli, "GSL_CONST_NUM_MILLI"},
  {genie_num_nano, "GSL_CONST_NUM_NANO"},
  {genie_num_peta, "GSL_CONST_NUM_PETA"},
  {genie_num_pico, "GSL_CONST_NUM_PICO"},
  {genie_num_tera, "GSL_CONST_NUM_TERA"},
  {genie_num_yocto, "GSL_CONST_NUM_YOCTO"},
  {genie_num_yotta, "GSL_CONST_NUM_YOTTA"},
  {genie_num_zepto, "GSL_CONST_NUM_ZEPTO"},
  {genie_num_zetta, "GSL_CONST_NUM_ZETTA"},
  {NO_GPROC, NO_TEXT}
};
