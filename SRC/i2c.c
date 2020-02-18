#include "aduc812.h"
#include "i2c.h"

static void delay(void) {   // ~25 mcs
    char ch = 0;
    while (ch++ < 2);
}

static void start(void) {
    MDE = 1;    //Output
    MDO = 1;
    MCO = 1;

    delay();
    MDO = 0;
    delay();
    MCO = 0;
}

static unsigned char sendByte(unsigned char ch) {  //Returns ACK (0 = acknowledged)
    char i;
    unsigned char ack;

    MDE = 1;    //Output
    MCO = 0;

    for (i = 0 ; i < 8; i++, ch <<= 1) {
        MDO = (ch & 0x80) ? 1 : 0;
        MCO = 1;

        delay();

        MCO = 0;
    }

    MDE = 0;    //Input
    MCO = 1;

    delay();

    ack = MDI;
    MCO = 0;
    return ack;
}

static void stop(void) {
    MDE = 1;    //Output
    MCO = 0;
    MDO = 0;
    MCO = 1;

    delay();
    MDO = 1;
    delay();
    MDE = 0;    //Input (release line)
}

static unsigned char begin(unsigned char periphAddr) {  //Returns ACK (0 = acknowledged)
    start();
    return sendByte(periphAddr);
}

static void ack(void) {   //Sends ACK
    MDE = 1;    //Output
    MCO = 0;
    MDO = 0;
    MCO = 1;

    delay();

    MCO = 0;
}

static void nack(void) {    //Sends NACK
    MDE = 1;
    MCO = 0;
    MDO = 1;
    MCO = 1;

    delay();

    MCO = 0;
}

unsigned char getAck(unsigned char periphAddr) {  //Returns 1 if there was an ACK
    I2CM = 1; //I2C Master mode

    if (begin(periphAddr & 0xFE)) { 
        stop();
        return 0;
    }

    stop();
    return 1;
}

unsigned char recvByte(void) {
    char i;
    unsigned char ch = 0;

    MDE = 0;    //Input
    MCO = 0;

    for (i = 0; i < 8; i++) {
        ch <<= 1;
        MCO = 1;

        delay();
        ch |= MDI;

        MCO = 0;
    }

    return ch;
}

unsigned char receiveByte(unsigned char periphAddr, unsigned char addr, unsigned char *dataByte) { //addr - address in target
    I2CM = 1;   // I2C Master mode
    periphAddr = periphAddr & 0xFE;   // Write

    if (begin(periphAddr)) {
        stop();
        return 1;
    }   //Error - No ACK

    if (sendByte(addr)) {
        stop();
        return 1;
    }
    delay();
    delay();

    periphAddr |= 1;   //Read

    if (begin(periphAddr)) {
        stop();
        return 1;
    }
    delay();

    (*dataByte) = recvByte();
    nack();
    stop();

    return 0;
}

unsigned char transmitByte(unsigned char periphAddr, unsigned char addr, unsigned char dataByte) { //addr - address in target
    I2CM = 1;   //I2C Master mode
    periphAddr = periphAddr & 0xFE;   //Write

    if (begin(periphAddr)) {
        stop();
        return 1;
    }   //Error - no Ack

    if (sendByte(addr)) {
        stop();
        return 1;
    }

    if (sendByte(dataByte)) { 
        stop(); 
        return 1;
    }

    stop();
    return 0;
}