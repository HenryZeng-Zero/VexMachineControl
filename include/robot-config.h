using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor Motor_left_Front;
extern motor Motor_right_Front;
extern motor Motor_left_Arm;
extern motor Motor_right_Arm;
extern motor Motor_left_back;
extern motor Motor_right_Back;
extern motor Collect_Bottom;
extern motor Collect_Top;
extern signature Vision_bottom__BLUEBALL;
extern signature Vision_bottom__REDBALL;
extern signature Vision_bottom__SIG_3;
extern signature Vision_bottom__SIG_4;
extern signature Vision_bottom__SIG_5;
extern signature Vision_bottom__SIG_6;
extern signature Vision_bottom__SIG_7;
extern vision Vision_bottom;
extern inertial Inertial;
extern signature Vision_top__GREEN_BIN;
extern signature Vision_top__SIG_2;
extern signature Vision_top__SIG_3;
extern signature Vision_top__SIG_4;
extern signature Vision_top__SIG_5;
extern signature Vision_top__SIG_6;
extern signature Vision_top__SIG_7;
extern vision Vision_top;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );