#include "TM4C123.h" // Device header
#include "TimeDelay.h"

//PF0 and PF4 are switches
//PF2 is blue LED and PF3 is green LED

int main()
{
	SYSCTL->RCGCGPIO |= (1U << 5); // Clock for PortF
	
	// GPIO Pins with special consideration -> PF[0]
	GPIOF->LOCK |= 0x4C4F434B;
	GPIOF->CR |= (1U << 0);
	GPIOF->LOCK |= 0;
	
	// Configure the switches
	GPIOF->DEN |= (1U << 0) | (1U << 4); // Digitally enable PF0 and PF4
	GPIOF->DIR &= ~((1U << 0) & (1U << 4)); // Configure PF0 and PF4 as inputs	
	// Enable Pull-Ups
	GPIOF->PUR |= (1U << 0) | (1U << 4);
	
	// Configure the LEDs
	GPIOF->DEN |= (1U << 2) | (1U << 3); // Digital enable PF2 and PF3
	GPIOF->DIR |= (1U << 2) | (1U << 3); // Enable PF2 and PF3 as output
	
	GPIOF->IS &= ~((1 << 0) & (1U << 4)); // Edge triggered interrupt
	GPIOF->IBE &= ~((1U << 0) & (1U << 4)); // Disabling both edge triggered interrupt
	GPIOF->IEV &= ~((1U << 0) & (1U << 4)); // Falling edge triggered interrupt
	GPIOF->IM |= (1U << 0) | (1U << 4); // PF0 and PF4 are not masked
	
	GPIOF->ICR |= (1U << 0) | (1U << 4); // Clearing interrupt flag for PF0 and PF4
	
	// Set the NVIC Register for enabling the EXTI for GPIOF
	NVIC->ISER[0] |= (1U << 30);  // IRQ no: GPIOF = 30
	
	// Set the Priority for the GPIOF interrupt
	NVIC->IPR[30] |= 0x60; // Interrupt Priority Register 3 -> Used "IP" in place of "IPR" cos I couldn't find it
	
	while (1)
	{
	
	}	
	
}

void GPIOF_Handler()
{
	if((GPIOF->MIS & (1U << 4)) == (1U << 4)) // PF4
	{
		GPIOF->DATA |= (1U << 3); // Turn on the green LED
		GPIOF->DATA &= ~(1U << 2); // Turn off the blue LED
		GPIOF->ICR |= (1U << 4); // Clearing interrupt flag for PF4
	}
	else if ((GPIOF->MIS & (1U << 0)) == (1U << 0)) // PF0
	{
		GPIOF->DATA |= (1U << 2); // Turn on the blue LED
		GPIOF->DATA &= ~(1U << 3); // Turn off the green LED
		GPIOF->ICR |= (1U << 0); // Clearing interrupt flag for PF0
	}
}