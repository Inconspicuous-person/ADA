#include "constants.h"
#include "classes.h"

Telemetry_downlink downlink_payload;
Telemetry_uplink uplink_telemetry;
Commands_uplink uplink_payload;
Heartbeet heartbeet_payload;

Rover rover;


byte stringChecksum(char *s);

void setup()
{
}

void loop()
{
}

byte stringChecksum(char *s)
{
    byte c = 0;
    while (*s != '\0')
        c ^= *s++;
    return c;
}