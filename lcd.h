#ifndef _LCD_H
#define	_LCD_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 8000000
void E_TOG(void);
void LCDout(unsigned char number);
void SendLCD(unsigned char Byte, char type);
void LCD_Init(void);
void SetLine(char line);
void LCD_String(char *string);
#endif	/* XC_HEADER_TEMPLATE_H */

