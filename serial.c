#include <xc.h>
#include "serial.h"

char getCharSerial(void) {
    while (!PIR1bits.RCIF); //wait for the data to arrive
    return RCREG; //return byte in RCREG
}

void sendCharSerial(char charToSend) {
    while (!PIR1bits.TXIF); // wait for flag to be set
    TXREG = charToSend; //transfer char H to transmitter
}

void Serial_String(char *string) {
    //While the data pointed to isn?t a 0x00 do below
    while (*string != 0) {
        //Send out the current byte pointed to
        // and increment the pointer
        sendCharSerial(*string++);
        __delay_us(50); //so we can see each character
        //being printed in turn (remove delay if you want
        //your message to appear almost instantly)
    }
}

void initSerial() {
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1; //set data direction registers
    SPBRG = 207; //set baud rate to 9600
    SPBRGH = 0;//high bits of baud rate (set to 0)
    BAUDCONbits.BRG16 = 1; //set baud rate scaling to 16 bit mode
    TXSTAbits.BRGH = 1; //high baud rate select bit
    RCSTAbits.CREN = 1; //continuous receive mode
    RCSTAbits.SPEN = 1; //enable serial port, other settings default
    TXSTAbits.TXEN = 1; //enable transmitter, other settings default

}