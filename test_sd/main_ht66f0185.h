#ifndef __IC_HOLTEK_HT66F0185
#define __IC_HOLTEK_HT66F0185

#include "HT66F0185.h"
#include "util.h"

#define IAR0 (*((volatile unsigned char *)0x00))
#define MP0 (*((volatile unsigned char *)0x01))
#define IAR1 (*((volatile unsigned char *)0x02))
#define MP1 (*((volatile unsigned char *)0x03))
#define BP (*((volatile unsigned char *)0x04))
#define ACC (*((volatile unsigned char *)0x05))
#define PCL (*((volatile unsigned char *)0x06))
#define TBLB (*((volatile unsigned char *)0x07))
#define TBLH (*((volatile unsigned char *)0x08))
#define TBHP (*((volatile unsigned char *)0x09))
#define STATUS (*((volatile unsigned char *)0x0A))
#define SMOD (*((volatile unsigned char *)0x0B))
#define LVDC (*((volatile unsigned char *)0x0C))
#define INTEG (*((volatile unsigned char *)0x0D))
#define INTC0 (*((volatile unsigned char *)0x0E))
#define INTC1 (*((volatile unsigned char *)0x0F))
#define INTC2 (*((volatile unsigned char *)0x10))
#define MFI0 (*((volatile unsigned char *)0x11))
#define MFI1 (*((volatile unsigned char *)0x12))
#define MFI2 (*((volatile unsigned char *)0x13))
//#define GPIO_PORTA (*((volatile unsigned char *)0x14))
//#define GPIO_DDRA (*((volatile unsigned char *)0x15))
#define PUA (*((volatile unsigned char *)0x16))
#define WAKEA (*((volatile unsigned char *)0x17))

#define TMPC (*((volatile unsigned char *)0x19))
#define WDTC (*((volatile unsigned char *)0x1A))
#define TBC (*((volatile unsigned char *)0x1B))
#define CTRL (*((volatile unsigned char *)0x1C))
#define LVRC (*((volatile unsigned char *)0x1D))
#define EEA (*((volatile unsigned char *)0x1E))
#define EED (*((volatile unsigned char *)0x1F))
#define SADOL (*((volatile unsigned char *)0x20))
#define SADOH (*((volatile unsigned char *)0x21))
#define SADC0 (*((volatile unsigned char *)0x22))
#define SADC1 (*((volatile unsigned char *)0x23))
#define SADC2 (*((volatile unsigned char *)0x24))
//#define GPIO_PORTB (*((volatile unsigned char *)0x25))
//#define GPIO_DDRB (*((volatile unsigned char *)0x26))
#define PUB (*((volatile unsigned char *)0x27))
#define TM2C0 (*((volatile unsigned char *)0x28))
#define TM2C1 (*((volatile unsigned char *)0x29))
#define TM2DL (*((volatile unsigned char *)0x2A))
#define TM2DH (*((volatile unsigned char *)0x2B))
#define TM2AL (*((volatile unsigned char *)0x2C))
#define TM2AH (*((volatile unsigned char *)0x2D))
#define TM2RP (*((volatile unsigned char *)0x2E))
#define TM0C0 (*((volatile unsigned char *)0x2F))
#define TM0C1 (*((volatile unsigned char *)0x30))
#define TM0DL (*((volatile unsigned char *)0x31))
#define TM0DH (*((volatile unsigned char *)0x32))
#define TM0AL (*((volatile unsigned char *)0x33))
#define TM0AH (*((volatile unsigned char *)0x34))
#define TM0RP (*((volatile unsigned char *)0x35))

#define TM1C0 (*((volatile unsigned char *)0x37))
#define TM1C1 (*((volatile unsigned char *)0x38))
#define TM1DL (*((volatile unsigned char *)0x39))
#define TM1DH (*((volatile unsigned char *)0x3A))
#define TM1AL (*((volatile unsigned char *)0x3B))
#define TM1AH (*((volatile unsigned char *)0x3C))
#define TM1RPL (*((volatile unsigned char *)0x3D))
#define TM1RPH (*((volatile unsigned char *)0x3E))
#define CPC (*((volatile unsigned char *)0x3F))

