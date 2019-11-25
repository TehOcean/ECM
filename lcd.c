#include <xc.h>
#include "lcd.h"

void E_TOG(void) {
    //don?t forget to put a delay between the on and off
    //commands! 5us will be plenty.

    LATCbits.LATC0 = 1;
    __delay_us(5); // 5us delay ? remember to define _XTAL_FREQ
    LATCbits.LATC0 = 0;
}
//function to send four bits to the LCD

void LCDout(unsigned char number) {
    //set data pins using the four bits from number
    LATCbits.LATC1 = number & 0b0001;
    LATCbits.LATC2 = (number & 0b0010) >> 1;
    LATDbits.LATD0 = (number & 0b0100) >> 2;
    LATDbits.LATD1 = (number & 0b1000) >> 3;
    E_TOG();
    //toggle the enable bit to send data
    __delay_us(5); // 5us delay
}
//function to send data/commands over a 4bit interface

void SendLCD(unsigned char Byte, char type) {
    // set RS pin whether it is a Command (0) or Data/Char (1)
    // using type as the argument
    LATAbits.LATA6 = type;
    // send high bits of Byte using LCDout function
    LCDout((Byte & 0b11110000) >> 4);
    __delay_us(10); // 10us delay
    LCDout(Byte & 0b00001111);
    // send low bits of Byte using LCDout function
    __delay_us(50);
}

void LCD_Init(void) {
    // set initial LAT output values (they start up in a random state)
    TRISAbits.RA6 = 0;
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;
    TRISCbits.RC2 = 0;
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;

    LATAbits.LA6 = 0;
    LATCbits.LC0 = 0;
    LATCbits.LC1 = 0;
    LATCbits.LC2 = 0;
    LATDbits.LD0 = 0;
    LATDbits.LD1 = 0;

    //    LATA = 0;
    //    LATC = 0;
    //    LATD = 0;

    // set LCD pins as output (TRIS registers)


    // Initialisation sequence code - see the data sheet

    //delay 15mS
    __delay_ms(15);
    LCDout(0b0011);
    __delay_ms(5);
    LCDout(0b0011);
    __delay_us(200);
    LCDout(0b0011);
    __delay_us(50);
    LCDout(0b0010);
    __delay_us(50);

    SendLCD(0b00101000, 0); //functionset
    SendLCD(0b00001000, 0); //Display Off
    SendLCD(0b00000001, 0); //Display Clear
    __delay_ms(2);
    SendLCD(0b00000110, 0); //Entry Mode Set
    SendLCD(0b00001111, 0); //Display On

    // screen, set entry mode, display on etc to finish initialisation
}
//function to put cursor to start of line

void SetLine(char line) {
    if (line == 1) {
        SendLCD(0x80, 0); //Send 0x80 to set line to 1 (0x00 ddram address)
    } else {
        SendLCD(0xC0, 0); //Send 0xC0 to set line to 2 (0x40 ddram address)
    }
    __delay_us(50); // 50us delay
}

void LCD_String(char *string) {
    //While the data pointed to isn?t a 0x00 do below
    while (*string != 0) {
        //Send out the current byte pointed to
        // and increment the pointer
        SendLCD(*string++, 1);
        __delay_us(50); //so we can see each character
        //being printed in turn (remove delay if you want
        //your message to appear almost instantly)
    }
}
