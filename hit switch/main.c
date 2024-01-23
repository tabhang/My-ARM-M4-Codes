/*
 * main.c
 */
#include <stdint.h>
#include <tm4c123gh6pge.h>
volatile int i=0,j=0,k=0;

int main(void)
{
	SYSCTL_RCGCGPIO_R|= 0x1FF;
	GPIO_PORTH_DIR_R = 0xFF;
	GPIO_PORTJ_DIR_R = 0;
	GPIO_PORTH_DEN_R = 0xFF;
	GPIO_PORTJ_DEN_R = 0x4;
	GPIO_PORTJ_PUR_R = 0x4;
	GPIO_PORTJ_DATA_R = 0x4;
	GPIO_PORTG_DIR_R = 0xFF;
	GPIO_PORTG_DEN_R = 0xFF;
	while(1)
	{
    	if((GPIO_PORTJ_DATA_R & 0x4 )== 0 )
    	{
    		for(j=0;j<5000;j++)
    		{
    		}
    		if((GPIO_PORTJ_DATA_R )==0x4)
    		{
    			GPIO_PORTH_DATA_R ^=0x2 ;
    			GPIO_PORTG_DATA_R ^=0x2 ;
    		}
    	}

	}
}
/*
int main(void)
{
	SYSCTL_RCGCGPIO_R|= 0x1FF;
	GPIO_PORTH_DIR_R = 0xFF;
	GPIO_PORTF_DIR_R = 0;
	GPIO_PORTH_DEN_R = 0xFF;
	GPIO_PORTF_DEN_R = 0xFF;
	GPIO_PORTF_PUR_R = 0xFE;
    while(1)
    {
    	if(!(GPIO_PORTF_DATA_R ==0xFE )) // (GPIO_PORTF_DATA_R & 0x01)==0    (GPIO_PORTF_DATA_R !=0x01)
    	{
    		GPIO_PORTH_DATA_R = (1<<i);
    		for(j=0;j<500000;j++)
    		{

    		}
    	}
    	i++;
    	if(i>7)
    	{
    		i=0;
    	}


    }
	return 0;
}
*/
