/*  SEOS MODULE
 *  1- initates the timer2 module to work periodically
 *  2- each time the interrupt occurs, it updates the 3 other modules (adc - eeprom - uart)
 *
 * Author: mnana3a
 * Date  : 05/03/2018
 *
 * USAGE : used in a data logger device
*/

#include "config.h"
#include "seos.h"
#include "main_ht66f0185.h"
#include "HT66F0185.h"
#include "uart.h"
#include "port.h"

void SEOS_init(void)
{
    sEOS_TIMER_ENABLE(SYS_TICK);
}

void SEOS_sleep(void)
{
    SLEEP;
}

void __attribute((interrupt(0x10))) ISR_tmr2 (void)
{
    ADC_update();
    EEPROM_update();
    UART_update();
    sEOS_TIMER_FLAG_CLEAR;
}
