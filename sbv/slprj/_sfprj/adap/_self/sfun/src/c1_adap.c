/* Include files */

#include "blascompat32.h"
#include "adap_sfun.h"
#include "c1_adap.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "adap_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[25] = { "wn", "ksi", "gama1", "gama2",
  "P", "T", "T_last", "X", "X_last", "A_last", "A", "u", "nargin", "nargout",
  "thi", "dthi", "thi_last", "dthi_last", "Kp_last", "Kd_last", "Kthi_last", "C",
  "Kp", "Kd", "Kthi" };

/* Function Declarations */
static void initialize_c1_adap(SFc1_adapInstanceStruct *chartInstance);
static void initialize_params_c1_adap(SFc1_adapInstanceStruct *chartInstance);
static void enable_c1_adap(SFc1_adapInstanceStruct *chartInstance);
static void disable_c1_adap(SFc1_adapInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_adap(SFc1_adapInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_adap(SFc1_adapInstanceStruct
  *chartInstance);
static void set_sim_state_c1_adap(SFc1_adapInstanceStruct *chartInstance, const
  mxArray *c1_st);
static void finalize_c1_adap(SFc1_adapInstanceStruct *chartInstance);
static void sf_c1_adap(SFc1_adapInstanceStruct *chartInstance);
static void c1_chartstep_c1_adap(SFc1_adapInstanceStruct *chartInstance);
static void initSimStructsc1_adap(SFc1_adapInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance, const
  mxArray *c1_Kthi, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_c_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2]);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_d_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[4]);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[22]);
static void c1_eml_scalar_eg(SFc1_adapInstanceStruct *chartInstance);
static void c1_b_eml_scalar_eg(SFc1_adapInstanceStruct *chartInstance);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_e_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_f_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_adap, const char_T *c1_identifier);
static uint8_T c1_g_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_adapInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_adap(SFc1_adapInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_adap = 0U;
}

static void initialize_params_c1_adap(SFc1_adapInstanceStruct *chartInstance)
{
}

