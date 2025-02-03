 #include "TM4C123.h" // Device header
 #include <stdint.h>
 
 /*
 LED_GREEN 	PF3
 Swith 1	PF4
 Swith 2	PF0
 */
 
 uint8_t Button_state;
 uint8_t Button_state1;

int main()
{
	SYSCTL->RCGCGPIO |= (1U << 5); // GPIOF Clock enabled
	
	GPIOF->LOCK |= 0x4C4F434B;
	GPIOF->CR |= (1U <<0); // PF0 unlocked
	
	GPIOF->DIR |= (1U << 3); // PF3 is set as output <-> LED_GREEN
	GPIOF->DIR &= ~(1U << 4 & 1U << 0); // PF4 and PF0 are set as input <-> SW1 and SW2
	
	GPIOF->PUR |= (1U << 4 | 1U << 0); // PF4 and PF0 internal pull-up enabled
	
	GPIOF->DEN |= (1U << 4 | 1U << 3 | 1U << 0); // Digitalised PF4, PF3 and PF0
	
	while (1)
	{	
		// Pull Up logic sets pressed = 0 and released = 1
		Button_state = ((GPIOF->DATA & (1U << 4)) >> 4);
		if (Button_state == 0) // Button is pressed
		{
			GPIOF->DATA |= (1U << 3); // Led is on
		}
		// Pull Down logic sets pressed = 1 and released = 0
		Button_state1 = ((GPIOF->DATA & (1U << 0)) >> 0);
		if (Button_state1 == 0)
		{
			GPIOF->DATA &= ~(1U << 3); // LED is off
		}
	}	
}