#define EEC (*((volatile unsigned char *)0x40))   // ONLY IN BANK 1
//#define GPIO_PORTC (*((volatile unsigned char *)0x41))
//#define GPIO_DDRC (*((volatile unsigned char *)0x42))
#define PUC (*((volatile unsigned char *)0x43))
#define ACERL (*((volatile unsigned char *)0x44))
#define SIMC0 (*((volatile unsigned char *)0x45))
#define SIMC1 (*((volatile unsigned char *)0x46))
#define SIMD (*((volatile unsigned char *)0x47))
#define SIMA (*((volatile unsigned char *)0x48))    // SHARED LOCATION
#define SIMC2 (*((volatile unsigned char *)0x48))   // SHARED LOCATION
#define SIMTOC (*((volatile unsigned char *)0x49))
#define SLCDC0 (*((volatile unsigned char *)0x4A))
#define SLCDC1 (*((volatile unsigned char *)0x4B))
#define SLCDC2 (*((volatile unsigned char *)0x4C))
#define SLCDC3 (*((volatile unsigned char *)0x4D))
#define SLCDC4 (*((volatile unsigned char *)0x4E))
#define SLEDC0 (*((volatile unsigned char *)0x4F))
#define SLEDC1 (*((volatile unsigned char *)0x50))
#define IFS (*((volatile unsigned char *)0x51))
//#define GPIO_PORTD (*((volatile unsigned char *)0x52))
//#define GPIO_DDRD (*((volatile unsigned char *)0x53))
#define PUD (*((volatile unsigned char *)0x54))
#define USR (*((volatile unsigned char *)0x55))
#define UCR1 (*((volatile unsigned char *)0x56))
#define UCR2 (*((volatile unsigned char *)0x57))
#define BRG (*((volatile unsigned char *)0x58))
#define TXR_RXR (*((volatile unsigned char *)0x59))

#define GPIO_DDRA  (_pac)
#define GPIO_DDRB  (_pbc)
#define GPIO_DDRC  (_pcc)
#define GPIO_DDRD  (_pdc)

#define GPIO_PORTA (_pa)
#define GPIO_PORTB (_pb)
#define GPIO_PORTC (_pc)
#define GPIO_PORTD (_pd)

#define  GPIO_PINA (_pa)
#define  GPIO_PINB (_pb)
#define  GPIO_PINC (_pc)
#define  GPIO_PIND (_pd)

#define DELAY_uS(x) (_delay(x))

#define RAM_BANK1 (0x180)

//clear flag
#define FLAG_CLEAR (0)
/***********************************************************************************/
//global interrupt enable bit
#define GLOBAL_INTERRUPTS_ENABLE     (_emi=1)
#define GLOBAL_INTERRUPTS_DISABLE    (_emi=0)
#define CRITICAL_SECTION_START       (_emi=0)
#define CRITICAL_SECTION_END         (_emi=1)                    
/***********************************************************************************/
//ADC config
#define ADC_CONTROL_REG0 SADC0
#define ADC_CONTROL_REG1 SADC1
#define ADC_CONTROL_REG2 SADC2
#define ADC_CONFIG_PINS_REG ACERL
#define ADC_START CONTROL_BIT(ADC_CONTROL_REG0, 7, 1)
#define ADC_STOP CONTROL_BIT(ADC_CONTROL_REG0, 7, 0)
#define ADC_CHANNEL0 (0)
#define ADC_CHANNEL1 (1)
#define ADC_CHANNEL2 (2)
#define ADC_CHANNEL3 (3)
#define ADC_CHANNEL4 (4)
#define ADC_CHANNEL5 (5)
#define ADC_CHANNEL6 (6)
#define ADC_CHANNEL7 (7)
// as interrupt isn't used adc flag is set to be the end of conversion flag                    
#define ADC_FLAG _adbz
#define ADC_FLAG_CLEAR ADC_FLAG =0;

// TEST:
#define ADC_CHANNEL_SELECT(channel) \
                do{\
                    _sacs0 = channel;\
                }while(0)

#define ADC_READ(ainput)  do {\
                    ADC_FLAG_CLEAR; ADC_CONFIG_PINS_REG = (1<<ainput);\
                    ADC_CONTROL_REG0 = (0x30 | ainput);\
                    ADC_STOP;\
                    ADC_START;\
                    ADC_STOP;\
                    while (ADC_FLAG == 0);\
                    ADC_FLAG_CLEAR;\
                    _adf = 0;\
                    } while (0)

#define ADC_OFF do {\
                    CLR_BIT(ADC_CONTROL_REG0, 5);\
                    SET_REG(ADC_CONFIG_PINS_REG, 0X00);\
                } while (0)
                
