// we need to send the initalization code to the sd

// this unique code is to give the sd card time to initialize
CS_DISABLE();
for(i=0; i<10; i++) // idle for 1 bytes / 80 clocks
    SPI_write(0xFF);

// then we start communication using spi
// 1- SD_command(0x40, 0x00000000, 0x95, 8);
// 2- SD_command(0x41, 0x00000000, 0xff, 8);
// 3- SD_command(0x50, 0x00000200, 0xff, 8);
// now we can read or write using the commands from D$

// we need to check the feedback from the sd card as it shows it status, success & failure.

void SD_command(unsigned char cmd, unsigned long arg, 
                unsigned char crc, unsigned char read) {
    unsigned char i, buffer[8];
        
    CS_ENABLE();
    SPI_write(cmd);
    SPI_write(arg>>24);
    SPI_write(arg>>16);
    SPI_write(arg>>8);
    SPI_write(arg);
    SPI_write(crc);
                
    for(i=0; i<read; i++)
        buffer[i] = SPI_write(0xFF);
                
    CS_DISABLE();               
                
    // print out read bytes
}
