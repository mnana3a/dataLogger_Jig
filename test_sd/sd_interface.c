// NOTE: kept the spi driver as a function to make the program memory a small footprint as possible. instead of expanding macros that would take more program memory.

// MISO HAS A PULL UP IN THE CURRENT DRIVE (pull up to 3.3v) ??
// GCC_DELAY(NO._SYS_TICKS)  8M/4 --> 1/2M (0.5 us)--> need 200 ticks to get 100 uS

#include "util.h"
#include "sd_interface.h"
#include "main_ht66f0185.h"
#include "spi.h"

static uint8_t CardType;

void delay_100us(void)
{
    GCC_DELAY(200);
}


static uint8_t p_send_cmd(uint8_t cmd, uint32_t arg)
{
    uint8_t n, res;
    /* Select the card */
    SPI_cs_disable();
    SPI_transmit(0XFF);
    SPI_cs_enable();
    SPI_transmit(0XFF);

    /* Send a command packet */
    SPI_transmit(cmd);                      /* Start + Command index */
    SPI_transmit((uint8_t)(arg >> 24));        /* Argument[31..24] */
    SPI_transmit((uint8_t)(arg >> 16));        /* Argument[23..16] */
    SPI_transmit((uint8_t)(arg >> 8));         /* Argument[15..8] */
    SPI_transmit((uint8_t)arg);                /* Argument[7..0] */
    n = 0x01;                           /* Dummy CRC + Stop */
    if (cmd == CMD0) n = 0x95;          /* Valid CRC for CMD0(0) */
    if (cmd == CMD8) n = 0x87;          /* Valid CRC for CMD8(0x1AA) */
    SPI_transmit(n);

    /* Receive a command response */
    n = 10;                             /* Wait for a valid response in timeout of 10 attempts */
    do {
        res = SPI_transmit(0xff);
    } while ((res & 0x80) && --n);

    return res;         /* Return with the response value */    
}


static uint8_t send_cmd(uint8_t cmd, uint32_t arg)
{
    uint8_t n, res;

    if (cmd & 0x80) {   /* ACMD<n> is the command sequense of CMD55-CMD<n> */
        cmd &= 0x7F;
        res = p_send_cmd(CMD55, 0);
        if (res > 1) return res;
    }
    
    res = p_send_cmd(cmd, arg);
    
    return res;
}