#define ADC_ON(adc)     do {\
                        CONFIG_REG(ADC_CONFIG_PINS_REG, (1<<adc));\
                        SET_BIT(ADC_CONTROL_REG0, 5);\
                        } while (0) 
#define ADC_DATA_REG ((uint16_t)(((uint16_t)_sadoh<<8) | (uint16_t)_sadol))
//#define ADC_DATA_REG (tWord)(((_sadol>>4) & 0x000F) | ((_sadoh<<4) & 0x0FF0));       // 8-bit mode

// prescaler 16                      
#define ADC_INIT  do{\
                    CONFIG_REG(ADC_CONTROL_REG1, 0B10000100);\
                    CONFIG_REG(ADC_CONFIG_PINS_REG, 0X01);\
                    _ade = 0;_adf = 0;\
                    ADC_CONTROL_REG2 = 0b11011010;\
                    CONFIG_REG(ADC_CONTROL_REG0, 0B00110000);\
                    }while(0)
/***********************************************************************************/               
/* External interrupt 0 configuration **********************************************/
/***********************************************************************************/
#define EXT_INTERRUPT0_ENABLE   do{\
                            GLOBLE_INTERRUPT_ENABLE;\
                            EXTERNAL_INTERRUPT_ENABLE;\
                            _et0i = 0;\
                            _eadi = 0;\
                            }while(0)
//IR external interrupt 0 on The falling edge of INT1 generates an interrupt request.
#define IR_INTERRUPT_ENABLE     \
                (_int0e = 1)
                
#define IR_INTERRUPT_EDGE_SET  \
                do{ _int0s0 =0; _int0s1 =1; \
                }while(0)
                
#define IR_INTERRUPT_DISABLE  (_int0e = 0)

#define IR_INTERRUPT_FLAG_CLEAR     \
                (_int0f = 0)
/***********************************************************************************/               
/* External interrupt 1 configuration **********************************************/
/***********************************************************************************/
//ZCD external interrupt enable bit
#define ZCD_INTERRUPT_ENABLE  \
                (_int1e = 1)

//ZCD external interrupt on Rising and falling edges
#define ZCD_INTERRUPT_EDGE_SET  \
                do{_int1s0 =1; _int1s1 =1;\
                }while(0)

//ZCD external interrupt flag
#define ZCD_INTERRUPT_FLAG  \
                (_int1f)

//clear ZCD external interrupt flag bit
#define ZCD_INTERRUPT_FLAG_CLEAR    \
                (ZCD_INTERRUPT_FLAG=0)
/***********************************************************************************/
//external interrupt on falling edge
#define EXTERNAL_INTERRUPT_ENABLE  (_eei=1)
//external interrupt flag
#define EXTERNAL_INTERRUPT_FLAG     _eif
//clear flag bits
#define EXTERNAL_INTERRUPT_FLAG_CLEAR    (EXTERNAL_INTERRUPT_FLAG=0)            
/* timer0 config for Buzzer timer **************************************************/
/***********************************************************************************/
//timer register
#define BUZZER_TIMER_REGL  (_tm0al)
#define BUZZER_TIMER_REGH  (_tm0ah)
//timer flag
 //TIMER_INTERRUPT_FLAG     (_tb0f)
 //TIMER_FLAG               (_t0af)
#define BUZZER_TIMER_FLAG   (_t0af)
//clear flag bits           
#define CLEAR_BUZZER_TIMER_FLAG_BIT (BUZZER_TIMER_FLAG=0)

#define BUZZER_UPDATE_TIMER_REG(time_us)    \
                do{\
                    BUZZER_TIMER_REGL = ((tWord)(time_us)/8);\
                    BUZZER_TIMER_REGH = ((tWord)(time_us)/8)>>8;\
                }while(0)
                    
// Set timer as timer mode 
#define BUZZER_SET_TIMER_ENBLE_BIT  \
                do{ _t0pau=0; _t0ck2 = 0;_t0ck1 = 1; _t0ck0 = 1;_t0on=0;\
                    _t0m1 = 0; _t0m0 = 0; _t0io0 = 1;_t0io1 = 1;_t0oc = 0;_t0pol = 0;_t0cclr = 1;\
                    _tm0al = 0xff; _tm0ah = 0xff;_t0cp = 1;\
                }while(0)
                            
#define BUZZER_START_TIMER  \
                do{ CLEAR_BUZZER_TIMER_FLAG_BIT;\
                    _t0on = 1;\
                }while(0)
                                
#define BUZZER_STOP_TIMER   \
                do{ CLEAR_BUZZER_TIMER_FLAG_BIT;\
                    _t0on = 0;\
                }while(0)
                            
