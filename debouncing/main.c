#include <stdint.h>
#include <tm4c123gh6pge.h>
volatile int i=0,j;
int main(void)
{
	SYSCTL_RCGCGPIO_R|= 0x1FF;

	GPIO_PORTH_DIR_R = 0xFF;
	GPIO_PORTH_DEN_R = 0xFF;

	GPIO_PORTF_DIR_R = 0;
	GPIO_PORTF_DEN_R = 0xFF;
	GPIO_PORTF_DATA_R= 0xFE;
	GPIO_PORTF_PUR_R = 0xFE;                           //................................:............................:
    while(1)                                           // (GPIO_PORTF_DATA_R & 0x01)==0  : (GPIO_PORTF_DATA_R !=0x01) :
    {                                                  //................................:............................:
    	if(!(GPIO_PORTF_DATA_R ==0xFE ))
    	{
    		for(j=0;j<5000;j++)
    		{
    		}
    		if(GPIO_PORTF_DATA_R ==0xFE)
    		{
    			GPIO_PORTH_DATA_R=i++;
    		}
    	}
    }
	return 0;
}
