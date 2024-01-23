/*
 * trans with interrupts
 */
#include<stdint.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

ISR()
{
	UART5_DR_R = 0xF0;
	UART5_ICR_R = 0x20;
}

int main(void)
{
	SYSCTL_RCGCUART_R = 0x20;
	SYSCTL_RCGCGPIO_R = 0x100;

	NVIC_EN1_R = 0x20000000;

	GPIO_PORTJ_AFSEL_R = 0xC;
	GPIO_PORTJ_PCTL_R = 0x1100;
	GPIO_PORTJ_DEN_R = 0x8;
	
	UART5_CTL_R = 0x100;
	UART5_IBRD_R = 0x82;
	UART5_FBRD_R = 0xD;
	UART5_LCRH_R = 0x60;
	UART5_CTL_R = 0x111;
	UART5_IM_R = 0x20;
	UART5_RIS_R = 0x20;
	UART5_MIS_R = 0x20;
	//UART5_CTL_R = 0x111;
	while(1)
	{

	}
	return 0;
}
