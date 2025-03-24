#ifndef UART_H
#define UART_H
#include <SoftwareSerial.h>
extern SoftwareSerial mySerial;

char controll = 0b01001010;
extern bool algoBlink;

void giveDataUsingUART()
{
    if (mySerial.available() > 0)
    {
        char input = mySerial.read();
        Serial.println(input);
        if (input == controll)
        {
            algoBlink = !algoBlink;
        }
    }
}

#endif