#ifndef SUPPORT_
#define SUPPORT_
#include "vex.h"

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
            Motor_left_Front.stop(mode);
            Motor_left_back.stop(mode);
            Motor_right_Front.stop(mode);
            Motor_right_Back.stop(mode);
            Collect_Bottom.stop(mode);
            Collect_Top.stop(mode);
            Motor_left_Arm.stop(mode);
            Motor_right_Arm.stop(mode);
        }

        void StopAll_empty(){
            Motor_left_Front.stop();
            Motor_left_back.stop();
            Motor_right_Front.stop();
            Motor_right_Back.stop();
            Collect_Bottom.stop();
            Collect_Top.stop();
            Motor_left_Arm.stop();
            Motor_right_Arm.stop();
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
                    
                    Motor_left_Front.stop(brake);
                    Motor_left_back.stop(brake);
                    Motor_right_Front.stop(brake);
                    Motor_right_Back.stop(brake);
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

        void Shake(int v_left,int v_right,double return_cm,double back_bump_cm,double timeout_msec = 0,bool wait = 0){
            // return_ : 后退距离
            // back_bump : 回撞距离

            Turning_TurnsMode(v_left,v_right,TurnsConvert_Length(return_cm),wait);

            Turning_TurnsMode(v_left,v_right,TurnsConvert_Length(back_bump_cm),wait);

            if(timeout_msec != 0){
                vex::wait(timeout_msec,vex::msec);
                Motor_left_Front.stop(brake);
                Motor_left_back.stop(brake);
                Motor_right_Front.stop(brake);
                Motor_right_Back.stop(brake);
            }

        }
};

#endif;