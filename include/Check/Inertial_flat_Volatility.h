#include "../vex.h"
#include <thread>
using namespace vex;

double Get(){
    return Inertial.gyroRate(vex::axisType::xaxis, vex::velocityUnits::dps) + Inertial.gyroRate(vex::axisType::yaxis, vex::velocityUnits::dps);
}

namespace Inertial_flat_Volatility{
    double DataList[10];
    void get(){
        int count = 0;
        while (true)
        {
            count++;
            if(count == 10){
                count = 0;
            }
            DataList[count] =  Get() ;
        }
    }

    double average(){
        double average_num = 0;
        for(int i = 0;i<10;i++){
            average_num += DataList[i];
        }
        average_num /=10;
        return average_num;
    }

    int init(){
        thread get_(get);
        get_.join();
    }
}

