#include "constants.h"
#include "classes.h"
#include "stc.h"

// Global instances of telemetry and payload structures
Telemetry_downlink downlink_payload;
Telemetry_uplink uplink_telemetry;
Commands_uplink uplink_payload;
Heartbeet heartbeet_payload;

// Global instance of Rover class
Rover rover;

// Function to calculate checksum of a string
byte stringChecksum(char *s);

// Setup function, called once during initialization
void setup()
{
    rover.init(); // Initialize all systems
}

// Loop function, continuously executed
void loop()
{
}

// Function to calculate checksum of a string
byte stringChecksum(char *s)
{
    byte c = 0;
    while (*s != '\0')
        c ^= *s++;
    return c;
}
