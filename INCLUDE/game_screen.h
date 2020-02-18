#ifndef __GAME_SCREEN__H
#define __GAME_SCREEN__H

//LCD char codes
#define SPACE 				0x10
#define PLAT 				0x5F
#define SLASH				0x2F
#define CUBE_TOP 			0x00
#define CUBE_ABOVE_MID 		0x01
#define CUBE_BELOW_MID 		0x02
#define CUBE_DOWN 			0x03
#define PLAT_CUBE_TOP 		0x04
#define PLAT_CUBE_MIDDLE 	0x05
#define PLAT_CUBE_DOWN 		0x06

#define MAX_CUBE_CNT		0x0A
#define MAX_CUBE_CNT_STR	"10"

unsigned char initRand(unsigned char randSeed);
void initGameTimer(void);
void defineUserChars(void);

void drawMainScreen(void);
void drawStartScreen(void);
void drawFinishScreen(unsigned char isRecord);
void drawRecResetScreen(unsigned char isReset);
void movePlatformToLeft(void);
void movePlatformToRight(void);

unsigned char isGameFinished(void);
unsigned char getGameRes(void);

void T1Handling(void) __interrupt (3);

#endif //__GAME_SCREEN__H