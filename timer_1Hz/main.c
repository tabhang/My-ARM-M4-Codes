
#include<stdint.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>
//t0ccp1-f1

int main(void)
{
	System80Mhz();

	SYSCTL_RCGCTIMER_R = 0x1;
	SYSCTL_RCGCGPIO_R = 0xA0;

	GPIO_PORTF_DIR_R  =0x2;
	GPIO_PORTF_DEN_R = 0x2;
	GPIO_PORTF_AFSEL_R = 0x2;
	GPIO_PORTF_PCTL_R = 0x70;

	TIMER0_CTL_R = 0;
	TIMER0_CFG_R = 0;
	TIMER0_TAMR_R = 0x12;
	TIMER0_TAILR_R = 120760;
	TIMER0_CTL_R = 0x1;
	TIMER0_TAMATCHR_R = 60380;

	GPIO_PORTH_DIR_R  =0xFF;
	GPIO_PORTH_DEN_R = 0xFF;
	while(1)
	{
		if(TIMER0_TAR_R <(TIMER0_TAMATCHR_R ))
		{
			GPIO_PORTH_DATA_R = 0xFF;
		}
		else
		{
			GPIO_PORTH_DATA_R = 0;
		}
	}
	return 0;
}

///////////////////////////////////////////// 1Hz////////////////////////

/*
#include<stdint.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>
//t0ccp1-f1
volatile float t=0,x=0;

ISR()
{
t++;
GPIO_PORTH_DATA_R = 0xFF;
GPIO_PORTG_DATA_R = 0xFF;
TIMER0_ICR_R = 0x10;
}
int main(void)
{
	System80Mhz();

	SYSCTL_RCGCTIMER_R = 0x1;
	SYSCTL_RCGCGPIO_R = 0x2F0;
	NVIC_EN0_R = 0x80000;
	GPIO_PORTF_DIR_R  =0x2;
	GPIO_PORTF_DEN_R = 0x2;
	GPIO_PORTF_AFSEL_R = 0x2;
	GPIO_PORTF_PCTL_R = 0x70;

	TIMER0_CTL_R = 0;
	TIMER0_CFG_R = 0;
	TIMER0_TAMR_R = 0x32;
	TIMER0_TAILR_R = 78500000;
	TIMER0_CTL_R = 0x1;
	TIMER0_TAMATCHR_R = 39250000;
	
	GPIO_PORTH_DIR_R  =0xFF;
	GPIO_PORTH_DEN_R = 0xFF;
	GPIO_PORTG_DIR_R = 0xFF;
	GPIO_PORTG_DEN_R |= 0xFF;
	while(1)
	{
		if(TIMER0_TAR_R <(TIMER0_TAMATCHR_R ))
		{
			GPIO_PORTH_DATA_R = 0xFF;
			t++;
		}
		else
		{
			GPIO_PORTH_DATA_R = 0;
		}
		x=(t/1226562)*2 ;
	}
	return 0;
}

*/
