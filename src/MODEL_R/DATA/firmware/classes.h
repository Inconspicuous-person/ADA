#pragma once
#include "constants.h"

String LastPayload;
String LastLastPayload;
char *LastPayloadBuf;
char *LastLastPayloadBuf;
bool waitc;
bool acked;
int CMD;

void DATA_INT();

void INT_PULSE()
{
    digitalWrite(3, 1);
    delay(200);
    digitalWrite(3, 0);
}

class IO_MCU
{
private:
    static constexpr unsigned int djb2Hash(const char *str, int index = 0)
    {
        return !str[index] ? 0x1505 : (djb2Hash(str, index + 1) * 0x21) ^ str[index];
    }

    void ACK()
    {
        Serial.print("ACK\0");
        INT_PULSE();
    }

    // Sends a request signal and waits for ACK
    bool REQ_ACK()
    {
        Serial.print("REQ\0");
        INT_PULSE();
        delay(10); // Let the IO MCU process the request
        for (int i; i < 3; i++)
        {

            if (acked)
            {
                acked = false;
                return (1);
            }
            else
            {
                return (0);
            }
        }
        return (0);
    }

public:
    void PARSE_DATA()
    {
    }

    void PARSE_CMD()
    {
        switch (djb2Hash(LastPayloadBuf))
        {
        case djb2Hash("REQ"):
            waitc = false;
            Serial.print("ACK\0");
            INT_PULSE();
            break;
        case djb2Hash("ACK"):
            waitc = false;
            acked = true;
            break;
        default:
            break;
        }
    }

    // Initializes the IO MCU with specified baud rate

    bool initialize(int baud)
    {
        waitc = false;
        Serial.begin(baud);
        pinMode(3, OUTPUT);
        attachInterrupt(digitalPinToInterrupt(2), DATA_INT, RISING);
        delay(2000);
        return (REQ_ACK());
    }
};

IO_MCU IOM;

// Interrupt handler for receiving data
void DATA_INT()
{
    Serial.println("INT1"); // DEBUG ONLY
    LastLastPayload = LastPayload;
    LastPayload = Serial.readStringUntil('\n');
    LastPayload.toCharArray(LastPayloadBuf, sizeof(LastPayload));
    LastLastPayload.toCharArray(LastLastPayloadBuf, sizeof(LastLastPayload));
    if (!waitc)
    {
        IOM.PARSE_CMD();
    }
    else
    {
        IOM.PARSE_DATA();
    }
}