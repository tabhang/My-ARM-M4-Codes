#include <stdint.h>
#include <tm4c123gh6pge.h>
volatile int i=0,j=0;
int main(void)
{
	SYSCTL_RCGCGPIO_R = 0x100;

	GPIO_PORTJ_DIR_R = 0;
	GPIO_PORTJ_DEN_R = 0xFF;
	GPIO_PORTJ_PUR_R|= 0xC;
	GPIO_PORTJ_DATA_R|= 0xC;
	while(1)
	{
		if((GPIO_PORTJ_DATA_R & 0x8)==0x8 && j==0)
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
	}
	return 0;
}
