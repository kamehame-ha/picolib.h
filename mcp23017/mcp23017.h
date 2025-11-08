/*
*
* SPDX-License-Identifier: MIT
*
* Copyright (c) 2025 kameHame HA
* 
* All of my pico code is tested on RPi Pico W
*
*/

#ifndef MCP23017_H
#define MCP23017_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <cstdint>

class Mcp23017
{
public:
    enum class PinDirection
    {
        OUTPUT = 0,
        INPUT = 1
    };

    /**
     * @brief Construct a new Mcp23017 object.
     * @param i2c_port The I2C instance to use.
     * @param i2c_address The I2C address of the MCP23017 device.
     */
    Mcp23017(i2c_inst_t *i2c_port, uint8_t i2c_address);
    
    /**
     * @brief Initializes the MCP23017 with all pins as inputs.
     */
    void init();
    
    /**
     * @brief Sets the direction of a single pin.
     * @param pin Pin number (0-15).
     * @param direction Pin direction (INPUT or OUTPUT).
     */
    void setPinDirection(uint8_t pin, PinDirection direction);
    
    /**
     * @brief Sets the direction of all pins in a port.
     * @param port Port number (0 or 1).
     * @param direction_mask Bitmask where 1=INPUT, 0=OUTPUT.
     */
    void setPortDirection(uint8_t port, uint8_t direction_mask);
    
    /**
     * @brief Writes a digital value to a single pin.
     * @param pin Pin number (0-15).
     * @param state Pin state (true=HIGH, false=LOW).
     */
    void writePin(uint8_t pin, bool state);
    
    /**
     * @brief Writes values to all pins in a port.
     * @param port Port number (0 or 1).
     * @param value 8-bit value to write to the port.
     */
    void writePort(uint8_t port, uint8_t value);
    
    /**
     * @brief Reads the digital value of a single pin.
     * @param pin Pin number (0-15).
     * @return Pin state (true=HIGH, false=LOW).
     */
    bool readPin(uint8_t pin);
    
    /**
     * @brief Reads the values of all pins in a port.
     * @param port Port number (0 or 1).
     * @return 8-bit value representing the port state.
     */
    uint8_t readPort(uint8_t port);

private:
    static constexpr uint8_t REG_IODIRA = 0x00;
    static constexpr uint8_t REG_IODIRB = 0x01;
    static constexpr uint8_t REG_GPIOA = 0x12;
    static constexpr uint8_t REG_GPIOB = 0x13;
    static constexpr uint8_t REG_OLATA = 0x14;
    static constexpr uint8_t REG_OLATB = 0x15;

    i2c_inst_t *i2c_port;
    uint8_t i2c_address;

    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
};

#endif // MCP23017_H