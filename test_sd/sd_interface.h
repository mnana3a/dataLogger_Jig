#ifndef _DISKIO_DEFINED
#define _DISKIO_DEFINED

// uart handle
#define FORWARD(d)  UART_PUT_CHAR(d)             /* Data forwarding function (console out) */


uint8_t SD_init(void);
int8_t SD_get(uint8_t* buff, uint32_t sector, uint16_t offset, uint16_t count);
int8_t SD_put(const uint8_t* buff, uint32_t sc);

#define STA_NOINIT      0x01    /* Drive not initialized */
#define STA_NODISK      0x02    /* No medium in the drive */

/* Card type flags (CardType) */
#define CT_MMC              0x01    /* MMC ver 3 */
#define CT_SD1              0x02    /* SD ver 1 */
#define CT_SD2              0x04    /* SD ver 2 */
#define CT_SDC              (CT_SD1|CT_SD2) /* SD */
#define CT_BLOCK            0x08    /* Block addressing */


#define RES_OK              0      /* 0: Function succeeded */
#define RES_ERROR           1      /* 1: Disk error */
#define RES_NOTRDY          2     /* 2: Not ready */
#define RES_PARERR          3

/* Definitions for MMC/SDC command */
#define CMD0    (0x40+0)    /* GO_IDLE_STATE */
#define CMD1    (0x40+1)    /* SEND_OP_COND (MMC) */
#define ACMD41  (0xC0+41)   /* SEND_OP_COND (SDC) */
#define CMD8    (0x40+8)    /* SEND_IF_COND */
#define CMD16   (0x40+16)   /* SET_BLOCKLEN */
#define CMD17   (0x40+17)   /* READ_SINGLE_BLOCK */
#define CMD24   (0x40+24)   /* WRITE_BLOCK */
#define CMD55   (0x40+55)   /* APP_CMD */
#define CMD58   (0x40+58)   /* READ_OCR */


#endif
