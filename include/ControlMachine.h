#include "vex.h"
#include "usercontrol.h"
#include "autonomous.h"
#include <thread>

using namespace vex;

void autonomous()
{
  init();

  GoOn(55, 30);

  Change_direction(90, 50);

  GoOn(45, 30);

  ChangeHand(true,30);

  Up_Arm(true,30,1800);

  GoOn(45, 30);

  Change_direction(90, 50);

  GoOn(35, 30);

  Up_Arm(false,30,500);

  ChangeHand(false,30);
  // ok
  GoOn(-45, 30);
}

void usercontrol()
{
  //创建线程
  thread direction_control(direction_controlling);
  thread Catch_hand_process(Catch_hand);
  thread Up_arm_process(Up_arm);
  //启动线程
  direction_control.join();
  Catch_hand_process.join();
  Up_arm_process.join();
}