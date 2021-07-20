/**
 *******************************************************************************
 **  FILE INFORMATION:
 **  Filename:           UltraSonic_Sensor.c
 **  File Creation Date: 24-Jun-2021
 **
 **  ABSTRACT:
 **
 **
 **  NOTES:
 **
 **
 **  MODEL INFORMATION:
 **  Model Name:         UltraSonic_Sensor
 **  Model Description:
 **  Model Version:      10.67
 **  Model Author:       The MathWorks, Inc. - Thu Feb 16 11:28:08 2012
 **
 **  MODIFICATION HISTORY:
 **  Model at Code Generation: moody - Thu Jun 24 15:33:25 2021
 **
 **  Last Saved Modification:  moody - Thu Jun 24 15:24:21 2021
 **
 **
 *******************************************************************************
 **/

#include "UltraSonic_Sensor.h"

/*  Defines */

// /* Named constants for Chart: '<S1>/EchoGenerator' */
// #define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
// #define IN_calculateTriggetDuration    ((uint8_T)1U)
// #define IN_echoOff                     ((uint8_T)2U)
// #define IN_echoOn                      ((uint8_T)3U)
// #define IN_flagError                   ((uint8_T)4U)
// #define IN_watingEchoLatency           ((uint8_T)5U)
// #define IN_watingTriggerHigh           ((uint8_T)6U)

/*  Data Types */

/**************************** GLOBAL DATA *************************************/
/*  Definitions */

/*  Declarations  */

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

/***************************** FILE SCOPE DATA ********************************/

/*************************** FUNCTIONS ****************************************/

/* Model step function */
void UltraSonic_Sensor_step(RT_MODEL *const rtM, ExtU *rtU, ExtY *rtY)
{
  DW *rtDW = rtM->dwork;
  uint16_T rtb_Gain;
  boolean_T tmp;

  /* Gain: '<S3>/Gain' incorporates:
   *  Inport: '<Root>/distance'
   */
  rtb_Gain = (uint16_T)(58U * rtU->distance);

  /* Chart: '<S1>/EchoGenerator' incorporates:
   *  Inport: '<Root>/Trigger'
   */
  if (rtDW->temporalCounter_i1 < MAX_uint32_T) {
    rtDW->temporalCounter_i1++;
  }

  if (rtDW->is_active_c2_UltraSonic_Sensor == 0U) {
    rtDW->is_active_c2_UltraSonic_Sensor = 1U;
    rtDW->is_c2_UltraSonic_Sensor = IN_watingTriggerHigh;

    /* Outport: '<Root>/Echo' */
    rtY->Echo = false;

    /* Outport: '<Root>/errorFlag' */
    rtY->errorFlag = false;
  } else {
    switch (rtDW->is_c2_UltraSonic_Sensor) {
     case IN_calculateTriggetDuration:
      tmp = !rtU->Trigger;
      if (tmp && (rtDW->triggerDuraion >= 90.0)) {
        rtDW->triggerDuraion = (real_T)rtDW->temporalCounter_i1 * 10.0;
        rtDW->is_c2_UltraSonic_Sensor = IN_watingEchoLatency;
        rtDW->temporalCounter_i1 = 0U;

        /* Outport: '<Root>/Echo' */
        rtY->Echo = false;
      } else if (tmp && (rtDW->triggerDuraion < 90.0)) {
        rtDW->triggerDuraion = (real_T)rtDW->temporalCounter_i1 * 10.0;
        rtDW->is_c2_UltraSonic_Sensor = IN_flagError;
        rtDW->temporalCounter_i1 = 0U;

        /* Outport: '<Root>/errorFlag' */
        rtY->errorFlag = true;
      } else {
        rtDW->triggerDuraion = (real_T)rtDW->temporalCounter_i1 * 10.0;
      }
      break;

     case IN_echoOff:
      rtDW->is_c2_UltraSonic_Sensor = IN_watingTriggerHigh;

      /* Outport: '<Root>/Echo' */
      rtY->Echo = false;

      /* Outport: '<Root>/errorFlag' */
      rtY->errorFlag = false;
      break;

     case IN_echoOn:
      /* Outport: '<Root>/Echo' */
      rtY->Echo = true;
      if ((uint32_T)((int32_T)rtDW->temporalCounter_i1 * 100) >= rtb_Gain) {
        rtDW->is_c2_UltraSonic_Sensor = IN_echoOff;

        /* Outport: '<Root>/Echo' */
        rtY->Echo = false;
      }
      break;

     case IN_flagError:
      /* Outport: '<Root>/errorFlag' */
      rtY->errorFlag = true;
      if (rtDW->temporalCounter_i1 >= 10U) {
        rtDW->is_c2_UltraSonic_Sensor = IN_watingTriggerHigh;

        /* Outport: '<Root>/Echo' */
        rtY->Echo = false;

        /* Outport: '<Root>/errorFlag' */
        rtY->errorFlag = false;
      }
      break;

     case IN_watingEchoLatency:
      /* Outport: '<Root>/Echo' */
      rtY->Echo = false;
      if ((rtDW->temporalCounter_i1 >= 2U) && (rtb_Gain != 0)) {
        rtDW->is_c2_UltraSonic_Sensor = IN_echoOn;
        rtDW->temporalCounter_i1 = 0U;

        /* Outport: '<Root>/Echo' */
        rtY->Echo = true;
      } else {
        if (rtb_Gain == 0) {
          rtDW->is_c2_UltraSonic_Sensor = IN_watingTriggerHigh;

          /* Outport: '<Root>/Echo' */
          rtY->Echo = false;

          /* Outport: '<Root>/errorFlag' */
          rtY->errorFlag = false;
        }
      }
      break;

     default:
      /* Outport: '<Root>/Echo' */
      /* case IN_watingTriggerHigh: */
      rtY->Echo = false;

      /* Outport: '<Root>/errorFlag' */
      rtY->errorFlag = false;
      if (rtU->Trigger) {
        rtDW->is_c2_UltraSonic_Sensor = IN_calculateTriggetDuration;
        rtDW->temporalCounter_i1 = 0U;
        rtDW->triggerDuraion = (real_T)rtDW->temporalCounter_i1 * 10.0;
      }
      break;
    }
  }

  /* End of Chart: '<S1>/EchoGenerator' */
}

/* Model initialize function */
void UltraSonic_Sensor_initialize(RT_MODEL *const rtM, ExtU *rtU, ExtY *rtY)
{
  DW *rtDW = rtM->dwork;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  (void) memset((void *)rtY, 0,
                sizeof(ExtY));

  /* SystemInitialize for Chart: '<S1>/EchoGenerator' */
  rtDW->temporalCounter_i1 = 0U;
  rtDW->is_active_c2_UltraSonic_Sensor = 0U;
  rtDW->is_c2_UltraSonic_Sensor = IN_NO_ACTIVE_CHILD;
  rtDW->triggerDuraion = 0.0;
}

/* Model terminate function */
void UltraSonic_Sensor_terminate(RT_MODEL *const rtM)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(rtM);
}

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
