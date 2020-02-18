#include "aduc812.h"

#define MAXBASE 8

void writeMax(unsigned char xdata *regnum, unsigned char val) {
	unsigned char oldDPP = DPP;
	DPP = MAXBASE;
	*regnum = val;
	DPP = oldDPP;
}

unsigned char readMax(unsigned char xdata *regnum) {
	unsigned char oldDPP = DPP;
	unsigned char val = 0;
	DPP = MAXBASE;
	val = *regnum;
	DPP = oldDPP;
	return val;
}