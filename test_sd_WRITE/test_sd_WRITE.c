#define _WRITE

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
	FAT16_init();
	i = 0;
	UART_PUT_STRING("\n\rhello\n\r");
	
	FAT16_create_file("TST    ", "TXT");

    while (1)
    {
    	
    	UART_GET_STRING(fat16_buffer);
    	
        while (fat16_buffer[i] != 0) i++;
        fat16_buffer[i++] = '\n';
        FAT16_write_file(i);
        //fwrite(fat16_buffer, counter, 1, out); // Write read bytes
        i = 0;        
    }
}
