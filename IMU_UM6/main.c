#include<stdint.h>
#include"tm4c123gh6pge.h"
#include"delaym4.h"
#include"80Mhz.h"
#include"Pin.h"
#include"Uart.h"
#include "um7.h"

volatile int a=0;
volatile float angle_rock=0.0;
volatile float um6_angle=0.0;
volatile int ini=0;
volatile int sign=0;
volatile float yaw_raw=0;
volatile float yaw_final=0;

volatile float pitch_raw=0;
volatile float pitch_final=0;

volatile float roll_raw=0;
volatile float roll_final=0;


void ISR1()
{
	UART4_ICR_R			|=0x00000010;
	a=(UART4_DR_R&0x000000ff);
	encode(a);
}
int main()
{
	System80Mhz();
	ClockPortG();
	ClockPortF();
	DigitalSetF();
	GPIO_PORTF_AFSEL_R = 0x2;
	GPIO_PORTF_PCTL_R = 0x70;

	DigitalSetG();
	OutputG();

	TIMER0_CTL_R = 0;
	TIMER0_CFG_R = 0;
	TIMER0_TAMR_R = 0x12;
	TIMER0_TAILR_R = 120760;
	TIMER0_CTL_R = 0x1;
	TIMER0_TAMATCHR_R = 60380;

	state = STATE_ZERO;
	EnableUART4(1,115200,1,0);
	while(1)
	{
		yaw_raw=yaw&0x7fff;
		yaw_final=((yaw_raw)/32767)*360;

		roll_raw=roll&0x7fff;
		roll_final=((roll_raw)/32767)*360;

		pitch_raw=pitch&0x7fff;
		pitch_final=((pitch_raw)/32767)*360;

		if(TIMER0_TAR_R <(TIMER0_TAMATCHR_R ))
		{
			GPIO_PORTG_DATA_R = 0xFF;
		}
		else
		{
			GPIO_PORTG_DATA_R = 0;
		}


	}
}
