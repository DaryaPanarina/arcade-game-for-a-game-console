#ifndef __LCD__H
#define __LCD__H

//LCD command constans
#define CLEAR           0x01    //requires delay cylce of min 57 NOPs
#define RAM_CG          0x40
#define RAM_DD          0x80

unsigned char getBF(void);
void clear(void);
void home(void);
void setDDRAMaddr(unsigned char addr);
void printChar(unsigned char c);
void printString(unsigned char *str);

#endif //__LCD__H