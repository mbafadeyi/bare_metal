 #include "TM4C123.h" // Device header
#include "TimeDelay.h"

/*
a - PA7
b - PA6
c - PA5
d - PB4
e - PE5
f - PE4
g - PB1
h - PB0
*/

void PrintData(unsigned char data);

int main()
{
	// Enable clock of GPIO A, B and E
	SYSCTL->RCGCGPIO = 0x13; // Same as 1U << 0 | 1U << 1 | 1U << 4 Clock for PortA, PortB and PortE
	// Digitalise these pins
	GPIOA->DEN |= (1U << 5) | (1U << 6) | (1U << 7); // Digital enable PA5, PA6 and PA7
	GPIOB->DEN |= (1U << 0) | (1U << 1) | (1U << 4); // Digital enable PB0, PB1 and PB4
	GPIOE->DEN |= (1U << 4) | (1U << 5);	// Digital enable PE4 and PE5
	// Configure these pins as output pins
	GPIOA->DIR |= (1U << 5) | (1U << 6) | (1U << 7);
	GPIOB->DIR |= (1U << 0) | (1U << 1) | (1U << 4);
	GPIOE->DIR |= (1U << 4) | (1U << 5);
	
	while (1)
	{	
		// Common Anode
		PrintData(0xC0);	// 0
		delay(1000000);
		PrintData(0xF9);	// 1
		delay(1000000);
		PrintData(0xA4);	// 2
		delay(1000000);
		PrintData(0xB0);	// 3
		delay(1000000);
		PrintData(0x99);	// 4
		delay(1000000);
		PrintData(0x92);	// 5
		delay(1000000);
		PrintData(0x82);	// 6
		delay(1000000);
		PrintData(0xF8);	// 7
		delay(1000000);
		PrintData(0x80);	// 8
		delay(1000000);
		PrintData(0x90);	// 9
		delay(1000000);
	}	
}


void PrintData(unsigned char data)  // data = 8 bits hexadecimal data
{
    // zeroth bit = a = PA7
    if((data&0x01) == 0x01){GPIOA->DATA |= (1U << 7);  }
    else                   {GPIOA->DATA &= ~(1U << 7); }
    // first bit = b = PA6
    if((data&0x02) == 0x02){GPIOA->DATA |= (1U << 6);  }
    else                   {GPIOA->DATA &= ~(1U << 6); }
    // second bit = c = PA5
    if((data&0x04) == 0x04){GPIOA->DATA |= (1U << 5);  }
    else                   {GPIOA->DATA &= ~(1U << 5); }
    // third bit = d = PB4
    if((data&0x08) == 0x08){GPIOB->DATA |= (1U << 4);  }
    else                   {GPIOB->DATA &= ~(1U << 4); }
    // fourth bit = e = PE5
    if((data&0x10) == 0x10){GPIOE->DATA |= (1U << 5);  }
    else                   {GPIOE->DATA &= ~(1U << 5); }
    // fifth bit = f = PE4
    if((data&0x20) == 0x20){GPIOE->DATA |= (1U << 4);  }
    else                   {GPIOE->DATA &= ~(1U << 4); }
    // sixth bit = g = PB1
    if((data&0x40) == 0x40){GPIOB->DATA |= (1U << 1);  }
    else                   {GPIOB->DATA &= ~(1U << 1); }
    // seventh bit = h = PB0
    if((data&0x80) == 0x80){GPIOB->DATA |= (1U << 0);  }
    else                   {GPIOB->DATA &= ~(1U << 0); }
}