#define BUZZER_ENABLE_TIMER_INTERRUPT   \
                (_tb0e = 0)
/***********************************************************************************/               
/* timer2 config for sEOS timer **************************************************/
/***********************************************************************************/
//timer registers
#define TM2_DATAL   (_tm2dl)
#define TM2_DATAH   (_tm2dh)
#define TM2_COMP_AL (_tm2al)
#define TM2_COMP_AH (_tm2ah)
#define TM2_COMP_PL (_tm2rp)
//timer flags
 // TIMER_FLAG              (_t2af)
 // TIMER_INTERRUPT_FLAG    (_mf2f)
 // Timer Comparator P flag (_t2pf) 
#define TIMER2_FLAG                  (_t2af)
#define TIMER2_COMPARATOR_A_FLAG     (_t2af)
#define MULTIFUCTION_1_FLAG          (_mf1f)

//timer_reg equation
#define sEOS_TIMER_UPDATE(time_us)  \
                do{ \
                    TM2_COMP_AL = (uint8_t)((uint16_t)((time_us)>>3));\
                    TM2_COMP_AH = (uint8_t)(((uint16_t)((time_us)>>3))>>8);\
                }while(0)

#define sEOS_TIMER_READ \
                ( ((uint16_t)((uint16_t)_tm2dh)<<8)|(_tm2dl) )
                
//clear flag bits                   
#define sEOS_TIMER_FLAG_CLEAR \
                do{ TIMER2_FLAG = 0;\
                    MULTIFUCTION_1_FLAG = 0;\
                }while(0)
                
// Set timer MODE AS COMPARE 
// set the prescaler to 64
#define sEOS_TIMER_MODE_SET    \
                do{ _tm2c0 = 0b00110000;\
                    _tm2c1 = 0b00000001;\
                    _tm2al = 0; _tm2ah = 0;\
                }while(0)

//_t2capts=0;_t2cp=0;                                               
#define sEOS_TIMER_START    \
                do{ sEOS_TIMER_FLAG_CLEAR;\
                    _t2on = 1;\
                }while(0)
                
#define sEOS_TIMER_STOP     \
                do{ sEOS_TIMER_FLAG_CLEAR;\
                    _t2on = 0;\
                }while(0)

//time base interrupt enable
  //enable timer2 comparator p interrupt    (_t2pe =1)      
  //enable multifunction 2 interrupt enable (_mf2e =1)                      
#define TM2_INTERRUPT_ENABLE \
                do{\
                    _t2ae =1;_mf1e =1;\
                }while(0)

/*
// with 64 prescaler , 1ms timeout
#define sEOS_TIMER_ENABLE(time_us)   \
                            do{\
                            sEOS_TIMER_UPDATE(time_us);\
                            sEOS_TIMER_MODE_SET;\
                            TM2_INTERRUPT_SET;\
                            GLOBAL_INTERRUPTS_ENABLE;\
                            sEOS_TIMER_START;\
                            }while(0)
*/
#define sEOS_TIMER_ENABLE(time_us)  do{\
                                    sEOS_TIMER_MODE_SET;\
                                    sEOS_TIMER_UPDATE(time_us);\
                                    sEOS_TIMER_START;\
                                    TM2_INTERRUPT_ENABLE;\
                                    GLOBAL_INTERRUPTS_ENABLE;\
                                    }while (0)
/***********************************************************************************/                           
/* timer1 config for sandwiches ****************************************************/
/***********************************************************************************/
//maximum time =8000ms because of the limitation of prescaler and osc 
//timer register
#define TIMER1_REG_DATAL    (_tm1dl)
#define TIMER1_REG_DATAH    (_tm1dh)
#define TIMER1_REG_COMP_AL  (_tm1al)
#define TIMER1_REG_COMP_AH  (_tm1ah)
#define TIMER1_REG_COMP_PL  (_tm1rpl)
#define TIMER1_REG_COMP_PH  (_tm1rph)
                
//timer_reg equation
#define UPDATE_SANDWICH_TIMER_REG(time_us)  \
                do{ \
                    TIMER_REG_COMP_PL = ((tWord)(time_us)/8);\
                    TIMER_REG_COMP_PH = ((tWord)(time_us)/8)>>8;\
                }while (0)
                

#define READ_SANDWICH_TIMER_VALUE \
                ( (((tWord)_tm1dh)<<8)|(_tm1dl) )

