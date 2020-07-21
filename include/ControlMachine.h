#include "vex.h"
#include "usercontrol.h"
#include "autonomous.h"
#include <thread>

using namespace vex;

void autonomous(){
  
}

void usercontrol(){
  //创建线程
  thread direction_control(direction_controlling);
  thread Catch_hand_process(Catch_hand);
  thread Up_arm_process(Up_arm);
  //启动线程
  direction_control.join();
  Catch_hand_process.join();
  Up_arm_process.join();
}