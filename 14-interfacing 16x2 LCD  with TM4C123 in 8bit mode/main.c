 #include "TM4C123.h"                    // Device header
#include "TimeDelay.h"


void printData(unsigned char data);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_string(unsigned char *str, unsigned char len);
void lcd_init(void);

/*
RS = PD0
RW = PD1
EN = PD2

D0 = PA7
D1 = PA6
D2 = PA5
D3 = PB4
D4 = PE5
D5 = PE4
D6 = PB1
D7 = PB0
*/

int main()
{
	// Clock of PortA, PortB, PortD, and PortE
	SYSCTL->RCGCGPIO |= (1U << 0)|(1U << 1)|(1U << 3)|(1U << 4);
	// Digitalise data pins and config pins
	GPIOA->DATA |= (1U << 5)|(1U << 6)|(1U << 7); // PA5, PA6 and PA7.
	GPIOB->DATA |= (1U << 0)|(1U << 1)|(1U << 4); // PB0, PB1 and PB4
	GPIOD->DATA |= (1U << 0)|(1U << 1)|(1U << 2); // PD0, PD1 and PD2
	GPIOE->DATA |= (1U << 4)|(1U << 5); // PE4 and PE5
	// Direction of data pins
	GPIOA->DIR |= (1U << 5)|(1U << 6)|(1U << 7); // PA5, PA6 and PA7.
	GPIOB->DIR |= (1U << 0)|(1U << 1)|(1U << 4); // PB0, PB1 and PB4
	GPIOD->DIR |= (1U << 0)|(1U << 1)|(1U << 2); // PD0, PD1 and PD2
	GPIOE->DIR |= (1U << 4)|(1U << 5); // PE4 and PE5
	
	delay(10000);
	lcd_init();
	
	// Row 1 starts from address 0x80 - 0x8F ->row 1 col 1 == 0x80 etc.
	// Row 2	- 0xC0 - 0xCF
	lcd_cmd(0x80); // cursor to first row and first col
	lcd_data('a');
	
	while (1)
	{	
		
	}	
}

void lcd_data(unsigned char data)
{
	printData(data);			// pass 8bits of data to the datalines of LCD
	GPIOD->DATA |= 1 << 0;		// Turn on the RS for writing to the data register of LCD	
	GPIOD->DIR &= ~(1 << 1);	// Turn off the R/W for write operation in LCD
	GPIOD->DATA |= 1 << 2;		// Turn on the EN of LCD for enabling the clock of LCD
	delay(10000);				// Wait for some time
	GPIOD->DATA &= ~(1 << 2);	// Turn off the EN of LCD
}

void lcd_cmd(unsigned char cmd)
{
	printData(cmd);				// pass 8bits of data to the datalines of LCD
	GPIOD->DATA &= ~(1 << 0);	// Turn off the RS for disbaling writing to the data register of LCD	
	GPIOD->DIR &= ~(1 << 1);	// Turn off the R/W for write operation in LCD
	GPIOD->DATA |= 1 << 2;		// Turn on the EN of LCD for enabling the clock of LCD
	delay(10000);				// Wait for some time
	GPIOD->DATA &= ~(1 << 2);	// Turn off the EN of LCD
}

void lcd_string(unsigned char *str, unsigned char len)
{
	char i;
	for (i = 0; i < len; i++)
	{
		lcd_data(str[i]);
	}
}
void lcd_init(void)
{
	lcd_cmd(0x38);				// 8bit mode utilising 16 columns and 2 rows
	lcd_cmd(0x06);				// auto-incrementing the cursor when printing the data in current column
	lcd_cmd(0x0C);				// cursor off and on
	lcd_cmd(0x01);				// clear screen
}

void printData(unsigned char data) // data = 8 bit hexadecimal data
{
	// zeroth bit = D0 = PA7
	if ((data&0x01) == 0x01) { GPIOA->DATA |= (1 << 7);  }
	else					 { GPIOA->DATA &= ~(1 << 7); }
	// first bit = D1 = PA6
	if ((data&0x02) == 0x02) { GPIOA->DATA |= (1 << 6);  }
	else					 { GPIOA->DATA &= ~(1 << 6); }
	// second bit = D2 = PA5
	if ((data&0x04) == 0x04) { GPIOA->DATA |= (1 << 5);  }
	else					 { GPIOA->DATA &= ~(1 << 5); }	
	// third bit = D3 = PB4
	if ((data&0x08) == 0x08) { GPIOA->DATA |= (1 << 4);  }
	else					 { GPIOA->DATA &= ~(1 << 4); }	
	// fourth bit = D4 = PE5
	if ((data&0x10) == 0x10) { GPIOA->DATA |= (1 << 5);  }
	else					 { GPIOA->DATA &= ~(1 << 5); }	
	// fifth bit = D5 = PE4
	if ((data&0x20) == 0x20) { GPIOA->DATA |= (1 << 4);  }
	else					 { GPIOA->DATA &= ~(1 << 4); }	
	// sixth bit = D6 = PB1
	if ((data&0x40) == 0x40) { GPIOA->DATA |= (1 << 1);  }
	else					 { GPIOA->DATA &= ~(1 << 1); }	
	// seventh bit = D7 = PB0
	if ((data&0x80) == 0x80) { GPIOA->DATA |= (1 << 0);  }
	else					 { GPIOA->DATA &= ~(1 << 0); }
}
