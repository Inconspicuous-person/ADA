#pragma once
#include "constants.h"

String LastPayload;
String LastLastPayload;
char *LastPayloadBuf;
char *LastLastPayloadBuf;
bool waitc;
bool acked;
int CMD;

void INT_PULSE()
{
    digitalWrite(3, 1);
    delay(50);
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
        Serial.print("ACK");
        INT_PULSE();
    }

    // Sends a request signal and waits for ACK
    bool REQ_ACK()
    {
        Serial.print("REQ");
        INT_PULSE();
        delay(10); // Let the IO MCU process the request
        for (int i; i < 3; i++)
        {

                if (acked)
                {
                    return (1);
                }
                else
                {
                    return (0);
                }
        }
        return (0);
    }

    // Interrupt handler for receiving data
    static void DATA_INT()
    {
        LastLastPayload = LastPayload;
        LastPayload = Serial.readStringUntil('\n');
        LastPayload.toCharArray(LastPayloadBuf, sizeof(LastPayload));
        LastLastPayload.toCharArray(LastLastPayloadBuf, sizeof(LastLastPayload));
        if (!waitc)
        {
            PARSE_CMD();
        }
        else
        {
            PARSE_DATA();
        }
    }

    static void PARSE_DATA()
    {
    }

    static void PARSE_CMD()
    {
        switch (djb2Hash(LastPayloadBuf))
        {
        case djb2Hash("REQ"):
            waitc = false;
            Serial.println("ACK");
            INT_PULSE();
            break;

        default:
            break;
        }
    }

public:
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
