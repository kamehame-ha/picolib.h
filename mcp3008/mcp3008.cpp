/*
*
* Port created by kameHame HA
* 
* All of my pico code is tested on RPi Pico W
*
* Ported to Pico from: https://github.com/adafruit/Adafruit_MCP3008
*
*/

#include "mcp3008.h"

Mcp3008::Mcp3008(spi_inst_t *spi_port, uint8_t cs_pin)
    : _spi_port(spi_port), _cs_pin(cs_pin)
{
}

void Mcp3008::init()
{
    gpio_init(_cs_pin);
    gpio_set_dir(_cs_pin, GPIO_OUT);
    gpio_put(_cs_pin, 1);
}

int16_t Mcp3008::readAdc(uint8_t channel)
{
    if (channel > 7)
        return -1;
    return spiTransfer(channel, false);
}

int16_t Mcp3008::readAdcDifference(uint8_t differential_pair)
{
    if (differential_pair > 7)
        return -1;
    return spiTransfer(differential_pair, true);
}

int16_t Mcp3008::spiTransfer(uint8_t channel, bool is_differential)
{
    uint8_t command = 0x01;
    if (!is_differential)
        command |= 0x08;
    command |= (channel & 0x07) << 1;

    uint8_t tx_buf[3] = {0x01, command << 4, 0x00};
    uint8_t rx_buf[3];

    gpio_put(_cs_pin, 0);
    spi_write_read_blocking(_spi_port, tx_buf, rx_buf, 3);
    gpio_put(_cs_pin, 1);

    int16_t result = ((rx_buf[1] & 0x03) << 8) | rx_buf[2];
    return result;
}