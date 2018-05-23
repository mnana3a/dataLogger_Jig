/*
*   Function : creates a timer Interrupt every 1 msec that is used for time purposes
*   Notes    : it uses TIMER0 CTC Mode for operation
*/

#ifndef __SEOS_H
#define __SEOS_H

#define MILLIS __time
//#define MILLIS() __time

extern volatile unsigned long int __time;   // value of msec since last reset ( running cpu time)

void SEOS_init(void);
void SEOS_sleep(void);
void __attribute((interrupt(0x10))) ISR_tmr2 (void);

#endif
