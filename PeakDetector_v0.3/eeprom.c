/*  EEPROM MODULE
 *  1- receives data from the adc & stores it in eeprom
 *  2- monitors a flag from the uart, if set it will display the eeprom content on the serial monitor
 *
 * Author: mnana3a
 * Date  : 05/03/2018
 *
 * USAGE : used in a data logger device
*/

// NOTE: EEPROM_WRITE here waits for the write operation to compelete that takes up to 
//       20 msec for 4 write operations. if the app. needs to poll&pass without waiting
//       you need to changet the EEPROM_WRITE macro from main.h

#include "config.h"
#include "main_ht66f0185.h"
#include "HT66F0185.h"
#include "util.h"
#include "adc.h"
#include "uart.h"
#include "eeprom.h"
#include "port.h"

volatile static uint8_t stSCTR_addr = 0x00;     // address pointer in the 1st sector
volatile static uint8_t ndSCTR_addr = 0x00;     // address pointer in the 2nd sector
volatile static uint8_t stSCTR_data = 0x00;     // samples
volatile static uint8_t ndSCTR_data = 0x00;     // max/min/average data
static uint8_t flag = 0;


void EEPROM_init(void)
{
    stSCTR_addr = 0;
    stSCTR_data = 0;
    ndSCTR_addr = 120;
    ndSCTR_data = 0;
    flag = 0;
}

        
void EEPROM_update(void)
{
    uint8_t i = 0;
    uint8_t cac[5];
    if (ADC_getSignal() == 0) return ;
    
    if (!flag) {    UART_PUT_STRING("Address Voltage");UART_NEW_LINE; flag =1;}
    if (UART_getSignal())
    {
        for (i =0; i <= EEPROM_2ND_SECTOR_END; i++)
        {
            if (i == 0)
            {
                UART_PUT_STRING("----------START_1ST_SECTOR----------");
                UART_PUT_STRING("\n\r");
            }
            else if (i == 120)
            {
                UART_PUT_STRING("----------START_2ND_SECTOR----------");
                UART_PUT_STRING("\n\r");
            }
            else if (i == 127)
            {
                UART_PUT_STRING("----------ADDR._POINTER----------");
                UART_PUT_STRING("\n\r");
            }
            EEPROM_setAddr(i);
            itoa(i, cac);
            UART_PUT_STRING(cac);
            UART_PUT_STRING(" ");
            if (i > 121 && i != 126)
                itoa(EEPROM_getData(), cac);
            else
                itoa((EEPROM_getData()<<1), cac);
                
            UART_PUT_STRING(cac);
            UART_PUT_STRING("\n\r");
        }
        UART_PUT_STRING("------------END------------");
        UART_PUT_STRING("\n\r");
        EEPROM_setAddr(EEPROM_1ST_SECTOR_START);
        //UART_setSignal(0);
        ADC_setSignal(0);
        CLR_BIT(SYS_INDICATION_PORT, SYS_INDICATION_PIN);
    }
    else
    {
        stSCTR_data = (uint8_t)((uint16_t)ADC_getValue(ADC_CHANNEL0) >> 1);
        EEPROM_WRITE(stSCTR_addr, stSCTR_data);
        
        itoa(EEPROM_getAddr(), cac);
        UART_PUT_STRING(cac);
        UART_PUT_STRING(" ");
        itoa((EEPROM_getData()<<1), cac);
        UART_PUT_STRING(cac);
        UART_NEW_LINE;
        //UART_NEW_LINE;
        
        EEPROM_WRITE(127, stSCTR_addr);
        
        
        ndSCTR_data = (uint8_t)((uint16_t)ADC_getMax() >> 1);
        EEPROM_WRITE(ndSCTR_addr, ndSCTR_data);
        ndSCTR_addr++;
        
        ndSCTR_data = (uint8_t)((uint16_t)ADC_getMin() >> 1);
        EEPROM_WRITE(ndSCTR_addr, ndSCTR_data);
        ndSCTR_addr++;
        
        ndSCTR_data = (uint8_t)ADC_getMaxTime();
        EEPROM_WRITE(ndSCTR_addr, ndSCTR_data);
        ndSCTR_addr++;
        ndSCTR_data = (uint8_t)(ADC_getMaxTime() >> 8);
        EEPROM_WRITE(ndSCTR_addr, ndSCTR_data);
        ndSCTR_addr++;
        
        ndSCTR_data = (uint8_t)ADC_getMinTime();
        EEPROM_WRITE(ndSCTR_addr, ndSCTR_data);
        ndSCTR_addr++;
        ndSCTR_data = (uint8_t)(ADC_getMinTime() >> 8);
        EEPROM_WRITE(ndSCTR_addr, ndSCTR_data);
        ndSCTR_addr = EEPROM_2ND_SECTOR_START;
        
        
        if (stSCTR_addr < EEPROM_1ST_SECTOR_END) stSCTR_addr++;
        else stSCTR_addr = EEPROM_1ST_SECTOR_START;
    }
}

uint8_t EEPROM_getData(void)
{
    EEPROM_READ(stSCTR_addr, stSCTR_data);
    return stSCTR_data;
}

void EEPROM_setAddr(uint8_t addr)
{
    stSCTR_addr = addr;
}

uint8_t EEPROM_getAddr(void)
{
    return stSCTR_addr;
}

// this disables both READ & WRITE opeartions, i.e., you CAN'T use the eeprom
void EEPROM_disable(void)
{
    EEPROM_DISABLE;
}
