#include "TM4C123.h" // Device header

int main()
{
	SYSCTL->RCGCGPIO |= (1U << 5); // Clock for PortF
	GPIOF->DEN |= 0x0E; // (1U << 1) | (1U << 2) | (1U << 3) Digital enable PF1, PF2 and PF3
	GPIOF->DIR |= 0x0E; // Enable PF1, PF2 and PF3 as output
	
	// Configuration of SysTick Timer (4MHz) and SysTick Interrupt
	SysTick->CTRL |= 0x03; // (1U << 0) | (1U << 1)
	// Load = Time Delay / (1 / Clock Frequency)
	// Time for one tick of systick timer = 0.25useconds
	// LOAD = 0.001S / 0.25uS  => Time Delay is 1mS
	SysTick->LOAD |= 4000-1; // 1mS
	
	while (1)
	{
	
	}	
	
}

void SysTick_Handler()
{
	GPIOF->DATA ^= (1U << 3); // Toggling green LED for 1 second
}