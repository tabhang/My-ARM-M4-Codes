/*
 * main.c
 */
#include<stdint.h>
#include<tm4c123gh6pge.h>
#include<80Mhz.h>
#include<delaym4.h>

int main(void)
{

	System80Mhz();

	SYSCTL_RCGC0_R = 0x100000;
	SYSCTL_RCGC2_R = 0x80;

	GPIO_PORTH_DIR_R  =0x3;
	GPIO_PORTH_DEN_R = 0x3;
	GPIO_PORTH_AFSEL_R = 0x3;
	GPIO_PORTH_PCTL_R = 0x44;

	SYSCTL_RCC_R = 0x100000;

	PWM0_0_GENA_R = 0x8C;
	PWM0_0_DBCTL_R = 0x1;
	PWM0_0_DBRISE_R = 2;
	PWM0_0_DBFALL_R = 2;
	PWM0_0_LOAD_R = 0x63;
	PWM0_0_CMPA_R = 0x31;
	PWM0_0_CTL_R = 0x1;
	PWM0_ENABLE_R = 0x3;
	while(1)
	{

	}
	return 0;
}
