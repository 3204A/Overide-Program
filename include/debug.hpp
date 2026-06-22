#pragma once

#include "user_config.hpp"

#ifdef DEBUG_ENABLED
struct debug_drivetrain {
    double fl, fr, bl, br;
    double peak;
    double scale;
};

struct debug_controller {
    double velocity_x, velocity_y, velocity_turn;
};

extern debug_drivetrain drivetrain_debug;
extern debug_controller controller_debug;

void debug_display();

#endif