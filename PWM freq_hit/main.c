/*
 * main.c
 */
#include<stdint.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

volatile int duty,j=0,freq=7;

int main(void)
{
	SYSCTL_RCC_R = 0x140000;

	System80Mhz();

	SYSCTL_RCGC0_R = 0x100000;
	SYSCTL_RCGC2_R = 0xF0;

	GPIO_PORTH_DIR_R  =0x1;
	GPIO_PORTH_DEN_R = 0x1;
	GPIO_PORTH_AFSEL_R = 0x1;
	GPIO_PORTH_PCTL_R = 0x4;

	PWM0_0_GENA_R = 0x8C;
	PWM0_0_LOAD_R = 24;
	freq = 	PWM0_0_LOAD_R;
	PWM0_0_CMPA_R = 0xC;
	PWM0_0_CTL_R = 0x1;
	PWM0_ENABLE_R = 0x1;
	
	SYSCTL_RCGCGPIO_R|= 0x20;
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
	    		freq= freq +20;
	    		PWM0_0_LOAD_R = freq;
	    		/*if(duty>100)
	    		{
	    			duty=1;
	    		}*/
	   		}
	   	}
    }
	return 0;
}
