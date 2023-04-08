#include "joystick.h"

Joystick::Joystick(Adafruit_ADS1115 *ads, uint16_t x_channel, uint16_t y_channel)
    : ads(ads), x_channel(x_channel), y_channel(y_channel)
{
    for (int index = 0; index < int(NUM_ADS_CHANNELS); ++index)
    {
        if(x_channel == ads_channels[index])
        {
            x_ch_index = index;
        }
        if(y_channel == ads_channels[index])
        {
            y_ch_index = index;
        }
    }
}

cursor_pos_t Joystick::adc_to_pos(int16_t adc_value)
{
    cursor_pos_t pos = MIDDLE;
    for (int i = 0; i < int(NUM_CURSOR_POS); ++i)
    {
        if (adc_value >= ADC_TO_POSITION_MAPPING[i][0] && adc_value <= ADC_TO_POSITION_MAPPING[i][1])
        {
            pos = cursor_pos_t(ADC_TO_POSITION_MAPPING[i][2]);
        }
    }
    return pos;
}

void Joystick::sync()
{
    ads->startADCReading(x_channel, /*continuous=*/false);
    ads->startADCReading(y_channel, /*continuous=*/false);
    while (!ads->conversionComplete())
        ;
    X = adc_to_pos(ads->readADC_SingleEnded(x_ch_index));
    Y = adc_to_pos(ads->readADC_SingleEnded(y_ch_index));
}

cursor_pos_t Joystick::get_X()
{
    return this->X;
}

cursor_pos_t Joystick::get_Y()
{
    return this->Y;
}

void JoystickTest::setup()
{
    Serial.begin(9600);
    if (!ads.begin())
    {
        Serial.println("Failed to initialize ADS.");
    }
}

void JoystickTest::loop()
{
    joystick.sync();
    String msg = "X: " + String(int(joystick.get_X())) + ", Y: " + String(int(joystick.get_Y()));
    Serial.println(msg);
}