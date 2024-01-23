/*
 * main.c
 */
#include<stdint.h>
#include<tm4c123gh6pge.h>

volatile int i;
int main(void)
{
	SYSCTL_RCGCGPIO_R|= 0x1FF;
	GPIO_PORTG_DIR_R = 0xFF;
	GPIO_PORTG_DEN_R = 0xFF;
	/*GPIO_PORTG_DIR_R = 0xFF;
		GPIO_PORTG_DEN_R = 0xFF;*/
	while(1)
	{
		//GPIO_PORTG_DATA_R = 0x00;
		GPIO_PORTG_DATA_R = 0xFF;
		for( i=0;i<2000000;i++)
		{

		}
		GPIO_PORTG_DATA_R = 0;
		for( i=0;i<2000000;i++)
		{

		}
    }

    return 0;
}
