#include<stdint.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

volatile int i=0,j=0,k=0;

int main(void)
{
	System80Mhz();

	SYSCTL_RCGCADC_R = 0x1;
	SYSCTL_RCGCGPIO_R = 0x8;

	GPIO_PORTD_DIR_R = 0;
	GPIO_PORTD_AFSEL_R = 0x3;
	GPIO_PORTD_DEN_R = 0;
	GPIO_PORTD_AMSEL_R = 0x3;

	ADC0_ACTSS_R = 0x0;
	ADC0_EMUX_R = 0xF;

	ADC0_SSMUX0_R = 0xF0;
	ADC0_SSCTL0_R = 0x60;
	ADC0_ACTSS_R = 0x1;
    while(1)
	{
		if((ADC0_SSMUX0_R & 0xF0)==0xF0)
		{
			i = ADC0_SSFIFO0_R;
			ADC0_SSMUX0_R = 0xE0;
			delay(100);
		}
		if((ADC0_SSMUX0_R & 0xE0)==0xE0)
		{
			j = ADC0_SSFIFO0_R;
			ADC0_SSMUX0_R = 0xF0;
			delay(100);
		}
	}
	return 0;
}



/*if(k==0)
{
	ADC0_SSMUX0_R = 0xF0000000;
	ADC0_SSCTL0_R = 0x60000000;

	ADC0_ACTSS_R = 0x1;
	ADC0_PSSI_R = 0x8000001;

    i=ADC0_SSFIFO0_R;
	k=1;
}
else if(k==1)
{
	ADC0_SSMUX1_R = 0xE000;
	ADC0_SSCTL1_R = 0x6000;

	ADC0_ACTSS_R = 0x2;
	ADC0_PSSI_R = 0x8000002;

	j=ADC0_SSFIFO1_R;
	k=0;
}*/

/*
if((ADC0_RIS_R & 0x2)==0x2)
{
	j=ADC0_SSFIFO1_R;
	ADC0_ACTSS_R = 0x1;
	ADC0_PSSI_R = 0x8000001;
}
if((ADC0_RIS_R & 0x1)==0x1)
{
	i=ADC0_SSFIFO0_R;
	ADC0_ACTSS_R = 0x2;
	ADC0_PSSI_R = 0x8000002;
}*/
/*ADC0_SSCTL0_R = 0x60000000;
ADC0_SSMUX1_R = 0xE000;
ADC0_SSCTL1_R = 0x6000;

ADC0_ACTSS_R = 0x3;
ADC0_PSSI_R = 0x8000003;*/
