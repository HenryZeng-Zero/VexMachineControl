#include "vex.h"
using namespace vex;
const double pi = 3.141592653;

const double deg_spin = 270 / 90;
void Change_direction(int degree = 0, int speed = 0, bool wait = false)
{
  Motor_left.spinFor(forward, degree * deg_spin + 20, vex::rotationUnits::deg, speed, velocityUnits::pct, wait);
  Motor_right.spinFor(forward, degree * deg_spin + 20, vex::rotationUnits::deg, speed, velocityUnits::pct, wait);
  task::sleep(1500);
}

double LengthTodeg = 0.0;
void GoOn(int length = 0, int speed = 0, bool wait = false)
{
  LengthTodeg = (length / (pi * 10)) * 360;
  Motor_left.spinFor(forward, LengthTodeg, vex::rotationUnits::deg, speed, velocityUnits::pct, wait);
  Motor_right.spinFor(reverse, LengthTodeg, vex::rotationUnits::deg, speed, velocityUnits::pct, wait);
  task::sleep(length * (100 / speed) * 25);
}

void ChangeHand(bool now = false, int power = 0)
{
  if (now)
  {
    Motor_hand.spin(forward, power, vex::velocityUnits::pct);
  }
  else
  {
    Motor_hand.spin(forward, (-1) * power, vex::velocityUnits::pct);
  }

  task::sleep(1000);
  Motor_hand.stop(vex::brakeType::hold);
}

void Up_Arm(bool up = false, int power = 0 ,int time = 1000)
{
  if (up)
  {
    Motor_arm.spin(forward, power, vex::velocityUnits::pct);
  }
  else
  {
    Motor_arm.spin(forward, (-1) * power, vex::velocityUnits::pct);
  }
  task::sleep(time);
  Motor_arm.stop(vex::brakeType::hold);
}

void init()
{
  ChangeHand(false, 30);
  Up_Arm(false, 30);
}