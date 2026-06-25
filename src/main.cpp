#include "main.h"
#include "config.hpp"
#include "user_config.hpp"
#include "drivetrain.hpp"
#include "sensors.hpp"

#ifdef DEBUG_ENABLED
#include "debug.hpp"
#endif

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(0, "Starting initialisation...");

	drivetrain_fl.set_brake_mode(MOTOR_BRAKE_BRAKE);
	drivetrain_fr.set_brake_mode(MOTOR_BRAKE_BRAKE);
	drivetrain_bl.set_brake_mode(MOTOR_BRAKE_BRAKE);
	drivetrain_br.set_brake_mode(MOTOR_BRAKE_BRAKE);
	drivetrain_fl.set_encoder_units(MOTOR_ENCODER_DEGREES);
	drivetrain_fr.set_encoder_units(MOTOR_ENCODER_DEGREES);
	drivetrain_bl.set_encoder_units(MOTOR_ENCODER_DEGREES);
	drivetrain_br.set_encoder_units(MOTOR_ENCODER_DEGREES);

	lift.set_brake_mode_all(MOTOR_BRAKE_HOLD);
	lift.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
	lift.tare_position_all();

	inertial.reset(true);

	#ifdef DEBUG_ENABLED
	// At start if B held down enter debug mode
	pros::delay(500);
	if (controller_main.get_digital(DIGITAL_B)) {
		debug_tools();
	}
	
	// Start background processes
	pros::Task debug_task(debug_display, 7, TASK_STACK_DEPTH_DEFAULT, "debug_task"); // Debug display is set to a lower prioity to not slow down main robot functions
	#endif

	pros::Task sensor_task(sensor_variable_update, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "sensor_task");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// Temporary auto code
	drivetrain_move(50, 0, 0, 300);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::lcd::set_text(0, "Starting driver control...");

	// Calculates the scale factor to scale controller input to RPM
	constexpr double CONTROLLER_MAIN_AXIS_SCALE = DRIVETRAIN_CARTRIDGE_RPM / 127.0; // 127 is the range of the joysticks analog outputs

	bool field_centered = false;

	while (true) {
		// Scales controller input to drivetrain RPM
		double velocity_x = controller_main.get_analog(ANALOG_LEFT_X) * CONTROLLER_MAIN_AXIS_SCALE;
		double velocity_y = controller_main.get_analog(ANALOG_LEFT_Y) * CONTROLLER_MAIN_AXIS_SCALE;
		double velocity_turn = controller_main.get_analog(ANALOG_RIGHT_X) * CONTROLLER_MAIN_AXIS_SCALE;

		if (controller_main.get_digital_new_press(DIGITAL_Y)) {
			if (field_centered) {
				field_centered = false;
				pros::lcd::set_text(1, "Robot centered");
			}
			else {
				field_centered = true;
				pros::lcd::set_text(1, "Field centered");
			}
		}

		if (field_centered) {
			drivetrain_move_field_centered(velocity_x, velocity_y, velocity_turn);
		}
		else {
			drivetrain_move(velocity_x, velocity_y, velocity_turn);
		}

		// TEMP: WHEEL TOGGLE
		if (controller_main.get_digital(DIGITAL_R1)) {
			TempWheel.move_velocity(200);
		}
		else {
			TempWheel.move_velocity(0);
		}
		// TEMP: WHEEL TOGGLE
 
		#ifdef DEBUG_ENABLED
		controller_debug = {velocity_x, velocity_y, velocity_turn};
		#endif

		pros::delay(20);
	}
}