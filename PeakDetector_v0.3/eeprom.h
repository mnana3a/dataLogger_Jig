#ifndef __EEPROM_H
#define __EEPROM_H

void EEPROM_init(void);
void EEPROM_update(void);
uint8_t EEPROM_getData(void);
void EEPROM_setAddr(uint8_t addr);
uint8_t EEPROM_getAddr(void);
void EEPROM_disable(void);

#endif