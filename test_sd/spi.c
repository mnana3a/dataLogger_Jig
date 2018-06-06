#include "util.h"
#include "main_ht66f0185.h"
#include "spi.h"


volatile uint8_t res;
uint8_t count = 0;


void SPI_init(void)
{
    uint8_t n;
    count = 0;
    SPI_INIT;
}

void SPI_update(void)
{
}

uint8_t SPI_transmit(uint8_t _data)
{
    SPI_XMIT(_data);
    return _data;
}

void SPI_cs_enable(void)
{
    SPI_SS_PIN = LOW;
}

void SPI_cs_disable(void)
{
    SPI_SS_PIN = HIGH;
}