uint8_t SD_init(void)
{
    uint8_t n, cmd, ty, ocr[4];
    uint16_t tmr;

#if _USE_WRITE
    if (CardType && SELECTING) SD_put(0, 0);   /* Finalize write process if it is in progress */
#endif

    SPI_init();
    SPI_cs_disable();
    for (n = 10; n; n--) SPI_transmit(0XFF); /* 80 dummy clocks with CS=H */

    ty = 0;
    if (send_cmd(CMD0, 0) == 1) {           /* GO_IDLE_STATE */
        if (send_cmd(CMD8, 0x1AA) == 1) {   /* SDv2 */
            for (n = 0; n < 4; n++) ocr[n] = SPI_transmit(0xff);     /* Get trailing return value of R7 resp */
            if (ocr[2] == 0x01 && ocr[3] == 0xAA) {         /* The card can work at vdd range of 2.7-3.6V */
                for (tmr = 10000; tmr && send_cmd(ACMD41, 1UL << 30); tmr--) delay_100us();   /* Wait for leaving idle state (ACMD41 with HCS bit) */
                if (tmr && send_cmd(CMD58, 0) == 0) {       /* Check CCS bit in the OCR */
                    for (n = 0; n < 4; n++) ocr[n] = SPI_transmit(0xff);
                    ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;  /* SDv2 (HC or SC) */
                }
            }
        } else {                            /* SDv1 or MMCv3 */
            if (send_cmd(ACMD41, 0) <= 1)   {
                ty = CT_SD1; cmd = ACMD41;  /* SDv1 */
            } else {
                ty = CT_MMC; cmd = CMD1;    /* MMCv3 */
            }
            for (tmr = 10000; tmr && send_cmd(cmd, 0); tmr--) delay_100us();  /* Wait for leaving idle state */
            if (!tmr || send_cmd(CMD16, 512) != 0)          /* Set R/W block length to 512 */
                ty = 0;
        }
    }
    CardType = ty;
    SPI_cs_disable();
    SPI_transmit(0xff);

    return ty ? 0 : STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Read partial sector                                                   */
/*-----------------------------------------------------------------------*/

// buff    :  Pointer to the read buffer (NULL:Forward to the stream) 
// sector  :  Sector number (LBA) 
// offset  :  byte offset to read from (0..511) 
// count   :  Number of bytes to read (ofs + cnt mus be <= 512) 

int8_t SD_get(uint8_t *buff, uint32_t sector, uint16_t offset, uint16_t count)
{
    int8_t res;
    uint8_t rc;
    uint16_t bc;


    if (!(CardType & CT_BLOCK)) sector *= 512;  /* Convert to byte address if needed */

    res = RES_ERROR;
    if (send_cmd(CMD17, sector) == 0)
    { /* READ_SINGLE_BLOCK */
        bc = 40000;         /* Time counter */
        do {                /* Wait for data packet */
            rc = SPI_transmit(0xff);
        } while (rc == 0xFF && --bc);

        if (rc == 0xFE) {   /* A data packet arrived */

            // 512 is the sector size, 2 is the 2 bytes of the CRC
            bc = 512 + 2 - offset - count;  /* Number of trailing bytes to skip */

            /* Skip leading bytes */
            while (offset--) SPI_transmit(0xff);

            /* Receive a part of the sector */
            if (buff) { /* Store data to the memory */
                do {
                    *buff++ = SPI_transmit(0xff);
                } while (--count);
            } else {    /* Forward data to the outgoing stream */
                do {
                    FORWARD(SPI_transmit(0xff));
                } while (--count);
            }

            /* Skip trailing bytes and CRC */
            do SPI_transmit(0xff); while (--bc);

            res = RES_OK;
        }
    }

    SPI_cs_disable();
    SPI_transmit(0xff);

    return res;
}


/*-----------------------------------------------------------------------*/
/* Write partial sector                                                  */
/*-----------------------------------------------------------------------*/
// buff   :   Pointer to the bytes to be written (NULL:Initiate/Finalize sector write) 
// sc     :   Number of bytes to send, Sector number (LBA) or zero 

int8_t SD_put(const uint8_t *buff, uint32_t sc)
{
    int8_t res;
    uint16_t bc;
    static uint16_t wc; /* Sector write counter */

    res = RES_ERROR;

    if (buff) {     /* Send data bytes */
        bc = sc;
        while (bc && wc) {      /* Send data bytes to the card */
            SPI_transmit(*buff++);
            wc--; bc--;
        }
        res = RES_OK;
    } else {
        if (sc) {   /* Initiate sector write process */
            if (!(CardType & CT_BLOCK)) sc *= 512;  /* Convert to byte address if needed */
            if (send_cmd(CMD24, sc) == 0) {         /* WRITE_SINGLE_BLOCK */
                SPI_transmit(0xFF); SPI_transmit(0xFE);     /* Data block header */
                wc = 512;                           /* Set byte counter */
                res = RES_OK;
            }
        } else {    /* Finalize sector write process */
            bc = wc + 2;
            while (bc--) SPI_transmit(0);   /* Fill left bytes and CRC with zeros */
            if ((SPI_transmit(0xff) & 0x1F) == 0x05)
            {   /* Receive data resp and wait for end of write process in timeout of 500ms */
                for (bc = 5000; SPI_transmit(0XFF) != 0xFF && bc; bc--)  /* Wait for ready */
                    delay_100us();
                if (bc) res = RES_OK;
            }
            SPI_cs_disable();
            SPI_transmit(0xff);
        }
    }

    return res;
}
