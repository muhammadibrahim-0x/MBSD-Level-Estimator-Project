/**
 ******************************************************************************
 **  Filename:      Controller.h
 **  Date:          25-Jun-2021
 **
 **  Model Version: 1.171
 ******************************************************************************
 **/

#ifndef RTW_HEADER_Controller_h_
#define RTW_HEADER_Controller_h_
#include <math.h>
#include <string.h>
#ifndef Controller_COMMON_INCLUDES_
#define Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Controller_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Named constants for Chart: '<S1>/Blinking' */
#define Controller_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define Controller_IN_StateOff ((uint8_T)1U)
#define Controller_IN_StateOn ((uint8_T)2U)

/* Named constants for Chart: '<S1>/EchoCapture' */
#define Con_IN_calculateDurationAverage ((uint8_T)1U)
#define Contro_IN_calculateEchoDuration ((uint8_T)2U)
#define Contro_IN_waitingCaptureRequest ((uint8_T)8U)
#define Controller_IN_chech_N_Trigger ((uint8_T)3U)
#define Controller_IN_checkEchoOn ((uint8_T)4U)
#define Controller_IN_echoError ((uint8_T)5U)
#define Controller_IN_exitState ((uint8_T)6U)
#define Controller_IN_triggerOn ((uint8_T)7U)

/* Named constants for Chart: '<S1>/MainTask' */
#define Control_IN_CalcualtionexitState ((uint8_T)1U)
#define Controll_IN_DistanceCalcualtion ((uint8_T)2U)
#define Controll_IN_waitingErrorHandler ((uint8_T)7U)
#define Controlle_IN_clearTaskComoleted ((uint8_T)1U)
#define Controller_IN_InitialState ((uint8_T)3U)
#define Controller_IN_requestOff ((uint8_T)4U)
#define Controller_IN_requestOn ((uint8_T)5U)
#define Controller_IN_wait1sec ((uint8_T)2U)
#define Controller_IN_waitWakeUp ((uint8_T)6U)

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_Controller RT_MODEL_Controller;

/* Block signals (default storage) */
typedef struct {
  real_T distance;                     /* '<S1>/MainTask' */
  real_T echoAverageDuration;          /* '<S1>/EchoCapture' */
  boolean_T captureRequest;            /* '<S1>/MainTask' */
  boolean_T updateDistance;            /* '<S1>/MainTask' */
  boolean_T echoDurationCalculated;    /* '<S1>/EchoCapture' */
  boolean_T errorFlag;                 /* '<S1>/EchoCapture' */
} BlockIO_Controller;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Memory1_PreviousInput;        /* '<S4>/Memory1' */
  real_T echoOffDuraion;               /* '<S1>/EchoCapture' */
  uint32_T temporalCounter_i1;         /* '<S1>/EchoCapture' */
  uint16_T temporalCounter_i1_i;       /* '<S1>/MainTask' */
  uint16_T offTime;                    /* '<S1>/Blinking' */
  uint16_T onTime;                     /* '<S1>/Blinking' */
  uint16_T temporalCounter_i1_j;       /* '<S1>/Blinking' */
  uint8_T is_active_c3_Controller;     /* '<S1>/MainTask' */
  uint8_T is_mainTask;                 /* '<S1>/MainTask' */
  uint8_T is_wakeEvery1sec;            /* '<S1>/MainTask' */
  uint8_T is_active_c2_Controller;     /* '<S1>/EchoCapture' */
  uint8_T is_EchoDurationCapture;      /* '<S1>/EchoCapture' */
  uint8_T counter;                     /* '<S1>/EchoCapture' */
  uint8_T is_active_c1_Controller;     /* '<S1>/Blinking' */
  uint8_T is_Blinking;                 /* '<S1>/Blinking' */
  boolean_T Memory2_PreviousInput;     /* '<S4>/Memory2' */
  boolean_T Memory3_PreviousInput;     /* '<S4>/Memory3' */
  boolean_T Memory2_PreviousInput_i;   /* '<S3>/Memory2' */
  boolean_T taskCompleted;             /* '<S1>/MainTask' */
} D_Work_Controller;

/* External inputs (root inport signals with default storage) */
typedef struct {
  boolean_T Echo;                      /* '<Root>/Echo' */
} ExternalInputs_Controller;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T Blink;                     /* '<Root>/Blink' */
  boolean_T Trigger;                   /* '<Root>/Trigger' */
  boolean_T errorWarning;              /* '<Root>/errorWarning' */
} ExternalOutputs_Controller;

/* Real-time Model Data Structure */
struct tag_RTM_Controller {
  const char_T * volatile errorStatus;
  BlockIO_Controller *blockIO;
  D_Work_Controller *dwork;
};

/* Model entry point functions */
extern void Controller_initialize(RT_MODEL_Controller *const Controller_M,
  ExternalInputs_Controller *Controller_U, ExternalOutputs_Controller
  *Controller_Y);
extern void Controller_step(RT_MODEL_Controller *const Controller_M,
  ExternalInputs_Controller *Controller_U, ExternalOutputs_Controller
  *Controller_Y);
extern void Controller_terminate(RT_MODEL_Controller *const Controller_M);

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
 * '<Root>' : 'Controller'
 * '<S1>'   : 'Controller/Controller'
 * '<S2>'   : 'Controller/Controller/Blinking'
 * '<S3>'   : 'Controller/Controller/DRCon2'
 * '<S4>'   : 'Controller/Controller/DRConv1'
 * '<S5>'   : 'Controller/Controller/EchoCapture'
 * '<S6>'   : 'Controller/Controller/MainTask'
 */
#endif                                 /* RTW_HEADER_Controller_h_ */

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