static void enable_c1_adap(SFc1_adapInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_adap(SFc1_adapInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_adap(SFc1_adapInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_adap(SFc1_adapInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_d_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  uint8_T c1_e_hoistedGlobal;
  uint8_T c1_e_u;
  const mxArray *c1_f_y = NULL;
  real_T *c1_C;
  real_T *c1_Kd;
  real_T *c1_Kp;
  real_T *c1_Kthi;
  c1_Kthi = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_Kd = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_Kp = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_C = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(5), FALSE);
  c1_hoistedGlobal = *c1_C;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *c1_Kd;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = *c1_Kp;
  c1_c_u = c1_c_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = *c1_Kthi;
  c1_d_u = c1_d_hoistedGlobal;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_e_hoistedGlobal = chartInstance->c1_is_active_c1_adap;
  c1_e_u = c1_e_hoistedGlobal;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_adap(SFc1_adapInstanceStruct *chartInstance, const
  mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T *c1_C;
  real_T *c1_Kd;
  real_T *c1_Kp;
  real_T *c1_Kthi;
  c1_Kthi = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_Kd = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_Kp = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_C = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_C = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
    "C");
  *c1_Kd = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 1)),
    "Kd");
  *c1_Kp = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 2)),
    "Kp");
  *c1_Kthi = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    3)), "Kthi");
  chartInstance->c1_is_active_c1_adap = c1_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 4)), "is_active_c1_adap");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_adap(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_adap(SFc1_adapInstanceStruct *chartInstance)
{
}

static void sf_c1_adap(SFc1_adapInstanceStruct *chartInstance)
{
  real_T *c1_thi;
  real_T *c1_C;
  real_T *c1_dthi;
  real_T *c1_thi_last;
  real_T *c1_dthi_last;
  real_T *c1_Kp_last;
  real_T *c1_Kd_last;
  real_T *c1_Kp;
  real_T *c1_Kd;
  real_T *c1_Kthi_last;
  real_T *c1_Kthi;
  c1_Kthi = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_Kthi_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c1_Kd = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_Kp = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_Kd_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c1_Kp_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c1_dthi_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c1_thi_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_dthi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_C = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_thi = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c1_thi, 0U);
  _SFD_DATA_RANGE_CHECK(*c1_C, 1U);
  _SFD_DATA_RANGE_CHECK(*c1_dthi, 2U);
  _SFD_DATA_RANGE_CHECK(*c1_thi_last, 3U);
  _SFD_DATA_RANGE_CHECK(*c1_dthi_last, 4U);
  _SFD_DATA_RANGE_CHECK(*c1_Kp_last, 5U);
  _SFD_DATA_RANGE_CHECK(*c1_Kd_last, 6U);
  _SFD_DATA_RANGE_CHECK(*c1_Kp, 7U);
  _SFD_DATA_RANGE_CHECK(*c1_Kd, 8U);
  _SFD_DATA_RANGE_CHECK(*c1_Kthi_last, 9U);
  _SFD_DATA_RANGE_CHECK(*c1_Kthi, 10U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_adap(chartInstance);
  sf_debug_check_for_state_inconsistency(_adapMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_adap(SFc1_adapInstanceStruct *chartInstance)
{
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_hoistedGlobal;
  real_T c1_d_hoistedGlobal;
  real_T c1_e_hoistedGlobal;
  real_T c1_f_hoistedGlobal;
  real_T c1_g_hoistedGlobal;
  real_T c1_thi;
  real_T c1_dthi;
  real_T c1_thi_last;
  real_T c1_dthi_last;
  real_T c1_Kp_last;
  real_T c1_Kd_last;
  real_T c1_Kthi_last;
  uint32_T c1_debug_family_var_map[25];
  real_T c1_wn;
  real_T c1_ksi;
  real_T c1_gama1;
  real_T c1_gama2;
  real_T c1_P[4];
  real_T c1_T[4];
  real_T c1_T_last[4];
  real_T c1_X[2];
  real_T c1_X_last[2];
  real_T c1_A_last[2];
  real_T c1_A[2];
  real_T c1_u;
  real_T c1_nargin = 7.0;
  real_T c1_nargout = 4.0;
  real_T c1_C;
  real_T c1_Kp;
  real_T c1_Kd;
  real_T c1_Kthi;
  int32_T c1_i0;
  static real_T c1_b[4] = { 35.784985714285718, 0.005, 0.005,
    0.035714285714285712 };

  int32_T c1_i1;
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  int32_T c1_i5;
  int32_T c1_i6;
  int32_T c1_i7;
  int32_T c1_i8;
  real_T c1_a[4];
  int32_T c1_i9;
  int32_T c1_i10;
  int32_T c1_i11;
  real_T c1_y[4];
  int32_T c1_i12;
  int32_T c1_i13;
  int32_T c1_i14;
  real_T c1_b_b[2];
  int32_T c1_i15;
  real_T c1_b_y[2];
  int32_T c1_i16;
  int32_T c1_i17;
  int32_T c1_i18;
  int32_T c1_i19;
  int32_T c1_i20;
  int32_T c1_i21;
  int32_T c1_i22;
  int32_T c1_i23;
  int32_T c1_i24;
  int32_T c1_i25;
  int32_T c1_i26;
  int32_T c1_i27;
  int32_T c1_i28;
  real_T c1_c_y[2];
  int32_T c1_i29;
  int32_T c1_i30;
  int32_T c1_i31;
  int32_T c1_i32;
  int32_T c1_i33;
  real_T c1_b_A;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_d_y;
  real_T c1_b_a;
  real_T c1_e_y;
  real_T c1_c_A;
  real_T c1_c_x;
  real_T c1_d_x;
  real_T c1_f_y;
  real_T c1_e_x;
  real_T c1_f_x;
  real_T c1_g_y;
  real_T c1_c_b;
  real_T c1_h_y;
  real_T c1_d_A;
  real_T c1_g_x;
  real_T c1_h_x;
  real_T c1_i_y;
  real_T c1_c_a;
  real_T c1_j_y;
  real_T c1_e_A;
  real_T c1_i_x;
  real_T c1_j_x;
  real_T c1_k_y;
  real_T c1_k_x;
  real_T c1_l_x;
  real_T c1_d_a;
  real_T c1_d_b;
  real_T c1_e_a;
  real_T c1_e_b;
  real_T c1_l_y;
  real_T c1_f_a;
  real_T c1_f_b;
  real_T c1_m_y;
  real_T *c1_b_thi;
  real_T *c1_b_dthi;
  real_T *c1_b_thi_last;
  real_T *c1_b_dthi_last;
  real_T *c1_b_Kp_last;
  real_T *c1_b_Kd_last;
  real_T *c1_b_Kthi_last;
  real_T *c1_b_C;
  real_T *c1_b_Kp;
  real_T *c1_b_Kd;
  real_T *c1_b_Kthi;
  c1_b_Kthi = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_b_Kthi_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c1_b_Kd = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_b_Kp = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_b_Kd_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c1_b_Kp_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c1_b_dthi_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c1_b_thi_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_b_dthi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_C = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_thi = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *c1_b_thi;
  c1_b_hoistedGlobal = *c1_b_dthi;
  c1_c_hoistedGlobal = *c1_b_thi_last;
  c1_d_hoistedGlobal = *c1_b_dthi_last;
  c1_e_hoistedGlobal = *c1_b_Kp_last;
  c1_f_hoistedGlobal = *c1_b_Kd_last;
  c1_g_hoistedGlobal = *c1_b_Kthi_last;
  c1_thi = c1_hoistedGlobal;
  c1_dthi = c1_b_hoistedGlobal;
  c1_thi_last = c1_c_hoistedGlobal;
  c1_dthi_last = c1_d_hoistedGlobal;
  c1_Kp_last = c1_e_hoistedGlobal;
  c1_Kd_last = c1_f_hoistedGlobal;
  c1_Kthi_last = c1_g_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 25U, 25U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c1_wn, 0U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_ksi, 1U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_gama1, 2U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_gama2, 3U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c1_P, 4U, c1_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c1_T, 5U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_T_last, 6U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_X, 7U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_X_last, 8U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_A_last, 9U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_A, 10U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_u, 11U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 12U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 13U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c1_thi, 14U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_dthi, 15U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_thi_last, 16U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_dthi_last, 17U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_Kp_last, 18U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_Kd_last, 19U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_Kthi_last, 20U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_C, 21U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Kp, 22U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Kd, 23U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Kthi, 24U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 2);
  c1_wn = 10.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 3);
  c1_ksi = 0.707;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
  c1_gama1 = -4.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 5);
  c1_gama2 = -4.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
  for (c1_i0 = 0; c1_i0 < 4; c1_i0++) {
    c1_P[c1_i0] = c1_b[c1_i0];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  c1_i1 = 0;
  for (c1_i2 = 0; c1_i2 < 2; c1_i2++) {
    c1_T[c1_i1] = 0.0;
    c1_i1 += 2;
  }

  c1_T[1] = c1_thi;
  c1_T[3] = c1_dthi;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
  c1_i3 = 0;
  for (c1_i4 = 0; c1_i4 < 2; c1_i4++) {
    c1_T_last[c1_i3] = 0.0;
    c1_i3 += 2;
  }

  c1_T_last[1] = c1_thi_last;
  c1_T_last[3] = c1_dthi_last;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
  c1_X[0] = c1_thi;
  c1_X[1] = c1_dthi;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  c1_X_last[0] = c1_thi_last;
  c1_X_last[1] = c1_dthi_last;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  c1_A_last[0] = c1_Kp_last;
  c1_A_last[1] = c1_Kd_last;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
  c1_i5 = 0;
  for (c1_i6 = 0; c1_i6 < 2; c1_i6++) {
    c1_i7 = 0;
    for (c1_i8 = 0; c1_i8 < 2; c1_i8++) {
      c1_a[c1_i8 + c1_i5] = c1_T_last[c1_i7 + c1_i6];
      c1_i7 += 2;
    }

    c1_i5 += 2;
  }

  c1_eml_scalar_eg(chartInstance);
  c1_eml_scalar_eg(chartInstance);
  for (c1_i9 = 0; c1_i9 < 2; c1_i9++) {
    c1_i10 = 0;
    for (c1_i11 = 0; c1_i11 < 2; c1_i11++) {
      c1_y[c1_i10 + c1_i9] = 0.0;
      c1_i12 = 0;
      for (c1_i13 = 0; c1_i13 < 2; c1_i13++) {
        c1_y[c1_i10 + c1_i9] += c1_a[c1_i12 + c1_i9] * c1_b[c1_i13 + c1_i10];
        c1_i12 += 2;
      }

      c1_i10 += 2;
    }
  }

  for (c1_i14 = 0; c1_i14 < 2; c1_i14++) {
    c1_b_b[c1_i14] = c1_X_last[c1_i14];
  }

  c1_b_eml_scalar_eg(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  for (c1_i15 = 0; c1_i15 < 2; c1_i15++) {
    c1_b_y[c1_i15] = 0.0;
    c1_i16 = 0;
    for (c1_i17 = 0; c1_i17 < 2; c1_i17++) {
      c1_b_y[c1_i15] += c1_y[c1_i16 + c1_i15] * c1_b_b[c1_i17];
      c1_i16 += 2;
    }
  }

  c1_i18 = 0;
  for (c1_i19 = 0; c1_i19 < 2; c1_i19++) {
    c1_i20 = 0;
    for (c1_i21 = 0; c1_i21 < 2; c1_i21++) {
      c1_a[c1_i21 + c1_i18] = c1_T[c1_i20 + c1_i19];
      c1_i20 += 2;
    }

    c1_i18 += 2;
  }

  c1_eml_scalar_eg(chartInstance);
  c1_eml_scalar_eg(chartInstance);
  for (c1_i22 = 0; c1_i22 < 2; c1_i22++) {
    c1_i23 = 0;
    for (c1_i24 = 0; c1_i24 < 2; c1_i24++) {
      c1_y[c1_i23 + c1_i22] = 0.0;
      c1_i25 = 0;
      for (c1_i26 = 0; c1_i26 < 2; c1_i26++) {
        c1_y[c1_i23 + c1_i22] += c1_a[c1_i25 + c1_i22] * c1_b[c1_i26 + c1_i23];
        c1_i25 += 2;
      }

      c1_i23 += 2;
    }
  }

  for (c1_i27 = 0; c1_i27 < 2; c1_i27++) {
    c1_b_b[c1_i27] = c1_X[c1_i27];
  }

  c1_b_eml_scalar_eg(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  for (c1_i28 = 0; c1_i28 < 2; c1_i28++) {
    c1_c_y[c1_i28] = 0.0;
    c1_i29 = 0;
    for (c1_i30 = 0; c1_i30 < 2; c1_i30++) {
      c1_c_y[c1_i28] += c1_y[c1_i29 + c1_i28] * c1_b_b[c1_i30];
      c1_i29 += 2;
    }
  }

  for (c1_i31 = 0; c1_i31 < 2; c1_i31++) {
    c1_b_y[c1_i31] += c1_c_y[c1_i31];
  }

  for (c1_i32 = 0; c1_i32 < 2; c1_i32++) {
    c1_b_y[c1_i32] *= -0.02;
  }

  for (c1_i33 = 0; c1_i33 < 2; c1_i33++) {
    c1_A[c1_i33] = c1_A_last[c1_i33] + c1_b_y[c1_i33];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
  c1_Kp = c1_A[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
  c1_Kd = c1_A[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
  c1_b_A = c1_thi;
  c1_x = c1_b_A;
  c1_b_x = c1_x;
  c1_d_y = c1_b_x / 200.0;
  c1_b_a = c1_dthi;
  c1_e_y = c1_b_a * 101.0;
  c1_c_A = c1_e_y;
  c1_c_x = c1_c_A;
  c1_d_x = c1_c_x;
  c1_f_y = c1_d_x / 2828.0;
  c1_e_x = c1_d_y + c1_f_y;
  c1_f_x = c1_e_x;
  c1_g_y = muDoubleScalarAbs(c1_f_x);
  c1_c_b = c1_g_y;
  c1_h_y = -0.04 * c1_c_b;
  c1_Kthi = c1_Kthi_last + c1_h_y;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 18);
  c1_d_A = c1_thi;
  c1_g_x = c1_d_A;
  c1_h_x = c1_g_x;
  c1_i_y = c1_h_x / 200.0;
  c1_c_a = c1_dthi;
  c1_j_y = c1_c_a * 101.0;
  c1_e_A = c1_j_y;
  c1_i_x = c1_e_A;
  c1_j_x = c1_i_x;
  c1_k_y = c1_j_x / 2828.0;
  c1_k_x = c1_i_y + c1_k_y;
  c1_l_x = c1_k_x;
  c1_l_x = muDoubleScalarSign(c1_l_x);
  c1_d_a = -c1_Kthi;
  c1_d_b = c1_l_x;
  c1_u = c1_d_a * c1_d_b;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
  c1_e_a = -c1_Kp;
  c1_e_b = c1_thi;
  c1_l_y = c1_e_a * c1_e_b;
  c1_f_a = c1_Kd;
  c1_f_b = c1_dthi;
  c1_m_y = c1_f_a * c1_f_b;
  c1_C = (c1_l_y - c1_m_y) + c1_u;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -19);
  sf_debug_symbol_scope_pop();
  *c1_b_C = c1_C;
  *c1_b_Kp = c1_Kp;
  *c1_b_Kd = c1_Kd;
  *c1_b_Kthi = c1_Kthi;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_adap(SFc1_adapInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_adapInstanceStruct *chartInstance;
  chartInstance = (SFc1_adapInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance, const
  mxArray *c1_Kthi, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Kthi), &c1_thisId);
  sf_mex_destroy(&c1_Kthi);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_Kthi;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_adapInstanceStruct *chartInstance;
  chartInstance = (SFc1_adapInstanceStruct *)chartInstanceVoid;
  c1_Kthi = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Kthi), &c1_thisId);
  sf_mex_destroy(&c1_Kthi);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i34;
  real_T c1_b_inData[2];
  int32_T c1_i35;
  real_T c1_u[2];
  const mxArray *c1_y = NULL;
  SFc1_adapInstanceStruct *chartInstance;
  chartInstance = (SFc1_adapInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i34 = 0; c1_i34 < 2; c1_i34++) {
    c1_b_inData[c1_i34] = (*(real_T (*)[2])c1_inData)[c1_i34];
  }

  for (c1_i35 = 0; c1_i35 < 2; c1_i35++) {
    c1_u[c1_i35] = c1_b_inData[c1_i35];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_c_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2])
{
  real_T c1_dv0[2];
  int32_T c1_i36;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv0, 1, 0, 0U, 1, 0U, 1, 2);
  for (c1_i36 = 0; c1_i36 < 2; c1_i36++) {
    c1_y[c1_i36] = c1_dv0[c1_i36];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_A;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[2];
  int32_T c1_i37;
  SFc1_adapInstanceStruct *chartInstance;
  chartInstance = (SFc1_adapInstanceStruct *)chartInstanceVoid;
  c1_A = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_A), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_A);
  for (c1_i37 = 0; c1_i37 < 2; c1_i37++) {
    (*(real_T (*)[2])c1_outData)[c1_i37] = c1_y[c1_i37];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i38;
  int32_T c1_i39;
  int32_T c1_i40;
  real_T c1_b_inData[4];
  int32_T c1_i41;
  int32_T c1_i42;
  int32_T c1_i43;
  real_T c1_u[4];
  const mxArray *c1_y = NULL;
  SFc1_adapInstanceStruct *chartInstance;
  chartInstance = (SFc1_adapInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i38 = 0;
  for (c1_i39 = 0; c1_i39 < 2; c1_i39++) {
    for (c1_i40 = 0; c1_i40 < 2; c1_i40++) {
      c1_b_inData[c1_i40 + c1_i38] = (*(real_T (*)[4])c1_inData)[c1_i40 + c1_i38];
    }

    c1_i38 += 2;
  }

  c1_i41 = 0;
  for (c1_i42 = 0; c1_i42 < 2; c1_i42++) {
    for (c1_i43 = 0; c1_i43 < 2; c1_i43++) {
      c1_u[c1_i43 + c1_i41] = c1_b_inData[c1_i43 + c1_i41];
    }

    c1_i41 += 2;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_d_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[4])
{
  real_T c1_dv1[4];
  int32_T c1_i44;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv1, 1, 0, 0U, 1, 0U, 2, 2, 2);
  for (c1_i44 = 0; c1_i44 < 4; c1_i44++) {
    c1_y[c1_i44] = c1_dv1[c1_i44];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_T_last;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[4];
  int32_T c1_i45;
  int32_T c1_i46;
  int32_T c1_i47;
  SFc1_adapInstanceStruct *chartInstance;
  chartInstance = (SFc1_adapInstanceStruct *)chartInstanceVoid;
  c1_T_last = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_T_last), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_T_last);
  c1_i45 = 0;
  for (c1_i46 = 0; c1_i46 < 2; c1_i46++) {
    for (c1_i47 = 0; c1_i47 < 2; c1_i47++) {
      (*(real_T (*)[4])c1_outData)[c1_i47 + c1_i45] = c1_y[c1_i47 + c1_i45];
    }

    c1_i45 += 2;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_adap_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[22];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i48;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 22), FALSE);
  for (c1_i48 = 0; c1_i48 < 22; c1_i48++) {
    c1_r0 = &c1_info[c1_i48];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i48);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i48);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i48);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i48);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i48);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i48);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i48);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i48);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[22])
{
  c1_info[0].context = "";
  c1_info[0].name = "mrdivide";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[0].fileTimeLo = 1342789344U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 1319708366U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[1].name = "rdivide";
  c1_info[1].dominantType = "double";
  c1_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[1].fileTimeLo = 1286797244U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 0U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[2].name = "eml_div";
  c1_info[2].dominantType = "double";
  c1_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[2].fileTimeLo = 1313326210U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context = "";
  c1_info[3].name = "mpower";
  c1_info[3].dominantType = "double";
  c1_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[3].fileTimeLo = 1286797242U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[4].name = "power";
  c1_info[4].dominantType = "double";
  c1_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[4].fileTimeLo = 1336500496U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[5].name = "eml_scalar_eg";
  c1_info[5].dominantType = "double";
  c1_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[5].fileTimeLo = 1286797196U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[6].name = "eml_scalexp_alloc";
  c1_info[6].dominantType = "double";
  c1_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[6].fileTimeLo = 1330583234U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[7].name = "floor";
  c1_info[7].dominantType = "double";
  c1_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[7].fileTimeLo = 1286797142U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[8].name = "eml_scalar_floor";
  c1_info[8].dominantType = "double";
  c1_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[8].fileTimeLo = 1286797126U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context = "";
  c1_info[9].name = "mtimes";
  c1_info[9].dominantType = "double";
  c1_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[9].fileTimeLo = 1289494492U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[10].name = "eml_index_class";
  c1_info[10].dominantType = "";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[10].fileTimeLo = 1323145378U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[11].name = "eml_scalar_eg";
  c1_info[11].dominantType = "double";
  c1_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[11].fileTimeLo = 1286797196U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[12].name = "eml_xgemm";
  c1_info[12].dominantType = "char";
  c1_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c1_info[12].fileTimeLo = 1299051572U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c1_info[13].name = "eml_blas_inline";
  c1_info[13].dominantType = "";
  c1_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c1_info[13].fileTimeLo = 1299051568U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 0U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c1_info[14].name = "mtimes";
  c1_info[14].dominantType = "double";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[14].fileTimeLo = 1289494492U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[15].name = "eml_index_class";
  c1_info[15].dominantType = "";
  c1_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[15].fileTimeLo = 1323145378U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
  c1_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[16].name = "eml_scalar_eg";
  c1_info[16].dominantType = "double";
  c1_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[16].fileTimeLo = 1286797196U;
  c1_info[16].fileTimeHi = 0U;
  c1_info[16].mFileTimeLo = 0U;
  c1_info[16].mFileTimeHi = 0U;
  c1_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[17].name = "eml_refblas_xgemm";
  c1_info[17].dominantType = "char";
  c1_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c1_info[17].fileTimeLo = 1299051574U;
  c1_info[17].fileTimeHi = 0U;
  c1_info[17].mFileTimeLo = 0U;
  c1_info[17].mFileTimeHi = 0U;
  c1_info[18].context = "";
  c1_info[18].name = "abs";
  c1_info[18].dominantType = "double";
  c1_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[18].fileTimeLo = 1286797094U;
  c1_info[18].fileTimeHi = 0U;
  c1_info[18].mFileTimeLo = 0U;
  c1_info[18].mFileTimeHi = 0U;
  c1_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[19].name = "eml_scalar_abs";
  c1_info[19].dominantType = "double";
  c1_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[19].fileTimeLo = 1286797112U;
  c1_info[19].fileTimeHi = 0U;
  c1_info[19].mFileTimeLo = 0U;
  c1_info[19].mFileTimeHi = 0U;
  c1_info[20].context = "";
  c1_info[20].name = "sign";
  c1_info[20].dominantType = "double";
  c1_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c1_info[20].fileTimeLo = 1286797150U;
  c1_info[20].fileTimeHi = 0U;
  c1_info[20].mFileTimeLo = 0U;
  c1_info[20].mFileTimeHi = 0U;
  c1_info[21].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c1_info[21].name = "eml_scalar_sign";
  c1_info[21].dominantType = "double";
  c1_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sign.m";
  c1_info[21].fileTimeLo = 1307629638U;
  c1_info[21].fileTimeHi = 0U;
  c1_info[21].mFileTimeLo = 0U;
  c1_info[21].mFileTimeHi = 0U;
}

