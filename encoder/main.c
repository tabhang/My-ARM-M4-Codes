
#include <stdint.h>
#include <tm4c123gh6pge.h>

volatile int i=0;

ISR1(void)
{
	int x=(GPIO_PORTJ_DATA_R & 0x4)==0x4;
	if((x))
	{
		i++;
	}
	else
	{
	    i--;
	}
	GPIO_PORTJ_ICR_R = 0x8;

}
int main(void)
{
	SYSCTL_RCGCGPIO_R = 0x100;

	GPIO_PORTJ_DIR_R = 0;
	GPIO_PORTJ_DEN_R = 0xFF;
	GPIO_PORTJ_PUR_R|= 0xC;
	GPIO_PORTJ_DATA_R|= 0xC;

	NVIC_EN1_R = 0x400000;
	GPIO_PORTJ_IM_R = 0x8;
	GPIO_PORTJ_IEV_R = 0x8;
	while(1)
	{
	}
	return 0;
}


/*
 * if((GPIO_PORTJ_DATA_R & 0x8)==0x8 && j==0)
		{
			if((GPIO_PORTJ_DATA_R & 0x4)==0x4)
			{
				i++;
			}
			if((GPIO_PORTJ_DATA_R & 0x4)==0)
			{
				i--;
			}
			j=1;
		}
		if((GPIO_PORTJ_DATA_R & 0xC)==0)
		{
			j=0;
		}
 */
