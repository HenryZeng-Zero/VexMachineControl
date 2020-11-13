#ifndef RIGHT_MODE_
#define RIGHT_MODE_

#include "../support.h"
#include "../vex.h"
using namespace vex;

namespace RightMode
{

  Motors M;

  void step1()
  {
    wait(1500, msec);

    M.Turning_TurnsMode(50, 50, M.TurnsConvert_Length(75),
                        true); // 走两块地垫距离

    // wait(1000,msec);
    // M.Turning_TurnsMode(100,100,-3,true);
    // wait(1000,msec);

    M.Rotating(true, 45, 133);

    M.Collect(false, 0); // 提前打开收球

    M.Turning_TurnsMode(60, 60, M.TurnsConvert_Length(90 * StaticValue::Sqrt2), false); // 走对角线

    wait(1400, msec); // 时间阻塞

    // --------

    M.Up_down(true, true, true, 1200);

    M.Collect_Stop();
  }

  void step2()
  {
    M.Turning_TurnsMode(60, 60, -1.2, true);

    M.Rotating(true, 45, 132);

    M.Turning_TurnsMode(60, 60, M.TurnsConvert_Length(130),
                        true); // 走两块地垫距离

    M.Rotating(false, 45, 90);

    M.Turning_TurnsMode(60, 60, M.TurnsConvert_Length(60 * 0.8),
                        false); // 走0.8地垫距离

    // M.Shake(100,100,2,2,1,true);

    M.Up_down(true, true, true, 0);

    wait(1400, msec);
  }

  void autonomous()
  {
    step1();
    step2();
    M.StopAll(coast);
  }
} // namespace RightMode

#endif;