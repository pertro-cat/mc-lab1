#ifndef BTN_H
#define BTN_H

#include <Arduino.h>
#include <SoftwareSerial.h>
extern SoftwareSerial mySerial;
#define HOLD_TIME 2000

extern const uint8_t btnGPIO;
extern const uint8_t btnGPI1;

extern unsigned long lastHoldTime;
extern unsigned long lastClickTime;
extern unsigned long currentDelay;

extern bool btnHold;
extern bool btnHoldUART;
extern bool UARTBtnState;

extern bool isPressBtn;
extern bool algoBlink;
extern bool siteBtnPressed;
extern bool siteBtnPressedUART;
extern bool isSiteBtnHold;

void buttonHold()
{
    if (!digitalRead(btnGPIO))
    {
        if (!btnHold)
        {
            lastHoldTime = millis();
            btnHold = true;
            Serial.println("press");
        }

        if (millis() - lastHoldTime >= HOLD_TIME)
        {
            algoBlink = !algoBlink;
            Serial.println("Button is held");
        }
    }
    else
    {
        btnHold = false;
    }
}

void buttonHoldUART()
{
    if (!digitalRead(btnGPI1))
    {
        if (!btnHoldUART)
        {
            lastHoldTime = millis();
            btnHoldUART = true;
        }

        if (millis() - lastHoldTime >= HOLD_TIME)
        {
            UARTBtnState = !UARTBtnState;
            mySerial.print("ButtonUART is held");
        }
    }
    else
    {
        btnHoldUART = false;
    }
}

void checkSiteBtn()
{
    static bool lastState = false;

    if (siteBtnPressed && !lastState)
    {
        algoBlink = !algoBlink;
        Serial.println(algoBlink ? "Algorithm mode activated" : "Default mode activated");
    }

    lastState = siteBtnPressed;
}

void checkSiteBtnUART()
{
    static bool lastState = false;

    if (siteBtnPressedUART && !lastState)
    {
        UARTBtnState = !UARTBtnState;
        Serial.println(algoBlink ? "Algorithm mode activated" : "Default mode activated");
    }

    lastState = siteBtnPressedUART;
}

#endif