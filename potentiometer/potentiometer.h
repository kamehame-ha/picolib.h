/*
*
* SPDX-License-Identifier: MIT
*
* Copyright (c) 2025 kameHame HA
* 
* All of my pico code is tested on RPi Pico W
*
*/

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "pico/stdlib.h"
#include "hardware/adc.h"

class Potentiometer
{
public:
    /**
     * @brief Construct a new Potentiometer object.
     * @param adc_input The ADC channel to use (0, 1, or 2, corresponding to GPIO 26, 27, 28).
     */
    Potentiometer(uint8_t adc_input);

    /**
     * @brief Initializes the GPIO pin for ADC use. This should be called after the global adc_init().
     */
    void init();

    /**
     * @brief Reads the raw 12-bit value from the ADC.
     * @return A value between 0 and 4095.
     */
    uint16_t readRaw();

    /**
     * @brief Reads the potentiometer's position as a percentage.
     * @return A value between 0.0 and 100.0.
     */
    float readPercent();

    /**
     * @brief Reads the potentiometer's position as a normalized float.
     * @return A value between 0.0 and 1.0.
     */
    float readNormalized();

    /**
     * @brief Maps the potentiometer's reading to a custom integer range.
     *        This is similar to the Arduino map() function.
     * @param out_min The minimum value of the output range.
     * @param out_max The maximum value of the output range.
     * @return The mapped integer value.
     */
    int32_t readMapped(int32_t out_min, int32_t out_max);

private:
    uint8_t _adc_input;
    uint8_t _gpio_pin;
};

#endif // POTENTIOMETER_H