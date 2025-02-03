 #include "TM4C123.h"                    // Device header
#include "TimeDelay.h"

int main()
{
	SYSCTL->RCGCGPIO |= (1U << 1); // Clock for PortB
	GPIOB->DEN |= (1U << 1); // Digital enable PB1
	GPIOB->DIR |= (1U << 1); // Enable PB1 as output
	
	while (1)
	{	
		GPIOB->DATA |= (1U << 1);
		delay(10000000);
		GPIOB->DATA &= ~(1U << 1);
		delay(10000000);
	}	
}