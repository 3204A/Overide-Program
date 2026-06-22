#pragma once

struct distance_processed {
    double left_mm;
    double back_mm;
};

struct inertial_processed {
    double rotation_degree;
    double heading_degree;
};

struct tracking_wheel_processed {
    double horizontal_rotation_centidegree;
    double vertical_rotation_centidegree;
};

struct gps_processed {
    double x_m;
    double y_m;
    double heading_degree;
};

extern distance_processed processed_distance;
extern inertial_processed processed_inertial;
extern tracking_wheel_processed processed_tracking_wheel;
extern gps_processed processed_gps;

enum class fieldSide {
    red_close,
    red_far,
    blue_close,
    blue_far,
    unknown
};

fieldSide field_quadrant(double x, double y);

void sensor_variable_update();