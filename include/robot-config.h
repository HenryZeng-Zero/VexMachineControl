using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Motor_left;
extern motor Motor_right;
extern motor Motor_arm;
extern motor Motor_hand;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );