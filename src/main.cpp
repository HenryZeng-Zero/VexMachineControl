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
// Motor_left           motor         1               
// Motor_right          motor         10              
// Motor_arm            motor         8               
// Motor_hand           motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "ControlMachine.h"
using namespace vex;
competition Competition;


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
}
