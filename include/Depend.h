#include "vex.h"
#include "cmath"
using namespace vex;

class InertialTool{
    public:
        void init(){
            Inertial.calibrate();
        }

        double Direction_preprocessing(bool Direction,double deg){
            // Direction 是方向指定，True表示顺时针
            // deg 表示转动角度
            double angle = Inertial.angle();

            if(Direction){
                if(angle + deg > 360){
                    // 特别判断 ： 逆时针 越过 0
                    return (deg - (360 - angle));
                }else{
                    return (angle + deg);
                }
            }else{
                
                if((angle -0) < deg){
                    // 特别判断 ： 顺时针 越过 0
                    return (360 - (deg - (angle -0)));
                }else{
                    return (angle - deg);
                }
            }
        }
        
        void BackDistance(bool Direction,double deg){
            double angle = Inertial.angle();

            if(Direction){
                if(angle + deg > 360){
                    // 特别判断 ： 逆时针 越过 0
                    return (deg + 360 - angle);
                }else{
                    return (angle - deg);
                }
            }else{
                
                // if((angle -0) < deg){
                //     // 特别判断 ： 顺时针 越过 0
                //     return (360 - (deg - (angle -0)));
                // }else{
                //     return (angle - deg);
                // }
            }
        }

        void AngleDistance(double deg){
            double angle_plus = Direction_preprocessing(true,deg);
            double angle_minus = Direction_preprocessing(false,deg);
            return min(angle_plus,angle_minus);
        }

        void Turning_Limit(bool Direction,double deg,int power_pct){
            double angle = Direction_preprocessing(Direction,deg);
            
        }

};