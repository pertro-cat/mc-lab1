#ifndef UART_H
#define UART_H
#include <SoftwareSerial.h>
extern SoftwareSerial mySerial;
uint8_t controll = 0b01001010;

extern bool UARTBtnState;

void sentDataUsingUART()
{
    if (UARTBtnState)
    {
        mySerial.print(controll);
    }
    else
    {
        mySerial.print(controll);
    }
}

#endif