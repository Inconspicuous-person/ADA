#pragma once
#include "constants.h"

// Convert Telemetry_downlink struct to a CSV string
String DownlinkToCSV(const Telemetry_downlink &data)
{
    String csvString;

    // Append each struct member to the string
    csvString += String(data.status) + ",";
    csvString += String(data.baro_alt) + ",";
    csvString += String(data.gnss_alt) + ",";
    csvString += String(data.gnss_lat) + ",";
    csvString += String(data.gnss_lon) + ",";
    csvString += String(data.motor_one_err) + ",";
    csvString += String(data.motor_two_err) + ",";
    csvString += String(data.motor_three_err) + ",";
    csvString += String(data.motor_four_err) + ",";
    csvString += String(data.motor_five_err) + ",";
    csvString += String(data.motor_six_err) + ",";
    csvString += String(data.motor_one_en) + ",";
    csvString += String(data.motor_two_en) + ",";
    csvString += String(data.motor_three_en) + ",";
    csvString += String(data.motor_four_en) + ",";
    csvString += String(data.motor_five_en) + ",";
    csvString += String(data.motor_six_en) + ",";
    csvString += String(data.arm_one_locked) + ",";
    csvString += String(data.arm_two_locked) + ",";
    csvString += String(data.arm_three_locked) + ",";
    csvString += String(data.arm_four_locked) + ",";
    csvString += String(data.arm_five_locked) + ",";
    csvString += String(data.arm_six_locked) + ",";
    csvString += String(data.arm_one_axis) + ",";
    csvString += String(data.arm_two_axis) + ",";
    csvString += String(data.arm_three_axis) + ",";
    csvString += String(data.arm_four_axis) + ",";
    csvString += String(data.arm_five_axis) + ",";
    csvString += String(data.arm_six_axis) + ",";
    csvString += String(data.accel_x) + ",";
    csvString += String(data.accel_y) + ",";
    csvString += String(data.accel_z) + ",";
    csvString += String(data.gyro_x) + ",";
    csvString += String(data.gyro_y) + ",";
    csvString += String(data.gyro_z) + ",";
    csvString += String(data.IO_DATA_COMM) + ",";
    csvString += String(data.IO_ACCELGYRO_COMM) + ",";
    csvString += String(data.batt_volts) + ",";
    csvString += String(data.batt_amps) + ",";
    csvString += String(data.checksum);

    // Return the comma-separated string
    return csvString;
}

// Convert Commands_uplink struct to a CSV string
String UplinkToCSV(const Commands_uplink &data)
{
    String csvString;

    // Append each struct member to the string
    csvString += String(data.type) + ",";
    csvString += String(data.motor_one_en) + ",";
    csvString += String(data.motor_two_en) + ",";
    csvString += String(data.motor_three_en) + ",";
    csvString += String(data.motor_four_en) + ",";
    csvString += String(data.motor_five_en) + ",";
    csvString += String(data.motor_six_en) + ",";
    csvString += String(data.arm_one_axis) + ",";
    csvString += String(data.arm_two_axis) + ",";
    csvString += String(data.arm_three_axis) + ",";
    csvString += String(data.arm_four_axis) + ",";
    csvString += String(data.arm_five_axis) + ",";
    csvString += String(data.arm_six_axis) + ",";
    csvString += String(data.arm_one_locked) + ",";
    csvString += String(data.arm_two_locked) + ",";
    csvString += String(data.arm_three_locked) + ",";
    csvString += String(data.arm_four_locked) + ",";
    csvString += String(data.arm_five_locked) + ",";
    csvString += String(data.arm_six_locked) + ",";
    csvString += String(data.motor_one_speed) + ",";
    csvString += String(data.motor_two_speed) + ",";
    csvString += String(data.motor_three_speed) + ",";
    csvString += String(data.motor_four_speed) + ",";
    csvString += String(data.motor_five_speed) + ",";
    csvString += String(data.motor_six_speed) + ",";
    csvString += String(data.motor_steps) + ",";
    csvString += String(data.turn_angle) + ",";
    csvString += String(data.checksum);

    // Return the comma-separated string
    return csvString;
}

