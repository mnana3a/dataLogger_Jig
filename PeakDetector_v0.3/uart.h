#ifndef __UART_H
#define __UART_H

void UART_init(void);
void UART_update(void);
uint8_t UART_getSignal(void);
void UART_setSignal(uint8_t signal);

#endif