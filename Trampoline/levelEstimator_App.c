/**
 * @file levelEstimator_App.c
 * @author Muhammad Ibrahim (muhammadibrahim.muhammad@studenti.polito.it)
 * @brief  this file integrate the controller and sensor models to trampoline OS.
 *         simulating the behavior of the controller at each distance reading 
 *         from the ultrasonic sensor.
 * @version 2.1
 * @date 2021-06-19
 * 
 * @copyright Copyright (c) 2021
 */


/* UltraSonic Sensor Model Headers */
#include "UltraSonic_Sensor.h"
#include "rtwtypes.h"

/* Controller Model Headers */
#include "Controller.h"


/* Trampoline Headers */
#include <stdio.h>
#include "tpl_os.h"

/* UltraSonoc Sensor Model Data Definition */
static RT_MODEL rtM_;
static RT_MODEL *const UltraSonicSensor_rtMPtr =&rtM_;/* Real-time model */
static DW rtDW;                                       /* Observable states */
static ExtU UltraSonicSensor_In;                      /* External inputs */
static ExtY UltraSonicSensor_Out;                     /* External outputs */

/* Controller Model Data Definitions */
static RT_MODEL_Controller Controller_M_;
static RT_MODEL_Controller *const Controller_MPtr =
    &Controller_M_;                             /* Real-time model */
static BlockIO_Controller Controller_B;         /* Observable signals */
static D_Work_Controller Controller_DWork;      /* Observable states */
static ExternalInputs_Controller Controller_In;  /* External inputs */
static ExternalOutputs_Controller Controller_Out; /* External outputs */

DeclareAlarm(alarm_ControllerStep);
DeclareAlarm(alarm_UltraSonicStep);
DeclareAlarm(alarm_SimulationStep);
DeclareAlarm(stopper);


/* BSW fuction Decleartion */
void BSW_CheckControllerState(uint8_T TaskState, uint32_T *timeStampPtr);
void BSW_ControllerCheckBlinkingOut(boolean_T updateDistanceSiganl,
                                    boolean_T errorSiganl, uint16_T BlinkingTime,
                                    uint32_T *timeStampPtr);

int main(void)
{
  /* UltraSonic Sensor Model reference */
  UltraSonicSensor_rtMPtr->dwork = &rtDW;

  /* Controller Model reference */
  Controller_MPtr->dwork = &Controller_DWork;
  Controller_MPtr->blockIO = & Controller_B;

  /* Initialize UltraSonic Sensor model */
  UltraSonic_Sensor_initialize(UltraSonicSensor_rtMPtr, &UltraSonicSensor_In,
                               &UltraSonicSensor_Out);

  /* Initialize Controller Model */
  Controller_initialize(Controller_MPtr, &Controller_In, &Controller_Out);

  StartOS(OSDEFAULTAPPMODE);
  return 0;
}


/*
 * Controller Step Task 
 * used to update the controller at each step
 */
TASK(Controller_Step){
 
 /* connect echo input of the controller from the ultrasonic sensor */
 Controller_In.Echo = UltraSonicSensor_Out.Echo;
 
 /* call controller step function */
 Controller_step(Controller_MPtr, &Controller_In, &Controller_Out); 
 
 /* terminate the task */
 TerminateTask();
}

/*
 * Ultrasonic Sensor Step Task
 * used to update the Ultrasonic Sensor at each step
 */
TASK(UltraSonic_Sensor_Step)
{
 /* connect the trigger input of the sensot from the conntroller */
 UltraSonicSensor_In.Trigger = Controller_Out.Trigger;
 
 /* call the ultrasnoic step function */
 UltraSonic_Sensor_step(UltraSonicSensor_rtMPtr, &UltraSonicSensor_In, &UltraSonicSensor_Out);
 
 /* terminate the task */                        
 TerminateTask();
}

/*
 * Simulation Task
 * used to update apply the test set for simulation
 */
TASK(SimulationStep){
 /* 
  * definition of timestamp 
  * used to hold the task step time
  */
 static uint32_T timeStamp = 0;
 
 /* start of the simulation */
 if (timeStamp == 0)
 {
   printf("*------------ Start of Controller Simulation -----------*\r\n");
   printf("timeStamp: %d msec \r\n\n", timeStamp);
 }

 /* Application of Test Set
  * changing the distance of the sensor
  */
 if (timeStamp == 1) {
   UltraSonicSensor_In.distance = 0;  /* sensor disconnected */
 } else if (timeStamp == 1000) {
   UltraSonicSensor_In.distance = 40; /* distance 40 cm */
 } else if (timeStamp == 2000) {
   UltraSonicSensor_In.distance = 400; /* distance 400 cm */
 }else if (timeStamp == 3000) {
   UltraSonicSensor_In.distance = 100; /* distance 100 cm */
 }else if (timeStamp == 4000) {
   UltraSonicSensor_In.distance = 0;   /* sensor disconnected */
 }else if (timeStamp == 5000) {
   UltraSonicSensor_In.distance = 90;  /* distance 90 cm */ 
 }else if (timeStamp == 6000) {
   UltraSonicSensor_In.distance = 200; /* distance 200 cm */
 }else if (timeStamp == 7000) {
   UltraSonicSensor_In.distance = 7;   /* distance 7 cm */
 }

 /*
  * Call of BSW_ControllerCheckBlinkingOut Function
  * use to check the output blink of the controller 
  */
 BSW_ControllerCheckBlinkingOut(Controller_B.updateDistance,
                                Controller_Out.errorWarning,
                                Controller_DWork.onTime, &timeStamp);

 /*
  * Call of BSW_ControllerCheckBlinkingOut Function.
  * use only to check the internal states of the controller.
  * commented in defult usage.
  */
 /*BSW_CheckControllerState(Controller_DWork.is_mainTask, &timeStamp);*/
 
 /* increament the timestamp at each step */
 timeStamp++; 

 /* terminate the task at the end of the os call */
 TerminateTask();
}

