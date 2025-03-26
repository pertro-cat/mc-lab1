#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include "indexHtml.h"
#include "wifi.h"
#include "btn.h"
#include "UART.h"
#include "pins.h"


unsigned long lastHoldTime = 0;
unsigned long currentDelay = 0;
unsigned long lastClickTime = 0;

bool btnHold = false;

bool isPressBtn = false;
bool algoBlink = false;
bool siteBtnPressed = false;

bool UARTBtnState = false;
bool siteBtnPressedUART = false;

const uint8_t defaulLED[] = {LED1GPIO, LED2GPIO, LED3GPIO};
const uint8_t algolLED[] = {LED3GPIO, LED2GPIO, LED1GPIO, LED2GPIO, LED3GPIO};

SoftwareSerial mySerial(TX, RX, SWSERIAL_6O1);


void pinsSetup()
{
    pinMode(btnGPIO, INPUT);
    for (uint8_t i = 0; i < PIN_DEFOULT; i++)
    {
        pinMode(defaulLED[i], OUTPUT);
    }
    for (uint8_t j = 0; j < PIN_ALGO; j++)
    {
        pinMode(algolLED[j], OUTPUT);
    }
}

void setup()
{
    Serial.begin(SERIAL_SPEED_PC);
    mySerial.begin(SERIAL_SPEED_UART);
    pinsSetup();
    initWiFi();
    InitMDNS();
}

uint8_t currentLED = 0;

void do_algorithm()
{
    if (millis() - currentDelay >= BLINK_TIME)
    {
        currentDelay = millis();

        if (algoBlink)
        {
            if (currentLED > 0)
                digitalWrite(algolLED[currentLED - 1], LOW);
            else
                digitalWrite(algolLED[sizeof(algolLED) / sizeof(algolLED[0]) - 1], LOW);

            digitalWrite(algolLED[currentLED], HIGH);
            Serial.println(currentLED);
            Serial.println("algo blink");
            

            currentLED = (currentLED + 1) % (sizeof(algolLED) / sizeof(algolLED[0]));
        }
        else
        {
            if (currentLED > 0)
                digitalWrite(defaulLED[currentLED - 1], LOW);
            else
                digitalWrite(defaulLED[sizeof(defaulLED) / sizeof(defaulLED[0]) - 1], LOW);

            digitalWrite(defaulLED[currentLED], HIGH);
            Serial.println(currentLED);
            Serial.println("default blink");



            currentLED = (currentLED + 1) % (sizeof(defaulLED) / sizeof(defaulLED[0]));
        }
    }
}

void loop()
{
    MDNS.update();
    buttonHold();
    do_algorithm();
    checkSiteBtn();
    buttonHoldUART();
    checkSiteBtnUART();
    sentDataUsingUART();
    giveDataUsingUART();
        

}
