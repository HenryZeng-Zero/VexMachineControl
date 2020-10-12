#include "vex.h"
#include <thread>
using namespace vex;

namespace Inertial_flat_Volatility{
    using namespace vex;
    double DataList[10];
    int count = 0;
    void get(){
        count++;
        if(count == 10){
            count = 0;
        }
        DataList[count] =  Inertial.gyroRate(vex::axisType::zaxis, vex::velocityUnits::dps);
    }

    double average(){
        double average_num = 0;
        for(int i = 0;i<10;i++){
            average_num += DataList[i];
        }
        average_num = average_num/10;
        return average_num;
    }

}

namespace deg_Check{
    using namespace vex;
    void init(){
        Inertial.resetHeading();
    }

    bool Check(bool Clockwise,double deg,double v){
        double Now_deg = Inertial.angle();
        if(Clockwise){
            if(Now_deg > 350){
                Now_deg = 0;
            }
            if(Now_deg + (v/5) > deg){
                return true;
            }else{
                return false;
            }
        }else{
            if(Now_deg < 10){
                Now_deg = 360;
            }
            if(Now_deg - (v/5) < (360 - deg)){
                return true;
            }else{
                return false;
            }
        }
        
    }
}

const double pi = 3.1415926;
const double wheel = 10.5;
const double Length_wheel = pi * wheel;
const double diagonal = 38 * sqrt(2); //斜边
const double Rotating_circle = diagonal * pi;

class Motors{
    public:
        void waitting(){
            while (true)
            {
                if (Inertial.gyroRate(vex::axisType::zaxis, vex::velocityUnits::dps) <= 0){
                    break;
                }
            }
        }

        void Deg_init(){
            Motor_left_Front.resetPosition();
        }

        void Deg_waitting(double deg){
            while (true)
            {
                
                if (Motor_left_Front.position(rotationUnits::deg) >= deg){
                    break;
                }
            }
        }

        void Turning_DegMode(double v_left,double v_right,double deg,bool waits = false){
            Deg_init();

            Motor_left_Front.spinFor(directionType::fwd, deg, rotationUnits::deg, v_left, velocityUnits::pct, false);
            Motor_left_back.spinFor(directionType::fwd, deg, rotationUnits::deg, v_left, velocityUnits::pct, false);
            Motor_right_Front.spinFor(directionType::rev, deg, rotationUnits::deg, -v_right, velocityUnits::pct, false);
            Motor_right_Back.spinFor(directionType::rev, deg, rotationUnits::deg, -v_right, velocityUnits::pct, false);

            Deg_waitting(deg);
        }

        void Turning_TurnsMode(double v_left,double v_right,double cycle,bool waits = false){
            Motor_left_Front.spinFor(directionType::fwd, cycle, rotationUnits::rev, v_left, velocityUnits::pct, false);
            Motor_left_back.spinFor(directionType::fwd, cycle, rotationUnits::rev, v_left, velocityUnits::pct, false);
            Motor_right_Front.spinFor(directionType::rev, cycle, rotationUnits::rev, -v_right, velocityUnits::pct, false);
            Motor_right_Back.spinFor(directionType::rev, cycle, rotationUnits::rev, -v_right, velocityUnits::pct, true);
            
        }

        void Rotating(bool Clockwise,double v,double deg){
            double v_left = 0;
            double v_right = 0;
            // double cycle = (Rotating_circle * deg)/360/Length_wheel;

            if(Clockwise){
                v_left = v;
                v_right = -v;
            }else{
                v_left = -v;
                v_right = v;
            }

            // Motor_left_Front.spinFor(directionType::fwd, cycle, rotationUnits::rev, v_left, velocityUnits::pct, false);
            // Motor_left_back.spinFor(directionType::fwd, cycle, rotationUnits::rev, v_left, velocityUnits::pct, false);
            // Motor_right_Front.spinFor(directionType::rev, -cycle, rotationUnits::rev, -v_right, velocityUnits::pct, false);
            // Motor_right_Back.spinFor(directionType::rev, -cycle, rotationUnits::rev, -v_right, velocityUnits::pct, false);
            Motor_left_Front.spin(forward, v_left,velocityUnits::pct);
            Motor_left_back.spin(forward, v_left,velocityUnits::pct);
            Motor_right_Front.spin(reverse, v_right,velocityUnits::pct);
            Motor_right_Back.spin(reverse, v_right,velocityUnits::pct);

            deg_Check::init();

            while (true)
            {
                if(deg_Check::Check(Clockwise,deg,v)){
                    Motor_left_Front.setStopping(brakeType::hold);
                    Motor_left_back.setStopping(brakeType::hold);
                    Motor_right_Front.setStopping(brakeType::hold);
                    Motor_right_Back.setStopping(brakeType::hold);
                    
                    Motor_left_Front.stop();
                    Motor_left_back.stop();
                    Motor_right_Front.stop();
                    Motor_right_Back.stop();
                    break;
                }
            }
        }

        void Collect(bool Front,double t){
            if(Front){
                Motor_left_Arm.spin(forward, -100, velocityUnits::pct);
                Motor_right_Arm.spin(reverse, -100, velocityUnits::pct);
            }else{
                Motor_left_Arm.spin(forward, 100, velocityUnits::pct);
                Motor_right_Arm.spin(reverse, 100, velocityUnits::pct);
            }

            if(t == 0){
                return;
            }

            wait(t,msec);
            Motor_left_Arm.stop();
            Motor_right_Arm.stop();

            
        }
        void Collect_Stop(){
            Motor_left_Arm.stop();
            Motor_right_Arm.stop();
        }

        void Up_down(bool Up,double t){
            if(Up){
                Collect_Bottom.spin(reverse, 100,velocityUnits::pct);
                Collect_Top.spin(forward, 100, velocityUnits::pct);
            }else{
                Collect_Bottom.spin(reverse, -100,velocityUnits::pct);
                Collect_Top.spin(forward, -100,velocityUnits::pct);
            }
            
            if(t == 0){
                return;
            }

            wait(t,msec);
            Collect_Bottom.stop();
            Collect_Top.stop();
            
        }
        void Up_down_Stop(){
            Collect_Bottom.stop();
            Collect_Top.stop();
        }
};


Motors M;

void autonomous_(){
    wait(2000,msec);

    M.Collect(false,0);
    M.Turning_TurnsMode(100,100,3,true);
    M.Collect_Stop();
    // wait(1000,msec);
    // M.Turning_TurnsMode(100,100,-3,true);
    // wait(1000,msec);
    
    M.Rotating(false,45,135);

    M.Turning_TurnsMode(100,100,5,true);

    M.Up_down(true,3);
}