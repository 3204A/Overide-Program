#include "main.h"
#include "drivetrain.hpp"
#include "config.hpp"
#include "user_config.hpp"
#include "sensors.hpp"
#include <numbers>

#ifdef DEBUG_ENABLED
#include "debug.hpp"
#endif

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

void drivetrain_move_feild_centered(double velocity_x, double velocity_y, double velocity_turn) {
    constexpr double DEGREES_TO_RADIANS = std::numbers::pi / 180;
    
    double inertial_heading_rad = processed_inertial.heading_degree * DEGREES_TO_RADIANS;
    
    double cos_heading = std::cos(inertial_heading_rad);
    double sin_heading = std::sin(inertial_heading_rad);

    double field_centered_velocity_x = (velocity_x * cos_heading) - (velocity_y * sin_heading);
    double field_centered_velocity_y = (velocity_x * sin_heading) + (velocity_y * cos_heading);

    drivetrain_move(field_centered_velocity_x, field_centered_velocity_y, velocity_turn);
}