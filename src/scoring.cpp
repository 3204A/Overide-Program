#include "main.h"
#include "scoring.hpp"
#include "user_config.hpp"

// Lift motors
pros::MotorGroup lift({LIFT_1, LIFT_2});

// Claw pneumatics
pros::adi::DigitalOut claw(CLAW);
pros::adi::DigitalOut claw_rotate(CLAW_ROTATE);