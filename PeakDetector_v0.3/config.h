#ifndef __CONFIG_H
#define __CONFIG_H

#define IC_HOLTEK_HT66F0185

#define TM2_ISR

#define CRIT_MAX_AC					240
#define CRIT_MIN_AC					190

#define SYS_TICK                    50000
#define REPETITION_VALUE            40
#define INIT_VALUE					100

// (1005000/5000)
#define VOLTAGE_DIVIDER_FACTOR      201.0
// sqrt(2)
#define AC_DC_CONVERSION_RATE		1.414

// 219 --> 1.2
// x   --> 2.03
// x = 372/4096 = 0.0903
#define CONVERSION_FACTOR			0.08777
#define AC_CALIBRATION_VALUE		215

#define ADC_REF_VOLTAGE				2.03
#define ADC_RESOLUTION				4096.0


#define EEPROM_1ST_SECTOR_START 	0
#define EEPROM_1ST_SECTOR_END		119
#define EEPROM_2ND_SECTOR_START		120
#define EEPROM_2ND_SECTOR_END		127

#define UART_DISPLAY				'd'
#define UART_MONITOR				'm'


#endif