//timer flags
 // TIMER_FLAG              (_t1af)
 // TIMER_INTERRUPT_FLAG    (_mf1f)
 // Timer Comparator P flaf (_t1pf)
#define TIMER1_FLAG                  (_t1af)
#define TIMER1_COMPARATOR_P_FLAG     (_t1pf)
#define MULTIFUCTION_1_FLAG          (_mf1f)
                
//clear flag bits
#define CLEAR_SANDWICH_TIMER_FLAG_BIT \
                do{ TIMER1_FLAG = 0;TIMER1_COMPARATOR_P_FLAG = 0;\
                    MULTIFUCTION_1_FLAG=0;\
                }while(0)

// Set timer as timer mode 
// _tm1rp = 0;
#define SET_SANDWICH_TIMER_ENBLE_BIT    \
                do{ _t1cp = 0; _t1on = 0; _t1pau = 0;_t1ck2 = 0;_t1ck1 = 1; _t1ck0 = 1;\
                    _t1m1 = 0; _t1m0 = 0;_t1io0=0;_t1io1=0;_t1cclr = 0;_t1capts=0;_t1pol=0;_t1oc=0;\
                    _tm1al = 0; _tm1ah = 0;\
                }while(0)
                
#define START_SANDWICH_TIMER    \
                do{ CLEAR_sEOS_TIMER_FLAG_BIT;\
                    _t1on = 1;\
                }while(0)
                
#define STOP_SANDWICH_TIMER     \
                do{ CLEAR_sEOS_TIMER_FLAG_BIT;\
                    _t1on = 0;\
                }while(0)

//time base interrupt enable
  //enable timer1 comparator p interrupt    (_t1pe =1)      
  //enable multifunction 1 interrupt enable (_mf1e =1)
                    
#define sANDWICH_ENABLE_TIMER_INTERRUPT \
                do{\
                    _t1pe =1;_mf1e =1;\
                }while(0)
/***********************************************************************************/                         
/* SPI Configuration ***************************************************************/
/***********************************************************************************/       
#define SPI_ENABLE_BIT                                  (_simen)
#define SPI_DATA_REGISTER                               (_simd)
#define SPI_WRITE_COLLESION_FLAG                        (_wcol)
#define SPI_CHIP_SELECT_ENABLE_BIT                      (_csen)
#define SPI_INTERRUPT_ENABLE_BIT                        (_sime)
#define SPI_DATA_ORDER_BIT                              (_mls)
#define SPI_TRANSMIT_COMPLETE_FLAG                      (_trf)
#define SPI_SLAVE_INCOMPLETE_FLAG                       (_simicf)
#define SPI_CONTROL_REGISTER0                           (_simc0)
#define SPI_CONTROL_REGISTER2                           (_simc2)

//constatnts assignment
#define SPI_MODE_MASK                                   (7)
#define SPI_MASTER_FSYS_BY_4                            (0)
#define SPI_MASTER_FSYS_BY_16                           (1)
#define SPI_MASTER_FSYS_BY_64                           (2)
#define SPI_MASTER_FTBC                                 (3)
#define SPI_MASTER_TMR1                                 (4)
#define SPI_SLAVE                                       (5)
#define SPI_NONE                                        (7)
#define SPI_MODE_0                                      (0)
#define SPI_MODE_1                                      (1)
#define SPI_MODE_2                                      (2)
#define SPI_MODE_3                                      (3)
#define SPI_LSB_FIRST                                   (0)
#define SPI_MSB_FIRST                                   (1)
#define SPI_SLAVE_RECEIVING_HEADER                      (0x02)
#define SPI_SLAVE_SENDING_HEADER                        (0x03)
#define SPI_SLAVE_HEADER_BREAK                          (0x00)
#define SPI_FRAME_LENGTH                                (32)
#define MATCHED                                         (0)

// if you enable cs to be controlled by the spi, to set it, just enable the spi using simen... when putting simen =1 it pulls down the cs pin, when simen = 0 it pulls high the cs pin.

// prescaler = /64
//use these two macros to set operating and data mode
#define SPI_SET_OPERATING_MODE(SPI_MODE)      (SPI_CONTROL_REGISTER0 = (SPI_CONTROL_REGISTER0 & (~(5<<5))) | (SPI_MODE << 5))
#define SPI_SET_DATA_MODE(SPI_DATA_MODE)      (SPI_CONTROL_REGISTER2 = (SPI_CONTROL_REGISTER2 & (~(3<<4))) | (SPI_DATA_MODE << 4))

