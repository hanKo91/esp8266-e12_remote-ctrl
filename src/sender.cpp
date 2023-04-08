#include "sender.h"

RemoteCtrlSender::RemoteCtrlSender(String ssid, String pwd, IPAddress apIp, uint16_t port)
: ssid(ssid), pwd(pwd), apIp(apIp), port(port) 
{
    joystick0 = std::unique_ptr<Joystick>(new Joystick{&ads, ads_channels[0], ads_channels[1]});
    joystick1 = std::unique_ptr<Joystick>(new Joystick{&ads, ads_channels[2], ads_channels[3]});
}

void RemoteCtrlSender::setup()
{
    Serial.begin(9600);
    if (!ads.begin())
    {
        Serial.println("Failed to initialize ADS.");
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pwd);

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
}

void RemoteCtrlSender::loop()
{
    if(!client.connected())
    {
        if (client.connect(apIp, port))
        {
            while(client.connected())
            {
                joystick0->sync();
                joystick1->sync();

                String msg = "" 
                + String(int(joystick0->get_X())) 
                + String(int(joystick0->get_Y())) 
                + "|" 
                + String(int(joystick1->get_X())) 
                + String(int(joystick1->get_Y())) 
                + "\n";

                client.print(msg.c_str());
                delay(50);
            }    
        }
    }
    delay(10);
}
