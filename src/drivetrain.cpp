#include "main.h"
#include "drivetrain.hpp"
#include "config.hpp"
#include "sensors.hpp"
#include <numbers>

#ifdef DEBUG_ENABLED
#include "debug.hpp"
#endif

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

void drivetrain_initialise() {
    drivetrain_all.set_brake_mode(MOTOR_BRAKE_BRAKE);
	drivetrain_all.set_encoder_units(MOTOR_ENCODER_DEGREES);
}

void drivetrain_move(double velocity_x, double velocity_y, double velocity_turn) {
    // calculate drivetrain motor velocity
    double fl = -velocity_x - velocity_y - velocity_turn;
    double fr = -velocity_x + velocity_y - velocity_turn;
    double bl = velocity_x + velocity_y - velocity_turn;
    double br = velocity_x - velocity_y - velocity_turn;
    double scale = 1;
    
    // scale to keep velocity under Drivetrain RPM
    double peak = std::max({std::abs(fl), std::abs(fr), std::abs(bl), std::abs(br)});
    
    if (DRIVETRAIN_CARTRIDGE_RPM < peak) {
        scale = DRIVETRAIN_CARTRIDGE_RPM / peak;
        
        fl *= scale;
        fr *= scale;
        bl *= scale;
        br *= scale;
    }

    #ifdef DEBUG_ENABLED
    drivetrain_debug = {fl, fr, bl, br, peak, scale};
    #endif

    drivetrain_fl.move_velocity(fl);
    drivetrain_fr.move_velocity(fr);
    drivetrain_bl.move_velocity(bl);
    drivetrain_br.move_velocity(br);
}

void drivetrain_move(double velocity_x, double velocity_y, double velocity_turn, double duration_ms) {
    drivetrain_move(velocity_x, velocity_y, velocity_turn);
    pros::delay(duration_ms);
    drivetrain_all.move_velocity(0);
}

void drivetrain_move_field_centered(double velocity_x, double velocity_y, double velocity_turn) {
    constexpr double DEGREES_TO_RADIANS = std::numbers::pi / 180;
    
    double inertial_heading_rad = processed_inertial.heading_degree * DEGREES_TO_RADIANS;
    
    double cos_heading = std::cos(inertial_heading_rad);
    double sin_heading = std::sin(inertial_heading_rad);

    double field_centered_velocity_x = (velocity_x * cos_heading) - (velocity_y * sin_heading);
    double field_centered_velocity_y = (velocity_x * sin_heading) + (velocity_y * cos_heading);

    drivetrain_move(field_centered_velocity_x, field_centered_velocity_y, velocity_turn);
}

void drivetrain_move_field_centered(double velocity_x, double velocity_y, double velocity_turn, double duration_ms) {
    drivetrain_move(velocity_x, velocity_y, velocity_turn);
    pros::delay(duration_ms);
    drivetrain_all.move_velocity(0);
}