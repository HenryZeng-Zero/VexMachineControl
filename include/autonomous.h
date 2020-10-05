#include "vex.h"
#include "RobotControl.h"
#include <thread>
using namespace vex;

Motors M;

void autonomous_(){
    M.Turning_TurnsMode(100,100,3,true);
    wait(1000,msec);
    M.Turning_TurnsMode(100,100,-3,true);
}