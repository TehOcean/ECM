#include <xc.h>
#include "motor.h"
#pragma config OSC = IRCIO // internal oscillator


void main(void) {
    OSCCON = 0x72; //8MHz clock
   
    while (!OSCCONbits.IOFS); //wait until stable
    initMotor(); //setup PWM registers
    while (1) {
        fullSpeedAhead(&motorL, &motorR);
        delay_s(1);
        stop(&motorL, &motorR);
        delay_s(1);
        turnLeft(&motorL, &motorR);
        delay_s(1);
        turnRight(&motorL, &motorR);
        delay_s(1);
        stop(&motorL, &motorR);
        delay_s(1);
    }
}