//use these macro to set which bit to be send first most or least
#define SPI_MLS_BIT(MLS_MODE)                 (SPI_DATA_ORDER_BIT = MLS_MODE)

//use these two macros to enable or disable spi module
#define SPI_ENABLE                            (SPI_ENABLE_BIT = TRUE)
#define SPI_DISABLE                           (SPI_ENABLE_BIT = FALSE)

#define SPI_WAIT_TRANSMIT_COMPLETE  do{\
                                        while((SPI_CONTROL_REGISTER2 & (1<<SPI_TRANSMIT_COMPLETE_FLAG)) == 0);\
                                    } while(0)

//use these two macros to enable or disable chip select bin
#define SPI_CHIP_SELECT_ENABLE                (SPI_CHIP_SELECT_ENABLE_BIT = TRUE)
#define SPI_CHIP_SELECT_DISABLE               (SPI_CHIP_SELECT_ENABLE_BIT = FALSE)

//use these two macros to enable or disable spi interrupt
#define SPI_INTERRUPT_CONTROL_ENABLE          (SPI_INTERRUPT_ENABLE_BIT = TRUE)
#define SPI_INTERRUPT_CONTROL_DISABLE         (SPI_INTERRUPT_ENABLE_BIT = FALSE)

//use these two macros to set or reset data transfer flag
#define SPI_DATA_TRANSFER_FLAG_RESET          (SPI_TRANSMIT_COMPLETE_FLAG = FALSE)
#define SPI_DATA_TRANSFER_FLAG_SET            (SPI_TRANSMIT_COMPLETE_FLAG = TRUE)

//use these two macros to set or reset incomplete data transfer flag
#define SPI_SIM_INCOMPLETE_FLAG_SET           (SPI_SLAVE_INCOMPLETE_FLAG = TRUE)
#define SPI_SIM_INCOMPLETE_FLAG_RESET         (SPI_SLAVE_INCOMPLETE_FLAG = FALSE)

//use these two macros to set or reset data transfer flag
#define SPI_WRITE_COLLISION_FLAG_SET          (SPI_WRITE_COLLESION_FLAG = TRUE)
#define SPI_WRITE_COLLISION_FLAG_RESET        (SPI_WRITE_COLLESION_FLAG = FALSE)


// NOTE: change this according to the spi config.
#define SPI_INIT        do{\
                            SPI_SS_CONFIG = OUTPUT;\
                            SPI_CONTROL_REGISTER0 = 0X00;\
                            SPI_CONTROL_REGISTER2 = 0X00;\
                            SPI_SET_OPERATING_MODE(SPI_MASTER_FSYS_BY_64);\
                            SPI_SET_DATA_MODE(SPI_MODE_0);\
                            SPI_MLS_BIT(SPI_MSB_FIRST);\
                            SPI_CHIP_SELECT_ENABLE;\
                            SPI_ENABLE;\
                        } while (0)


#define SPI_XMIT(_data)  do{\
                            SPI_DATA_REGISTER = _data;\
                            SPI_WAIT_TRANSMIT_COMPLETE;\
                            SPI_DATA_TRANSFER_FLAG_RESET;\
                            _data = SPI_DATA_REGISTER;\
                        } while (0)


#define SPI_RCV(_data)  do{\
                            SPI_DATA_REGISTER = 0xff;\
                            SPI_WAIT_TRANSMIT_COMPLETE;\
                            SPI_DATA_TRANSFER_FLAG_RESET;\
                            _data = SPI_DATA_REGISTER;\
                        } while (0)
/***********************************************************************************/                            
/* UART Configuration ***************************************************************/
/***********************************************************************************/ 
// uart config
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#define UART_CONTROL_REG1       UCR1
#define UART_CONTROL_REG2       UCR2
#define UART_STATUS_REG         USR
#define UART_BAUD_REG           BRG
#define UART_DATA_REG           TXR_RXR
#define BAUD_RATE               (9600)
#define BAUD_PRESCALER          (((F_CPU) / ( 16UL * BAUD_RATE )) - 1 )
#define UART_TRANSMIT_FLAG      (_txif)

#define TERMINATOR0             '\0'
#define TERMINATOR1             '\n'
#define TERMINATOR2             '\r'
#define TERMINATOR3             '\r\n'
#define TERMINATOR4             '\n\r'
#define UART_RECEIVE_ENABLE     BIT2
#define UART_INTERRUPT_ENABLE   _ure=1
#define MAX_UART_BUF_SIZE       5

