#include "vex.h"
#include "Share.h"
using namespace vex;

int Stop_Collect_Bottom = 100;
int Stop_Collect_Top = 100;
bool switch_ = false;

const float Hindering_factor = 0.4;

void direction_controlling()
{
  while (Share::ON)
  {
    Motor_left_Front.spin(
        forward, Controller1.Axis1.value() * Hindering_factor + Controller1.Axis2.value(),
        velocityUnits::pct);
    Motor_left_back.spin(
        forward, Controller1.Axis1.value() * Hindering_factor + Controller1.Axis2.value(),
        velocityUnits::pct);
    Motor_right_Front.spin(
        reverse, Controller1.Axis2.value() - Controller1.Axis1.value() * Hindering_factor,
        velocityUnits::pct);
    Motor_right_Back.spin(
        reverse, Controller1.Axis2.value() - Controller1.Axis1.value() * Hindering_factor,
        velocityUnits::pct);
    wait(10, msec);
  }
}

void collect()
{
  while (Share::ON)
  {
    if (Controller1.ButtonL1.pressing())
    {
      Motor_left_Arm.spin(forward, 100, velocityUnits::pct);
      Motor_right_Arm.spin(reverse, 100, velocityUnits::pct);
    }
    else if (Controller1.ButtonR1.pressing())
    {
      Motor_left_Arm.spin(forward, -100, velocityUnits::pct);
      Motor_right_Arm.spin(reverse, -100, velocityUnits::pct);
    }
    else if (switch_ == false)
    {
      Motor_left_Arm.stop();
      Motor_right_Arm.stop();
    }
    wait(10, msec);
  }
}

void Up_down()
{
  while (Share::ON)
  {
    if (Controller1.ButtonL2.pressing())
    {
      Collect_Bottom.spin(reverse, Stop_Collect_Bottom * 0.8,
                          velocityUnits::pct);
      Collect_Top.spin(forward, Stop_Collect_Top * 0.8, velocityUnits::pct);
    }
    else if (Controller1.ButtonR2.pressing())
    {
      Collect_Bottom.spin(reverse, -1 * Stop_Collect_Bottom * 0.8,
                          velocityUnits::pct);
      Collect_Top.spin(forward, -1 * Stop_Collect_Top * 0.8,
                       velocityUnits::pct);
    }
    else if (switch_ == false)
    {
      Collect_Bottom.stop();
      Collect_Top.stop();
    }
    wait(10, msec);
  }
}

void Stop_Up_down()
{
  while (Share::ON)
  {
    if (Controller1.ButtonUp.pressing())
    {
      Stop_Collect_Top = 0;
    }
    else
    {
      Stop_Collect_Top = 100;
    }
    if (Controller1.ButtonDown.pressing())
    {
      Stop_Collect_Bottom = 0;
    }
    else
    {
      Stop_Collect_Bottom = 100;
    }
    wait(10, msec);
  }
}

void Push()
{
  while (Share::ON)
  {
    if (Controller1.Axis3.value() != 0)
    {
      switch_ = true;
      Collect_Bottom.spin(reverse, Controller1.Axis3.value(),
                          velocityUnits::pct);
      Collect_Bottom.spin(reverse, Controller1.Axis3.value(),
                          velocityUnits::pct);
      Motor_left_Arm.spin(forward, Controller1.Axis3.value(),
                          velocityUnits::pct);
      Motor_right_Arm.spin(reverse, Controller1.Axis3.value(),
                           velocityUnits::pct);
    }
    else
    {
      switch_ = false;
    }
    wait(10, msec);
  }
}

void usercontrol(void)
{
  Share::ON = true;
  // 创建线程
  thread direction_controlling_(direction_controlling);
  thread collect_(collect);
  thread Up_down_(Up_down);
  thread Stop_Up_down_(Stop_Up_down);
  thread Push_(Push);

  //启动线程
  direction_controlling_.join();
  collect_.join();
  Up_down_.join();
  Stop_Up_down_.join();
  Push_.join();
}