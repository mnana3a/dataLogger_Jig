#include "util.h"
#include "uart.h"
#include "main_ht66f0185.h"
#include "HT66F0185.h"
#include "sd_interface.h"
#include "spi.h"
#include "fat16.h"

uint8_t c[5];

void main()
{
    int8_t i;
    uint32_t j;
    j = 0x140200;
    //char x[6];
    SAFEGUARD_INIT_1;
    //IDLE1_ENABLE;
    UART_init();
    i = SD_init();
    if (i != 0)	UART_PUT_STRING("ERROR\n\r");
    while (i == 1 || i == -1) {UART_PUT_CHAR('.'); delay_100us(); i = SD_init();}
    for (i = 0; i < 5; i++) c[i] = 0;

	i = 0;
	UART_PUT_STRING("\n\rhello\n\r");

    while (1)
    {
        //UART_GET_CHAR(i);
        if (i == 0)
        {
        	i = 0;
		   	SD_seek(j);
		   	i = SD_get(c, 5);
		   	j += 5;
		   	//itoa(i,c);
		   	UART_PUT_STRING(c);
		   	//UART_NEW_LINE;
        }
        else 
        {
        	UART_PUT_STRING("\n\rERROR\n\r");
        	do 
        	{ 
        		UART_PUT_STRING(".");
        		delay_100us();
        		i = SD_init();
        	} while (i != 0);
        }
        
    }
}
