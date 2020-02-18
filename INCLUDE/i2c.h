#ifndef __I2C__H
#define __I2C__H

unsigned char getAck(unsigned char periphAddr); 
unsigned char receiveByte(unsigned char periphAddr, unsigned char addr, unsigned char *dataByte);
unsigned char transmitByte(unsigned char periphAddr, unsigned char addr, unsigned char dataByte);

#endif //_I2C_H