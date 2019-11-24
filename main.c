#include <xc.h>
#define _XTAL_FREQ 8000000
#pragma config OSC = IRCIO // internal oscillator
#include "lcd.h"
#include "motor.h"
#include <string.h>
#include <stdio.h>
#include "serial.h"
volatile char reader = 0;
volatile char A[16];

void __interrupt(high_priority) InterruptHandlerHigh() {
    if (PIR1bits.RCIF) {
        A[reader]=RCREG;//reads bit to A AND clears bit
        
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

    char j;
    char i = 0;
    char kms;

    while (1) {
            SendLCD(0b00000001, 0);//Clear LCD
            LCD_String(A);
            __delay_ms(100);

    }
}