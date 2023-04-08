#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>

typedef enum
{
    MIDDLE,
    FRONT,
    BACK,
    NUM_CURSOR_POS
} cursor_pos_t;

/**
 * @brief ADC-value to position mapping
 * Position is given by range of min-max value
 * The ADC-value range is mapped to cursor_pos
 */
const int16_t ADC_TO_POSITION_MAPPING[3][3] =
{
    //min       max     cursor_pos
    {-10,       10000,  BACK},
    {10000,     16000,  MIDDLE},
    {16000,     30000,  FRONT}
};

const uint16_t ads_channels[] = {
    ADS1X15_REG_CONFIG_MUX_SINGLE_0, // A0
    ADS1X15_REG_CONFIG_MUX_SINGLE_1, // A1
    ADS1X15_REG_CONFIG_MUX_SINGLE_2, // A2
    ADS1X15_REG_CONFIG_MUX_SINGLE_3  // A3
};
#define NUM_ADS_CHANNELS (sizeof(ads_channels) / sizeof(ads_channels[0]))

class Joystick 
{
public:
    Joystick(Adafruit_ADS1115 *ads, uint16_t x_channel, uint16_t y_channel);
    void sync();
    cursor_pos_t get_X();
    cursor_pos_t get_Y();

private:
    cursor_pos_t adc_to_pos(int16_t adc_value);
    Adafruit_ADS1115 *ads;
    uint16_t x_channel; // X output
    uint16_t y_channel; // Y output
    int x_ch_index;
    int y_ch_index;
    cursor_pos_t X;
    cursor_pos_t Y;
};

class JoystickTest
{
public:
    void setup();
    void loop();

private:
    Adafruit_ADS1115 ads;
    Joystick joystick{&ads, ads_channels[0], ads_channels[1]};
};

#endif // JOYSTICK_H