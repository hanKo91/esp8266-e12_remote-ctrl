#include "network.h"

#ifdef JOYSTICK_TEST
#include "joystick.h"
    JoystickTest test;
    void setup() { test.setup(); }
    void loop() { test.loop(); }
#endif
#ifdef REMOTECTRL_SENDER
#include "sender.h"
    RemoteCtrlSender sender{Network::ssid, Network::pwd, Network::apIp, Network::port};
    void setup() { sender.setup(); }
    void loop() { sender.loop(); }
#endif
#ifdef REMOTECTRL_RECEIVER
#include "receiver.h"
    RemoteCtrlReceiver receiver{Network::ssid, Network::pwd, Network::port};
    void setup() { receiver.setup(); }
    void loop() { receiver.loop(); }
#endif
