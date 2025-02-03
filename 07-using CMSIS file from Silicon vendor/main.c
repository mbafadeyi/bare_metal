#include <stdint.h>
#include "TM4C123.h"                    // Device header
#include "TimeDelay.h"

#define LED_RED		(1U << 1)
#define	LED_BLUE	(1U << 2)
#define	LED_GREEN	(1U << 3)


int main()
{
	SYSCTL->RCGCGPIO |= (1U << 5); // Clock for PortF
	GPIOF->DEN |= (LED_RED | LED_BLUE | LED_GREEN); // Digital enable PF1, PF2, PF3
	GPIOF->DIR |= (LED_RED | LED_BLUE | LED_GREEN); // Enable PF1, PF2, PF3 as output
	
	while (1)
	{	
		GPIOF->DATA |= (LED_GREEN);
		delay(1000000);
		GPIOF->DATA &= ~(LED_GREEN);
		delay(1000000);
	}	
}