/*
*
* SPDX-License-Identifier: MIT
*
* Copyright (c) 2025 kameHame HA
* 
* All of my pico code is tested on RPi Pico W
*
*/

#ifndef HT16K33_H
#define HT16K33_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <cstdint>
#include <string_view>
#include <map>

class Ht16k33
{
public:
    /**
     * @brief Construct a new Ht16k33 object.
     * @param i2c_port The I2C instance to use.
     * @param i2c_address The I2C address of the HT16K33 device.
     * @param has_colon_display Set to true if the display has a dedicated colon position (5-digit display).
     */
    Ht16k33(i2c_inst_t *i2c_port, uint8_t i2c_address, bool has_colon_display = false);
    
    /**
     * @brief Initializes the HT16K33 display.
     */
    void init();
    
    /**
     * @brief Sets the brightness of the display.
     * @param brightness Brightness level (0-15).
     */
    void setBrightness(uint8_t brightness);
    
    /**
     * @brief Clears the display buffer.
     */
    void clear();
    
    /**
     * @brief Writes the current buffer to the display.
     */
    void writeDisplay();
    
    /**
     * @brief Sets a single digit at the specified position.
     * @param position The position (0-7).
     * @param character The character to display.
     * @param has_dot Whether to show a decimal point.
     */
    void setDigit(uint8_t position, char character, bool has_dot = false);
    
    /**
     * @brief Displays an integer value.
     * @param n The integer to display.
     */
    void displayInt(int n);
    
    /**
     * @brief Displays a hexadecimal value.
     * @param n The hexadecimal value to display.
     */
    void displayHex(uint16_t n);
    
    /**
     * @brief Displays time in HH:MM format with colon.
     * @param hours The hours (0-99).
     * @param minutes The minutes (0-99).
     */
    void displayTime(uint8_t hours, uint8_t minutes);
    
    /**
     * @brief Displays date in DD.MM format with dot.
     * @param day The day (0-99).
     * @param month The month (0-99).
     */
    void displayDate(uint8_t day, uint8_t month);
    
    /**
     * @brief Displays a floating-point number.
     * @param n The float to display.
     * @param decimals Number of decimal places (default 2).
     */
    void displayFloat(float n, uint8_t decimals = 2);
    
    /**
     * @brief Displays raw segment data.
     * @param data Array of raw segment values.
     * @param length Length of the data array.
     */
    void displayRaw(const uint8_t* data, size_t length);

private:
    i2c_inst_t *i2c_port;
    uint8_t i2c_address;
    bool _has_colon_display;
    void sendCommand(uint8_t cmd);
    static constexpr int BUFFER_SIZE = 8;
    uint8_t display_buffer[BUFFER_SIZE];
    static const std::map<char, uint8_t> char_map;
};

#endif // HT16K33_H