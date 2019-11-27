#include <xc.h>
#define _XTAL_FREQ 8000000
#pragma config OSC = IRCIO // internal oscillator
#include "lcd.h"
#include "motor.h"
#include <string.h>
#include <stdio.h>
#include "serial.h"
volatile char reader = 0;
volatile char A[15];
volatile int right;
volatile int left;

void __interrupt(high_priority) InterruptHandlerHigh() {
    if (PIR1bits.RCIF == 1) {
        A[reader] = RCREG; //reads bit to A AND clears bit
        reader++;
    }
}

void __interrupt(low_priority) InterruptHandlerLow() {
    if (INTCONbits.INT0IF = 1) {
        TMR1 = 0;
        INTCONbits.INT0IF = 0;

        if (PIR1bits.CCP1IF = 1) {
            left=CCPR1L;
            PIR1bits.CCP1IF = 0;
        }
        if (PIR2bits.CCP2IF = 1) {
            right=CCPR2L;
            PIR2bits.CCP2IF = 0;
        }
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

    TRISCbits.RC1 = 1; //input on RC1
    TRISCbits.RC2 = 1; //input on RC2
    TRISCbits.RC3 = 1; //input on RC3/INT0
    CCP1CONbits.CCP1M3 = 0;
    CCP1CONbits.CCP1M2 = 1;
    CCP1CONbits.CCP1M1 = 0;
    CCP1CONbits.CCP1M0 = 1;

    CCP2CONbits.CCP2M3 = 0;
    CCP2CONbits.CCP2M2 = 1;
    CCP2CONbits.CCP2M1 = 0;
    CCP2CONbits.CCP2M0 = 1;

    INTCONbits.INT0IE = 1;//Enable external interrupts
    INTCON2bits.INTEDG0 = 0;//Interrupt on falling edge 

    T1CONbits.TMR1ON = 1; //turn on timer1
    T1CONbits.RD16 = 1; // 16bit mode
    T1CONbits.TMR1CS = 0; //use internal clock
    T1CONbits.T1OSCEN = 0; //The oscillator inverter and feedback resistor are turned off to eliminate power drain
    T1CONbits.T1CKPS0 = 1; //1:8 prescaler
    T1CONbits.T1CKPS1 = 1; //1:8 prescaler
    T1CONbits.T1RUN=1;



    //    char i;
    //    char buf[10];
    //    strcpy(buf, "Hello World!");
    //    LCD_String(buf); //output string to LCD

    while (1) { 
        if (left>right){
            turnLeft(&motorL, &motorR); 
        }
        else {
            turnRight(&motorL, &motorR);
        }
    }
}