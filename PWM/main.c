/*
 * main.c
 */
#include<stdint.h>
#include<delaym4.h>
#include<tm4c123gh6pge.h>
#include<80Mhz.h>

int main(void)
{
	System80Mhz();

	SYSCTL_RCGC0_R |= 0x100000;
	SYSCTL_RCGC2_R |= 0x80;
	SYSCTL_RCGCGPIO_R = 0x2FFF;

	GPIO_PORTH_DIR_R  =0xff;
	GPIO_PORTH_DEN_R = 0xff;
	GPIO_PORTH_AFSEL_R = 0x1;
	GPIO_PORTH_PCTL_R = 0x4;

	SYSCTL_RCC_R &= ~0x1E0000;

	PWM0_0_GENA_R = 0x8C;
	PWM0_0_LOAD_R = 2499;
	PWM0_0_CMPA_R = 1249;
	PWM0_0_CTL_R = 0x1;
	PWM0_ENABLE_R = 0x1;

/*	GPIO_PORTK_DIR_R  =0xff;
	GPIO_PORTK_DEN_R = 0xff;
	GPIO_PORTH_DIR_R  =0xff;
	GPIO_PORTH_DEN_R = 0xff;
	GPIO_PORTH_AFSEL_R = 0x9;
	GPIO_PORTH_PCTL_R = 0x4004;

	SYSCTL_RCC_R = 0x140000;

	PWM0_0_GENA_R = 0x8C;
	PWM0_0_LOAD_R = 99;
	PWM0_0_CMPA_R = 44;
	PWM0_0_CTL_R = 0x1;

	PWM0_1_GENB_R = 0x80C;
	PWM0_1_LOAD_R = 99;
	PWM0_1_CMPA_R = 49;

	PWM0_1_CTL_R = 0x1;

	PWM0_ENABLE_R = 0x9;*/
	GPIO_PORTH_DATA_R |=0x2;
	//GPIO_PORTK_DATA_R &=~0x4;

	while(1)
	{

	}
	return 0;
}
