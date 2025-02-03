#include <stdint.h>
#include "tm4c.h"
#include "TimeDelay.h"

#define LED_RED		(1U << 1)
#define	LED_BLUE	(1U << 2)
#define	LED_GREEN	(1U << 3)

#define GPIOF_BASE      0x40025000UL
#define GPIOF           ((GPIO_Registers *)GPIOF_BASE)

typedef struct{
    uint32_t Dummy1[255]; // 0x000 => 0x3FC
    uint32_t DATA;
    uint32_t DIR;
    uint32_t IS;
    uint32_t IBE;
    uint32_t IEV;
    uint32_t IM;
    uint32_t RIS;
    uint32_t MIS;    
    uint32_t ICR;
    uint32_t AFSEL; // 0x420 => 0x424
    uint32_t Dummy2[55];
    uint32_t DR2R;
    uint32_t DR4R;
    uint32_t DR8R;
    uint32_t ODR;
    uint32_t PUR;
    uint32_t PDR;
    uint32_t SLR;
    uint32_t DEN;
    uint32_t LOCK;
    uint32_t CR;
    uint32_t AMSEL;
    uint32_t PCTL;
    uint32_t ADCCTL;
    uint32_t DMACTL;
    uint32_t PeriphlD4;
    uint32_t PeriphlD5;
    uint32_t PeriphlD6;
    uint32_t PeriphlD7;
    uint32_t PeriphlD0;
    uint32_t PeriphlD1;
    uint32_t PeriphlD2;
    uint32_t PeriphlD3;
    uint32_t PCellID0;
    uint32_t PCellID1;
    uint32_t PCellID2;
    uint32_t PCellID3;
}GPIO_Registers;

int main()
{
	SYSCTL_RCGCGPIO_R |= (1U << 5);
	GPIOF->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
	GPIOF->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
	
	while (1)
	{	
		GPIOF->DATA |= (LED_GREEN);
		delay(1000000);
		GPIOF->DATA &= ~(LED_GREEN);
		delay(1000000);
	}	
	
}