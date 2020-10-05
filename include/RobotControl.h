#include "vex.h"
#include "Check/Inertial_flat_Volatility.h"
using namespace vex;

class Motors{
    public:
        void Turning_DegMode(double v_left,double v_right,double deg,bool waits = false){
            Motor_left_Front.spinFor(directionType::fwd, deg, rotationUnits::deg, v_left, velocityUnits::pct, true);
            Motor_left_back.spinFor(directionType::fwd, deg, rotationUnits::deg, v_left, velocityUnits::pct, true);
            Motor_right_Front.spinFor(directionType::rev, deg, rotationUnits::deg, -v_right, velocityUnits::pct, true);
            Motor_right_Back.spinFor(directionType::rev, deg, rotationUnits::deg, -v_right, velocityUnits::pct, true);
        }
        void Turning_TurnsMode(double v_left,double v_right,double cycle,bool waits = false){
            Motor_left_Front.spinFor(directionType::fwd, cycle, rotationUnits::rev, v_left, velocityUnits::pct, false);
            Motor_left_back.spinFor(directionType::fwd, cycle, rotationUnits::rev, v_left, velocityUnits::pct, false);
            Motor_right_Front.spinFor(directionType::rev, cycle, rotationUnits::rev, -v_right, velocityUnits::pct, false);
            Motor_right_Back.spinFor(directionType::rev, cycle, rotationUnits::rev, -v_right, velocityUnits::pct, false);
            
            wait(700,msec);
            
            while (waits)
            {
                wait(100,msec);

                double average = Inertial_flat_Volatility::average();
                
                if (average == 0){
                    break;
                }
            }
            
        }
};