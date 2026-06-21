#pragma once

#include "main.h"

// Drivetrain cartridge RPM
constexpr int DRIVETRAIN_CARTRIDGE_RPM = 200;

// Drivetrain motors
constexpr std::int8_t DRIVETRAIN_FL = -1;
constexpr std::int8_t DRIVETRAIN_FR = -2;
constexpr std::int8_t DRIVETRAIN_BL = -3;
constexpr std::int8_t DRIVETRAIN_BR = -4;

// Lift motors
constexpr std::int8_t LIFT_1 = 5;
constexpr std::int8_t LIFT_2 = 6;

// Claw Pneumatics
constexpr char CLAW = 'A';
constexpr char CLAW_ROTATE = 'B';

// Distance sensors for odometry setup
constexpr std::int8_t DISTANCE_LEFT = 7;
constexpr std::int8_t DISTANCE_BACK = 8;

// Inertial sensor
constexpr std::int8_t INERTIAL = 9;

// Rotation sensors for odometry
constexpr std::int8_t TRACKING_WHEEL_HORIZONTAL = 10;
constexpr std::int8_t TRACKING_WHEEL_VERTICAL = 11;

// Optical sensor for toggles
constexpr std::int8_t OPTICAL_TOGGLE = 12;

// GPS sensor for odometry setup
constexpr std::int8_t GPS_PORT = 13;
constexpr double GPS_X_OFFSET = 0;
constexpr double GPS_Y_OFFSET = 0;