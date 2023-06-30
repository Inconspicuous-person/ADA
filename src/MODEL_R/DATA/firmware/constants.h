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