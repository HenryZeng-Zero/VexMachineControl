/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\28799                                            */
/*    Created:      Mon Jul 20 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Motor_left_Front     motor         1               
// Motor_right_Front    motor         2               
// Motor_left_Arm       motor         5               
// Motor_right_Arm      motor         6               
// Motor_left_back      motor         3               
// Motor_right_Back     motor         11              
// Collect_Bottom       motor         7               
// Collect_Top          motor         8               
// Vision_bottom        vision        9               
// Inertial             inertial      10              
// Vision_top           vision        13              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "usercontrol.h"
#include "autonomous.h"

using namespace vex;
competition Competition;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Competition.drivercontrol(autonomous);
  
  // usercontrol();
  while (true) {
    wait(100, msec);
  }
}
