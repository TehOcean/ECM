#include <xc.h>
#define _XTAL_FREQ 8000000
#pragma config OSC = IRCIO, MCLRE=OFF, LVP = OFF // internal oscillator
#include "lcd.h"
#include "motor.h"
#include <string.h>
#include <stdio.h>
#include "serial.h"
volatile char reader;
volatile char A[15];

void __interrupt(high_priority) InterruptHandlerHigh() {
    if (PIR1bits.RCIF == 1) {
        A[reader] = RCREG; //reads bit to A AND clears bit
        reader++;
    }
}

void main(void) {
    OSCCON = 0x72; //8MHz clock
    while (!OSCCONbits.IOFS); //wait until stable
    initSerial(); //Initialize the Serial   
    LCD_Init(); //Initialize the LCD
    SetLine(1); //Set Line 1
    
    INTCONbits.GIEL = 1; // enable low priority interrupts
    RCONbits.IPEN = 1; //enable priority interrupts
    PIE1bits.RCIE = 1; //enable EUSART receive interrupts.
    INTCONbits.GIEH = 1; // enable high priority interrupts

    char i;
    char buf[11];
    reader=0;
    
    while (1) {
        if (reader == 15) {
            for (i = 0; i<10; i++) {
                buf[i] = A[i + 1];
            }
            buf[10]=0;
            //sprintf(buf, "%.10s", A[1]);
            ClearLCD();
            LCD_String(buf);
            SetLine(2);
            
            LCD_String(A);
            delay_s(1);
            reader=0;
        }
    }
}
