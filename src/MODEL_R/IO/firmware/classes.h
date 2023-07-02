#pragma once
#include "constants.h"
#include "stc.h"

bool waitc;
bool acked;
String LastPayload;
String LastLastPayload;
char *LastPayloadBuf;
char *LastLastPayloadBuf;

void INT_PULSE()
{
    digitalWrite(3, 1);
    delay(50);
    digitalWrite(3, 0);
}

// Class representing the Data MCU
class Data_MCU
{
private:
    // Sends an ACK signal
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
        delay(10); // Let the data MCU process the request
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
        LastPayload = Serial.readStringUntil('\0');
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
            Serial.print("ACK");
            break;

        default:
            break;
        }
    }

public:
    // Initializes the Data MCU with specified baud rate
    template <typename T>

    void generateAndSetChecksum(T &data)
    {
        // Calculate size of the struct
        size_t dataSize = sizeof(data);

        // Calculate the checksum using XOR
        uint8_t *dataBytes = reinterpret_cast<uint8_t *>(&data);
        uint8_t checksum = 0;
        for (size_t i = 0; i < dataSize; ++i)
        {
            checksum ^= dataBytes[i];
        }

        // Set the checksum value
        data.checksum = checksum;
    }
    bool initialize(int baud)
    {
        waitc = false;
        Serial.begin(baud);
        pinMode(3, OUTPUT);
        attachInterrupt(digitalPinToInterrupt(2), DATA_INT, RISING);
        delay(2000);
        return (REQ_ACK());
    }

    // Serializes downlink telemetry payload and sends it
    String SerializeDownlink(Telemetry_downlink down_payload)
    {
        Serial.print("ENCODE");
        INT_PULSE();
        generateAndSetChecksum(down_payload);
        Serial.println(DownlinkToCSV(down_payload));
        INT_PULSE();
    }
};

// Class representing the Rover
class Rover
{
private:
    /* data */
public:
    Data_MCU DATA;

    // Initializes the Rover by initializing the Data MCU
    void init()
    {
        switch (MCU_SERIAL) // Initialize DATA MCU at specified speed
        {
        case 1:
            DATA.initialize(serial_LOW);
            break;
        case 2:
            DATA.initialize(serial_MED);
            break;
        case 3:
            DATA.initialize(serial_HIGH);
            break;
        case 4:
            DATA.initialize(serial_SS);
            break;
        default:
            DATA.initialize(serial_LOW);
            break;
        }
    }

    // Moves the Rover by the specified number of steps and direction
    void move(int steps, bool direction)
    {
        Serial.println("Moving"); // Placeholder
    }

    // Turns the Rover by the specified angle and direction
    void turn(float angle, bool direction)
    {
        Serial.println("Turn"); // Placeholder
    }

    // Sends a heartbeat payload to the Data MCU
    void heartbeet(Heartbeet heartbeet)
    {
        Serial.println("ENCODE");
        DATA.generateAndSetChecksum(heartbeet);
        Serial.print(HeartbeetToCSV(heartbeet));
        INT_PULSE();
    }
};
