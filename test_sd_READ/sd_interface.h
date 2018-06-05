#ifndef _DISKIO_DEFINED
#define _DISKIO_DEFINED

#define NULL 				((void *)(0))

// uart handle
#define FORWARD(d)  		UART_PUT_CHAR(d)             /* Data forwarding function (console out) */

extern uint8_t c[5];

uint8_t SD_init(void);
void SD_seek(uint32_t offset);
//int8_t SD_get(uint8_t* buff, uint32_t sector, uint16_t offset, uint16_t count);
int8_t SD_get(uint8_t *buff, uint8_t byte_count);
int8_t SD_put(const uint8_t* buff, uint32_t sc);
uint8_t send_cmd(uint8_t cmd, uint32_t arg);

#define STA_NOINIT      	0x01    /* Drive not initialized */
#define STA_NODISK      	0x02    /* No medium in the drive */

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
#define CMD0                (0x40|0)    /* GO_IDLE_STATE */
#define CMD1                (0x40|1)    /* SEND_OP_COND (MMC) */
#define ACMD41              (0x40|41)   /* SEND_OP_COND (SDC) */
#define CMD8                (0x40|8)    /* SEND_IF_COND */
#define CMD9				(0x40|9)
#define CMD12               (0x40|12)   /* STOP TRANSMISSION */
#define CMD16               (0x40|16)   /* SET_BLOCKLEN */
#define CMD17               (0x40|17)   /* READ_SINGLE_BLOCK */
#define CMD24               (0x40|24)   /* WRITE_BLOCK */
#define CMD55               (0x40|55)   /* APP_CMD */
#define CMD58               (0x40|58)   /* READ_OCR */
#define CMD59				(0X40|59)	/* TURN ON/OFF CRC */


#define IDLE_STATE          0x01     // The state if the card is idle.
#define ILLEGAL_COMMAND     0x04     // The flag for an illegal command.
#define READY_STATE         0x00     // The ready state.
#define DATA_BLOCK_START    0xfe


#endif
