#ifndef __KEYBOARD__H
#define __KEYBOARD__H

void initKeyboardTimer(void);

void T0Handling(void) __interrupt (1);

unsigned char isStartPressed(void);
unsigned char isStopPressed(void);
unsigned char isRecResetPressed(void);
unsigned char isLeftPressed(void);
unsigned char isRightPressed(void);

#endif //__KEYBOARD__H