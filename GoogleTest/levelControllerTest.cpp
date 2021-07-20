/*
 * @file levelControllerTest.cpp
 * @brief test unit for the controller
 *  MODEL-BASED SOFTWARE DESIGN
 *  LevelEstimator Project - A.Y. 2020/21
 * 
 * @auther Muhammad Ibrahim - muhammadibrahim.muhammad@studenti.polito.it
 */

extern "C"
{
#include "../Controller.h"
}
#include <gtest/gtest.h>

/*  Definitions */
static RT_MODEL_Controller Controller_M_;
static RT_MODEL_Controller *const Controller_MPtr = &Controller_M_; /* Real-time model */
static BlockIO_Controller Controller_B;                             /* Observable signals */
static D_Work_Controller Controller_DWork;                          /* Observable states */
static ExternalInputs_Controller Controller_U;                      /* External inputs */
static ExternalOutputs_Controller Controller_Y;                     /* External outputs */

/* Definition of used MACROS */
#define LE_UC1_FIRIST_CYCLE 0U         /* start cycle of UC1 */
#define LE_UC1_LAST_CYCLE   9999U      /* end cycle of UC1 */
#define LE_UC2_FIRIST_CYCLE 10000U     /* start cycle of UC2 */
#define LE_UC2_LAST_CYCLE   39999U     /* end cycle of UC2 */
#define LE_UC3_FIRIST_CYCLE 40000U     /* start cycle of UC3 */
#define LE_UC3_LAST_CYCLE   109999U    /* end cycle of UC3 */
#define LE_UC4_FIRIST_CYCLE 110000U    /* start cycle of UC4 */
#define LE_UC4_LAST_CYCLE   179999U    /* end cycle of UC4 */
#define LE_UC5_FIRIST_CYCLE 180000U    /* start cycle of UC5 */
#define LE_UC5_LAST_CYCLE   200000U    /* end cycle of UC5 */

/* declearation of test vector structure */
typedef struct
{
 boolean_T echoIn[200006];
 boolean_T blinkOut[200006];
 boolean_T triggerOut[200006];
 boolean_T warningOut[200006];
} testVector;

/* declearation of readTestVector fuction */
void readTestVector(testVector *thisTesVector, uint32_t firstCycle, uint32_t lastCycle);

/* 
 * TEST of UC ID: LE_UC1
 *   Description: testing the avergae of the 4 reading cycle.
 *   Test Set: {5, 10, 15, 20} 
 */
TEST(levelControllerTest, FT_LE_UC1)
{
 /* decleare testVector instance to holde test vector of LE_UC1  */
 testVector LE_UC1_testVector;

 /* read test vector from input test set */
 readTestVector(&LE_UC1_testVector, LE_UC1_FIRIST_CYCLE, LE_UC1_LAST_CYCLE);

 /* decleare model reference */
 RT_MODEL_Controller *const Controller_M = Controller_MPtr;

 /* Pack model data into RTM */
 Controller_M->blockIO = &Controller_B;
 Controller_M->dwork = &Controller_DWork;

 /* Initialize model */
 Controller_initialize(Controller_M, &Controller_U, &Controller_Y);

 fprintf(stderr, "Start of the Testing UC ID: LE_UC1!\n");

 /* 
  * loop the duration 100000 step 
  * duration: 1sec at step size of 1e-4 
  */
 for (uint32_T i = LE_UC1_FIRIST_CYCLE; i <= LE_UC1_LAST_CYCLE; i++)
 {
  /* assign input echo for the controller from the test vector */ 
  Controller_U.Echo = LE_UC1_testVector.echoIn[i];
  
  /* run the controller for 1 step*/
  Controller_step(Controller_M, &Controller_U, &Controller_Y);
  
  /* check the intigrity of the controller blink out */
  ASSERT_EQ(
      LE_UC1_testVector.blinkOut[i],
      Controller_Y.Blink)
      << "Error in blinking at step: " << i << "e-4\n";
  
  /* check the intigrity of the controller trigger out */
  ASSERT_EQ(
      LE_UC1_testVector.triggerOut[i],
      Controller_Y.Trigger)
      << "Error in trigger at step: " << i << "e-4\n";
  
  /* check the intigrity of the controller warning out */
  ASSERT_EQ(
      LE_UC1_testVector.warningOut[i],
      Controller_Y.errorWarning)
      << "Error in warning at step: " << i << "e-4\n";
  }
   /* terminate the cantroller */
   Controller_terminate(Controller_M);
}

/* 
 * TEST of UC ID: LE_UC2
 *   testing distance boundry range (10cm to 100m).
 *   Test Set: distance =  {19, 50, 91}
 */
