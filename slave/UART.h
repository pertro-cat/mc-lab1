#ifndef UART_H
#define UART_H
#include <SoftwareSerial.h>
extern SoftwareSerial mySerial;

uint8_t controll = 0b01001010;
extern bool algoBlink;

void giveDataUsingUART()
{
    if (mySerial.available() > 0)
    {
        uint8_t input = mySerial.read();
        if (input == controll)
        {
            algoBlink = !algoBlink;
        }
    }
}

#endif