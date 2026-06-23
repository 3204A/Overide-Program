#include "main.h"
#include "sensors.hpp"
#include "config.hpp"
#include "user_config.hpp"

distance_processed processed_distance;
inertial_processed processed_inertial;
tracking_wheel_processed processed_tracking_wheel;
gps_processed processed_gps;
robot_position position_robot;
allianceColour alliance;

void sensor_processing() {
    // Smooths sensor readings using a exponential moving average (EMA)
    // Smoothed reading = (current reading * smoothing value) + (previous smoothed reading * (1 - smoothing value))
    
    // Reverses smoothing value for the (1 - smoothing value) part of formular to reduce required math during runtime
    constexpr double SMOOTHING_VALUE_DISTANCE_REVERSED = 1 - SMOOTHING_VALUE_DISTANCE;
    constexpr double SMOOTHING_VALUE_INERTIAL_REVERSED = 1 - SMOOTHING_VALUE_INERTIAL;
    constexpr double SMOOTHING_VALUE_TRACKING_WHEEL_REVERSED = 1 - SMOOTHING_VALUE_TRACKING_WHEEL;
    constexpr double SMOOTHING_VALUE_GPS_REVERSED = 1 - SMOOTHING_VALUE_GPS;

    double current_distance_back = distance_back.get_distance();
    double current_distance_left = distance_left.get_distance();
    double current_inertial_rotation = inertial.get_rotation() * ERROR_CORECTION_INERTIAL; // Cancel out error in inertial readings where 1 full rotation ± 360 degrees
    double current_tracking_wheel_horizontal_rotation = tracking_wheel_horizontal.get_position();
    double current_tracking_wheel_vertical_rotation = tracking_wheel_vertical.get_position();
    double current_gps_x = gps.get_position_x();
    double current_gps_y = gps.get_position_y();
    double current_gps_heading = gps.get_heading();
    
    // EMA implementation
    processed_distance.back_mm = (current_distance_back * SMOOTHING_VALUE_DISTANCE) + (processed_distance.back_mm * SMOOTHING_VALUE_DISTANCE_REVERSED);
    processed_distance.left_mm = (current_distance_left * SMOOTHING_VALUE_DISTANCE) + (processed_distance.left_mm * SMOOTHING_VALUE_DISTANCE_REVERSED);
    processed_inertial.rotation_degree = (current_inertial_rotation * SMOOTHING_VALUE_INERTIAL) + (processed_inertial.rotation_degree * SMOOTHING_VALUE_INERTIAL_REVERSED);
    processed_tracking_wheel.horizontal_rotation_centidegree = (current_tracking_wheel_horizontal_rotation * SMOOTHING_VALUE_TRACKING_WHEEL) + (processed_tracking_wheel.horizontal_rotation_centidegree * SMOOTHING_VALUE_TRACKING_WHEEL_REVERSED);
    processed_tracking_wheel.vertical_rotation_centidegree = (current_tracking_wheel_vertical_rotation * SMOOTHING_VALUE_TRACKING_WHEEL) + (processed_tracking_wheel.vertical_rotation_centidegree * SMOOTHING_VALUE_TRACKING_WHEEL_REVERSED);
    processed_gps.x_m = (current_gps_x * SMOOTHING_VALUE_GPS) + (processed_gps.x_m * SMOOTHING_VALUE_GPS_REVERSED);
    processed_gps.y_m = (current_gps_y * SMOOTHING_VALUE_GPS) + (processed_gps.y_m * SMOOTHING_VALUE_GPS_REVERSED);
    processed_gps.heading_degree = (current_gps_heading * SMOOTHING_VALUE_GPS) + (processed_gps.heading_degree * SMOOTHING_VALUE_GPS_REVERSED);

    // Calculates inertial heading from inertial rotation
    // Does not directly use inertial.get_heading() as smoothing would not work with the value wraping
    // Same not done with gps as no equivelent .get_heading
    processed_inertial.heading_degree = std::fmod(processed_inertial.rotation_degree, 360.0);
    if (processed_inertial.heading_degree < 0) processed_inertial.heading_degree += 360.0;
}

fieldSide field_quadrant(double x, double y) {
    // Splits sides of field
    double diagonal_1 = x + y;
    double diagonal_2 = x - y;

    if (diagonal_1 > 0 && diagonal_2 > 0) return fieldSide::red_close;
    if (diagonal_1 > 0 && diagonal_2 < 0) return fieldSide::red_far;
    if (diagonal_1 < 0 && diagonal_2 > 0) return fieldSide::blue_close;
    if (diagonal_1 < 0 && diagonal_2 < 0) return fieldSide::blue_far;

    return fieldSide::unknown;
}

void starting_position() {
    constexpr double FIELD_SIZE_HALF_M = FIELD_SIZE_M * 0.5;

    fieldSide side = field_quadrant(processed_gps.x_m, processed_gps.y_m);

    double distance_back_m = processed_distance.back_mm * 0.001 + DISTANCE_BACK_OFFSET_M;
    double distance_left_m = processed_distance.left_mm * 0.001 + DISTANCE_LEFT_OFFSET_M;

    switch (side) {
        case fieldSide::red_close:
            position_robot = {-FIELD_SIZE_HALF_M + distance_left_m, -FIELD_SIZE_HALF_M + distance_back_m};
            alliance = allianceColour::red;
            break;
        case fieldSide::red_far:
            position_robot = {FIELD_SIZE_HALF_M - distance_left_m, -FIELD_SIZE_HALF_M + distance_back_m};
            alliance = allianceColour::red;
            break;
        case fieldSide::blue_close:
            position_robot = {FIELD_SIZE_HALF_M - distance_left_m, FIELD_SIZE_HALF_M - distance_back_m};
            alliance = allianceColour::blue;
            break;
        case fieldSide::blue_far:
            position_robot = {-FIELD_SIZE_HALF_M + distance_left_m, FIELD_SIZE_HALF_M - distance_back_m};
            alliance = allianceColour::blue;
            break;
        default:
            position_robot = {processed_gps.x_m, processed_gps.y_m};
            alliance = allianceColour::unknown;
            break;
    }
}

ownedState toggle_state() {
    double hue = optical_toggle.get_hue();

    if (hue < 30 || hue > 330)      return ownedState::red;
    if (hue > 50  && hue < 70)      return ownedState::yellow;
    if (hue > 210 && hue < 270)     return ownedState::blue;

    return ownedState::unknown;
}

spinDirection toggle_spin(double x, double y) {
    ownedState state = toggle_state();
    fieldSide side = field_quadrant(x, y);

    if (state == ownedState::unknown) return spinDirection::none;

    if (alliance == allianceColour::red  && state == ownedState::red)  return spinDirection::none;
    if (alliance == allianceColour::blue && state == ownedState::blue) return spinDirection::none;

    bool red_side = (side == fieldSide::red_close || side == fieldSide::red_far);

    // Red alliance toggles: Red - Blue - Yellow
    // Blue alliance toggles: Blue - Red - Yellow
    if (red_side) {
        if (alliance == allianceColour::red) {
            if (state == ownedState::yellow) return spinDirection::clockwise;
            return spinDirection::counter_clockwise;
        }
        if (state == ownedState::yellow) return spinDirection::counter_clockwise;
        return spinDirection::clockwise;
    }
    if (alliance == allianceColour::blue) return spinDirection::counter_clockwise;
    return spinDirection::clockwise;
}

void sensor_variable_update() {
    while (true)
    {
        sensor_processing();
        pros::delay(20);
    }
}