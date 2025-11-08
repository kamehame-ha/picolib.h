/*
*
* SPDX-License-Identifier: MIT
*
* Copyright (c) 2025 kameHame HA
* 
* All of my pico code is tested on RPi Pico W
*
* This file is a port of the Adafruit_MCP3008 library.
* Original source: https://github.com/adafruit/Adafruit_MCP3008
*
*/

#ifndef PICO_MCP3008_H
#define PICO_MCP3008_H

#include "pico/stdlib.h"
#include "hardware/spi.h"

class Mcp3008
{
public:
    /**
     * @brief Construct a new Mcp3008 object.
     * @param spi_port The SPI instance to use.
     * @param cs_pin The chip select GPIO pin.
     */
    Mcp3008(spi_inst_t *spi_port, uint8_t cs_pin);
    
    /**
     * @brief Initializes the MCP3008 ADC.
     */
    void init();
    
    /**
     * @brief Reads a single-ended ADC value from the specified channel.
     * @param channel The ADC channel to read (0-7).
     * @return The 10-bit ADC value (0-1023) or -1 if channel is invalid.
     */
    int16_t readAdc(uint8_t channel);
    
    /**
     * @brief Reads a differential ADC value from the specified channel pair.
     * @param differential_pair The differential pair to read (0-7).
     * @return The 10-bit differential ADC value or -1 if pair is invalid.
     */
    int16_t readAdcDifference(uint8_t differential_pair);

private:
    int16_t spiTransfer(uint8_t channel, bool is_differential);
    spi_inst_t *_spi_port;
    uint8_t _cs_pin;
};

#endif // PICO_MCP3008_H