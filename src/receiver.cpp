#include "receiver.h"

RemoteCtrlReceiver::RemoteCtrlReceiver(String ssid, String pwd, uint16_t port)
: ssid(ssid), pwd(pwd), port(port)
{
    server = std::unique_ptr<WiFiServer>(new WiFiServer{port});
}

void RemoteCtrlReceiver::setup()
{
    Serial.begin(9600);
    Serial.println();

    Serial.print("Setting soft-AP ... ");
    WiFi.mode(WIFI_AP);
    bool result = WiFi.softAP(ssid, pwd, 1, 0, 1);
    if (result == true)
    {
        Serial.println("Ready");
    }
    else
    {
        Serial.println("Failed!");
    }
    server->begin();
}

void RemoteCtrlReceiver::loop()
{
    WiFiClient client = server->available();
    if (client)
    {
        Serial.println("Client available");
        while (true)
        {
            if(client.connected())
            {
                Serial.println(client.readStringUntil('\n'));
            }
            else
            {
                Serial.println("Client not connected");
                break;
            }
            delay(25);
        }
        delay(10);
        client.stop();
        Serial.println("Client stopped");
    }
}
