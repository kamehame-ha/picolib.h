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

#include "liquid-crystal-i2c.h"

LiquidCrystal_I2C::LiquidCrystal_I2C(i2c_inst_t *i2c_port, uint8_t i2c_address, uint8_t cols, uint8_t rows)
    : i2c_port(i2c_port), i2c_address(i2c_address), _cols(cols), _rows(rows)
{
    _backlight_val = PIN_BACKLIGHT;
}

bool LiquidCrystal_I2C::init()
{
    _display_function = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;

    sleep_ms(50);

    if (!write4bits(0x03 << 4))
        return false;
    sleep_us(4500);

    if (!write4bits(0x03 << 4))
        return false;
    sleep_us(4500);

    if (!write4bits(0x03 << 4))
        return false;
    sleep_us(150);

    if (!write4bits(0x02 << 4))
        return false;

    if (!command(LCD_FUNCTIONSET | _display_function))
        return false;

    _display_control = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKON;
    display();
    noCursor();
    noBlink();

    clear();

    _display_mode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    if (!command(LCD_ENTRYMODESET | _display_mode))
        return false;

    home();
    return true;
}

void LiquidCrystal_I2C::clear()
{
    command(LCD_CLEARDISPLAY);
    sleep_us(2000);
}

void LiquidCrystal_I2C::home()
{
    command(LCD_RETURNHOME);
    sleep_us(2000);
}

void LiquidCrystal_I2C::setCursor(uint8_t col, uint8_t row)
{
    int row_offsets[] = {0x00, 0x40, 0x00 + _cols, 0x40 + _cols};
    if (row >= _rows)
    {
        row = _rows - 1;
    }
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LiquidCrystal_I2C::print(std::string_view str)
{
    for (char c : str)
    {
        sendData(c);
    }
}

void LiquidCrystal_I2C::display()
{
    _display_control |= LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _display_control);
}

void LiquidCrystal_I2C::noDisplay()
{
    _display_control &= ~LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _display_control);
}

void LiquidCrystal_I2C::cursor()
{
    _display_control |= LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _display_control);
}

void LiquidCrystal_I2C::noCursor()
{
    _display_control &= ~LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _display_control);
}

void LiquidCrystal_I2C::blink()
{
    _display_control |= LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _display_control);
}

void LiquidCrystal_I2C::noBlink()
{
    _display_control &= ~LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _display_control);
}

void LiquidCrystal_I2C::backlight()
{
    _backlight_val = PIN_BACKLIGHT;
    expanderWrite(0);
}

void LiquidCrystal_I2C::noBacklight()
{
    _backlight_val = 0x00;
    expanderWrite(0);
}

void LiquidCrystal_I2C::createChar(uint8_t location, const uint8_t charmap[])
{
    location &= 0x7;
    command(LCD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++)
    {
        sendData(charmap[i]);
    }
}

void LiquidCrystal_I2C::write(uint8_t value)
{
    sendData(value);
}

bool LiquidCrystal_I2C::command(uint8_t command_byte)
{
    return send(command_byte, 0);
}

bool LiquidCrystal_I2C::sendData(uint8_t data_byte)
{
    return send(data_byte, PIN_RS);
}

bool LiquidCrystal_I2C::send(uint8_t value, uint8_t mode)
{
    uint8_t high_nibble = value & 0xF0;
    uint8_t low_nibble = (value << 4) & 0xF0;
    if (!write4bits(high_nibble | mode))
        return false;
    if (!write4bits(low_nibble | mode))
        return false;
    return true;
}

bool LiquidCrystal_I2C::write4bits(uint8_t value)
{
    if (!expanderWrite(value))
        return false;
    if (!pulseEnable(value))
        return false;
    return true;
}

bool LiquidCrystal_I2C::expanderWrite(uint8_t data)
{
    uint8_t packet = data | _backlight_val;
    return i2c_write_blocking(i2c_port, i2c_address, &packet, 1, false) == 1;
}

bool LiquidCrystal_I2C::pulseEnable(uint8_t data)
{
    if (!expanderWrite(data | PIN_EN))
        return false;
    sleep_us(1);
    if (!expanderWrite(data & ~PIN_EN))
        return false;
    sleep_us(50);
    return true;
}