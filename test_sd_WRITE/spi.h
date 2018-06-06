#ifndef _SPI_H
#define _SPI_H

#ifndef F_CPU
    #define F_CPU 8000000UL
#endif

#define SPI_SS_CONFIG  _pdc0
#define SPI_SS_PIN     _pd0

extern volatile uint8_t res;

void SPI_init(void);
uint8_t SPI_transmit(uint8_t _data);
void SPI_cs_enable(void);
void SPI_cs_disable(void);
void SPI_update(void);

#endif
