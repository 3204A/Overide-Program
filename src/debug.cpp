#include "main.h"
#include "debug.hpp"

#ifdef DEBUG_ENABLED

debug_drivetrain drivetrain_debug;
debug_controller controller_debug;

void debug_display() {
    while(true) {
        pros::lcd::set_text(3, 
            "Axis input: " +
            std::format("{:.2f}", controller_debug.velocity_x) + " " +
            std::format("{:.2f}", controller_debug.velocity_y) + " " +
            std::format("{:.2f}", controller_debug.velocity_turn)
        );
        
        pros::lcd::set_text(2, 
            "Dt Vel: " +
            std::format("{:.0f}", drivetrain_debug.fl) + " " +
            std::format("{:.0f}", drivetrain_debug.fr) + " " +
            std::format("{:.0f}", drivetrain_debug.bl) + " " +
            std::format("{:.0f}", drivetrain_debug.br) + " " +
            std::format("{:.0f}", drivetrain_debug.peak) + " " +
            std::format("{:.2f}", drivetrain_debug.scale)
        );

        pros::delay(20); // Screen refresh rate 60hz so don't put under 16.6ms
    }
}

#endif