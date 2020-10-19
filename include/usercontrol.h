#include "vex.h"
using namespace vex;

void check(){
    while(1){
        Brain.Screen.setFont(mono40);
        Brain.Screen.clearLine(1,black);
        Brain.Screen.setCursor(Brain.Screen.row(),1);
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print(Inertial.angle());
        
        wait(100,msec);
    }
}

void direction_controlling() {
  while(true){
    Motor_left_Front.spin(forward, Controller1.Axis1.value() * 0.5 + Controller1.Axis2.value(),velocityUnits::pct);
    Motor_left_back.spin(forward, Controller1.Axis1.value() * 0.5 + Controller1.Axis2.value(),velocityUnits::pct);
    Motor_right_Front.spin(reverse, Controller1.Axis2.value() - Controller1.Axis1.value() * 0.5,velocityUnits::pct);
    Motor_right_Back.spin(reverse, Controller1.Axis2.value() - Controller1.Axis1.value() * 0.5,velocityUnits::pct);
  }
  
}


void collect() {
    while (true) {
        if (Controller1.ButtonL1.pressing()) {
            Motor_left_Arm.spin(forward, 100, velocityUnits::pct);
            Motor_right_Arm.spin(reverse, 100, velocityUnits::pct);
        } else if (Controller1.ButtonR1.pressing()) {
            Motor_left_Arm.spin(forward, -100, velocityUnits::pct);
            Motor_right_Arm.spin(reverse, -100, velocityUnits::pct);
        } else {
            Motor_left_Arm.stop();
            Motor_right_Arm.stop();
        }
    }
}

int Stop_Collect_Bottom = 100;
int Stop_Collect_Top = 100;
bool switch_ = false;

void Up_down() {
    while (true) {
        if (Controller1.ButtonL2.pressing()) {
            Collect_Bottom.spin(reverse, Stop_Collect_Bottom,velocityUnits::pct);
            Collect_Top.spin(forward, Stop_Collect_Top, velocityUnits::pct);
        } else if (Controller1.ButtonR2.pressing()) {
            Collect_Bottom.spin(reverse, -1 * Stop_Collect_Bottom,velocityUnits::pct);
            Collect_Top.spin(forward, -1 * Stop_Collect_Top,velocityUnits::pct);
        } else if (switch_ == false){
            Collect_Bottom.stop();
            Collect_Top.stop();
        }
    }
}

void Stop_Up_down() {
    while (true) {
        if (Controller1.ButtonUp.pressing()) {
            Stop_Collect_Top = 0;
        } else{
            Stop_Collect_Top = 100;
        }
        if (Controller1.ButtonDown.pressing()) {
            Stop_Collect_Bottom = 0;
        } else{
            Stop_Collect_Bottom = 100;
        }
    }
}

void Push() {
    while (true) {
        if(Controller1.Axis3.value()!=0){
            switch_ = true;
            Collect_Bottom.spin(reverse, Controller1.Axis3.value(),velocityUnits::pct);
        }else{
            switch_ = false;
        }
    }
}