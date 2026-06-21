#include "main.h"
#include "debug.hpp"

#ifdef DEBUG_ENABLED

debug_drivetrain drivetrain_debug;
debug_controller controller_debug;

void debug_display() {
    pros::lcd::set_text(2, 
        "Drivetrain Velocity: " +
        std::to_string(drivetrain_debug.fl) + " " +
        std::to_string(drivetrain_debug.fr) + " " +
        std::to_string(drivetrain_debug.bl) + " " +
        std::to_string(drivetrain_debug.br) + " " +
        std::to_string(drivetrain_debug.peak) + " " +
        std::to_string(drivetrain_debug.scale)
    );

    pros::lcd::set_text(3, 
        "Controller Inputs: " +
        std::to_string(controller_debug.velocity_x) + " " +
        std::to_string(controller_debug.velocity_y) + " " +
        std::to_string(controller_debug.velocity_turn)
    );
}

#endif