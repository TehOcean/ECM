#include <xc.h>
#define _XTAL_FREQ 8000000
#pragma config OSC = IRCIO // internal oscillator
#include "lcd.h"
#include "motor.h"
#include <string.h>
#include <stdio.h>
#include "serial.h"
volatile char reader = 0;
volatile char A[10];

void __interrupt(high_priority) InterruptHandlerHigh() {
    if (PIR1bits.RCIF == 1) {
        A[reader] = RCREG; //reads bit to A AND clears bit
        reader++;
    }
}

void main(void) {
    OSCCON = 0x72; //8MHz clock
    while (!OSCCONbits.IOFS); //wait until stable
    initSerial(); //Initialize the LCD   
    LCD_Init(); //Initialize the LCD
    SetLine(1); //Set Line 1
    INTCONbits.GIEH = 1; // enable high priority interrupts
    INTCONbits.GIEL = 1; // enable low priority interrupts
    RCONbits.IPEN = 1; //enable priority interrupts
    PIE1bits.RCIE = 1; //enable EUSART receive interrupts.

    char j;
    char i = 0;
    char kms;
    char buf[10];

    while (1) {
        sprintf(buf,"%.10s",A[1]);
        ClearLCD;
        LCD_String(buf);
        delay_s(1);
    }
}