#define UART_INIT do{\
                    UART_INTERRUPT_ENABLE;\
                    CONFIG_REG(UART_CONTROL_REG1, 0B10000000);\
                    UART_BAUD_REG = 12;\
                    CONFIG_REG(UART_CONTROL_REG2, 0B11000100);\
                    GLOBAL_INTERRUPTS_ENABLE;\
                    } while (0)

#define UART_PUT_CHAR(u8data)  do{\
                                while(!(UART_STATUS_REG & (1<<0)));\
                                TXR_RXR = u8data;\
                                } while (0)
                          
#define UART_PUT_STRING(u8SData)  do{\
                                    uint8_t i = 0;\
                                    while(*(u8SData+i)){\
                                      UART_PUT_CHAR(*(u8SData+i));\
                                      i++;\
                                    }\
                                    UART_PUT_CHAR('\0');\
                                    } while (0)          
extern volatile uint8_t gu8Main_buf[MAX_UART_BUF_SIZE];
extern volatile uint8_t gu8Buffer_ready, gu8Buffer_flushed;
                                              
#define UART_GET_CHAR(u8data) do{\
                                volatile static uint8_t bufCounter = 0;\
                                if (gu8Buffer_ready)\
                                {\
                                    u8data = gu8Main_buf[bufCounter++];\
                                    if (u8data == TERMINATOR0 || bufCounter >= MAX_UART_BUF_SIZE){ \
                                        bufCounter = 0;\
                                        gu8Buffer_ready = 0;\
                                    }\
                                }\
                                else    u8data = TERMINATOR0;\
                                } while(0) 

//NOTE: obselete                                
#define UART_GET_STRING(u8SData)  do{\
                                    uint8_t i = 0;\
                                    while(UART_GET_CHAR(*(u8SData+i)) != TERMINATOR){\
                                      i++;\
                                    }\
                                    *(u8SData+i) = '\0';\
                                    } while (0)
                                    

#define UART_NEW_LINE   UART_PUT_STRING("\n\r")
/***********************************************************************************/                            
/* Internal EEPROM Configuration ***************************************************/
/***********************************************************************************/                   
// indirect access to the control reg eec: set bp=1, mp1 = 0x40 (eec location in bank1)
// then to write to the eec indirectly using iar1
#define EEPROM_MAX_ADD 128
#define EEPROM_ADDRESS_REG (_eea)
#define EEPROM_DATA_REG (_eed)
#define INDIRECT_ADDR_REG_1 (_iar1)
#define EEPROM_CONTROL_REG (_eec)
      
#define EEPROM_PUT_ADDR(addr)\
                do{\
                    EEPROM_ADDRESS_REG = addr;\
                }while (0)
        
#define EEPROM_GET_ADDR(addr)\
                do{\
                    addr = EEPROM_ADDRESS_REG;\
                }while (0)
                    
#define EEPROM_PUT_DATA(data)\
                do{\
                    EEPROM_DATA_REG = data;\
                }while (0)
                
#define EEPROM_GET_DATA(data)\
                do{\
                    data = EEPROM_DATA_REG;\
                }while (0)
  
#define EEPROM_WRITE(address, data) \
                do{\
                    EEPROM_ADDRESS_REG = address;\
                    EEPROM_DATA_REG = data;\
                    _mp1 = 0x40;\
                    _bp  = 0x01;\
                    GLOBAL_INTERRUPTS_DISABLE;\
                    SET_BIT(_iar1,3);\
                    SET_BIT(_iar1,2);\
                    GLOBAL_INTERRUPTS_ENABLE;\
                    EEPROM_WAIT_WRITE_CYCLE_END;\
                    EEPROM_WRITE_DISABLE;\
                }while(0)
                    
#define EEPROM_WRITE_DISABLE    \
                do{\
                    _iar1 = 0;\
                    _bp  = 0;\
                }while(0)

#define EEPROM_CHECK_WRITE_CYCLE_END \
                do{\
                    if(GET_BIT(INDIRECT_ADDR_REG_1, BIT2) != 0){\
                        return ;\
                    }\
                }while(0)
                
#define EEPROM_WAIT_WRITE_CYCLE_END\
                do{\
                    while (GET_BIT(INDIRECT_ADDR_REG_1, BIT2) != 0);\
                } while (0)
                    
