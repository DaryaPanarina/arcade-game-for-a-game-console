#include "eeprom.h"
#include "i2c.h"

unsigned char writeByteEeprom(unsigned short address, unsigned char dataByte) {
    unsigned short try = 0;

        if (address > EEPROM_SIZE)
            return 1;
        
        while (!getAck(EEPROM_ADDRESS)) {
            if (++try > 5000)   //> 10 ms
                return 1;   //EEPROM failed to respond
        }

        if (transmitByte(EEPROM_ADDRESS, address, dataByte))
            return 1;   //Error writing

    return 0;
}

unsigned char readByteEeprom(unsigned short address, unsigned char *dataByte) {
    unsigned short try = 0;

    if (address > EEPROM_SIZE)
        return 1;

    try = 0;

    while (!getAck(EEPROM_ADDRESS)) {
        if (++try > 5000)    //> 10 ms
            return 1;   //EEPROM failed to respond
    }
    
    if (receiveByte(EEPROM_ADDRESS, address, dataByte))
        return 1;   //Error reading

    return 0;
}