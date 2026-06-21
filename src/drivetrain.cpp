#include "main.h"
#include "drivetrain.hpp"
#include "config.hpp"
#include "user_config.hpp"

void drivetrain_move(double velocity_x, double velocity_y, double velocity_turn) {
    // calculate drivetrain motor velocity
    double fl = velocity_x + velocity_y + velocity_turn;
    double fr = velocity_x - velocity_y + velocity_turn;
    double bl = -velocity_x + velocity_y + velocity_turn;
    double br = -velocity_x - velocity_y + velocity_turn;
    
    // scale to keep velocity under Drivetrain RPM
    double peak = std::max({std::abs(fl), std::abs(fr), std::abs(bl), std::abs(br)});
    
    if (DRIVETRAIN_CARTRIDGE_RPM < peak) {
        double scale = DRIVETRAIN_CARTRIDGE_RPM / peak;
        
        fl *= scale;
        fr *= scale;
        bl *= scale;
        br *= scale;
    }

    drivetrain_fl.move_velocity(fl);
    drivetrain_fr.move_velocity(fr);
    drivetrain_bl.move_velocity(bl);
    drivetrain_br.move_velocity(br);
}