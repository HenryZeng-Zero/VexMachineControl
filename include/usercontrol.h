#include "vex.h"
using namespace vex;
bool Motor_arm_lock = false;

void Catch_hand()
{
  while (true)
  {
    if (Controller1.ButtonR1.pressing())
    {
      Motor_hand.spin(forward, 30, vex::velocityUnits::pct);
      task::sleep(200);
    }
    else if (Controller1.ButtonR2.pressing())
    {
      Motor_hand.spin(forward, -30, vex::velocityUnits::pct);
      Motor_hand.setTimeout(200, timeUnits::sec);
      task::sleep(200);
    }
    else
    {
      Motor_hand.stop(brakeType::hold);
    }
  }
}

void Up_arm()
{
  while (true)
  {
    if (Controller1.ButtonX.pressing())
    {
      Motor_arm_lock = false;
      Motor_arm.spin(forward, 30, vex::velocityUnits::pct);
    }
    else if (Controller1.ButtonB.pressing())
    {
      Motor_arm_lock = false;
      Motor_arm.spin(forward, -30, vex::velocityUnits::pct);
    }
    else
    {
      if (Motor_arm_lock)
      {
        Motor_arm.stop(brakeType::hold);
      }
      else
      {
        Motor_arm.stop(brakeType::coast);
        task::sleep(50);
        Motor_arm_lock = true;
      }
    }
  }
}

void direction_controlling()
{
  while (true)
  {
    Motor_left.spin(forward, Controller1.Axis1.value() + Controller1.Axis2.value(), velocityUnits::pct);
    Motor_right.spin(reverse, Controller1.Axis2.value() - Controller1.Axis1.value(), velocityUnits::pct);
  }
}