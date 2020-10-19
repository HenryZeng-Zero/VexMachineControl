#include "vex.h"
#include <thread>
using namespace vex;

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

class Motors{
    public:

        const double pi = 3.1415926;
        const double wheel = 10.5; // 车轮直径
        const double Length_wheel = pi * wheel; // pi*d 计算车轮的圈长

        void Turning_DegMode(double v_left,double v_right,double deg,bool waits = false){
            Motor_left_Front.spinFor(directionType::fwd, deg, rotationUnits::deg, v_left, velocityUnits::pct, false);
            Motor_left_back.spinFor(directionType::fwd, deg, rotationUnits::deg, v_left, velocityUnits::pct, false);
            Motor_right_Front.spinFor(directionType::rev, deg, rotationUnits::deg, -v_right, velocityUnits::pct, false);
            Motor_right_Back.spinFor(directionType::rev, deg, rotationUnits::deg, -v_right, velocityUnits::pct, waits);
        }

        void Turning_TurnsMode(double v_left,double v_right,double cycle,bool waits = false){
            Motor_left_Front.spinFor(directionType::fwd, cycle, rotationUnits::rev, v_left, velocityUnits::pct, false);
            Motor_left_back.spinFor(directionType::fwd, cycle, rotationUnits::rev, v_left, velocityUnits::pct, false);
            Motor_right_Front.spinFor(directionType::rev, cycle, rotationUnits::rev, -v_right, velocityUnits::pct, false);
            Motor_right_Back.spinFor(directionType::rev, cycle, rotationUnits::rev, -v_right, velocityUnits::pct, waits);
        }

        void StopAll(vex::brakeType mode){
            Motor_left_Front.stop();
            Motor_left_back.stop();
            Motor_right_Front.stop();
            Motor_right_Back.stop();
            Collect_Bottom.stop();
            Collect_Top.stop();
            Motor_left_Arm.stop();
            Motor_right_Arm.stop();

            Motor_left_Front.setStopping(mode);
            Motor_left_back.setStopping(mode);
            Motor_right_Front.setStopping(mode);
            Motor_right_Back.setStopping(mode);
            Collect_Bottom.setStopping(mode);
            Collect_Top.setStopping(mode);
            Motor_left_Arm.setStopping(mode);
            Motor_right_Arm.setStopping(mode);
        }

        void Rotating(bool Clockwise,double v,double deg){
            // Clockwise 顺时针/逆时针

            double v_left = 0;
            double v_right = 0;

            if(Clockwise){
                v_left = v;
                v_right = -v;
            }else{
                v_left = -v;
                v_right = v;
            }

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

        void Up_down(bool Up,bool Top,bool Bottom,double t){
            double Bottom_ = 100 * Bottom;
            double Top_ = 100 * Top;
            if(Up){
                Collect_Bottom.spin(reverse, Bottom_,velocityUnits::pct);
                Collect_Top.spin(forward, Top_, velocityUnits::pct);
            }else{
                Collect_Bottom.spin(reverse, -Bottom_,velocityUnits::pct);
                Collect_Top.spin(forward, -Top_,velocityUnits::pct);
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

        double TurnsConvert_Length(double length){
            return length / Length_wheel;
        }
};


Motors M;

void step1(){
    wait(1500,msec);

    M.Turning_TurnsMode(50,50,M.TurnsConvert_Length(90),true); // 走两块地垫距离

    // wait(1000,msec);
    // M.Turning_TurnsMode(100,100,-3,true);
    // wait(1000,msec);
    
    M.Rotating(false,45,133);

    M.Collect(false,0); // 提前打开收球

    M.Turning_TurnsMode(60,60,M.TurnsConvert_Length(90*sqrt(2)),false); // 走对角线
    
    wait(1400,msec); // 时间阻塞

    // --------

    M.Up_down(true,true,true,1200);

    M.Collect_Stop();

}

void step2(){

    M.Turning_TurnsMode(60,60,-1,true);

    M.Rotating(false,45,132);

    M.Turning_TurnsMode(60,60,M.TurnsConvert_Length(120),true); // 走两块地垫距离

    M.Rotating(true,45,90);

    M.Turning_TurnsMode(60,60,M.TurnsConvert_Length(60 * 0.8),false); // 走0.8地垫距离

    M.Up_down(true,true,true,0);
    
    wait(1400,msec);

    M.Turning_TurnsMode(100,100,-M.TurnsConvert_Length(60 * 2.5),false);

    wait(1400,msec);
    
    M.StopAll(vex::brakeType::coast);
}


void init(){
  Collect_Top.spin(forward, -100,velocityUnits::pct);
  wait(1000,vex::timeUnits::msec);
  Collect_Top.stop();
}

void autonomous_(){
    init();
    step1();
    step2();
}