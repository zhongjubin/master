/* Include files */

#include "blascompat32.h"
#include "sbv_sfun.h"
#include "c1_sbv.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "sbv_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[26] = { "Mp", "Mr", "D", "L", "b", "R",
  "Jp", "Jr", "g", "alpha", "beta", "gama", "A22", "A23", "B2", "A43", "B4",
  "nargin", "nargout", "C", "thi", "dthi", "thi1", "dthi1", "Cout", "ddthi" };

/* Function Declarations */
static void initialize_c1_sbv(SFc1_sbvInstanceStruct *chartInstance);
static void initialize_params_c1_sbv(SFc1_sbvInstanceStruct *chartInstance);
static void enable_c1_sbv(SFc1_sbvInstanceStruct *chartInstance);
static void disable_c1_sbv(SFc1_sbvInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_sbv(SFc1_sbvInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_sbv(SFc1_sbvInstanceStruct *chartInstance);
static void set_sim_state_c1_sbv(SFc1_sbvInstanceStruct *chartInstance, const
  mxArray *c1_st);
static void finalize_c1_sbv(SFc1_sbvInstanceStruct *chartInstance);
static void sf_c1_sbv(SFc1_sbvInstanceStruct *chartInstance);
static void initSimStructsc1_sbv(SFc1_sbvInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_sbvInstanceStruct *chartInstance, const
  mxArray *c1_ddthi, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_sbvInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_c_emlrt_marshallIn(SFc1_sbvInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_d_emlrt_marshallIn(SFc1_sbvInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_sbv, const char_T *c1_identifier);
static uint8_T c1_e_emlrt_marshallIn(SFc1_sbvInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_sbvInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_sbv(SFc1_sbvInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_sbv = 0U;
}

static void initialize_params_c1_sbv(SFc1_sbvInstanceStruct *chartInstance)
{
}

static void enable_c1_sbv(SFc1_sbvInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_sbv(SFc1_sbvInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_sbv(SFc1_sbvInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_sbv(SFc1_sbvInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  uint8_T c1_c_hoistedGlobal;
  uint8_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  real_T *c1_Cout;
  real_T *c1_ddthi;
  c1_ddthi = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_Cout = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(3), FALSE);
  c1_hoistedGlobal = *c1_Cout;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *c1_ddthi;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = chartInstance->c1_is_active_c1_sbv;
  c1_c_u = c1_c_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_sbv(SFc1_sbvInstanceStruct *chartInstance, const
  mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T *c1_Cout;
  real_T *c1_ddthi;
  c1_ddthi = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_Cout = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_Cout = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    0)), "Cout");
  *c1_ddthi = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    1)), "ddthi");
  chartInstance->c1_is_active_c1_sbv = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 2)), "is_active_c1_sbv");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_sbv(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_sbv(SFc1_sbvInstanceStruct *chartInstance)
{
}

static void sf_c1_sbv(SFc1_sbvInstanceStruct *chartInstance)
{
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_hoistedGlobal;
  real_T c1_d_hoistedGlobal;
  real_T c1_e_hoistedGlobal;
  real_T c1_C;
  real_T c1_thi;
  real_T c1_dthi;
  real_T c1_thi1;
  real_T c1_dthi1;
  uint32_T c1_debug_family_var_map[26];
  real_T c1_Mp;
  real_T c1_Mr;
  real_T c1_D;
  real_T c1_L;
  real_T c1_b;
  real_T c1_R;
  real_T c1_Jp;
  real_T c1_Jr;
  real_T c1_g;
  real_T c1_alpha;
  real_T c1_beta;
  real_T c1_gama;
  real_T c1_A22;
  real_T c1_A23;
  real_T c1_B2;
  real_T c1_A43;
  real_T c1_B4;
  real_T c1_nargin = 5.0;
  real_T c1_nargout = 2.0;
  real_T c1_Cout;
  real_T c1_ddthi;
  real_T c1_b_b;
  real_T c1_y;
  real_T c1_c_b;
  real_T c1_b_y;
  real_T c1_d_b;
  real_T c1_c_y;
  real_T c1_e_b;
  real_T c1_d_y;
  real_T c1_f_b;
  real_T c1_e_y;
  real_T c1_g_b;
  real_T c1_f_y;
  real_T *c1_b_ddthi;
  real_T *c1_b_Cout;
  real_T *c1_b_dthi1;
  real_T *c1_b_thi1;
  real_T *c1_b_dthi;
  real_T *c1_b_thi;
  real_T *c1_b_C;
  c1_b_ddthi = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_b_Cout = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_dthi1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c1_b_thi1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c1_b_dthi = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_b_thi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_C = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c1_b_C, 0U);
  _SFD_DATA_RANGE_CHECK(*c1_b_thi, 1U);
  _SFD_DATA_RANGE_CHECK(*c1_b_dthi, 2U);
  _SFD_DATA_RANGE_CHECK(*c1_b_thi1, 3U);
  _SFD_DATA_RANGE_CHECK(*c1_b_dthi1, 4U);
  _SFD_DATA_RANGE_CHECK(*c1_b_Cout, 5U);
  _SFD_DATA_RANGE_CHECK(*c1_b_ddthi, 6U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *c1_b_C;
  c1_b_hoistedGlobal = *c1_b_thi;
  c1_c_hoistedGlobal = *c1_b_dthi;
  c1_d_hoistedGlobal = *c1_b_thi1;
  c1_e_hoistedGlobal = *c1_b_dthi1;
  c1_C = c1_hoistedGlobal;
  c1_thi = c1_b_hoistedGlobal;
  c1_dthi = c1_c_hoistedGlobal;
  c1_thi1 = c1_d_hoistedGlobal;
  c1_dthi1 = c1_e_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 26U, 26U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c1_Mp, 0U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_Mr, 1U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_D, 2U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c1_L, 3U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_b, 4U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_R, 5U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_Jp, 6U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_Jr, 7U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_g, 8U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_alpha, 9U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_beta, 10U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_gama, 11U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_A22, 12U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_A23, 13U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_B2, 14U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c1_A43, 15U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_B4, 16U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 17U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 18U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c1_C, 19U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_thi, 20U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_dthi, 21U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_thi1, 22U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_dthi1, 23U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_Cout, 24U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_ddthi, 25U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 2);
  c1_Mp = 135.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 3);
  c1_Mr = 5.5;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
  c1_D = 0.6;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 5);
  c1_L = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
  c1_b = 0.03;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
  c1_R = 0.2;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  c1_Jp = 27.6;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
  c1_Jr = 0.11;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
  c1_g = 9.8;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
  c1_alpha = 3.0000000000000004;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
  c1_beta = 1.2044444444444444;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 17);
  c1_gama = 1323.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 18);
  c1_A22 = -0.0036363636363636359;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
  c1_A23 = -66.571620261657159;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 20);
  c1_B2 = 0.35334898803533488;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 21);
  c1_A43 = 8.1365313653136511;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
  c1_B4 = -0.006150061500615007;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 25);
  c1_b_b = c1_thi;
  c1_y = 8.1365313653136511 * c1_b_b;
  c1_c_b = c1_C;
  c1_b_y = -0.006150061500615007 * c1_c_b;
  c1_d_b = c1_thi - c1_thi1;
  c1_c_y = 430300.0 * c1_d_b;
  c1_e_b = c1_dthi - c1_dthi1;
  c1_d_y = 150800.0 * c1_e_b;
  c1_ddthi = ((c1_y + c1_b_y) + c1_c_y) + c1_d_y;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 26);
  c1_f_b = c1_thi1;
  c1_e_y = 2646.0 * c1_f_b;
  c1_g_b = c1_dthi1;
  c1_f_y = 927.0 * c1_g_b;
  c1_Cout = c1_e_y + c1_f_y;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -26);
  sf_debug_symbol_scope_pop();
  *c1_b_Cout = c1_Cout;
  *c1_b_ddthi = c1_ddthi;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  sf_debug_check_for_state_inconsistency(_sbvMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc1_sbv(SFc1_sbvInstanceStruct *chartInstance)
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
  SFc1_sbvInstanceStruct *chartInstance;
  chartInstance = (SFc1_sbvInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_sbvInstanceStruct *chartInstance, const
  mxArray *c1_ddthi, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_ddthi), &c1_thisId);
  sf_mex_destroy(&c1_ddthi);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_sbvInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
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
  const mxArray *c1_ddthi;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_sbvInstanceStruct *chartInstance;
  chartInstance = (SFc1_sbvInstanceStruct *)chartInstanceVoid;
  c1_ddthi = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_ddthi), &c1_thisId);
  sf_mex_destroy(&c1_ddthi);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_sbv_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[10];
  c1_ResolvedFunctionInfo (*c1_b_info)[10];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i0;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_b_info = (c1_ResolvedFunctionInfo (*)[10])c1_info;
  (*c1_b_info)[0].context = "";
  (*c1_b_info)[0].name = "mpower";
  (*c1_b_info)[0].dominantType = "double";
  (*c1_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  (*c1_b_info)[0].fileTimeLo = 1286797242U;
  (*c1_b_info)[0].fileTimeHi = 0U;
  (*c1_b_info)[0].mFileTimeLo = 0U;
  (*c1_b_info)[0].mFileTimeHi = 0U;
  (*c1_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  (*c1_b_info)[1].name = "power";
  (*c1_b_info)[1].dominantType = "double";
  (*c1_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  (*c1_b_info)[1].fileTimeLo = 1336500496U;
  (*c1_b_info)[1].fileTimeHi = 0U;
  (*c1_b_info)[1].mFileTimeLo = 0U;
  (*c1_b_info)[1].mFileTimeHi = 0U;
  (*c1_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  (*c1_b_info)[2].name = "eml_scalar_eg";
  (*c1_b_info)[2].dominantType = "double";
  (*c1_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c1_b_info)[2].fileTimeLo = 1286797196U;
  (*c1_b_info)[2].fileTimeHi = 0U;
  (*c1_b_info)[2].mFileTimeLo = 0U;
  (*c1_b_info)[2].mFileTimeHi = 0U;
  (*c1_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  (*c1_b_info)[3].name = "eml_scalexp_alloc";
  (*c1_b_info)[3].dominantType = "double";
  (*c1_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  (*c1_b_info)[3].fileTimeLo = 1330583234U;
  (*c1_b_info)[3].fileTimeHi = 0U;
  (*c1_b_info)[3].mFileTimeLo = 0U;
  (*c1_b_info)[3].mFileTimeHi = 0U;
  (*c1_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  (*c1_b_info)[4].name = "floor";
  (*c1_b_info)[4].dominantType = "double";
  (*c1_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  (*c1_b_info)[4].fileTimeLo = 1286797142U;
  (*c1_b_info)[4].fileTimeHi = 0U;
  (*c1_b_info)[4].mFileTimeLo = 0U;
  (*c1_b_info)[4].mFileTimeHi = 0U;
  (*c1_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  (*c1_b_info)[5].name = "eml_scalar_floor";
  (*c1_b_info)[5].dominantType = "double";
  (*c1_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  (*c1_b_info)[5].fileTimeLo = 1286797126U;
  (*c1_b_info)[5].fileTimeHi = 0U;
  (*c1_b_info)[5].mFileTimeLo = 0U;
  (*c1_b_info)[5].mFileTimeHi = 0U;
  (*c1_b_info)[6].context = "";
  (*c1_b_info)[6].name = "mtimes";
  (*c1_b_info)[6].dominantType = "double";
  (*c1_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c1_b_info)[6].fileTimeLo = 1289494492U;
  (*c1_b_info)[6].fileTimeHi = 0U;
  (*c1_b_info)[6].mFileTimeLo = 0U;
  (*c1_b_info)[6].mFileTimeHi = 0U;
  (*c1_b_info)[7].context = "";
  (*c1_b_info)[7].name = "mrdivide";
  (*c1_b_info)[7].dominantType = "double";
  (*c1_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c1_b_info)[7].fileTimeLo = 1342789344U;
  (*c1_b_info)[7].fileTimeHi = 0U;
  (*c1_b_info)[7].mFileTimeLo = 1319708366U;
  (*c1_b_info)[7].mFileTimeHi = 0U;
  (*c1_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c1_b_info)[8].name = "rdivide";
  (*c1_b_info)[8].dominantType = "double";
  (*c1_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c1_b_info)[8].fileTimeLo = 1286797244U;
  (*c1_b_info)[8].fileTimeHi = 0U;
  (*c1_b_info)[8].mFileTimeLo = 0U;
  (*c1_b_info)[8].mFileTimeHi = 0U;
  (*c1_b_info)[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c1_b_info)[9].name = "eml_div";
  (*c1_b_info)[9].dominantType = "double";
  (*c1_b_info)[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  (*c1_b_info)[9].fileTimeLo = 1313326210U;
  (*c1_b_info)[9].fileTimeHi = 0U;
  (*c1_b_info)[9].mFileTimeLo = 0U;
  (*c1_b_info)[9].mFileTimeHi = 0U;
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 10), FALSE);
  for (c1_i0 = 0; c1_i0 < 10; c1_i0++) {
    c1_r0 = &c1_info[c1_i0];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i0);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i0);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_sbvInstanceStruct *chartInstance;
  chartInstance = (SFc1_sbvInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_c_emlrt_marshallIn(SFc1_sbvInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i1;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i1, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i1;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_sbvInstanceStruct *chartInstance;
  chartInstance = (SFc1_sbvInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_d_emlrt_marshallIn(SFc1_sbvInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_sbv, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_is_active_c1_sbv),
    &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_sbv);
  return c1_y;
}

static uint8_T c1_e_emlrt_marshallIn(SFc1_sbvInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_sbvInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_sbv_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(174406487U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(211994010U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1849079962U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(799605739U);
}

mxArray *sf_c1_sbv_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("d2eHkZYECgxqMOV6OWJQuB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c1_sbv(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[17],T\"Cout\",},{M[1],M[18],T\"ddthi\",},{M[8],M[0],T\"is_active_c1_sbv\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_sbv_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_sbvInstanceStruct *chartInstance;
    chartInstance = (SFc1_sbvInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_sbvMachineNumber_,
          1,
          1,
          1,
          7,
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
          init_script_number_translation(_sbvMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_sbvMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_sbvMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"C");
          _SFD_SET_DATA_PROPS(1,1,1,0,"thi");
          _SFD_SET_DATA_PROPS(2,1,1,0,"dthi");
          _SFD_SET_DATA_PROPS(3,1,1,0,"thi1");
          _SFD_SET_DATA_PROPS(4,1,1,0,"dthi1");
          _SFD_SET_DATA_PROPS(5,2,0,1,"Cout");
          _SFD_SET_DATA_PROPS(6,2,0,1,"ddthi");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,841);
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
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);

        {
          real_T *c1_C;
          real_T *c1_thi;
          real_T *c1_dthi;
          real_T *c1_thi1;
          real_T *c1_dthi1;
          real_T *c1_Cout;
          real_T *c1_ddthi;
          c1_ddthi = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c1_Cout = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c1_dthi1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c1_thi1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c1_dthi = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c1_thi = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c1_C = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_C);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_thi);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_dthi);
          _SFD_SET_DATA_VALUE_PTR(3U, c1_thi1);
          _SFD_SET_DATA_VALUE_PTR(4U, c1_dthi1);
          _SFD_SET_DATA_VALUE_PTR(5U, c1_Cout);
          _SFD_SET_DATA_VALUE_PTR(6U, c1_ddthi);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_sbvMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization()
{
  return "NqK1LUdjSN23XH4aV5NbkF";
}

static void sf_opaque_initialize_c1_sbv(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_sbvInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c1_sbv((SFc1_sbvInstanceStruct*) chartInstanceVar);
  initialize_c1_sbv((SFc1_sbvInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_sbv(void *chartInstanceVar)
{
  enable_c1_sbv((SFc1_sbvInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_sbv(void *chartInstanceVar)
{
  disable_c1_sbv((SFc1_sbvInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_sbv(void *chartInstanceVar)
{
  sf_c1_sbv((SFc1_sbvInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_sbv(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_sbv((SFc1_sbvInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_sbv();/* state var info */
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

extern void sf_internal_set_sim_state_c1_sbv(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_sbv();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_sbv((SFc1_sbvInstanceStruct*)chartInfo->chartInstance,
                       mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_sbv(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_sbv(S);
}

static void sf_opaque_set_sim_state_c1_sbv(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_sbv(S, st);
}

static void sf_opaque_terminate_c1_sbv(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_sbvInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_sbv((SFc1_sbvInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_sbv_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_sbv((SFc1_sbvInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_sbv(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_sbv((SFc1_sbvInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_sbv(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_sbv_optimization_info();
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
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,2);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1200614096U));
  ssSetChecksum1(S,(3634155071U));
  ssSetChecksum2(S,(3504413755U));
  ssSetChecksum3(S,(2603369074U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_sbv(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_sbv(SimStruct *S)
{
  SFc1_sbvInstanceStruct *chartInstance;
  chartInstance = (SFc1_sbvInstanceStruct *)malloc(sizeof(SFc1_sbvInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_sbvInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_sbv;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_sbv;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_sbv;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_sbv;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_sbv;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_sbv;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_sbv;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_sbv;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_sbv;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_sbv;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_sbv;
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

void c1_sbv_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_sbv(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_sbv(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_sbv(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_sbv_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
