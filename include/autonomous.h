#include "vex.h"

#include "./Plan/LeftMode.h"
#include "./Plan/RightMode.h"
#include "./Plan/MasterMode.h"

using namespace vex;

void init(){
  Collect_Top.spin(forward, -100,velocityUnits::pct);
  wait(1000,vex::timeUnits::msec);
  Collect_Top.stop();
}

int MasterModeID = 0;
int LeftModeID = 1;
int RightModeID = 2;


void autonomous(){
  int Mode = MasterModeID;
  switch (Mode)
  {
    case 0:
    MasterMode::cycle();
    break;

    case 1:
    LeftMode::autonomous();
    break;

    case 2:
    RightMode::autonomous();
    break;
  }
}