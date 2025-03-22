#ifndef UART_H
#define UART_H
#include <SoftwareSerial.h>
extern SoftwareSerial mySerial;

extern bool UARTBtnState;

void sentDataUsingUART()
{
    if (UARTBtnState)
    {
        mySerial.print(0b01001010);
    }
    else
    {
        mySerial.print(0b01001010);
    }
}

#endif