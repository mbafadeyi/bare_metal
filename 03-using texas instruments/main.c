#include "tm4c.h"

/*
Clock enable PortF		0x400FE000+0x608  => 	0x400FE608 => RCGCGPIO
Digital PortF			0x40025000+0x51C  => 	0x4002551C => GPIOFDEN
Direction for PortF		0x40025000+0x400  => 	0x40025400 => GPIOFDIR
Data to PortF			0x40025000+0x000  =>	0x40025000 => GPIOFDATA
*/

#define LED_RED		(1U << 1)
#define	LED_BLUE	(1U << 2)
#define	LED_GREEN	(1U << 3)

void delay(long d){
	while(d--);
}

int main()
{
	SYSCTL_RCGCGPIO_R |= (1U << 5);
	GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
	GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
	
	while (1)
	{	
		GPIO_PORTF_DATA_R |= (LED_GREEN);
		delay(1000000);
		GPIO_PORTF_DATA_R &= ~(LED_GREEN);
		delay(1000000);
	}
	
	
	
}