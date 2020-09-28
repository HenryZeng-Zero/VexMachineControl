#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Motor_left_Front = motor(PORT1, ratio18_1, false);
motor Motor_right_Front = motor(PORT2, ratio18_1, false);
motor Motor_left_Arm = motor(PORT5, ratio18_1, false);
motor Motor_right_Arm = motor(PORT6, ratio18_1, false);
motor Motor_left_back = motor(PORT3, ratio18_1, false);
motor Motor_right_Back = motor(PORT4, ratio18_1, false);
motor Collect_Bottom = motor(PORT7, ratio18_1, false);
motor Collect_Top = motor(PORT8, ratio18_1, false);
/*vex-vision-config:begin*/
signature Vision__BLUEBALL = signature (1, -3163, -2101, -2632, 9067, 12437, 10752, 3.2, 0);
signature Vision__REDBALL = signature (2, 5923, 8993, 7458, -1, 1225, 612, 3.1, 0);
vision Vision = vision (PORT9, 50, Vision__BLUEBALL, Vision__REDBALL);
/*vex-vision-config:end*/
inertial Inertial = inertial(PORT10);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}