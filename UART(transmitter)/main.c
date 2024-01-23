/*
 * trans....
 */
#include<stdint.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

int main(void)
{
	System80Mhz();

	SYSCTL_RCGCUART_R = 0x20;
	SYSCTL_RCGCGPIO_R = 0x100;

	GPIO_PORTJ_AFSEL_R = 0xC;
	GPIO_PORTJ_PCTL_R = 0x1100;
	GPIO_PORTJ_DEN_R = 0x8;

	UART5_CTL_R = 0x100;
	UART5_IBRD_R = 0x82;
	UART5_FBRD_R = 0xD;
	UART5_LCRH_R = 0x60;
	UART5_CTL_R = 0x101;
    while(1)
	{
		if((UART5_FR_R & 0x20)==0x00)
    	{
			UART5_DR_R = 0xF0;
    	}
	}
	return 0;
}
