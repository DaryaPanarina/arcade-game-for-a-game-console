#include "aduc812.h"
#include "max.h"

void writeLEDs(unsigned char on) {
	writeMax(SV, on);
}