TEST(levelControllerTest, FT_LE_UC2)
{
 /* decleare testVector instance to holde test vector of LE_UC2  */
 testVector LE_UC2_testVector;

 /* read test vector from input test set */
 readTestVector(&LE_UC2_testVector, LE_UC2_FIRIST_CYCLE, LE_UC2_LAST_CYCLE);

 /* decleare model reference */
 RT_MODEL_Controller *const Controller_M = Controller_MPtr;

 /* Pack model data into RTM */
 Controller_M->blockIO = &Controller_B;
 Controller_M->dwork = &Controller_DWork;

 /* Initialize model */
 Controller_initialize(Controller_M, &Controller_U, &Controller_Y);

 fprintf(stderr, "Start of the Testing UC ID: LE_UC2!\n");

 /* 
  * loop the duration 400000 step 
  * duration: 1sec at step size of 1e-4 
  */
 for (uint32_T i = LE_UC2_FIRIST_CYCLE; i <= LE_UC2_LAST_CYCLE; i++)
 {
  /* assign input echo for the controller from the test vector */
  Controller_U.Echo = LE_UC2_testVector.echoIn[i];

  /* run the controller for 1 step*/
  Controller_step(Controller_M, &Controller_U, &Controller_Y);

  /* check the intigrity of the controller blink out */
  ASSERT_EQ(
      LE_UC2_testVector.blinkOut[i],
      Controller_Y.Blink)
      << "Error in blinking at step: " << i << "e-4\n";

  /* check the intigrity of the controller trigger out */
  ASSERT_EQ(
      LE_UC2_testVector.triggerOut[i],
      Controller_Y.Trigger)
      << "Error in trigger at step: " << i << "e-4\n";

  /* check the intigrity of the controller warning out */
  ASSERT_EQ(
      LE_UC2_testVector.warningOut[i],
      Controller_Y.errorWarning)
      << "Error in warning at step: " << i << "e-4\n";
 }
 /* terminate the cantroller */
 Controller_terminate(Controller_M);
}

/* 
 * TEST of UC ID: LE_UC3
 *   Description: testing distance boundry range (3cm to 10cm)
 *   Test Set: distance =  [ {2, 3, 4} , 7 ,  {9, 10, 11} ]
 */
TEST(levelControllerTest, FT_LE_UC3)
{
 /* decleare testVector instance to holde test vector of LE_UC3  */
 testVector LE_UC3_testVector;

 /* read test vector from input test set */
 readTestVector(&LE_UC3_testVector, LE_UC3_FIRIST_CYCLE, LE_UC3_LAST_CYCLE);

 /* decleare model reference */
 RT_MODEL_Controller *const Controller_M = Controller_MPtr;

 /* Pack model data into RTM */
 Controller_M->blockIO = &Controller_B;
 Controller_M->dwork = &Controller_DWork;

 /* Initialize model */
 Controller_initialize(Controller_M, &Controller_U, &Controller_Y);

 fprintf(stderr, "Start of the Testing UC ID: LE_UC3!\n");

 /* 
  * loop the duration 800000 step 
  * duration: 1sec at step size of 1e-4 
  */
 for (uint32_T i = LE_UC3_FIRIST_CYCLE; i <= LE_UC3_LAST_CYCLE; i++)
 {
  /* assign input echo for the controller from the test vector */
  Controller_U.Echo = LE_UC3_testVector.echoIn[i];

  /* run the controller for 1 step*/
  Controller_step(Controller_M, &Controller_U, &Controller_Y);

  /* check the intigrity of the controller blink out */
  ASSERT_EQ(
      LE_UC3_testVector.blinkOut[i],
      Controller_Y.Blink)
      << "Error in blinking at step: " << i << "e-4\n";

  /* check the intigrity of the controller trigger out */
  ASSERT_EQ(
      LE_UC3_testVector.triggerOut[i],
      Controller_Y.Trigger)
      << "Error in trigger at step: " << i << "e-4\n";

  /* check the intigrity of the controller warning out */
  ASSERT_EQ(
      LE_UC3_testVector.warningOut[i],
      Controller_Y.errorWarning)
      << "Error in warning at step: " << i << "e-4\n";
 }
 /* terminate the cantroller */
 Controller_terminate(Controller_M);
}

/* 
 * TEST of UC ID: LE_UC4
 *   Description: testing distance boundry range (100cm to 400cm)
 *   Test Set: distance =  [ {99, 100 , 101} , 200 ,  {399, 400, 401} ]
 */
