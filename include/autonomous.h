#include "vex.h"
using namespace vex;
void go_on(int degree = 0,int speed = 0){
  Motor_left.spin(forward,100,velocityUnits::pct);
  Motor_right.spin(reverse,100,velocityUnits::pct);
  Motor_left.setVelocity(speed,vex::percentUnits::pct);
  Motor_right.setVelocity(speed*(-1),vex::percentUnits::pct);

  Motor_left.setRotation(degree,rotationUnits::deg);
  Motor_right.setRotation(degree,rotationUnits::deg);

  Motor_left.stop(brakeType::hold);
  Motor_right.stop(brakeType::hold);
}