static void c1_eml_scalar_eg(SFc1_adapInstanceStruct *chartInstance)
{
}

static void c1_b_eml_scalar_eg(SFc1_adapInstanceStruct *chartInstance)
{
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_adapInstanceStruct *chartInstance;
  chartInstance = (SFc1_adapInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_e_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i49;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i49, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i49;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_adapInstanceStruct *chartInstance;
  chartInstance = (SFc1_adapInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_f_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_adap, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_is_active_c1_adap),
    &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_adap);
  return c1_y;
}

static uint8_T c1_g_emlrt_marshallIn(SFc1_adapInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_adapInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_adap_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1291067128U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1317639215U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(390903536U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4109708697U);
}

mxArray *sf_c1_adap_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("8qAwDCA8e8DheBpYiX5epB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c1_adap(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[5],T\"C\",},{M[1],M[12],T\"Kd\",},{M[1],M[11],T\"Kp\",},{M[1],M[14],T\"Kthi\",},{M[8],M[0],T\"is_active_c1_adap\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_adap_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_adapInstanceStruct *chartInstance;
    chartInstance = (SFc1_adapInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_adapMachineNumber_,
          1,
          1,
          1,
          11,
          0,
          0,
          0,
          0,
          0,
          &(chartInstance->chartNumber),
          &(chartInstance->instanceNumber),
          ssGetPath(S),
          (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_adapMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_adapMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_adapMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"thi");
          _SFD_SET_DATA_PROPS(1,2,0,1,"C");
          _SFD_SET_DATA_PROPS(2,1,1,0,"dthi");
          _SFD_SET_DATA_PROPS(3,1,1,0,"thi_last");
          _SFD_SET_DATA_PROPS(4,1,1,0,"dthi_last");
          _SFD_SET_DATA_PROPS(5,1,1,0,"Kp_last");
          _SFD_SET_DATA_PROPS(6,1,1,0,"Kd_last");
          _SFD_SET_DATA_PROPS(7,2,0,1,"Kp");
          _SFD_SET_DATA_PROPS(8,2,0,1,"Kd");
          _SFD_SET_DATA_PROPS(9,1,1,0,"Kthi_last");
          _SFD_SET_DATA_PROPS(10,2,0,1,"Kthi");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,744);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);

        {
          real_T *c1_thi;
          real_T *c1_C;
          real_T *c1_dthi;
          real_T *c1_thi_last;
          real_T *c1_dthi_last;
          real_T *c1_Kp_last;
          real_T *c1_Kd_last;
          real_T *c1_Kp;
          real_T *c1_Kd;
          real_T *c1_Kthi_last;
          real_T *c1_Kthi;
          c1_Kthi = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c1_Kthi_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c1_Kd = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c1_Kp = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c1_Kd_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c1_Kp_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c1_dthi_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c1_thi_last = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c1_dthi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c1_C = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c1_thi = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_thi);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_C);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_dthi);
          _SFD_SET_DATA_VALUE_PTR(3U, c1_thi_last);
          _SFD_SET_DATA_VALUE_PTR(4U, c1_dthi_last);
          _SFD_SET_DATA_VALUE_PTR(5U, c1_Kp_last);
          _SFD_SET_DATA_VALUE_PTR(6U, c1_Kd_last);
          _SFD_SET_DATA_VALUE_PTR(7U, c1_Kp);
          _SFD_SET_DATA_VALUE_PTR(8U, c1_Kd);
          _SFD_SET_DATA_VALUE_PTR(9U, c1_Kthi_last);
          _SFD_SET_DATA_VALUE_PTR(10U, c1_Kthi);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_adapMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization()
{
  return "KhUlR7pzb6jObFkRp1nYPH";
}

