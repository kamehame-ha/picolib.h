/*
*
* SPDX-License-Identifier: MIT
*
* Copyright (c) 2025 kameHame HA
* 
* All of my pico code is tested on RPi Pico W
*
* This file is a port of the Arduino LiquidCrystal_I2C library.
* Original source: https://github.com/lucasmaziero/LiquidCrystal_I2C
*
*/

#ifndef LIQUID_CRYSTAL_I2C_H
#define LIQUID_CRYSTAL_I2C_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <string_view>

class LiquidCrystal_I2C
{
public:
    /**
     * @brief Construct a new LiquidCrystal_I2C object.
     * @param i2c_port The I2C instance to use.
     * @param i2c_address The I2C address of the LCD device.
     * @param cols Number of columns.
     * @param rows Number of rows.
     */
    LiquidCrystal_I2C(i2c_inst_t *i2c_port, uint8_t i2c_address, uint8_t cols, uint8_t rows);
    
    /**
     * @brief Initializes the LCD display.
     * @return true if initialization was successful, false otherwise.
     */
    bool init();
    
    /**
     * @brief Clears the display.
     */
    void clear();
    
    /**
     * @brief Returns cursor to home position.
     */
    void home();
    
    /**
     * @brief Sets the cursor position.
     * @param col Column position.
     * @param row Row position.
     */
    void setCursor(uint8_t col, uint8_t row);
    
    /**
     * @brief Prints a string to the display.
     * @param str The string to print.
     */
    void print(std::string_view str);
    
    /**
     * @brief Turns on the display.
     */
    void display();
    
    /**
     * @brief Turns off the display.
     */
    void noDisplay();
    
    /**
     * @brief Shows the cursor.
     */
    void cursor();
    
    /**
     * @brief Hides the cursor.
     */
    void noCursor();
    
    /**
     * @brief Enables cursor blinking.
     */
    void blink();
    
    /**
     * @brief Disables cursor blinking.
     */
    void noBlink();
    
    /**
     * @brief Turns on the backlight.
     */
    void backlight();
    
    /**
     * @brief Turns off the backlight.
     */
    void noBacklight();
    
    /**
     * @brief Creates a custom character.
     * @param location Character location (0-7).
     * @param charmap Character bitmap (8 bytes).
     */
    void createChar(uint8_t location, const uint8_t charmap[]);
    
    /**
     * @brief Writes a single byte to the display.
     * @param value The byte value to write.
     */
    void write(uint8_t value);

private:
    bool send(uint8_t value, uint8_t mode);
    bool write4bits(uint8_t value);
    bool expanderWrite(uint8_t data);
    bool pulseEnable(uint8_t data);
    bool command(uint8_t command_byte);
    bool sendData(uint8_t data_byte);

    i2c_inst_t *i2c_port;
    uint8_t i2c_address;
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _backlight_val;
    uint8_t _display_function;
    uint8_t _display_control;
    uint8_t _display_mode;

    static constexpr uint8_t LCD_CLEARDISPLAY = 0x01;
    static constexpr uint8_t LCD_RETURNHOME = 0x02;
    static constexpr uint8_t LCD_ENTRYMODESET = 0x04;
    static constexpr uint8_t LCD_DISPLAYCONTROL = 0x08;
    static constexpr uint8_t LCD_CURSORSHIFT = 0x10;
    static constexpr uint8_t LCD_FUNCTIONSET = 0x20;
    static constexpr uint8_t LCD_SETCGRAMADDR = 0x40;
    static constexpr uint8_t LCD_SETDDRAMADDR = 0x80;

    static constexpr uint8_t LCD_ENTRYLEFT = 0x02;
    static constexpr uint8_t LCD_ENTRYSHIFTDECREMENT = 0x00;

    static constexpr uint8_t LCD_DISPLAYON = 0x04;
    static constexpr uint8_t LCD_CURSORON = 0x02;
    static constexpr uint8_t LCD_BLINKON = 0x01;

    static constexpr uint8_t LCD_4BITMODE = 0x00;
    static constexpr uint8_t LCD_2LINE = 0x08;
    static constexpr uint8_t LCD_5x8DOTS = 0x00;

    // I2C Expander Pinout
    static constexpr uint8_t PIN_RS = 0x01; // Register Select
    static constexpr uint8_t PIN_RW = 0x02; // Read/Write (not used)
    static constexpr uint8_t PIN_EN = 0x04; // Enable
    static constexpr uint8_t PIN_BACKLIGHT = 0x08;
};

#endif // LIQUID_CRYSTAL_I2C_H