#pragma once

class IO_MCU
{
private:
    static String LastPayload;
    static String LastLastPayload;
    static char *LastPayloadBuf;
    static char *LastLastPayloadBuf;
    static bool waitc;
    static int CMD;
    // Sends an ACK signal
    static constexpr unsigned int djb2Hash(const char* str, int index = 0)
    {
        return !str[index] ? 0x1505 : (djb2Hash(str, index + 1) * 0x21) ^ str[index];
    }

    void ACK()
    {
        Serial.print("ACK");
    }

    // Sends a request signal and waits for ACK
    bool REQ_ACK()
    {
        Serial.print("REQ");
        delay(10); // Let the IO MCU process the request
        for (int i; i < 3; i++)
        {
            if (Serial.available())
            {
                if (Serial.readString() == "ACK")
                {
                    return (1);
                }
                else
                {
                    return (0);
                }
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
        if (!waitc){
            PARSE_CMD();
        }
        else 
        {
            PARSE_DATA();
        }
    }

    static void PARSE_DATA() {


    }

    static void PARSE_CMD() {
        switch (djb2Hash(LastPayloadBuf))
        {
        case djb2Hash("REQ"):
                waitc = false;
                Serial.println("ACK");
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
        attachInterrupt(digitalPinToInterrupt(2), DATA_INT, RISING);
        delay(2000);
        return (REQ_ACK());
    }
};
