#include "vex.h"
#include "usercontrol.h"
#include "Find_ball.h"
#include "autonomous.h"
#include <thread>

using namespace vex;

void autonomous_In(){
  autonomous_();
}

void usercontrol()
{
  // 创建线程
  thread direction_controlling_(direction_controlling);
  thread collect_(collect);
  thread Up_down_(Up_down);
  thread Stop_Up_down_(Stop_Up_down);
  thread Push_(Push);

  // thread Find_Ball_(Find_Ball);
  //启动线程
  direction_controlling_.join();
  collect_.join();
  Up_down_.join();
  Stop_Up_down_.join();
  Push_.join();
}