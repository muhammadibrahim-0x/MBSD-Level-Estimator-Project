# MBSD-Level-Esitmator-Project
The aim for the project is to implement a level indicator, which is composed of Controller and Ultrasonic sensor.
### Description
 The ranging estimator measures the distance (by taking 4 consecutive measures and computing the average), and generates an output as follows: 
  - In case the measure is in between 10cm and 100 cm the Level output blinks with frequency 10 Hz and duty cycle from 10% to 100% depending on the measurement (10cm=10%, 100cm=100%)
  - In case the measurement is outside below 10cm or higher than 100 cm the Level output blinks with frequency 2 Hz and duty cycle 50%
  - In case the sensor is disconnected (no measure is received), the Level output blinks with frequency 1 Hz and duty cycle 50%
  

### Project subdirectories 
- Simulink Project Dir : contains the model for the controller, the ultrasonic sensor and the testbench.
- C Code Dir: the generated code using the *Embedded Coder*.
- GoogleTest: the test vector and the test application need to test the controller using *Gtest*.
- Trampoline Dir: integrate the controller code with Trampoline OS to bed simulated as posix application.
- Ardunio Dir: incuded the model for depolying the controller in Arduino as full expert mode.
