#include "constants.h"

class Rover
{
private:
    /* data */
public:
    void move(int steps, bool direction)
    {
        Serial.println("Moving"); // Placeholder
    }
    void turn(float angle, bool direction)
    {
        Serial.println("Turn"); // Placeholder
    }
    void heartbeet(Heartbeet heartbeet)
    {
        Serial.println("heartbeet"); // Placeholder
    }
};

class Data_MCU
{
private:
    void ACK()
    {
        Serial.print("ACK");
    }
    bool REQ_ACK()
    {
        Serial.print("REQ");
        delay(10); // Let the data MCU process the request
        for(int i; i < 3; i++)
        if (Serial.available())
        {
            if (Serial.readString() == "ACK")
            {
                return(1);
            }
            else
            {
                return(0);
            }
        }
        return(0);
    }

public:
    bool initialize(int baud)
    {
        Serial.begin(baud);
        delay(2000);
        return(REQ_ACK());
    }
};
