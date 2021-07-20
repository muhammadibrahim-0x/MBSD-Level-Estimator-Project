/**
 ******************************************************************************
 **  Filename:      UltraSonic_Sensor.h
 **  Date:          24-Jun-2021
 **
 **  Model Version: 10.67
 ******************************************************************************
 **/

#ifndef RTW_HEADER_UltraSonic_Sensor_h_
#define RTW_HEADER_UltraSonic_Sensor_h_
#include <string.h>
#ifndef UltraSonic_Sensor_COMMON_INCLUDES_
#define UltraSonic_Sensor_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* UltraSonic_Sensor_COMMON_INCLUDES_ */



/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Named constants for Chart: '<S1>/EchoGenerator' */
#define IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define IN_calculateTriggetDuration ((uint8_T)1U)
#define IN_echoOff ((uint8_T)2U)
#define IN_echoOn ((uint8_T)3U)
#define IN_flagError ((uint8_T)4U)
#define IN_watingEchoLatency ((uint8_T)5U)
#define IN_watingTriggerHigh ((uint8_T)6U)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T triggerDuraion;               /* '<S1>/EchoGenerator' */
  uint32_T temporalCounter_i1;         /* '<S1>/EchoGenerator' */
  uint8_T is_active_c2_UltraSonic_Sensor;/* '<S1>/EchoGenerator' */
  uint8_T is_c2_UltraSonic_Sensor;     /* '<S1>/EchoGenerator' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  boolean_T Trigger;                   /* '<Root>/Trigger' */
  uint16_T distance;                   /* '<Root>/distance' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T Echo;                      /* '<Root>/Echo' */
  boolean_T errorFlag;                 /* '<Root>/errorFlag' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
  DW *dwork;
};

/* Model entry point functions */
extern void UltraSonic_Sensor_initialize(RT_MODEL *const rtM, ExtU *rtU, ExtY
  *rtY);
extern void UltraSonic_Sensor_step(RT_MODEL *const rtM, ExtU *rtU, ExtY *rtY);
extern void UltraSonic_Sensor_terminate(RT_MODEL *const rtM);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'UltraSonic_Sensor'
 * '<S1>'   : 'UltraSonic_Sensor/UltraSonic Sensor'
 * '<S2>'   : 'UltraSonic_Sensor/UltraSonic Sensor/EchoGenerator'
 * '<S3>'   : 'UltraSonic_Sensor/UltraSonic Sensor/Subsystem'
 */
#endif                                 /* RTW_HEADER_UltraSonic_Sensor_h_ */

/*======================== TOOL VERSION INFORMATION ==========================*
 * MATLAB 9.9 (R2020b)29-Jul-2020                                             *
 * Simulink 10.2 (R2020b)29-Jul-2020                                          *
 * Simulink Coder 9.4 (R2020b)29-Jul-2020                                     *
 * Embedded Coder 7.5 (R2020b)29-Jul-2020                                     *
 * Stateflow 10.3 (R2020b)29-Jul-2020                                         *
 *============================================================================*/

/*======================= LICENSE IN USE INFORMATION =========================*
 * matlab                                                                     *
 * matlab_coder                                                               *
 * real-time_workshop                                                         *
 * rtw_embedded_coder                                                         *
 * simscape                                                                   *
 * simulink                                                                   *
 * simulink_coverage                                                          *
 * simulink_test                                                              *
 * stateflow                                                                  *
 *============================================================================*/
