#pragma once

/* ---CONFIG START--- */

#define MCU_SERIAL 1
const char modules[10][2] = {}; // Not implemented. 10 is a placeholder

/* ---CONFIG END--- */

#define serial_LOW 9600    // 1
#define serial_MED 115200  // 2
#define serial_HIGH 500000 // 3
#define serial_SS 1000000  // 4 (SuperSpeed tm)

#define light_channel_1 23
#define light_channel_2 24
#define light_channel_3 25
#define light_channel_4 26

// Structure for downlink telemetry
struct Telemetry_downlink
{
    int status;
    float baro_alt;
    float gnss_alt;
    float gnss_lat;
    float gnss_lon;
    bool motor_one_err;
    bool motor_two_err;
    bool motor_three_err;
    bool motor_four_err;
    bool motor_five_err;
    bool motor_six_err;
    bool motor_one_en;
    bool motor_two_en;
    bool motor_three_en;
    bool motor_four_en;
    bool motor_five_en;
    bool motor_six_en;
    bool arm_one_locked;
    bool arm_two_locked;
    bool arm_three_locked;
    bool arm_four_locked;
    bool arm_five_locked;
    bool arm_six_locked;
    double arm_one_axis;
    double arm_two_axis;
    double arm_three_axis;
    double arm_four_axis;
    double arm_five_axis;
    double arm_six_axis;
    double accel_x;
    double accel_y;
    double accel_z;
    double gyro_x;
    double gyro_y;
    double gyro_z;
    bool IO_DATA_COMM;
    bool IO_ACCELGYRO_COMM;
    float batt_volts;
    float batt_amps;
    char *checksum;
};

// Structure for uplink telemetry
struct Telemetry_uplink
{
    int ground_status;
    char *checksum;
};

// Structure for uplink commands
struct Commands_uplink
{
    int type;
    bool motor_one_en;
    bool motor_two_en;
    bool motor_three_en;
    bool motor_four_en;
    bool motor_five_en;
    bool motor_six_en;
    double arm_one_axis;
    double arm_two_axis;
    double arm_three_axis;
    double arm_four_axis;
    double arm_five_axis;
    double arm_six_axis;
    bool arm_one_locked;
    bool arm_two_locked;
    bool arm_three_locked;
    bool arm_four_locked;
    bool arm_five_locked;
    bool arm_six_locked;
    float motor_one_speed;
    float motor_two_speed;
    float motor_three_speed;
    float motor_four_speed;
    float motor_five_speed;
    float motor_six_speed;
    int motor_steps;
    float turn_angle;
    char *checksum;
};

// Structure for heartbeat payload
struct Heartbeet
{
    int status;
    char *checksum;
};
