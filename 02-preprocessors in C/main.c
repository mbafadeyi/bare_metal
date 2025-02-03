
/*
R - PF1
B - PF2
G - PF3
*/

/*
Clock enable PortF		0x400FE000+0x608  => 	0x400FE608 => RCGCGPIO
Digital PortF			0x40025000+0x51C  => 	0x4002551C => GPIOFDEN
Direction for PortF		0x40025000+0x400  => 	0x40025400 => GPIOFDIR
Data to PortF			0x40025000+0x000  =>	0x40025000 => GPIOFDATA
*/

#define LED_RED		(1U << 1)
#define	LED_BLUE	(1U << 2)
#define	LED_GREEN	(1U << 3)

#define RCGCGPIO	(*((unsigned int *)0x400FE608U))
#define GPIOFDEN	(*((unsigned int *)0x4002551CU))
#define GPIOFDIR	(*((unsigned int *)0x40025400U))
#define GPIOFDATA	(*((unsigned int *)0x400253FCU))

void delay(long d){
	while(d--);
}

int main()
{
	RCGCGPIO |= (1U << 5);
	GPIOFDEN |= (LED_RED | LED_BLUE | LED_GREEN);
	GPIOFDIR |= (LED_RED | LED_BLUE | LED_GREEN);
	
	while (1)
	{	
		GPIOFDATA |= (LED_GREEN);
		delay(1000000);
		GPIOFDATA &= 0x00U;
		delay(1000000);
	}
	
	
	
}