static void sf_opaque_initialize_c1_adap(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_adapInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c1_adap((SFc1_adapInstanceStruct*) chartInstanceVar);
  initialize_c1_adap((SFc1_adapInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_adap(void *chartInstanceVar)
{
  enable_c1_adap((SFc1_adapInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_adap(void *chartInstanceVar)
{
  disable_c1_adap((SFc1_adapInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_adap(void *chartInstanceVar)
{
  sf_c1_adap((SFc1_adapInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_adap(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_adap((SFc1_adapInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_adap();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_adap(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_adap();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_adap((SFc1_adapInstanceStruct*)chartInfo->chartInstance,
                        mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_adap(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_adap(S);
}

static void sf_opaque_set_sim_state_c1_adap(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_adap(S, st);
}

static void sf_opaque_terminate_c1_adap(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_adapInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_adap((SFc1_adapInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_adap_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_adap((SFc1_adapInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_adap(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_adap((SFc1_adapInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_adap(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_adap_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,7);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,4);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(34158316U));
  ssSetChecksum1(S,(4174620815U));
  ssSetChecksum2(S,(1977365688U));
  ssSetChecksum3(S,(885017260U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_adap(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_adap(SimStruct *S)
{
  SFc1_adapInstanceStruct *chartInstance;
  chartInstance = (SFc1_adapInstanceStruct *)malloc(sizeof
    (SFc1_adapInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_adapInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_adap;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_adap;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_adap;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_adap;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_adap;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_adap;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_adap;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_adap;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_adap;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_adap;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_adap;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_adap_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_adap(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_adap(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_adap(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_adap_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
