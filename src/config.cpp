#include "main.h"
#include "config.hpp"


// Controller
pros::Controller main_controller(CONTROLLER_MASTER);

// Drivetrain motors
pros::Motor drivetrain_fl(1);
pros::Motor drivetrain_fr(2);
pros::Motor drivetrain_bl(3);
pros::Motor drivetrain_br(4);

// Lift motors
pros::MotorGroup lift({5, 6});

// Claw Pneumatics
pros::ADIAnalogOut claw('A');
pros::ADIAnalogOut claw_rotate('B');

// Distance sensors
pros::Distance distance_left(7);
pros::Distance distance_back(8);

// Inertal sensor
pros::Imu Inertial(9);

// Rotation sensors for odometry
pros::Rotation tracking_wheel_horizontal(10);
pros::Rotation tracking_wheel_vertical(11);

// Optical sensor for toggles
pros::Optical optical_toggle(12);

// GPS sensor for odometry setup
pros::GPS gps(13, 0, 0); //TODO: set offset