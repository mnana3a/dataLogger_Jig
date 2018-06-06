#include "util.h"
#include "uart.h"
#include "main_ht66f0185.h"
#include "HT66F0185.h"
#include "sd_interface.h"
#include "spi.h"


void main()
{
    int x = 100;
    uint16_t i;
    char c[5];
    SAFEGUARD_INIT_1;
    IDLE1_ENABLE;
    UART_init();
    for (i =0; i < 65000; i++)  GCC_DELAY(200);
    x = SD_init();
        
    while (1)
    {
    }
}
