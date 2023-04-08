#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <memory>

class RemoteCtrlReceiver
{
public:
    RemoteCtrlReceiver(String ssid, String pwd, uint16_t port);
    void setup();
    void loop();

private:
    String ssid, pwd;
    uint16_t port;
    std::unique_ptr<WiFiServer> server;
};

#endif // RECEIVER_H