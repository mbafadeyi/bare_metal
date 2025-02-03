 #include "TM4C123.h"                    // Device header
#include "TimeDelay.h"

/*
r1 - PB3
r2 - PC4
r3 - PC5
r4 - PC6
c1 - PC7
c2 - PD6
c3 - PD7

	-> row scanning techniques
		r1, r2, r3, r4 -> output pins
		c1, c2, c3 -> input pins with pull ups enabled
		Pull Up -> 1 when button is not pressed and 0 when button is pressed
*/

unsigned int number;

int main()
{
	// RCGC -> Run Mode Clock Gating Control for Pins B, C and D
	SYSCTL->RCGCGPIO |= 0x0E; // Clock of PortB, PortC, PortD
	
	// DEN -> Digital Enable Register
	GPIOB->DEN |= 1U << 3; // Digitalise PB3
	GPIOC->DEN |= 1U << 4 | 1U << 5 | 1U << 6 | 1U << 7; // Digitalise PC4, PC5, PC6 and PC7
	GPIOD->DEN |= 1U << 6 | 1U << 7; // Digitalise PD6 and PD7
	
	// DIR -> Direction Register
	GPIOB->DIR |= 1U << 3; // Set PB3 as output
	GPIOC->DIR |= 1U << 4 | 1U << 5 | 1U << 6; // Set PC4, PC5 and PC6 as outputs
	GPIOC->DIR &= ~1U << 7; // Set PC7 as output
	GPIOD->DIR &= ~((1U << 6) & (1U << 7)); // Set PD6 and PD7 as inputs
	
	// PUR -> Pull Up Register
	GPIOC->PUR |= 1U << 7;
	GPIOD->PUR |= 1U << 6 | 1U << 7;
	
	while (1)
	{	
		// First Row
		GPIOB->DATA &= ~1U << 3; // Turn off PB3
		GPIOC->DATA |= 1U << 4 | 1U << 5 | 1U << 6; // Turn on PC4, PC5 and PC6
		
		if(((GPIOC->DATA & (1U << 7)) >> 7) == 0)
		{
			number = 1;
			delay(50000);
		}
		if(((GPIOD->DATA & (1U << 6)) >> 6) == 0)
		{
			number = 2;
			delay(50000);
		}
		if(((GPIOD->DATA & (1U << 7)) >> 7) == 0)
		{
			number = 3;
			delay(50000);
		}
		
		// Second Row
		GPIOC->DATA &= ~1U << 4; // Turn off PC4
		GPIOB->DATA |= 1U << 3; // Turn on PB3
		GPIOC->DATA |= 1U << 5 | 1U << 6; // Turn on PC5 and PC6
		
		if(((GPIOC->DATA & (1U << 7)) >> 7) == 0)
		{
			number = 4;
			delay(50000);
		}
		if(((GPIOD->DATA & (1U << 6)) >> 6) == 0)
		{
			number = 5;
			delay(50000);
		}
		if(((GPIOD->DATA & (1U << 7)) >> 7) == 0)
		{
			number = 6;
			delay(50000);
		}
		
		// Third Row
		GPIOC->DATA &= ~1U << 5; // Turn off PC5
		GPIOB->DATA |= 1U << 3; // Turn on PB3
		GPIOC->DATA |= 1U << 4 | 1U << 6; // Turn on PC4 and PC6
		
		if(((GPIOC->DATA & (1U << 7)) >> 7) == 0)
		{
			number = 7;
			delay(50000);
		}
		if(((GPIOD->DATA & (1U << 6)) >> 6) == 0)
		{
			number = 8;
			delay(50000);
		}
		if(((GPIOD->DATA & (1U << 7)) >> 7) == 0)
		{
			number = 9;
			delay(50000);
		}
		
		// Fourth Row
		GPIOC->DATA &= ~1U << 6; // Turn off PC6
		GPIOB->DATA |= 1U << 3; // Turn on PB3
		GPIOC->DATA |= 1U << 4 | 1U << 5; // Turn on PC4 and PC6

		if(((GPIOC->DATA & (1U << 7)) >> 7) == 0)
		{
			number = '*';
			delay(50000);
		}
		if(((GPIOD->DATA & (1U << 6)) >> 6) == 0)
		{
			number = 0;
			delay(50000);
		}
		if(((GPIOD->DATA & (1U << 7)) >> 7) == 0)
		{
			number = '#';
			delay(50000);
		}
		
	}	
}
