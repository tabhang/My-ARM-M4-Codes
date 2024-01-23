//reciv with interrupts

#include<stdint.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

volatile int i=0;

ISR1()
{
	i = UART5_DR_R;
	GPIO_PORTH_DATA_R = i;
	UART5_ICR_R = 0x10;
}
int main(void)
{
	System80Mhz();

	SYSCTL_RCGCUART_R = 0x20;
	SYSCTL_RCGCGPIO_R = 0x180;

	NVIC_EN1_R = 0x20000000;

	GPIO_PORTJ_AFSEL_R = 0xC;
	GPIO_PORTJ_PCTL_R = 0x1100;
	GPIO_PORTJ_DEN_R = 0x4;
	
	UART5_CTL_R = 0x200;
	UART5_IBRD_R = 0x82;
	UART5_FBRD_R = 0xD;
	UART5_LCRH_R = 0x60;
	UART5_IM_R = 0x10;
	UART5_RIS_R = 0x10;
	UART5_MIS_R = 0x10;
	UART5_CTL_R = 0x201;

	GPIO_PORTH_DIR_R = 0xFF;
	GPIO_PORTH_DEN_R = 0xFF;
	while(1)
	{

	}
	return 0;
}
