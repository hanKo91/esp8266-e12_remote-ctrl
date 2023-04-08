#ifndef SENDER_H
#define SENDER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "joystick.h"
#include <memory>

class RemoteCtrlSender
{
public:
    RemoteCtrlSender(String ssid, String pwd, IPAddress apIp, uint16_t port);
    void setup();
    void loop();

private:
    String ssid, pwd;
    IPAddress apIp;
    uint16_t port;
    WiFiClient client;
    Adafruit_ADS1115 ads;
    std::unique_ptr<Joystick> joystick0;
    std::unique_ptr<Joystick> joystick1;
};

#endif // SENDER_H