TEST(levelControllerTest, FT_LE_UC4)
{
 /* decleare testVector instance to holde test vector of LE_UC4  */
 testVector LE_UC4_testVector;

 /* read test vector from input test set */
 readTestVector(&LE_UC4_testVector, LE_UC4_FIRIST_CYCLE, LE_UC4_LAST_CYCLE);

 /* decleare model reference */
 RT_MODEL_Controller *const Controller_M = Controller_MPtr;

 /* Pack model data into RTM */
 Controller_M->blockIO = &Controller_B;
 Controller_M->dwork = &Controller_DWork;

 /* Initialize model */
 Controller_initialize(Controller_M, &Controller_U, &Controller_Y);

 fprintf(stderr, "Start of the Testing UC ID: LE_UC4!\n");

 /* 
  * loop the duration 800000 step 
  * duration: 1sec at step size of 1e-4 
  */
 for (uint32_T i = LE_UC4_FIRIST_CYCLE; i <= LE_UC4_LAST_CYCLE; i++)
 {
  /* assign input echo for the controller from the test vector */
  Controller_U.Echo = LE_UC4_testVector.echoIn[i];

  /* run the controller for 1 step*/
  Controller_step(Controller_M, &Controller_U, &Controller_Y);

  /* check the intigrity of the controller blink out */
  ASSERT_EQ(
      LE_UC4_testVector.blinkOut[i],
      Controller_Y.Blink)
      << "Error in blinking at step: " << i << "e-4\n";

  /* check the intigrity of the controller trigger out */
  ASSERT_EQ(
      LE_UC4_testVector.triggerOut[i],
      Controller_Y.Trigger)
      << "Error in trigger at step: " << i << "e-4\n";

  /* check the intigrity of the controller warning out */
  ASSERT_EQ(
      LE_UC4_testVector.warningOut[i],
      Controller_Y.errorWarning)
      << "Error in warning at step: " << i << "e-4\n";
 }
 /* terminate the cantroller */
 Controller_terminate(Controller_M);
}

/* 
 * TEST of UC ID: LE_UC5
 *   Description: testing sensor disconnect handling. 
 *    controller should signals a warning, and blinks at 1hz. after sensor
 *    is connected again, controller shoud back to normal mode.
 *   Test Set: distance =  distance =  {0, 205}
 */
TEST(levelControllerTest, FT_LE_UC5)
{
 /* decleare testVector instance to holde test vector of LE_UC5  */
 testVector LE_UC5_testVector;

 /* read test vector from input test set */
 readTestVector(&LE_UC5_testVector, LE_UC5_FIRIST_CYCLE, LE_UC5_LAST_CYCLE);

 /* decleare model reference */
 RT_MODEL_Controller *const Controller_M = Controller_MPtr;

 /* Pack model data into RTM */
 Controller_M->blockIO = &Controller_B;
 Controller_M->dwork = &Controller_DWork;

 /* Initialize model */
 Controller_initialize(Controller_M, &Controller_U, &Controller_Y);

 fprintf(stderr, "Start of the Testing UC ID: LE_UC5!\n");

 /* 
  * loop the duration 20000 step 
  * duration: 1sec at step size of 1e-5
  */
 for (uint32_T i = LE_UC5_FIRIST_CYCLE; i <= LE_UC5_LAST_CYCLE; i++)
 {
  /* assign input echo for the controller from the test vector */
  Controller_U.Echo = LE_UC5_testVector.echoIn[i];

  /* run the controller for 1 step*/
  Controller_step(Controller_M, &Controller_U, &Controller_Y);

  /* check the intigrity of the controller blink out */
  ASSERT_EQ(
      LE_UC5_testVector.blinkOut[i],
      Controller_Y.Blink)
      << "Error in blinking at step: " << i << "e-4\n";

  /* check the intigrity of the controller trigger out */
  ASSERT_EQ(
      LE_UC5_testVector.triggerOut[i],
      Controller_Y.Trigger)
      << "Error in trigger at step: " << i << "e-4\n";

  /* check the intigrity of the controller warning out */
  ASSERT_EQ(
      LE_UC5_testVector.warningOut[i],
      Controller_Y.errorWarning)
      << "Error in warning at step: " << i << "e-4\n";
 }
 /* terminate the cantroller */
 Controller_terminate(Controller_M);
}

/*
* @brief fuction to read the test vector form test set file.
* @parm pointer to reference the testvector
* @parm start cycle of the test duratuion
* @parm end cycle of the test duratuion
* @return non
*/
void readTestVector(testVector* thisTesVector, uint32_t firstCycle, uint32_t lastCycle)
{
 FILE *echoData;
 FILE *blinkData;
 FILE *triggerData;
 FILE *warningData;
 echoData = fopen("../../echo.txt", "r");
 blinkData = fopen("../../blink.txt", "r");
 triggerData = fopen("../../trigger.txt", "r");
 warningData = fopen("../../warning.txt", "r");
 if (echoData == NULL || blinkData == NULL || triggerData == NULL || warningData == NULL)
 {
  perror("Error while opening the file.\n");
  printf("Please ensure files: echo.txt, blink.text, trigger.txt, warning.txt are founded in the project path.\n");
  exit(EXIT_FAILURE);
 }
 for (uint32_T i = firstCycle; i <= lastCycle; i++)
 {
  fscanf(echoData, "%u",    (uint32_T *)&thisTesVector->echoIn[i]);
  fscanf(blinkData, "%u",   (uint32_T *)&thisTesVector->blinkOut[i]);
  fscanf(triggerData, "%u", (uint32_T *)&thisTesVector->triggerOut[i]);
  fscanf(warningData, "%u", (uint32_T *)&thisTesVector->warningOut[i]);
 }
 fclose(echoData);
 fclose(blinkData);
 fclose(triggerData);
 fclose(warningData);
}