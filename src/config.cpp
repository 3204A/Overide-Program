#include "main.h"
#include "config.hpp"
#include "user_config.hpp"

// Main controller
pros::Controller controller_main(CONTROLLER_MASTER);

// Automaticaly set all drivetrain motors to cartridge
constexpr pros::v5::MotorGears DRIVETRAIN_CARTRIDGE_COLOUR() {
    if (DRIVETRAIN_CARTRIDGE_RPM == 100) {
        return pros::v5::MotorGears::red;
    }
    if (DRIVETRAIN_CARTRIDGE_RPM == 600) {
        return pros::v5::MotorGears::blue;
    }
    return pros::v5::MotorGears::green;
}

// Drivetrain motors
pros::Motor drivetrain_fl(DRIVETRAIN_FL, DRIVETRAIN_CARTRIDGE_COLOUR());
pros::Motor drivetrain_fr(DRIVETRAIN_FR, DRIVETRAIN_CARTRIDGE_COLOUR());
pros::Motor drivetrain_bl(DRIVETRAIN_BL, DRIVETRAIN_CARTRIDGE_COLOUR());
pros::Motor drivetrain_br(DRIVETRAIN_BR, DRIVETRAIN_CARTRIDGE_COLOUR());
pros::MotorGroup drivetrain_all({DRIVETRAIN_FL, DRIVETRAIN_FR, DRIVETRAIN_BL, DRIVETRAIN_BR}, DRIVETRAIN_CARTRIDGE_COLOUR());

// Lift motors
pros::MotorGroup lift({LIFT_1, LIFT_2});

// Claw pneumatics
pros::adi::DigitalOut claw(CLAW);
pros::adi::DigitalOut claw_rotate(CLAW_ROTATE);

// TEMPORARY TOGGLE WHEEL MOTOR
pros::Motor TempWheel(2, pros::v5::MotorGears::green);

// Distance sensors
pros::Distance distance_left(DISTANCE_LEFT);
pros::Distance distance_back(DISTANCE_BACK);

// inertial sensor
pros::Imu inertial(INERTIAL);

// Rotation sensors for odometry
pros::Rotation tracking_wheel_horizontal(TRACKING_WHEEL_HORIZONTAL);
pros::Rotation tracking_wheel_vertical(TRACKING_WHEEL_VERTICAL);

// Optical sensor for toggles
pros::Optical optical_toggle(OPTICAL_TOGGLE);

// GPS sensor for odometry setup
pros::GPS gps(GPS_PORT, GPS_X_OFFSET_M, GPS_Y_OFFSET_M);