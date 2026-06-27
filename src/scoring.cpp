#include "main.h"
#include "scoring.hpp"
#include "config.hpp"

// Lift motors
pros::MotorGroup lift({LIFT_1, LIFT_2});

// Claw pneumatics
pros::adi::DigitalOut claw(CLAW);
pros::adi::DigitalOut claw_rotate(CLAW_ROTATE);

void scoring_initialise() {
    lift.set_brake_mode_all(MOTOR_BRAKE_HOLD);
	lift.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
	lift.tare_position_all();
}