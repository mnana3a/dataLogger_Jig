#ifndef __ADC_H
#define __ADC_H

void ADC_init(void);
void ADC_update(void);
uint16_t ADC_getValue(uint8_t adc_channel);
uint16_t ADC_getMin(void);
uint16_t ADC_getMax(void);
uint16_t ADC_getCount(void);
uint8_t ADC_getSignal(void);
void ADC_setCount(uint16_t count);
void ADC_setSignal(uint8_t signal);
uint16_t ADC_getMaxTime(void);
uint16_t ADC_getMinTime(void);

#endif