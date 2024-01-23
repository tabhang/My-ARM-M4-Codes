#include<stdint.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

volatile int i=0;

int main(void)
{
	System80Mhz();

	SYSCTL_RCGCADC_R = 0x1;
	SYSCTL_RCGCGPIO_R = 0x88;

	GPIO_PORTD_DIR_R = ~(1<<0);
	GPIO_PORTD_AFSEL_R = 0x1;
	GPIO_PORTD_DEN_R = ~(1<<0);
	GPIO_PORTD_AMSEL_R = 0x1;
	
	ADC0_ACTSS_R = 0x0;
	ADC0_EMUX_R = 0xF;
	ADC0_SSMUX0_R = 0xF;
	ADC0_SSCTL0_R = 0x6;
	ADC0_ACTSS_R = 0x1;

	while(1)
	{
		if((ADC0_RIS_R & 0x1)==0x1)
		{
			i=ADC0_SSFIFO0_R;
		}
	}
	return 0;
}
