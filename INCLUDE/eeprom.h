#ifndef __EEPROM__H
#define __EEPROM__H

#define EEPROM_ADDRESS  	0xA2
#define EEPROM_SIZE     	32768
#define EEPROM_RECORD_ADDR 	0x00
#define EEPROM_RAND_ADDR 	0x01

unsigned char writeByteEeprom(unsigned short address, unsigned char dataByte);
unsigned char readByteEeprom(unsigned short address, unsigned char *dataByte);

#endif //__EEPROM__H