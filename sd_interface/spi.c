#define IC_HOLTEK_HT66F0185
#include "util.h"
#include "main_ht66f0185.h"
#include "spi.h"


volatile uint8_t res;
uint8_t count = 0;


void SPI_init(void)
{
	uint8_t n;
	count = 0;
    SPI_SS_CONFIG = OUTPUT;
    SPI_CONTROL_REGISTER0 = 0X00;
    SPI_CONTROL_REGISTER2 = 0X00;
    SPI_SET_OPERATING_MODE(SPI_MASTER_FSYS_BY_64);
    SPI_SET_DATA_MODE(SPI_MODE_0);
    SPI_MLS_BIT(SPI_MSB_FIRST);
    SPI_CHIP_SELECT_ENABLE;
    SPI_ENABLE;
}

void SPI_update(void)
{
}



uint8_t SPI_transmit(uint8_t _data)
{
    SPI_DATA_REGISTER = _data;
    SPI_WAIT_TRANSMIT_COMPLETE;
    SPI_DATA_TRANSFER_FLAG_RESET;
    _data = SPI_DATA_REGISTER;
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
