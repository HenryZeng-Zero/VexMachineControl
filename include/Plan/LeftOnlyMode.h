#ifndef LEFT_ONLY_MODE_
#define LEFT_ONLY_MODE_

#include "../vex.h"
#include "../support.h"
using namespace vex;

namespace LeftOnlyMode
{

    Motors M;

    void step1()
    {
        wait(1500, msec);

        M.Turning_TurnsMode(50, 50, M.TurnsConvert_Length(90), true); // 走两块地垫距离

        // wait(1000,msec);
        // M.Turning_TurnsMode(100,100,-3,true);
        // wait(1000,msec);

        M.Rotating(false, 45, 133);

        M.Turning_TurnsMode(60, 60, M.TurnsConvert_Length(90 * StaticValue::Sqrt2), false); // 走对角线

        wait(1000, msec); // 时间阻塞

        M.Collect(false, 0); // 提前打开收球

        M.Up_down(true, true, true, 0);

        wait(1600, msec);

        M.Collect_Stop();

        wait(1000, msec);

        M.Up_down_Stop();

        wait(1200, msec);

        M.Collect(true, 0);

        M.Up_down_Stop();
    }

    void autonomous()
    {
        step1();
        M.StopAll(coast);
    }
} // namespace LeftOnlyMode

#endif;