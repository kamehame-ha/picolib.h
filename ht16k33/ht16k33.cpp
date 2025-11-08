/*
*
* SPDX-License-Identifier: MIT
*
* Copyright (c) 2025 kameHame HA
* 
* All of my pico code is tested on RPi Pico W
*
*/

#include "ht16k33.h"
#include <cstdio>
#include <cmath>
#include <cstring>

const std::map<char, uint8_t> Ht16k33::char_map = {
    {' ', 0b00000000}, // 0x00
    {'.', 0b10000000}, // 0x80
    {':', 0b00000011}, // 0x03 -- Note: This uses the central colon LEDs on some modules
    {'0', 0b00111111}, // 0x3F
    {'1', 0b00000110}, // 0x06
    {'2', 0b01011011}, // 0x5B
    {'3', 0b01001111}, // 0x4F
    {'4', 0b01100110}, // 0x66
    {'5', 0b01101101}, // 0x6D
    {'6', 0b01111101}, // 0x7D
    {'7', 0b00000111}, // 0x07
    {'8', 0b01111111}, // 0x7F
    {'9', 0b01101111}, // 0x6F
    {'A', 0b01110111}, // 0x77
    {'B', 0b01111100}, // 0x7C
    {'C', 0b00111001}, // 0x39
    {'D', 0b01011110}, // 0x5E
    {'E', 0b01111001}, // 0x79
    {'F', 0b01110001}, // 0x71
    {'-', 0b01000000}  // 0x40
};

Ht16k33::Ht16k33(i2c_inst_t *i2c_port, uint8_t i2c_address, bool has_colon_display)
    : i2c_port(i2c_port), i2c_address(i2c_address), _has_colon_display(has_colon_display)
{
    clear();
}

void Ht16k33::init()
{
    sendCommand(0x21); // Turn on oscillator
    sendCommand(0x81); // Display on, no blinking
    setBrightness(15); // Set max brightness
}

void Ht16k33::setBrightness(uint8_t brightness)
{
    if (brightness > 15)
        brightness = 15;
    sendCommand(0xE0 | brightness);
}

void Ht16k33::clear()
{
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        display_buffer[i] = 0;
    }
}

void Ht16k33::writeDisplay()
{
    uint8_t write_buf[17];
    write_buf[0] = 0x00;

    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        write_buf[i * 2 + 1] = display_buffer[i];
        write_buf[i * 2 + 2] = 0x00;
    }

    i2c_write_blocking(i2c_port, i2c_address, write_buf, 17, false);
}

void Ht16k33::setDigit(uint8_t position, char character, bool has_dot)
{
    if (position >= BUFFER_SIZE)
        return;

    uint8_t segments = 0;
    auto it = char_map.find(character);
    if (it != char_map.end())
    {
        segments = it->second;
    }

    if (has_dot)
    {
        segments |= char_map.at('.');
    }

    display_buffer[position] = segments;
}

void Ht16k33::displayInt(int n)
{
    clear();
    char buf[5];
    snprintf(buf, 5, "%4d", n);
    int display_pos = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (_has_colon_display && display_pos == 2) {
            display_pos++;
        }
        setDigit(display_pos++, buf[i]);
    }
    writeDisplay();
}

void Ht16k33::displayHex(uint16_t n)
{
    clear();
    char buf[5];
    snprintf(buf, 5, "%04X", n);
    int display_pos = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (_has_colon_display && display_pos == 2) {
            display_pos++;
        }
        setDigit(display_pos++, buf[i]);
    }
    writeDisplay();
}

void Ht16k33::displayTime(uint8_t hours, uint8_t minutes)
{
    clear();
    if (_has_colon_display)
    {
        setDigit(0, (hours / 10) + '0');
        setDigit(1, (hours % 10) + '0');
        setDigit(3, (minutes / 10) + '0');
        setDigit(4, (minutes % 10) + '0');
        display_buffer[2] = char_map.at(':');
    }
    else
    {
        setDigit(0, (hours / 10) + '0');
        setDigit(1, (hours % 10) + '0');
        setDigit(2, (minutes / 10) + '0');
        setDigit(3, (minutes % 10) + '0');
        display_buffer[1] |= char_map.at(':');
    }
    writeDisplay();
}

void Ht16k33::displayDate(uint8_t day, uint8_t month)
{
    clear();
    if (_has_colon_display)
    {
        setDigit(0, (day / 10) + '0');
        setDigit(1, (day % 10) + '0', true);
        setDigit(3, (month / 10) + '0');
        setDigit(4, (month % 10) + '0');
        display_buffer[2] = char_map.at('.');
    }
    else
    {
        setDigit(0, (day / 10) + '0');
        setDigit(1, (day % 10) + '0', true);
        setDigit(2, (month / 10) + '0');
        setDigit(3, (month % 10) + '0');
        display_buffer[1] |= char_map.at('.');
    }
    writeDisplay();
}

void Ht16k33::displayFloat(float n, uint8_t decimals)
{
    clear();
    char buf[16];
    snprintf(buf, sizeof(buf), "%f", n);

    char display_buf[4] = {' ', ' ', ' ', ' '};
    int display_idx = 0;
    int dot_pos = -1;

    for (int i = 0; buf[i] != '\0' && display_idx < 4; i++)
    {
        if (buf[i] == '.')
        {
            if (display_idx > 0)
            {
                dot_pos = display_idx - 1;
            }
        }
        else
        {
            display_buf[display_idx++] = buf[i];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        int display_pos = i;
        if (_has_colon_display)
        {
            if (i >= 2)
            {
                display_pos++;
            }
        }
        setDigit(display_pos, display_buf[i], (i == dot_pos));
    }

    writeDisplay();
}

void Ht16k33::displayRaw(const uint8_t* data, size_t length)
{
    clear();
    for (size_t i = 0; i < length && i < BUFFER_SIZE; ++i)
    {
        display_buffer[i] = data[i];
    }
    writeDisplay();
}

void Ht16k33::sendCommand(uint8_t cmd)
{
    i2c_write_blocking(i2c_port, i2c_address, &cmd, 1, false);
}