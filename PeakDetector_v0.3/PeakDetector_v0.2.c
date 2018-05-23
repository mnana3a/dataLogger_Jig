/*  PEAKDETECTOR_v0.3
 *  1- INITIATES THE MODULES
 *  2- ENABLE SLEEP MODE
 *  3- GOES INTO SLEEP MODE WAITING FOR sEOS INTERRUPT
 *
 * Author: mnana3a
 * Date  : 05/03/2018
 *
 * USAGE : monitors the ac mains voltage, samples & record it in eeprom,
 *         if a signal 'd' is sent through the serial port it will display the recorded data onto the serial monitor
*/

// RESTRICTION: when calibrating the ac value better be 215 vAC for higher precision

#include "config.h"
#include "util.h"
#include "uart.h"
#include "adc.h"
#include "seos.h"
#include "main_ht66f0185.h"
#include "port.h"
#include "HT66F0185.h"
#include "eeprom.h"

void main()
{
    SAFEGUARD_INIT_1;
    IDLE1_ENABLE;
    UART_init();
    ADC_init();
    EEPROM_init();
    
    CONTROL_BIT(SYS_INDICATION_DDR, SYS_INDICATION_PIN, OUTPUT);
    CONTROL_BIT(SYS_INDICATION_PORT, SYS_INDICATION_PIN, HIGH);
    
    SEOS_init();
    while (1)
    {
        SEOS_sleep();
    }
}
