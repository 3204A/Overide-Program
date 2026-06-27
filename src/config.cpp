#include "main.h"
#include "config.hpp"
#include "user_config.hpp"

// TEMPORARY TOGGLE WHEEL MOTOR
pros::Motor TempWheel(8, pros::v5::MotorGears::green);

// TEMPORARY CLAW
pros::Motor TempClaw(18, pros::v5::MotorGears::green);

// TEMPORARY ARM
pros::Motor TempArm(16, pros::v5::MotorGears::green);