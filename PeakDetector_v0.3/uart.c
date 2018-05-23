/*  UART MODULE
 *  1- MONITORS THE UART BUFFER FOR ANY RECEIVED DATA
 *  2- SIGNALS THAT TO THE EEPROM MODULE & ADC MODULE TO WORK INTO SPECIFIC MODE (MOINTOR MODE - DISPLAY MODE)
 *
 * Author: mnana3a
 * Date  : 05/03/2018
 *
 * USAGE : used in a data logger device
*/

#include "config.h"
#include "util.h"
#include "port.h"
#include "main_ht66f0185.h"
#include "adc.h"
#include "eeprom.h"
#include "uart.h"

volatile uint8_t gu8Buf_idx = 0;
volatile uint8_t gu8Main_buf[MAX_UART_BUF_SIZE] = {0};
volatile uint8_t gu8Buffer_ready = 0;
volatile static uint8_t uart_signal = 0;

void UART_init(void)
{
    uint8_t i = 0;
    UART_INIT;  
    for (i = 0; i < MAX_UART_BUF_SIZE; i++)
        gu8Main_buf[i] = 0;
    gu8Buf_idx = 0;
    gu8Buffer_ready = 0;
    uart_signal = 0;
}

void UART_update(void)
{
    uint8_t tmp;
    uint8_t cac[5];

    //if (ADC_getSignal() == 0) return ;
    
    ADC_setSignal(0);
    UART_GET_CHAR(tmp);
    if (tmp == UART_DISPLAY)
    {
        UART_PUT_STRING("----------EEPROM_DATA----------");
        UART_PUT_STRING("\n\r");
        UART_PUT_STRING("\n\r");
        uart_signal = 1;
        ADC_setSignal(1);
    }   
    else if (tmp == UART_MONITOR)
    {
        UART_PUT_STRING("\n\r");
        UART_PUT_STRING("----------MONITORING----------");
        UART_PUT_STRING("\n\r");
        uart_signal = 0;
        ADC_setSignal(0);
    }
}

uint8_t UART_getSignal(void)
{
    return uart_signal;
}

void UART_setSignal(uint8_t signal)
{
    uart_signal = signal;
}   
// NOTE:
// this driver depends on the application to read the buffer first before accepting new data
// thus some values will be lost if the sys_tick is high enough that the user input is faster.

void __attribute((interrupt(0x2c))) ISR_uart (void)
{
    volatile char data;
    
    data = TXR_RXR;
    if(gu8Buffer_ready == 0)
    {
        gu8Main_buf[gu8Buf_idx++] = data;
        if(data == TERMINATOR1 || data == TERMINATOR2 || data == TERMINATOR3 || data == TERMINATOR4 || gu8Buf_idx >= MAX_UART_BUF_SIZE-1)
        {
            gu8Main_buf[gu8Buf_idx-1] = TERMINATOR0;
            gu8Buf_idx = 0;
            gu8Buffer_ready = 1;
        }
    }
}
