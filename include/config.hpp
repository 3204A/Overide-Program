#pragma once

#include "main.h"

// Controller
pros::Controller main_controller;

// Drivetrain motors
extern pros::Motor drivetrain_fl;
extern pros::Motor drivetrain_fr;
extern pros::Motor drivetrain_bl;
extern pros::Motor drivetrain_br;

// Lift motors
extern pros::MotorGroup lift;

// Claw Pneumatics
extern pros::ADIAnalogOut claw;
extern pros::ADIAnalogOut claw_rotate;

// Distance sensors
extern pros::Distance distance_left;
extern pros::Distance distance_back;

// Inertal sensor
extern pros::Imu Inertial;

// Rotation sensors for odometry
extern pros::Rotation tracking_wheel_horizontal;
extern pros::Rotation tracking_wheel_vertical;

// Optical sensor for toggles
extern pros::Optical optical_toggle;

// GPS sensor for odometry setup
extern pros::GPS gps;