#define EEPROM_READ(address, data)\
                do{\
                    EEPROM_ADDRESS_REG = address;\
                    _mp1 = 0x40;\
                    _bp  = 0x01;\
                    SET_BIT(_iar1,1);\
                    SET_BIT(_iar1,0);\
                    EEPROM_CHECK_READ_CYCLE_END;\
                    EEPROM_READ_DISABLE;\
                    data = EEPROM_DATA_REG;\
                }while(0)

#define EEPROM_READ_DISABLE \
                do{\
                    _iar1 = 0;\
                    _bp  = 0;\
                }while(0)
                    
#define EEPROM_CHECK_READ_CYCLE_END \
                do{\
                    while(GET_BIT(INDIRECT_ADDR_REG_1,BIT0) != 0);\
                }while(0)    
                
// THIS DISABLES BOTH READ & WRITE OPERATIONS TO THE EEPROM
#define EEPROM_DISABLE\
                do {\
                    _iar1 = 0;\
                    _bp = 0;\
                } while (0)           
/***********************************************************************************/                            
/* WDT Configuration ***************************************************************/
/***********************************************************************************/   
#define WDT_CLEAR    _clrwdt()

#define WDT_ENABLE   do{\
            _we0 = 0;_we1 = 1;_we2 = 0;_we3 = 1;_we4 = 0;\
            _ws0=1;_ws1=0;_ws2=0;\
        }while(0)
        
#define WDT_DISABLE  do{\
            _wdtc = 0b10101000;\
        }while(0)
/***********************************************************************************/                            
/* SAFEGARD Init *******************************************************************/
/***********************************************************************************/                                               
//initialize registers for safeguard

// _hlclk=1;_cks0=0;_cks1=0;_cks2=0;
// to_enable_WDT : _we0 = 0;_we1 = 1;_we2 = 0;_we3 = 1;_we4 = 0;_ws0=1;_ws1=0;_ws2=0;
// to_disble_WDT : _we0 = 1;_we1 = 0;_we2 = 1;_we3 = 0;_we4 = 1;_ws0=1;_ws1=0;_ws2=0;
// to enable LVR for 4VDC : _lvrf=0;_lrf=0;_lvrc=0b10101010;
// to disable LCD control bins : _slcdc0=0x00;_slcdc1=0x00;_slcdc2=0x00;_slcdc3=0x00;_slcdc4=0x00;\
// to disable ADC :  _ade=0;_acerl=0x00;_sadc0=0x00;_sadc1=0x00;_sadc2=0x00;\
// to disable UART : _uarten=0;_txen=0;_rxen=0;_ucr1=0x00;_ucr2=0x00;_tmpc=0x00;\
// to disable SPI AND I2C :  _sledc0=0xff;_sledc1=0xff;_simc0=0x00;\
// to disable comparator pin Cout :  _cpc=0b00001001;\
// to disable pin remapping :  _ifs=0x00;\ 

#define SAFEGUARD_INIT  ( )

#define SAFEGUARD_INIT_1    \
                do{\
                WDT_DISABLE;\
                _cpc=0b00001000;\
                _pa= 0x00;_pb = 0x00; _pc = 0x00; _pd=0x00;\
                _pac = 0xff;_pbc = 0xff;_pcc = 0xff;_pdc = 0xff;\
                _pawu=0x00;_papu=0x00;_pbpu=0x00;_pcpu=0x00;_pdpu=0x00;\
                }while(0)


//to enable LVR for 2.55V: //_lvrf=0;_lrf=0;_lvrc=0b00110011;
#define SAFEGUARD_INIT_2    \
                do{\
                _cpc=0b00001000;\
                _we0 = 1;_we1 = 0;_we2 = 1;_we3 = 0;_we4 = 1;_ws0=1;_ws1=0;_ws2=0;\
                _lvrf=0;_lrf=0;_lvrc=0b00110011;_ifs=0x00;\
                _slcdc0=0x00;_slcdc1=0x00;_slcdc2=0x00;_slcdc3=0x00;_slcdc4=0x00;\
                _ade=0;_acerl=0x00;_sadc0=0x00;_sadc1=0x00;_sadc2=0x00;\
                _uarten=0;_txen=0;_rxen=0;_ucr1=0x00;_ucr2=0x00;_tmpc=0x00;\
                _sledc0=0xff;_sledc1=0xff;_simc0=0xE0;\
                }while(0)
/***********************************************************************************/
// ENABLE IDLE MODE 1
#define IDLE1_ENABLE do{\
                        SMOD |= (1<<1);\
                        CTRL |= (1<<7);\
                        } while (0)
#define SLEEP asm("halt")

#endif
