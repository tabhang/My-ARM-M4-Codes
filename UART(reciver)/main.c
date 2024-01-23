/*
 * reci....
 */

#include<stdint.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

volatile int i;

int main(void)
{
	System80Mhz();

	SYSCTL_RCGCUART_R = 0x20;
	SYSCTL_RCGCGPIO_R = 0x2fff;

	GPIO_PORTJ_AFSEL_R = 0xC;
	GPIO_PORTJ_PCTL_R = 0x1100;
	GPIO_PORTJ_DEN_R = 0x4;

	UART5_CTL_R = 0x200;
	UART5_IBRD_R = 0x82;
	UART5_FBRD_R = 0xD;
	UART5_LCRH_R = 0x60;
	UART5_CTL_R = 0x201;

	GPIO_PORTG_DIR_R = 0xFF;
	GPIO_PORTG_DEN_R = 0xFF;
	while(1)
	{
		if((UART5_FR_R & 0x10)==0x00)
		{
			i = UART5_DR_R;
			GPIO_PORTG_DATA_R = i;
		}
	}
	return 0;
}
