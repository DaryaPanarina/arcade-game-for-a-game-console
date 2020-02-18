#include "aduc812.h"
#include "max.h"
#include "lcd.h"

unsigned char getBF(void) {
	unsigned char BF_AC;
	writeMax(C_IND, 0x03);
	BF_AC = readMax(DATA_IND);        //Read Busy flag (DB7) and AC (DB6-0)
	writeMax(C_IND, 0x02);
	return BF_AC >> 7;
}

void clear(void) {
	while (getBF() != 0);
	writeMax(DATA_IND, CLEAR);
	writeMax(C_IND, 0x01);
	writeMax(C_IND, 0x00);
}

void setDDRAMaddr(unsigned char addr) {
	while (getBF() != 0);
	writeMax(DATA_IND, RAM_DD | addr);
	writeMax(C_IND, 0x01);
	writeMax(C_IND, 0x00);
}

void printChar(unsigned char c) {
	while (getBF() != 0);
	writeMax(DATA_IND, c);
	writeMax(C_IND, 0x05);
	writeMax(C_IND, 0x04);
}

void printString(unsigned char *str) {
    while (*str)
        printChar(*str++);
}