/*
*
* SPDX-License-Identifier: MIT
*
* Copyright (c) 2025 kameHame HA
* 
* All of my pico code is tested on RPi Pico W
*
*/

#include "mcp23017.h"

Mcp23017::Mcp23017(i2c_inst_t *i2c_port, uint8_t i2c_address)
    : i2c_port(i2c_port), i2c_address(i2c_address)
{
}

void Mcp23017::init()
{
    // Set both ports to be inputs by default, which is a safe state.
    // 0xFF means all 8 bits are 1 (INPUT).
    writeRegister(REG_IODIRA, 0xFF);
    writeRegister(REG_IODIRB, 0xFF);
}

void Mcp23017::setPinDirection(uint8_t pin, PinDirection direction)
{
    if (pin > 15)
        return;

    uint8_t reg = (pin < 8) ? REG_IODIRA : REG_IODIRB;
    uint8_t bit = pin % 8;

    uint8_t current_dir = readRegister(reg);

    if (direction == PinDirection::INPUT)
    {
        current_dir |= (1 << bit);
    }
    else
    {
        current_dir &= ~(1 << bit);
    }
    writeRegister(reg, current_dir);
}

void Mcp23017::setPortDirection(uint8_t port, uint8_t direction_mask)
{
    if (port > 1)
        return;
    writeRegister(port == 0 ? REG_IODIRA : REG_IODIRB, direction_mask);
}

void Mcp23017::writePin(uint8_t pin, bool state)
{
    if (pin > 15)
        return;

    uint8_t reg = (pin < 8) ? REG_OLATA : REG_OLATB;
    uint8_t bit = pin % 8;

    uint8_t current_val = readRegister(reg);

    if (state)
    {
        current_val |= (1 << bit);
    }
    else
    {
        current_val &= ~(1 << bit);
    }
    writeRegister(reg, current_val);
}

void Mcp23017::writePort(uint8_t port, uint8_t value)
{
    if (port > 1)
        return;
    writeRegister(port == 0 ? REG_OLATA : REG_OLATB, value);
}

bool Mcp23017::readPin(uint8_t pin)
{
    if (pin > 15)
        return false;

    uint8_t reg = (pin < 8) ? REG_GPIOA : REG_GPIOB;
    uint8_t bit = pin % 8;

    uint8_t value = readRegister(reg);
    return (value & (1 << bit)) != 0;
}

uint8_t Mcp23017::readPort(uint8_t port)
{
    if (port > 1)
        return 0;
    return readRegister(port == 0 ? REG_GPIOA : REG_GPIOB);
}


void Mcp23017::writeRegister(uint8_t reg, uint8_t value)
{
    uint8_t data[] = {reg, value};
    i2c_write_blocking(i2c_port, i2c_address, data, 2, false);
}

uint8_t Mcp23017::readRegister(uint8_t reg)
{
    uint8_t value;
    i2c_write_blocking(i2c_port, i2c_address, &reg, 1, true);
    i2c_read_blocking(i2c_port, i2c_address, &value, 1, false);
    return value;
}