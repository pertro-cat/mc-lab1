#ifndef WIFI_H
#define WIFI_H

#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);

#define ESP_WIFI_MODE DEVICE_WIFI
#define DEVICE_WIFI 1
#define AP_WIFI 2

#define SSID "admin"
#define PASSWORD "domestos1216"

// #define SSID "611VVA"
// #define PASSWORD "123qwerty9"
// #define HOST_NAME "lvivske1715" // mini
#define HOST_NAME "teteriv" // big

#include "pins.h"

extern bool siteBtnPressed;
extern bool siteBtnPressedUART;
void notFound(AsyncWebServerRequest *request);

uint8_t initWiFi()
{
    if (ESP_WIFI_MODE == DEVICE_WIFI)
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(SSID, PASSWORD);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Connecting to WiFi..");
        }
        Serial.println();
        Serial.print("ESP IP Address: http://");
        Serial.println(WiFi.localIP());

        Serial.print("RRSI: ");
        Serial.println(WiFi.RSSI());
    }
    else if (ESP_WIFI_MODE == AP_WIFI)
    {
        WiFi.mode(WIFI_AP);
        Serial.println("Setting AP (Access Point)…");
        WiFi.softAP(SSID, NULL);

        IPAddress IP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(IP);
    }
    else
    {
        WiFi.mode(WIFI_OFF);
        Serial.println("Wifi of");
        return -1;
    }
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", index_html); });

    server.on("/on_alg1", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    siteBtnPressed = true;
    Serial.println("site bnt true");
    request->send(200, "text/plain", "ok"); });

    server.on("/off_alg1", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    siteBtnPressed = false;
    Serial.println("site bnt false");
    request->send(200, "text/plain", "ok"); });

    server.on("/on_alg2", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        siteBtnPressedUART = true;
        Serial.println("site bnt1 true");
        request->send(200, "text/plain", "ok"); });

    server.on("/off_alg2", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        siteBtnPressedUART = false;
        Serial.println("site bnt1 false");
        request->send(200, "text/plain", "ok"); });

    server.on("/status_led_1", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(digitalRead(LED1GPIO)).c_str()); });

    server.on("/status_led_2", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(digitalRead(LED2GPIO)).c_str()); });

    server.on("/status_led_3", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(digitalRead(LED3GPIO)).c_str()); });

    server.onNotFound(notFound);
    server.begin();

    return 0;
}

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

void InitMDNS()
{
    if (!MDNS.begin(HOST_NAME))
    {
        Serial.println("Error starting mDNS");
    }
    Serial.println("mDNS started");
}

#endif