#include<stdint.h>
#include<tm4c123gh6pge.h>
#include<80Mhz.h>
#include<delaym4.h>

volatile int i=0,j=0,k=0;

int main(void)
{
	System80Mhz();

	SYSCTL_RCGC0_R |= 0x100000;
	SYSCTL_RCGC2_R |= 0x80;
	SYSCTL_RCGCGPIO_R |= 0x1C0;

	GPIO_PORTJ_DIR_R = 0;
	GPIO_PORTJ_DEN_R = 0x4;
	GPIO_PORTJ_PUR_R = 0x4;
	GPIO_PORTJ_DATA_R = 0x4;

	GPIO_PORTG_DIR_R = 0xFF;
	GPIO_PORTG_DEN_R = 0xFF;

	while(1)
	{
		if(((GPIO_PORTJ_DATA_R & 0x4 )== 0 )&& k==0)
		{
			GPIO_PORTH_DIR_R  =0xF;
			GPIO_PORTH_DEN_R = 0xF;
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

			GPIO_PORTH_DATA_R |= 0x8;
		    GPIO_PORTG_DATA_R =0x2 ;
		    delay(5000);
		    while(((GPIO_PORTJ_DATA_R & 0x4 )== 0 ))
		    {

		    }
		    delay(5000);
		    k=1;
		}
		else if(((GPIO_PORTJ_DATA_R & 0x4 )== 0 )&& k==1)
		{
			GPIO_PORTH_DIR_R  =0xF;
			GPIO_PORTH_DEN_R = 0xF;
			GPIO_PORTH_AFSEL_R = 0xC;
			GPIO_PORTH_PCTL_R = 0x4400;

			SYSCTL_RCC_R = 0x100000;

			PWM0_1_GENA_R = 0x8C;
			PWM0_1_DBCTL_R = 0x1;
			PWM0_1_DBRISE_R = 2;
			PWM0_1_DBFALL_R = 2;
			PWM0_1_LOAD_R = 0x63;
			PWM0_1_CMPA_R = 0x31;
			PWM0_1_CTL_R = 0x1;
			PWM0_ENABLE_R = 0xc;

			GPIO_PORTG_DATA_R = 0x40 ;
			GPIO_PORTH_DATA_R |= 0x2;
			delay(5000);
		    while(((GPIO_PORTJ_DATA_R & 0x4 )== 0 ))
		    {

		    }
		    delay(5000);
		    k=0;
		}
	}
	return 0;
}
