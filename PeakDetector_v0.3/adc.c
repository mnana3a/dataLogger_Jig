/*  ADC MODULE
 *  1- samples the ac mains voltage every 50 msec, calculates the average each 2 sec.
 *  2- calculates the average, min, max voltage measured during system run.
 *
 * Author: mnana3a
 * Date  : 05/03/2018
 *
 * USAGE : used in a data logger device
*/

/*
 * RESTRICTION: when calibrating the ac value better be 215 vAC for higher precision
 * 
 * NOTE: use 215 vAC for calibration as due to the rounding error in the adc, it gives
 *       the lowest error.
 *              (((Vac * 5100 / 1005100) * sqrt(2)) - 0.5) / 0.0004
 *          5.1k , 1M ohms resistors,    0.5: diode forward voltage drop
 *          0.0004: adc step (vref/2^resolution)
 *          ---------------------------------------------------------------------------------------
 *          | CALIBRATION VALUE | 210 | 211 | 212 | 213 | 214 | 215 | 216 | 217 | 218 | 219 | 220 |
 *          ---------------------------------------------------------------------------------------
 *          | ERROR PER READING |x.34 |x.28 |x.22 |x.16 | x.1 |x.04 |x.98 |x.92 |x.86 | x.8 |x.74 |
 *          ---------------------------------------------------------------------------------------
 * ****************************************************************************************************************************
 * NOTE: due to the adc accumulated error, values measured higher or lower than the calibration value isn't accurate and
 *       needs to be calibrated dynamically to get the actual values.
 *
 *       this is done using a curve fitting equation.
 *          the equation if driven from the actual voltage values & the measured voltage values
 *          ---------------------------------------------------------------------------
 *          | ACTUAL voltage values   | 190 | 200 | 210 | 215 | 220 | 230 | 240 | 250 |
 *          ---------------------------------------------------------------------------
 *          | MEASURED voltage values | 185 | 197 | 209 | 215 | 221 | 232 | 244 | 256 |
 *          ---------------------------------------------------------------------------
 *          for example:
 *              at 230v actual, the measured voltage = 232v
 *                  that means the error precense = (232-230) / (230-215) ~= 1/6
 *              at 240v actual, the measured voltage = 244v
 *                  that means the error precense = (244-240) / (240-215) ~= 1/6
 * 
 *                  so we need to add/substract this value to the measured value (depending on how far from
 *                      the calibration value we are).
 * ****************************************************************************************************************************
 * NOTE: the adc conversion into ac value is done as:
 *              AC = ADC_VALUE * Vref(ac) / 2^resolution
 *      Vref(ac) : is the ac value proportional to Vref of the adc ~= 359 VAC
 *
 *      THUS : AC = ADC_VALUE * 359/4096  =  ADC_VALUE * 0.08777   ----> which is defined as CONVERSION_FACTOR
*/

#include "config.h"
#include "main_ht66f0185.h"
#include "HT66F0185.h"
#include "util.h"
#include "port.h"
#include "uart.h"
#include "adc.h"
#include "eeprom.h"

volatile static double adc_val0 = 0;
volatile static uint16_t ac = 0, maxAC = 0, minAC = 0;
volatile static uint16_t counter = 0;
static uint32_t tmp = 0;
volatile static uint8_t adc_signal = 0;
volatile static uint8_t initCounter = 0;
static uint16_t maxTime = 0, minTime = 0;
static uint8_t maxFlag = 0, minFlag = 0;
static uint16_t runtime_counter = 0;

void ADC_init(void)
{
    ADC_INIT;
    adc_val0 = 0;
    ac = 0;
    maxAC = MIN_UINT16;
    minAC = MAX_UINT16;
    counter = 0;
    tmp = 0;
    adc_signal = 0;
    initCounter = 0;
    maxTime = 0;
    minTime = 0;
    maxFlag = 0;
    minFlag = 0;
    runtime_counter = 0; 
    
    // capacitor charge build-up delay at system power up
    while (initCounter < INIT_VALUE)
    {
        initCounter++;
    }
}

void ADC_update(void)
{
    uint8_t c[5];
    if (UART_getSignal() == 0)
    {
        counter++;
        ADC_READ(ADC_CHANNEL0);
        tmp += ADC_DATA_REG;
    
        if (counter == REPETITION_VALUE)
        {
            runtime_counter++;      // occurs once each 2000 msec
            ADC_OFF;
            GPIO_DDRB = 0X00;
            GPIO_PORTB = 0;

            // convert the adc reading into ac value
            adc_val0 = (float)((float)tmp/counter) * CONVERSION_FACTOR; 
            UART_NEW_LINE;
            itoa(adc_val0, c);
            UART_PUT_STRING(c);
            UART_NEW_LINE;
    
            // due to non-linearity of the adc reading. (curve fitting)
            //if (adc_val0 < 60)    adc_val0 = 0;
            if (adc_val0 > AC_CALIBRATION_VALUE)    adc_val0 = adc_val0 - ((adc_val0 - AC_CALIBRATION_VALUE) / 6);
            else if (adc_val0 < AC_CALIBRATION_VALUE)   adc_val0 = adc_val0 + ((AC_CALIBRATION_VALUE - adc_val0) / 7);
            
            itoa(adc_val0, c);
            UART_PUT_STRING(c);
            UART_NEW_LINE;
            ac = (uint16_t) adc_val0;
            
            if (ac > maxAC) maxAC = ac;
            else if (ac < minAC)    minAC = ac;
            
            
            if (!maxFlag && ac > CRIT_MAX_AC)
            {
                // take a snapshot of the time
                maxFlag = 1;
                maxTime = runtime_counter;
            }
            else if (!minFlag && ac < CRIT_MIN_AC)
            {
                // take a snapshot of the time
                minFlag = 1;
                minTime = runtime_counter;
            }   
            else
            {
                if (maxFlag && ac < CRIT_MAX_AC) {maxTime = ((runtime_counter - maxTime)<<1); maxFlag = 0; runtime_counter = 0;}
                else if (minFlag && ac > CRIT_MIN_AC) {minTime = ((runtime_counter - minTime)<<1) ; minFlag = 0; runtime_counter = 0;}
            }
                
            adc_signal = 1;
            TOG_BIT(SYS_INDICATION_PORT, SYS_INDICATION_PIN);
            tmp = 0;
            counter = 0;
            ADC_ON(0);
        }
    }
}

uint16_t ADC_getValue(uint8_t adc_channel)
{
    return ac;
}

uint16_t ADC_getMax(void)
{
    return maxAC;
}

uint16_t ADC_getMin(void)
{
    return minAC;
}

uint16_t ADC_getMaxTime(void)
{
    return maxTime;
}

uint16_t ADC_getMinTime(void)
{
    return minTime;
}

uint8_t ADC_getSignal(void)
{
    return adc_signal;
}

void ADC_setSignal(uint8_t signal)
{
    adc_signal = signal;
}

uint16_t ADC_getCount(void)
{
    return counter;
}

#if 0
void ADC_setCount(uint16_t count)
{
    counter = count;
}
#endif
