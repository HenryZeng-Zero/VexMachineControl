#include "vex.h"
#include "./Plan/LeftMode.h"
using namespace vex;

void init(){
  Collect_Top.spin(forward, -100,velocityUnits::pct);
  wait(1000,vex::timeUnits::msec);
  Collect_Top.stop();
}

int LeftMode = 0;
int RightMode = 1;


void autonomous(){
  int Mode = LeftMode;
  switch (Mode)
  {
    case 0:
    autonomous_leftMode();
    break;
  }
}