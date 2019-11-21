#ifndef _SERIAL_H
#define	_SERIAL_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 8000000

void initSerial();//Initializes Serial Port
void Serial_String(char *string);//Send a string over serial port
void sendCharSerial(char charToSend);//Send a single char over serial port
char getCharSerial(void);//Recieve a single char over serial port

#endif	/* XC_HEADER_TEMPLATE_H */

