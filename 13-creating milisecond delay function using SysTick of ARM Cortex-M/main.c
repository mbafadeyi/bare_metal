#include "TM4C123.h" // Device header
#include <stdint.h>

uint32_t ms;

void _delay_ms(uint16_t delay)
{
	ms = 0;
	while (delay > ms);
}

int main()
{
	SYSCTL->RCGCGPIO |= (1U << 5); // Clock for PortF
	GPIOF->DEN |= (1U << 1) | (1U << 2) | (1U << 3); // Digital enable PF1, PF2 and PF3
	GPIOF->DIR |= (1U << 1) | (1U << 2) | (1U << 3); // Enable PF1, PF2 and PF3 as output
	
	// Configuration of SysTick Timer (4MHz) and SysTick Interrupt
	SysTick->CTRL |= (1U << 0) | (1U << 1);
	// Load Value for 500ms -> Load = Time Delay / (1 / Clock Frequency)
	// Load = 1000mS / (0.25useconds)
	SysTick->LOAD |= 4000000-1; // 1s
	
	while (1)
	{
		GPIOF->DATA ^= (1U << 3); // Toggling green LED for 1 second
		_delay_ms(1000); // 1000ms or 1 second delay
	}	
	
}

void SysTick_Handler()
{
	ms++;
}