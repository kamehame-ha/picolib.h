/*
*
* SPDX-License-Identifier: MIT
*
* Copyright (c) 2025 kameHame HA
* 
* All of my pico code is tested on RPi Pico W
*
*/
#include "potentiometer.h"
#include <cstdio>

const float ADC_MAX_VALUE = 4095.0f;

Potentiometer::Potentiometer(uint8_t adc_input) : _adc_input(adc_input)
{
    if (adc_input > 2)
    {
        printf("ERROR: Invalid ADC input %d. Must be 0, 1, or 2.\n", adc_input);
        _gpio_pin = 26;
    }
    else
    {
        _gpio_pin = 26 + adc_input;
    }
}

void Potentiometer::init()
{
    adc_gpio_init(_gpio_pin);
}

uint16_t Potentiometer::readRaw()
{
    adc_select_input(_adc_input);
    return adc_read();
}

float Potentiometer::readPercent()
{
    return (readRaw() / ADC_MAX_VALUE) * 100.0f;
}

float Potentiometer::readNormalized()
{
    return readRaw() / ADC_MAX_VALUE;
}

int32_t Potentiometer::readMapped(int32_t out_min, int32_t out_max)
{
    long val = readRaw();
    return (val * (out_max - out_min) / (long)ADC_MAX_VALUE) + out_min;
}