#include "aduc812.h"
#include "max.h"

#define COL1 0xFE
#define COL3 0xFB
#define COL4 0xF7

static unsigned char buttonAState = 0, buttonBState = 0, buttonCState = 0, button7State = 0, button9State = 0;
static unsigned char row;

static void delay(int ms) {
    int i, j;
    
    for (j = 0; j < ms; j++) {
        for (i = 0; i < 50; i++);
    } 
}

void initKeyboardTimer(void) {
	TH0 = 0x00;
	TL0 = 0x00;
	TMOD = 0x01;
	TCON = 0x10;
}

void T0Handling(void) __interrupt (1) {
	EA = 0;

	//Start
	writeMax(KB, COL4);
	row = readMax(KB) & 0x10;
	if (!row) {
		buttonAState = 1;
		delay(10);
		row = readMax(KB) & 0x10;
		if (row)
			buttonAState = 0;
	} else
		buttonAState = 0;

	//Stop
	writeMax(KB, COL4);
	row = readMax(KB) & 0x20;
	if (!row) {
		buttonBState = 1;
		delay(10);
		row = readMax(KB) & 0x20;
		if (row)
			buttonBState = 0;
	} else
		buttonBState = 0;

	//Record reset
	writeMax(KB, COL4);
	row = readMax(KB) & 0x40;
	if (!row) {
		buttonCState = 1;
		delay(10);
		row = readMax(KB) & 0x40;
		if (row)
			buttonCState = 0;
	} else
		buttonCState = 0;

	//Left
	writeMax(KB, COL1);
	row = readMax(KB) & 0x40;
	if (!row) {
		button7State = 1;
		delay(10);
		row = readMax(KB) & 0x40;
		if (row)
			button7State = 0;
	} else
		button7State = 0;

	//Right
	writeMax(KB, COL3);
	row = readMax(KB) & 0x40;
	if (!row) {
		button9State = 1;
		delay(10);
		row = readMax(KB) & 0x40;
		if (row)
			button9State = 0;
	} else
		button9State = 0;

	EA = 1;
}

unsigned char isStartPressed(void) {
	return buttonAState;
}

unsigned char isStopPressed(void) {
	return buttonBState;
}

unsigned char isRecResetPressed(void) {
	return buttonCState;
}

unsigned char isLeftPressed(void) {
	return button7State;
}

unsigned char isRightPressed(void) {
	return button9State;
}