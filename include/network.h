#ifndef NETWORK_H
#define NETWORK_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

namespace Network {
    const String ssid = "esp8266AP";
    const String pwd = "WiFi123!";
    const IPAddress apIp = IPAddress(192, 168, 4, 1);
    const uint16_t port = 80;
}

#endif // NETWORK_H
