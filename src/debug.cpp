#include "main.h"
#include "debug.hpp"
#include "config.hpp"
#include "sensors.hpp"
#ifdef DEBUG_ENABLED

debug_drivetrain drivetrain_debug;
debug_controller controller_debug;

void debug_inertial_calibration() {
    constexpr int ROTATIONS = 5;

    pros::lcd::set_text(0, "Inertial calibration");
    pros::lcd::set_text(1, "Rotate robot " + std::to_string(ROTATIONS) + "x 360 CW");
    pros::lcd::set_text(2, "Press A when done");

    inertial.reset(true);

    while (!controller_main.get_digital_new_press(DIGITAL_A)) {
        pros::lcd::set_text(4, "Rotation: " + std::format("{:.2f}", inertial.get_rotation()));
        pros::delay(20);
    }

    double measured   = inertial.get_rotation();
    double correction = (ROTATIONS * 360.0) / measured;

    pros::lcd::set_text(0, "Measured: " + std::format("{:.2f}", measured));
    pros::lcd::set_text(1, "Correction: " + std::format("{:.4f}", correction));
    pros::lcd::clear_line(4);

    while (!controller_main.get_digital_new_press(DIGITAL_A)) {
        pros::delay(20);
    }
}

void debug_optical_calibration() {
    pros::lcd::set_text(0, "Optical calibration");
    pros::lcd::set_text(4, "Press A when done");
    while (!controller_main.get_digital_new_press(DIGITAL_B)) {
        pros::lcd::set_text(1, "Hue: " + std::format("{:.1f}", optical_toggle.get_hue()));
        switch (toggle_state()) {
            case ownedState::red:
                pros::lcd::set_text(2, "State: Red");
                break;
            case ownedState::blue:
                pros::lcd::set_text(2, "State: Blue");
                break;
            case ownedState::yellow:
                pros::lcd::set_text(2, "State: Yellow");
                break;
            default:
                pros::lcd::set_text(2, "State: Unknown");
                break;
        }
        pros::delay(20);
    }

    pros::lcd::clear_line(4);
}

void debug_tools() {
    auto debug_tools_display = []() {
        pros::lcd::set_text(0, "Setup tools:");
        pros::lcd::set_text(1, "Inertial calibration: Press A");
        pros::lcd::set_text(2, "Toggle optical calibraction: Press B");
    };
    debug_tools_display();

    while(true) {
        if (controller_main.get_digital_new_press(DIGITAL_A)) {
            debug_inertial_calibration();
            debug_tools_display();
        }
        else if (controller_main.get_digital_new_press(DIGITAL_B)) {
            debug_optical_calibration();
            debug_tools_display();
        }
        
        pros::delay(20);
    }
}

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