TASK(stop)
{
  CancelAlarm(alarm_UltraSonicStep);
  CancelAlarm(alarm_ControllerStep);
  CancelAlarm(alarm_SimulationStep);
  UltraSonic_Sensor_terminate(UltraSonicSensor_rtMPtr);
  Controller_terminate(Controller_MPtr);
  ShutdownOS(E_OK);
  TerminateTask();
}

/**------------------------- BSW Supported Functions -------------------------**/

/*
 * @name   BSW_ControllerCheckState
 * @brief  function to print the internal state transition of the controller
 * @param  controller state
 * @param  refernce to timestamp
 * @return non
 */
 void BSW_CheckControllerState(uint8_T TaskState, uint32_T * timeStampPtr)
 {
   static uint8_T NextTaskState = Controller_IN_NO_ACTIVE_CHILD;

   /* check if state transition happened*/
   if (TaskState != NextTaskState)
   {
     printf("*------ BSW_CheckControllerStateStates is Active! ------*\r\n");
     printf("timeStamp: %d msec\r\n", *timeStampPtr);
     switch (TaskState)
     {
     case Controller_IN_InitialState:
       printf("Current State: mainTaskState_InitialState\r\n");
       break;
     case Controller_IN_requestOn:
       printf("Current State: mainTaskState_requestOn\r\n");
       break;
     case Controller_IN_requestOff:
       printf("Current State: mainTaskState_requestOff\r\n");
       break;
     case Controll_IN_DistanceCalcualtion:
       printf("Current State: mainTaskState_DistanceCalcualtion\r\n");
       printf("distance = %.1f\r\n", Controller_B.distance);
       break;
     case Control_IN_CalcualtionexitState:
       printf("Current State: mainTaskState_exitState\r\n");
       break;
     case Controll_IN_waitingErrorHandler:
       printf("Current State: mainTaskState_waitingErrorHandler\r\n");
       break;
     case Controller_IN_waitWakeUp:
       printf("Current State: mainTaskState_waitWakeUp\r\n");
       break;
     default:
       printf("error mainTask\r\n");
       break;
     }
     printf("*-------------------------------------------------------*\r\n\n");
   }
   NextTaskState = TaskState;
}

/*
 * @name   BSW_ControllerCheckBlinkingOut
 * @brief  function to print the controller Blinking Output based on distance
calculated
 * @param  controller internal distance update signal
 * @param  controller error signal
 * @param  calculated blinking duration
 * @param  refernce to timestamp * @param  refernce to timestamp
 * @return non
 */
void BSW_ControllerCheckBlinkingOut(boolean_T updateDistanceSiganl, boolean_T errorSiganl,
                                    uint16_T BlinkingTime,
                                    uint32_T *timeStampPtr)
{
  /* check if blinking task is updated*/
  if (updateDistanceSiganl == true)
  {
    printf("*------ BSW_ControllerCheckBlinkingOut is Active! ------*\r\n");
    printf("timeStamp: %.3f sec\r\n", ((*timeStampPtr) / 100.0));
    if (BlinkingTime >= 10 && BlinkingTime <= 100)
    {
      printf("Blinking_10Hz\r\n");
      printf("Duty Cycle: %d\r\n", BlinkingTime);
    } else if (BlinkingTime == 250) {
      printf("Blinking_2Hz\r\n");
    } else if (BlinkingTime == 500) {
      printf("Blinking_1Hz\r\n");
    } else {
      printf("error\r\n");
    }
    printf("*-------------------------------------------------------*\r\n\n");
  }
  
  /* check if error handling is running*/
  if (errorSiganl == true)
  {
    printf("*------ BSW_ControllerCheckBlinkingOut is Active! ------*\r\n");
    printf("timeStamp: %.3f sec\r\n", ((*timeStampPtr) / 100.0));
    printf("Error: Sensor is not connected. \r\n");
    printf("Blinking_1Hz\r\n");
    printf("*------------------------------------------------------*\r\n\n");
  }
}

/**---------------------------------------------------------------------------**/