// Convert Telemetry_uplink struct to a CSV string
String TeleUplinkToCSV(const Telemetry_uplink &data)
{
    String csvString;

    // Append each struct member to the string
    csvString += String(data.ground_status) + ",";
    csvString += String(data.checksum);

    // Return the comma-separated string
    return csvString;
}

// Convert Heartbeet struct to a CSV string
String HeartbeetToCSV(const Heartbeet &data)
{
    String csvString;

    // Append each struct member to the string
    csvString += String(data.status) + ",";
    csvString += String(data.checksum);

    // Return the comma-separated string
    return csvString;
}

// Convert CSV string to Telemetry_downlink struct
Telemetry_downlink csvToDownlinkStruct(const char *csvString)
{
    Telemetry_downlink data;

    char csvCopy[200];
    strncpy(csvCopy, csvString, sizeof(csvCopy));
    csvCopy[sizeof(csvCopy) - 1] = '\0';

    char *token = strtok(csvCopy, ",");
    int index = 0;
    while (token != nullptr)
    {
        switch (index)
        {
        case 0:
            data.status = atoi(token);
            break;
        case 1:
            data.baro_alt = atof(token);
            break;
        case 2:
            data.gnss_alt = atof(token);
            break;
        case 3:
            data.gnss_lat = atof(token);
            break;
        case 4:
            data.gnss_lon = atof(token);
            break;
        case 5:
            data.motor_one_err = (atoi(token) != 0);
            break;
        case 6:
            data.motor_two_err = (atoi(token) != 0);
            break;
        case 7:
            data.motor_three_err = (atoi(token) != 0);
            break;
        case 8:
            data.motor_four_err = (atoi(token) != 0);
            break;
        case 9:
            data.motor_five_err = (atoi(token) != 0);
            break;
        case 10:
            data.motor_six_err = (atoi(token) != 0);
            break;
        case 11:
            data.motor_one_en = (atoi(token) != 0);
            break;
        case 12:
            data.motor_two_en = (atoi(token) != 0);
            break;
        case 13:
            data.motor_three_en = (atoi(token) != 0);
            break;
        case 14:
            data.motor_four_en = (atoi(token) != 0);
            break;
        case 15:
            data.motor_five_en = (atoi(token) != 0);
            break;
        case 16:
            data.motor_six_en = (atoi(token) != 0);
            break;
        case 17:
            data.arm_one_locked = (atoi(token) != 0);
            break;
        case 18:
            data.arm_two_locked = (atoi(token) != 0);
            break;
        case 19:
            data.arm_three_locked = (atoi(token) != 0);
            break;
        case 20:
            data.arm_four_locked = (atoi(token) != 0);
            break;
        case 21:
            data.arm_five_locked = (atoi(token) != 0);
            break;
        case 22:
            data.arm_six_locked = (atoi(token) != 0);
            break;
        case 23:
            data.arm_one_axis = atof(token);
            break;
        case 24:
            data.arm_two_axis = atof(token);
            break;
        case 25:
            data.arm_three_axis = atof(token);
            break;
        case 26:
            data.arm_four_axis = atof(token);
            break;
        case 27:
            data.arm_five_axis = atof(token);
            break;
        case 28:
            data.arm_six_axis = atof(token);
            break;
        case 29:
            data.accel_x = atof(token);
            break;
        case 30:
            data.accel_y = atof(token);
            break;
        case 31:
            data.accel_z = atof(token);
            break;
        case 32:
            data.gyro_x = atof(token);
            break;
        case 33:
            data.gyro_y = atof(token);
            break;
        case 34:
            data.gyro_z = atof(token);
            break;
        case 35:
            data.IO_DATA_COMM = (atoi(token) != 0);
            break;
        case 36:
            data.IO_ACCELGYRO_COMM = (atoi(token) != 0);
            break;
        case 37:
            data.batt_volts = atof(token);
            break;
        case 38:
            data.batt_amps = atof(token);
            break;
        case 39:
            data.checksum = new char[strlen(token) + 1];
            strcpy(data.checksum, token);
            break;
        default:
            break;
        }

        token = strtok(nullptr, ",");
        index++;
    }

    return data;
}
