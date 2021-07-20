/**
 *******************************************************************************
 **  FILE INFORMATION:
 **  Filename:           ert_main.c
 **  File Creation Date: 25-Jun-2021
 **
 **  ABSTRACT:
 **
 **
 **  NOTES:
 **
 **
 **  MODEL INFORMATION:
 **  Model Name:         Controller
 **  Model Description:
 **  Model Version:      1.180
 **  Model Author:       The MathWorks, Inc. - Thu Feb 16 11:28:08 2012
 **
 **  MODIFICATION HISTORY:
 **  Model at Code Generation: moody - Fri Jun 25 21:25:02 2021
 **
 **  Last Saved Modification:  moody - Fri Jun 25 19:52:08 2021
 **
 **
 *******************************************************************************
 **/

#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "Controller.h"                /* Model's header file */
#include "rtwtypes.h"

/*  Defines */

/*  Data Types */

/**************************** GLOBAL DATA *************************************/
/*  Definitions */
static RT_MODEL_Controller Controller_M_;
static RT_MODEL_Controller *const Controller_MPtr = &Controller_M_;/* Real-time model */
static BlockIO_Controller Controller_B;/* Observable signals */
static D_Work_Controller Controller_DWork;/* Observable states */
static ExternalInputs_Controller Controller_U;/* External inputs */
static ExternalOutputs_Controller Controller_Y;/* External outputs */

/*  Declarations  */

/***************************** FILE SCOPE DATA ********************************/

/*************************** FUNCTIONS ****************************************/

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(RT_MODEL_Controller *const Controller_M);
void rt_OneStep(RT_MODEL_Controller *const Controller_M)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(Controller_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  Controller_step(Controller_M, &Controller_U, &Controller_Y);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_Controller *const Controller_M = Controller_MPtr;

  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Pack model data into RTM */
  Controller_M->blockIO = &Controller_B;
  Controller_M->dwork = &Controller_DWork;

  /* Initialize model */
  Controller_initialize(Controller_M, &Controller_U, &Controller_Y);

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.0001 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep(Controller_M);
   */
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(Controller_M) == (NULL)) {
    /*  Perform other application tasks here */
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  Controller_terminate(Controller_M);
  return 0;
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
 * stateflow                                                                  *
 *============================================================================*/
