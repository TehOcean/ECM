#include <xc.h>
#include "led.h"

void LEDout(int number) {
    //    LATDbits.LATD2 = number & 0b00000001;
    //    LATDbits.LATD3 = number & 0b00000010;
    //    LATCbits.LATC4 = number & 0b00000100;
    //    LATCbits.LATC5 = number & 0b00001000;
    //    LATCbits.LATC6 = number & 0b00010000;
    //    LATCbits.LATC7 = number & 0b00100000;
    //    LATDbits.LATD4 = number & 0b01000000;
    //    LATDbits.LATD5 = number & 0b10000000;
    LATC = (number & 0b00111100) << 2;
    LATD = ((number & 0b00000011) << 2) | ((number & 0b11000000) >> 2);
}

void LEDInit() {
    LATDbits.LATD2 = 0;
    LATDbits.LATD3 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC5 = 0;
    LATCbits.LATC6 = 0;
    LATCbits.LATC7 = 0;
    LATDbits.LATD4 = 0;
    LATDbits.LATD5 = 0;
    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
    TRISDbits.RD4 = 0;
    TRISDbits.RD5 = 0;
    TRISCbits.RC4 = 0;
    TRISCbits.RC5 = 0;
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 0;
}