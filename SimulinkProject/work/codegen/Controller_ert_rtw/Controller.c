/**
 *******************************************************************************
 **  FILE INFORMATION:
 **  Filename:           Controller.c
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

#include "Controller.h"

/*  Defines */

/* Named constants for Chart: '<S1>/Blinking' */
#define Controller_IN_NO_ACTIVE_CHILD  ((uint8_T)0U)
#define Controller_IN_StateOff         ((uint8_T)1U)
#define Controller_IN_StateOn          ((uint8_T)2U)

/* Named constants for Chart: '<S1>/EchoCapture' */
#define Con_IN_calculateDurationAverage ((uint8_T)1U)
#define Contro_IN_calculateEchoDuration ((uint8_T)2U)
#define Contro_IN_waitingCaptureRequest ((uint8_T)8U)
#define Controller_IN_chech_N_Trigger  ((uint8_T)3U)
#define Controller_IN_checkEchoOn      ((uint8_T)4U)
#define Controller_IN_echoError        ((uint8_T)5U)
#define Controller_IN_exitState        ((uint8_T)6U)
#define Controller_IN_triggerOn        ((uint8_T)7U)

/* Named constants for Chart: '<S1>/MainTask' */
#define Control_IN_CalcualtionexitState ((uint8_T)1U)
#define Controll_IN_DistanceCalcualtion ((uint8_T)2U)
#define Controll_IN_waitingErrorHandler ((uint8_T)7U)
#define Controlle_IN_clearTaskComoleted ((uint8_T)1U)
#define Controller_IN_InitialState     ((uint8_T)3U)
#define Controller_IN_requestOff       ((uint8_T)4U)
#define Controller_IN_requestOn        ((uint8_T)5U)
#define Controller_IN_wait1sec         ((uint8_T)2U)
#define Controller_IN_waitWakeUp       ((uint8_T)6U)

/*  Data Types */

/**************************** GLOBAL DATA *************************************/
/*  Definitions */

/*  Declarations  */
extern real_T rt_roundd(real_T u);

