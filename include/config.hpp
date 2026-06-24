#pragma once

#include "main.h"

// Main controller
extern pros::Controller controller_main;

// Drivetrain motors
extern pros::Motor drivetrain_fl;
extern pros::Motor drivetrain_fr;
extern pros::Motor drivetrain_bl;
extern pros::Motor drivetrain_br;

// Lift motors
extern pros::MotorGroup lift;

// Claw Pneumatics
extern pros::adi::DigitalOut claw;
extern pros::adi::DigitalOut claw_rotate;

// Distance sensors for odometry setup
extern pros::Distance distance_left;
extern pros::Distance distance_back;

// inertial sensor
extern pros::Imu inertial;

// Rotation sensors for odometry
extern pros::Rotation tracking_wheel_horizontal;
extern pros::Rotation tracking_wheel_vertical;

// Optical sensor for toggles
extern pros::Optical optical_toggle;

// GPS sensor for odometry setup
extern pros::GPS gps;