#pragma once

// Drivetrain motors
extern pros::MotorGroup drivetrain_all;

void drivetrain_move(double velocity_x, double velocity_y, double velocity_turn);

void drivetrain_move(double velocity_x, double velocity_y, double velocity_turn, double duration_ms);

void drivetrain_move_field_centered(double velocity_x, double velocity_y, double velocity_turn);

void drivetrain_move_field_centered(double velocity_x, double velocity_y, double velocity_turn, double duration_ms);