/* Forward declaration for local functions */
static void Controller_blinkBasedOnDistance(real_T distanceIn, D_Work_Controller
  *Controller_DWork);

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
real_T rt_roundd(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Function for Chart: '<S1>/Blinking' */
static void Controller_blinkBasedOnDistance(real_T distanceIn, D_Work_Controller
  *Controller_DWork)
{
  real_T tmp;

  /* MATLAB Function 'blinkBasedOnDistance': '<S2>:177' */
  /* Graphical Function 'blinkBasedOnDistance': '<S2>:177' */
  /* Transition: '<S2>:186' */
  if ((distanceIn >= 10.0) && (distanceIn <= 100.0)) {
    /* '<S2>:187:1' */
    /* Transition: '<S2>:187' */
    /* Transition: '<S2>:189' */
    /* '<S2>:189:1' */
    tmp = rt_roundd(distanceIn);
    if (tmp < 65536.0) {
      if (tmp >= 0.0) {
        Controller_DWork->onTime = (uint16_T)tmp;
      } else {
        Controller_DWork->onTime = 0U;
      }
    } else {
      Controller_DWork->onTime = MAX_uint16_T;
    }

    /* '<S2>:189:1' */
    tmp = rt_roundd(100.0 - distanceIn);
    if (tmp < 65536.0) {
      if (tmp >= 0.0) {
        Controller_DWork->offTime = (uint16_T)tmp;
      } else {
        Controller_DWork->offTime = 0U;
      }
    } else {
      Controller_DWork->offTime = MAX_uint16_T;
    }

    /* Transition: '<S2>:193' */
    /* Transition: '<S2>:217' */
    /* Transition: '<S2>:192' */
  } else {
    /* Transition: '<S2>:188' */
    if ((distanceIn > 3.0) && (distanceIn < 10.0)) {
      /* '<S2>:190:1' */
      /* Transition: '<S2>:190' */
      /* Transition: '<S2>:191' */
      /* '<S2>:191:1' */
      Controller_DWork->onTime = 250U;

      /* '<S2>:191:1' */
      Controller_DWork->offTime = 250U;

      /* Transition: '<S2>:217' */
      /* Transition: '<S2>:192' */
    } else {
      /* Transition: '<S2>:212' */
      if ((distanceIn > 100.0) && (distanceIn <= 400.0)) {
        /* '<S2>:213:1' */
        /* Transition: '<S2>:213' */
        /* Transition: '<S2>:216' */
        /* '<S2>:216:1' */
        Controller_DWork->onTime = 250U;

        /* '<S2>:216:1' */
        Controller_DWork->offTime = 250U;

        /* Transition: '<S2>:192' */
      } else {
        /* Transition: '<S2>:195' */
        /* '<S2>:195:1' */
        Controller_DWork->onTime = 500U;

        /* '<S2>:195:1' */
        Controller_DWork->offTime = 500U;
      }
    }
  }

  /* Transition: '<S2>:194' */
}

/* Model step function */
void Controller_step(RT_MODEL_Controller *const Controller_M,
                     ExternalInputs_Controller *Controller_U,
                     ExternalOutputs_Controller *Controller_Y)
{
  BlockIO_Controller *Controller_B = Controller_M->blockIO;
  D_Work_Controller *Controller_DWork = Controller_M->dwork;
  int32_T tmp;

  /* Chart: '<S1>/MainTask' incorporates:
   *  Memory: '<S4>/Memory1'
   *  Memory: '<S4>/Memory2'
   *  Memory: '<S4>/Memory3'
   */
  if (Controller_DWork->temporalCounter_i1_i < 16383U) {
    Controller_DWork->temporalCounter_i1_i++;
  }

  /* Gateway: Controller/MainTask */
  /* During: Controller/MainTask */
  if (Controller_DWork->is_active_c3_Controller == 0U) {
    /* Entry: Controller/MainTask */
    Controller_DWork->is_active_c3_Controller = 1U;

    /* Entry Internal: Controller/MainTask */
    /* Entry Internal 'mainTask': '<S6>:69' */
    /* Transition: '<S6>:2' */
    Controller_DWork->is_mainTask = Controller_IN_InitialState;

    /* Entry 'InitialState': '<S6>:1' */
    Controller_B->captureRequest = false;
    Controller_B->updateDistance = false;

    /* Entry Internal 'wakeEvery1sec': '<S6>:68' */
    /* Transition: '<S6>:76' */
    Controller_DWork->is_wakeEvery1sec = Controller_IN_wait1sec;
    Controller_DWork->temporalCounter_i1_i = 0U;
  } else {
    /* During 'mainTask': '<S6>:69' */
    switch (Controller_DWork->is_mainTask) {
     case Control_IN_CalcualtionexitState:
      Controller_B->updateDistance = false;

      /* During 'CalcualtionexitState': '<S6>:44' */
      /* Transition: '<S6>:67' */
      Controller_DWork->is_mainTask = Controller_IN_waitWakeUp;

      /* Entry 'waitWakeUp': '<S6>:66' */
      Controller_DWork->taskCompleted = true;
      break;

     case Controll_IN_DistanceCalcualtion:
      /* During 'DistanceCalcualtion': '<S6>:6' */
      /* Transition: '<S6>:45' */
      Controller_DWork->is_mainTask = Control_IN_CalcualtionexitState;

      /* Entry 'CalcualtionexitState': '<S6>:44' */
      Controller_B->updateDistance = false;
      break;

     case Controller_IN_InitialState:
      Controller_B->updateDistance = false;

      /* During 'InitialState': '<S6>:1' */
      /* Transition: '<S6>:4' */
      Controller_DWork->is_mainTask = Controller_IN_requestOn;

      /* Entry 'requestOn': '<S6>:40' */
      Controller_B->captureRequest = true;
      break;

     case Controller_IN_requestOff:
      Controller_B->captureRequest = false;

      /* During 'requestOff': '<S6>:38' */
      if (Controller_DWork->Memory2_PreviousInput) {
        /* Transition: '<S6>:7' */
        Controller_DWork->is_mainTask = Controll_IN_DistanceCalcualtion;

        /* Entry 'DistanceCalcualtion': '<S6>:6' */
        Controller_B->updateDistance = true;
        Controller_B->distance = Controller_DWork->Memory1_PreviousInput / 58.0;
      } else {
        if (Controller_DWork->Memory3_PreviousInput) {
          /* Transition: '<S6>:43' */
          /* Transition: '<S6>:27' */
          Controller_DWork->is_mainTask = Controll_IN_waitingErrorHandler;

          /* Entry 'waitingErrorHandler': '<S6>:37' */
          Controller_B->distance = 0.0;

          /* Outport: '<Root>/errorWarning' */
          Controller_Y->errorWarning = true;
        }
      }
      break;

     case Controller_IN_requestOn:
      /* During 'requestOn': '<S6>:40' */
      /* Transition: '<S6>:39' */
      Controller_DWork->is_mainTask = Controller_IN_requestOff;

      /* Entry 'requestOff': '<S6>:38' */
      Controller_B->captureRequest = false;
      break;

     case Controller_IN_waitWakeUp:
      /* During 'waitWakeUp': '<S6>:66' */
      if (!Controller_DWork->taskCompleted) {
        /* Transition: '<S6>:84' */
        /* Transition: '<S6>:85' */
        /* Transition: '<S6>:86' */
        Controller_DWork->is_mainTask = Controller_IN_InitialState;

        /* Entry 'InitialState': '<S6>:1' */
        Controller_B->captureRequest = false;
        Controller_B->updateDistance = false;
      } else {
        Controller_DWork->taskCompleted = true;
      }
      break;

     default:
      /* During 'waitingErrorHandler': '<S6>:37' */
      if (!Controller_DWork->Memory3_PreviousInput) {
        /* Outport: '<Root>/errorWarning' */
        /* Transition: '<S6>:34' */
        /* Exit 'waitingErrorHandler': '<S6>:37' */
        Controller_Y->errorWarning = false;
        Controller_DWork->is_mainTask = Controller_IN_InitialState;

        /* Entry 'InitialState': '<S6>:1' */
        Controller_B->captureRequest = false;
        Controller_B->updateDistance = false;
      }
      break;
    }

    /* During 'wakeEvery1sec': '<S6>:68' */
    if (Controller_DWork->is_wakeEvery1sec == Controlle_IN_clearTaskComoleted) {
      /* During 'clearTaskComoleted': '<S6>:88' */
      /* Transition: '<S6>:81' */
      Controller_DWork->is_wakeEvery1sec = Controller_IN_wait1sec;
      Controller_DWork->temporalCounter_i1_i = 0U;
    } else {
      /* During 'wait1sec': '<S6>:78' */
      if (Controller_DWork->temporalCounter_i1_i >= 10000U) {
        /* Transition: '<S6>:80' */
        Controller_DWork->is_wakeEvery1sec = Controlle_IN_clearTaskComoleted;

        /* Entry 'clearTaskComoleted': '<S6>:88' */
        Controller_DWork->taskCompleted = false;
      }
    }
  }

  /* End of Chart: '<S1>/MainTask' */

  /* Chart: '<S1>/Blinking' incorporates:
   *  Outport: '<Root>/errorWarning'
   */
  if (Controller_DWork->temporalCounter_i1_j < 1048575U) {
    Controller_DWork->temporalCounter_i1_j++;
  }

  /* Gateway: Controller/Blinking */
  /* During: Controller/Blinking */
  if (Controller_DWork->is_active_c1_Controller == 0U) {
    /* Entry: Controller/Blinking */
    Controller_DWork->is_active_c1_Controller = 1U;

    /* Entry Internal: Controller/Blinking */
    /* Entry Internal 'updateDistance': '<S2>:173' */
    /* Transition: '<S2>:153' */
    /* Entry 'startState': '<S2>:135' */
    Controller_blinkBasedOnDistance(Controller_B->distance, Controller_DWork);

    /* Entry 'Blinking': '<S2>:200' */
    /* Entry Internal 'Blinking': '<S2>:200' */
    /* Transition: '<S2>:201' */
    Controller_DWork->is_Blinking = Controller_IN_StateOn;
    Controller_DWork->temporalCounter_i1_j = 0U;

    /* Outport: '<Root>/Blink' */
    /* Entry 'StateOn': '<S2>:204' */
    Controller_Y->Blink = true;
  } else {
    /* During 'updateDistance': '<S2>:173' */
    /* During 'startState': '<S2>:135' */
    if (Controller_B->updateDistance || Controller_Y->errorWarning) {
      /* Transition: '<S2>:206' */
      /* Entry 'startState': '<S2>:135' */
      Controller_blinkBasedOnDistance(Controller_B->distance, Controller_DWork);
    } else {
      Controller_blinkBasedOnDistance(Controller_B->distance, Controller_DWork);
    }

    /* During 'Blinking': '<S2>:200' */
    if (Controller_DWork->is_Blinking == Controller_IN_StateOff) {
      /* During 'StateOff': '<S2>:205' */
      if (Controller_DWork->temporalCounter_i1_j >= (uint32_T)
          (Controller_DWork->offTime * 10)) {
        /* Transition: '<S2>:202' */
        Controller_DWork->is_Blinking = Controller_IN_StateOn;
        Controller_DWork->temporalCounter_i1_j = 0U;

        /* Outport: '<Root>/Blink' */
        /* Entry 'StateOn': '<S2>:204' */
        Controller_Y->Blink = true;
      } else {
        /* Outport: '<Root>/Blink' */
        Controller_Y->Blink = false;
      }
    } else {
      /* During 'StateOn': '<S2>:204' */
      if ((Controller_DWork->temporalCounter_i1_j >= (uint32_T)
           (Controller_DWork->onTime * 10)) && (Controller_DWork->onTime != 100))
      {
        /* Transition: '<S2>:203' */
        Controller_DWork->is_Blinking = Controller_IN_StateOff;
        Controller_DWork->temporalCounter_i1_j = 0U;

        /* Outport: '<Root>/Blink' */
        /* Entry 'StateOff': '<S2>:205' */
        Controller_Y->Blink = false;
      } else {
        /* Outport: '<Root>/Blink' */
        Controller_Y->Blink = true;
      }
    }
  }

  /* End of Chart: '<S1>/Blinking' */

  /* Chart: '<S1>/EchoCapture' incorporates:
   *  Memory: '<S3>/Memory2'
   */
  if (Controller_DWork->temporalCounter_i1 < MAX_uint32_T) {
    Controller_DWork->temporalCounter_i1++;
  }

  /* Gateway: Controller/EchoCapture */
  /* During: Controller/EchoCapture */
  if (Controller_DWork->is_active_c2_Controller == 0U) {
    /* Entry: Controller/EchoCapture */
    Controller_DWork->is_active_c2_Controller = 1U;

    /* Entry Internal: Controller/EchoCapture */
    /* Entry Internal 'EchoDurationCapture': '<S5>:235' */
    /* Transition: '<S5>:414' */
    Controller_DWork->is_EchoDurationCapture = Contro_IN_waitingCaptureRequest;

    /* Entry 'waitingCaptureRequest': '<S5>:380' */
    Controller_DWork->counter = 0U;
    Controller_B->errorFlag = false;
  } else {
    /* During 'EchoDurationCapture': '<S5>:235' */
    switch (Controller_DWork->is_EchoDurationCapture) {
     case Con_IN_calculateDurationAverage:
      /* During 'calculateDurationAverage': '<S5>:411' */
      /* Transition: '<S5>:413' */
      Controller_DWork->is_EchoDurationCapture = Contro_IN_waitingCaptureRequest;

      /* Entry 'waitingCaptureRequest': '<S5>:380' */
      Controller_DWork->counter = 0U;
      Controller_B->errorFlag = false;
      break;

     case Contro_IN_calculateEchoDuration:
      /* During 'calculateEchoDuration': '<S5>:520' */
      if (Controller_B->errorFlag && (Controller_DWork->temporalCounter_i1 >=
           300U)) {
        /* Transition: '<S5>:541' */
        /* Transition: '<S5>:543' */
        /* Transition: '<S5>:544' */
        /* Exit 'calculateEchoDuration': '<S5>:520' */
        Controller_DWork->is_EchoDurationCapture =
          Contro_IN_waitingCaptureRequest;

        /* Entry 'waitingCaptureRequest': '<S5>:380' */
        Controller_DWork->counter = 0U;
        Controller_B->errorFlag = false;
      } else {
        if ((!Controller_DWork->Memory2_PreviousInput_i) &&
            (!Controller_B->errorFlag)) {
          /* Transition: '<S5>:515' */
          /* Exit 'calculateEchoDuration': '<S5>:520' */
          Controller_DWork->is_EchoDurationCapture = Controller_IN_exitState;

          /* Entry 'exitState': '<S5>:516' */
          Controller_B->echoAverageDuration += (real_T)
            Controller_DWork->temporalCounter_i1 * 100.0;
        }
      }
      break;

     case Controller_IN_chech_N_Trigger:
      /* During 'chech_N_Trigger': '<S5>:545' */
      if (Controller_DWork->counter >= 4) {
        /* Transition: '<S5>:524' */
        Controller_DWork->is_EchoDurationCapture =
          Con_IN_calculateDurationAverage;

        /* Entry 'calculateDurationAverage': '<S5>:411' */
        Controller_B->echoAverageDuration /= 4.0;
        Controller_B->echoDurationCalculated = true;
      } else {
        if (Controller_DWork->temporalCounter_i1 >= 300U) {
          /* Transition: '<S5>:546' */
          Controller_DWork->is_EchoDurationCapture = Controller_IN_triggerOn;
          Controller_DWork->temporalCounter_i1 = 0U;

          /* Outport: '<Root>/Trigger' */
          /* Entry 'triggerOn': '<S5>:512' */
          Controller_Y->Trigger = true;
        }
      }
      break;

     case Controller_IN_checkEchoOn:
      /* During 'checkEchoOn': '<S5>:518' */
      if (Controller_DWork->Memory2_PreviousInput_i) {
        /* Transition: '<S5>:521' */
        /* Exit 'checkEchoOn': '<S5>:518' */
        Controller_DWork->echoOffDuraion = (real_T)
          Controller_DWork->temporalCounter_i1 * 0.1;
        Controller_DWork->is_EchoDurationCapture =
          Contro_IN_calculateEchoDuration;
        Controller_DWork->temporalCounter_i1 = 0U;

        /* Entry 'calculateEchoDuration': '<S5>:520' */
      } else if (Controller_DWork->echoOffDuraion > 3.0) {
        /* Transition: '<S5>:519' */
        /* Exit 'checkEchoOn': '<S5>:518' */
        Controller_DWork->echoOffDuraion = (real_T)
          Controller_DWork->temporalCounter_i1 * 0.1;
        Controller_DWork->is_EchoDurationCapture = Controller_IN_echoError;
        Controller_DWork->temporalCounter_i1 = 0U;

        /* Entry 'echoError': '<S5>:517' */
        Controller_DWork->counter = 0U;
        Controller_B->errorFlag = true;
      } else {
        Controller_DWork->echoOffDuraion = (real_T)
          Controller_DWork->temporalCounter_i1 * 0.1;
      }
      break;

     case Controller_IN_echoError:
      /* During 'echoError': '<S5>:517' */
      /* Transition: '<S5>:513' */
      if (Controller_DWork->temporalCounter_i1 >= 300U) {
        /* Transition: '<S5>:538' */
        Controller_DWork->is_EchoDurationCapture = Controller_IN_triggerOn;
        Controller_DWork->temporalCounter_i1 = 0U;

        /* Outport: '<Root>/Trigger' */
        /* Entry 'triggerOn': '<S5>:512' */
        Controller_Y->Trigger = true;
      }
      break;

     case Controller_IN_exitState:
      /* During 'exitState': '<S5>:516' */
      /* Transition: '<S5>:430' */
      /* Transition: '<S5>:531' */
      Controller_DWork->is_EchoDurationCapture = Controller_IN_chech_N_Trigger;
      Controller_DWork->temporalCounter_i1 = 0U;
      break;

     case Controller_IN_triggerOn:
      /* During 'triggerOn': '<S5>:512' */
      if (Controller_DWork->temporalCounter_i1 >= 100U) {
        /* Outport: '<Root>/Trigger' */
        /* Transition: '<S5>:508' */
        /* Exit 'triggerOn': '<S5>:512' */
        Controller_Y->Trigger = false;
        tmp = (int32_T)(Controller_DWork->counter + 1U);
        if (Controller_DWork->counter + 1U > 255U) {
          tmp = 255;
        }

        Controller_DWork->counter = (uint8_T)tmp;
        Controller_DWork->is_EchoDurationCapture = Controller_IN_checkEchoOn;
        Controller_DWork->temporalCounter_i1 = 0U;

        /* Entry 'checkEchoOn': '<S5>:518' */
        Controller_DWork->echoOffDuraion = (real_T)
          Controller_DWork->temporalCounter_i1 * 0.1;
      }
      break;

     default:
      /* During 'waitingCaptureRequest': '<S5>:380' */
      if (Controller_B->captureRequest) {
        /* Transition: '<S5>:403' */
        /* Exit 'waitingCaptureRequest': '<S5>:380' */
        Controller_B->echoDurationCalculated = false;
        Controller_B->echoAverageDuration = 0.0;
        Controller_DWork->is_EchoDurationCapture = Controller_IN_triggerOn;
        Controller_DWork->temporalCounter_i1 = 0U;

        /* Outport: '<Root>/Trigger' */
        /* Entry 'triggerOn': '<S5>:512' */
        Controller_Y->Trigger = true;
      }
      break;
    }
  }

  /* End of Chart: '<S1>/EchoCapture' */

  /* Update for Memory: '<S4>/Memory2' */
  Controller_DWork->Memory2_PreviousInput = Controller_B->echoDurationCalculated;

  /* Update for Memory: '<S4>/Memory1' */
  Controller_DWork->Memory1_PreviousInput = Controller_B->echoAverageDuration;

  /* Update for Memory: '<S4>/Memory3' */
  Controller_DWork->Memory3_PreviousInput = Controller_B->errorFlag;

  /* Update for Memory: '<S3>/Memory2' incorporates:
   *  Inport: '<Root>/Echo'
   */
  Controller_DWork->Memory2_PreviousInput_i = Controller_U->Echo;
}

/* Model initialize function */
void Controller_initialize(RT_MODEL_Controller *const Controller_M,
  ExternalInputs_Controller *Controller_U, ExternalOutputs_Controller
  *Controller_Y)
{
  BlockIO_Controller *Controller_B = Controller_M->blockIO;
  D_Work_Controller *Controller_DWork = Controller_M->dwork;

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) Controller_B), 0,
                sizeof(BlockIO_Controller));

  /* states (dwork) */
  (void) memset((void *)Controller_DWork, 0,
                sizeof(D_Work_Controller));

  /* external inputs */
  Controller_U->Echo = false;

  /* external outputs */
  (void) memset((void *)Controller_Y, 0,
                sizeof(ExternalOutputs_Controller));

  /* SystemInitialize for Chart: '<S1>/MainTask' */
  Controller_DWork->is_mainTask = Controller_IN_NO_ACTIVE_CHILD;
  Controller_DWork->is_wakeEvery1sec = Controller_IN_NO_ACTIVE_CHILD;
  Controller_DWork->temporalCounter_i1_i = 0U;
  Controller_DWork->is_active_c3_Controller = 0U;
  Controller_DWork->taskCompleted = false;
  Controller_B->captureRequest = false;
  Controller_B->updateDistance = false;

  /* SystemInitialize for Outport: '<Root>/errorWarning' incorporates:
   *  Chart: '<S1>/MainTask'
   */
  Controller_Y->errorWarning = false;

  /* SystemInitialize for Chart: '<S1>/Blinking' */
  Controller_DWork->is_Blinking = Controller_IN_NO_ACTIVE_CHILD;
  Controller_DWork->temporalCounter_i1_j = 0U;
  Controller_DWork->is_active_c1_Controller = 0U;
  Controller_DWork->offTime = 0U;
  Controller_DWork->onTime = 0U;

  /* SystemInitialize for Outport: '<Root>/Blink' incorporates:
   *  Chart: '<S1>/Blinking'
   */
  Controller_Y->Blink = false;

  /* SystemInitialize for Chart: '<S1>/EchoCapture' */
  Controller_DWork->is_EchoDurationCapture = Controller_IN_NO_ACTIVE_CHILD;
  Controller_DWork->temporalCounter_i1 = 0U;
  Controller_DWork->is_active_c2_Controller = 0U;
  Controller_DWork->counter = 0U;

  /* SystemInitialize for Outport: '<Root>/Trigger' incorporates:
   *  Chart: '<S1>/EchoCapture'
   */
  Controller_Y->Trigger = false;

  /* SystemInitialize for Chart: '<S1>/EchoCapture' */
  Controller_B->echoDurationCalculated = false;
  Controller_B->echoAverageDuration = 0.0;
  Controller_B->errorFlag = false;
}

/* Model terminate function */
void Controller_terminate(RT_MODEL_Controller *const Controller_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(Controller_M);
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
