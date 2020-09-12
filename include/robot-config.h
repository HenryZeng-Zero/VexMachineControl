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
extern signature Vision__BLUEBALL;
extern signature Vision__REDBALL;
extern signature Vision__SIG_3;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );