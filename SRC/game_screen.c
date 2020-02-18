#include <stdlib.h>
#include "aduc812.h"
#include "max.h"
#include "lcd.h"
#include "game_screen.h"

static unsigned char platformCurPos = 0, cubeCurPos = 0, cubeFallStage = 0, gamerRes = 0, cubeCnt = 0;
static char waitCnt = 0;
static unsigned char chars[7][8] = {
	{0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C},
	{0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00},
	{0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x1F, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x1F, 0x00}};

unsigned char initRand(unsigned char randSeed) {
	srand(randSeed);
	return randSeed + 1;
}

void initGameTimer(void) {
	TH1 = 0x00;
	TL1 = 0x00;
	TMOD |= 0x10;
	TCON |= 0x40;
	platformCurPos = 0;
	cubeCurPos = 0;
	cubeFallStage = 0;
	waitCnt = 0;
}

void defineUserChars(void) {
	unsigned char i, j;
	
	while (getBF() != 0);
	writeMax(DATA_IND, RAM_CG);
	writeMax(C_IND, 0x01);
	writeMax(C_IND, 0x00);
	for (i = 0; i < 7; i++)
		for (j = 0; j < 8; j++)
			printChar(chars[i][j]);
}

void drawMainScreen(void) {
	clear();
	setDDRAMaddr(0x00);
	printString("Hello!");
	setDDRAMaddr(0x40);
	printString("Press A to start");
	platformCurPos = 0;
	cubeCurPos = 0;
	cubeFallStage = 0;
	waitCnt = 0;
}

void drawStartScreen(void) {
	clear();
	platformCurPos = 0x48;
	setDDRAMaddr(platformCurPos);
	printChar(PLAT);
	gamerRes = 0;
	cubeCnt = 0;
}

void drawFinishScreen(unsigned char isRecord) {
	clear();
	setDDRAMaddr(0x00);
	printChar(gamerRes + 0x30);
	printChar(SLASH);
	printString(MAX_CUBE_CNT_STR);
	if (isRecord) {
		setDDRAMaddr(0x40);
		printString("New record!");
	}
}

void drawRecResetScreen(unsigned char isReset) {
	clear();
	setDDRAMaddr(0x00);
	if (isReset)
		printString("Record reset");
	else {
		printString("Reset record");
		setDDRAMaddr(0x40);
		printString("failed");
	}
}

void movePlatformToLeft(void) {
	if (0x40 == platformCurPos)
		return;
	EA = 0;
	setDDRAMaddr(platformCurPos);
	if (platformCurPos == cubeCurPos)
		printChar(cubeFallStage - 4);
	else
		printChar(SPACE);
	platformCurPos--;
	setDDRAMaddr(platformCurPos);
	printChar(PLAT);
	EA = 1;
}

void movePlatformToRight(void) {
	if (0x4F == platformCurPos)
		return;
	EA = 0;
	setDDRAMaddr(platformCurPos);
	if (platformCurPos == cubeCurPos)
		printChar(cubeFallStage - 4);
	else
		printChar(SPACE);
	platformCurPos++;
	setDDRAMaddr(platformCurPos);
	printChar(PLAT);
	EA = 1;
}

unsigned char isGameFinished(void) {
	if (cubeCnt == MAX_CUBE_CNT)
		return 1;
	else
		return 0;
}

unsigned char getGameRes(void) {
	return gamerRes;
}

void T1Handling(void) __interrupt (3) {
	//EA = 0;
	if (waitCnt >= 0)
		waitCnt++;
	if (64 == waitCnt) {
		waitCnt = -1;
		cubeCurPos = rand() % 16;
		cubeCnt++;
	}
	if (-1 == waitCnt) {
		if (4 == cubeFallStage) {
			setDDRAMaddr(cubeCurPos);
			printChar(SPACE);
			cubeCurPos += 0x40;
		}
		setDDRAMaddr(cubeCurPos);
		
		if (cubeFallStage < 4)
			printChar(cubeFallStage);
		if (cubeFallStage >= 4 && cubeFallStage < 7) {
			if (platformCurPos == cubeCurPos) {
				printChar(cubeFallStage);
				if (6 == cubeFallStage) {
					gamerRes++;
					waitCnt = 1;
					cubeFallStage = -1;
				}
			} else
				printChar(cubeFallStage - 4);
		}
		if (7 == cubeFallStage)
			printChar(CUBE_DOWN);
		if (8 == cubeFallStage) {
			printChar(SPACE);
			waitCnt = 1;
			cubeFallStage = -1;
		}
		cubeFallStage++;
		waitCnt--;
	}
	if (-2 == waitCnt)
		waitCnt++;

	if (cubeCnt == MAX_CUBE_CNT)
		ET1 = 0;
	//EA = 1;
}