#pragma once

#include "main.h"

// Flag to enable/disable debugging features
// Comment out to disable
#define DEBUG_ENABLED

// Drivetrain cartridge RPM
constexpr int DRIVETRAIN_CARTRIDGE_RPM = 200;

// Drivetrain motors
// Assumes all drivetrain motors spin clockwise
constexpr std::int8_t DRIVETRAIN_FL = 20;
constexpr std::int8_t DRIVETRAIN_FR = 11;
constexpr std::int8_t DRIVETRAIN_BL = 1;
constexpr std::int8_t DRIVETRAIN_BR = 10;

// Lift motors
constexpr std::int8_t LIFT_1 = 5;
constexpr std::int8_t LIFT_2 = 6;

// Claw Pneumatics
constexpr char CLAW = 'A';
constexpr char CLAW_ROTATE = 'B';

// Distance sensors for odometry setup
constexpr std::uint8_t DISTANCE_LEFT = 7;
constexpr std::uint8_t DISTANCE_BACK = 8;
constexpr double DISTANCE_LEFT_OFFSET_M = 0;
constexpr double DISTANCE_BACK_OFFSET_M = 0;

// Inertial sensor
constexpr std::uint8_t INERTIAL = 9;

// Rotation sensors for odometry
constexpr std::uint8_t TRACKING_WHEEL_HORIZONTAL = 15;
constexpr std::uint8_t TRACKING_WHEEL_VERTICAL = 14;

// Optical sensor for toggles
constexpr std::uint8_t OPTICAL_TOGGLE = 12;

// GPS sensor for odometry setup
constexpr std::uint8_t GPS_PORT = 13;
constexpr double GPS_X_OFFSET_M = 0;
constexpr double GPS_Y_OFFSET_M = 0;

// Field size
constexpr double FIELD_SIZE_M = 3.6576;

// Smoothing values
// TODO: replace placeholder values
constexpr double SMOOTHING_VALUE_DISTANCE = 0.5;
constexpr double SMOOTHING_VALUE_INERTIAL = 0.3;
constexpr double SMOOTHING_VALUE_TRACKING_WHEEL = 0.9;
constexpr double SMOOTHING_VALUE_GPS = 0.2;

// For correcting error of raw inertial readings
constexpr double ERROR_CORECTION_INERTIAL = 1;

// Hue of toggle colours
constexpr double TOGGLE_HUE_RED_MAX = 0;
constexpr double TOGGLE_HUE_RED_MIN = 0;
constexpr double TOGGLE_HUE_YELLOW_MAX = 0;
constexpr double TOGGLE_HUE_YELLOW_MIN = 0;
constexpr double TOGGLE_HUE_BLUE_MAX = 0;
constexpr double TOGGLE_HUE_BLUE_MIN = 0;