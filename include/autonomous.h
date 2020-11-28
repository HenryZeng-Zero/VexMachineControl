#include "vex.h"

#include "Share.h"

#include "./Plan/LeftMode.h"
#include "./Plan/RightMode.h"
#include "./Plan/MasterMode.h"
#include "./Plan/LeftOnlyMode.h"
#include "./Plan/RightOnlyMode.h"

using namespace vex;

const int MasterModeID = 0;
const int LeftModeID = 1;
const int RightModeID = 2;

const int LeftOnlyModeID = 3;
const int RightOnlyModeID = 4;

void Init()
{
  Share::ON = false;
  Collect_Top.spin(forward, -100, velocityUnits::pct);
  wait(1000, vex::timeUnits::msec);
  Collect_Top.stop();
}

void autonomous(void)
{ 
  Init();

  int Mode = RightOnlyModeID;
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

    case 3:
    LeftOnlyMode::autonomous();
    break;

    case 4:
    RightOnlyMode::autonomous();
    break;
  }
}