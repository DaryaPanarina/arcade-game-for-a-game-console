#include "aduc812.h"
#include "game_screen.h"
#include "keyboard.h"
#include "eeprom.h"

void setVector(unsigned char xdata * address, void * vector) {
    unsigned char xdata * tmpVector;
    *address = 0x02;
    tmpVector = (unsigned char xdata *) (address + 1);
    *tmpVector = (unsigned char) ((unsigned short)vector >> 8);
    ++tmpVector;
    *tmpVector = (unsigned char) vector;
}

void delay(unsigned long ms) {
    volatile unsigned long i, j;
    
    for (j = 0; j < ms; j++) {
        for (i = 0; i < 50; i++);
    }  
}

void main(void) {
    unsigned char bestRes = 0, curRes = 0, randSeed = 0;

    setVector(0x200B, (void *)T0Handling);
    setVector(0x201B, (void *)T1Handling);
    defineUserChars();
    initKeyboardTimer();

    if (readByteEeprom(EEPROM_RAND_ADDR, &randSeed))
        randSeed = 0;
    randSeed = initRand(randSeed);
    writeByteEeprom(EEPROM_RAND_ADDR, randSeed);

    initGameTimer();
    IE = 0x82;

    if (readByteEeprom(EEPROM_RECORD_ADDR, &bestRes))
        bestRes = 0;
    if (bestRes > MAX_CUBE_CNT)
        bestRes = 0;

    drawMainScreen();
    while (1) {
        if (isStartPressed()) {
            drawStartScreen();
            ET1 = 1;
            while (1) {
                if (isStopPressed()) {
                    ET1 = 0;
                    drawMainScreen();
                    break;
                }
                if (isLeftPressed())
                    movePlatformToLeft();
                if (isRightPressed())
                    movePlatformToRight();
                if (isGameFinished()) {
                    curRes = getGameRes();
                    if (curRes > bestRes) {
                        bestRes = curRes;
                        drawFinishScreen(1);
                        writeByteEeprom(EEPROM_RECORD_ADDR, bestRes);
                    } else
                        drawFinishScreen(0);
                    ET1 = 0;
                    delay(3000);
                    drawMainScreen();
                    break;
                }
                delay(100);
            }
        }
        if (isRecResetPressed()) {
            if (writeByteEeprom(EEPROM_RECORD_ADDR, 0x00))
                drawRecResetScreen(0);
            else {
                bestRes = 0;
                drawRecResetScreen(1);
            }
            delay(3000);
            drawMainScreen();
        }
    }
}