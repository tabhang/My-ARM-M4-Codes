/*
 * trans.multiple...
 */
#include<stdint.h>
#include<math.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

#define R 0.3

// IMU variables
volatile float angle=0;
volatile int next_byte,imu_data,intger;

// encoder 1 variables
volatile int x1,y1,curr1=0,prev1=0,enc_count1=0;

// encoder 2 variables
volatile int x2,y2,curr2=0,prev2=0,enc_count2=0;

// equaton variables
volatile float v1=0,v2=0,v3=0,rpm1=0,rpm2=0,rpm3=0,crpm1=0,crpm2=0,crpm3=0,theta,vel_x=0,vel_y=0,k,y;
volatile int x;

// uart trans
int data[]={0,170,85,240};
int i=0;

ISR_IMU()
{
	imu_data=UART4_DR_R;
	if (imu_data & 0x80)
	{
		imu_data&=0b01111111;
		intger=(imu_data<<7);
		next_byte=1;
	}
	else if (next_byte)
	{
		intger+=imu_data;
		angle=intger/10;
		next_byte=0;
	}
	if (angle>180)
	{
		angle=angle-360;
		if (angle<0)
		{
			angle=angle*(-1);
		}
	}

	UART4_ICR_R = 0x10;
}
void uart()
{
	GPIO_PORTJ_AFSEL_R |= 0xC;
	GPIO_PORTJ_PCTL_R |= 0x1100;
	GPIO_PORTJ_DEN_R |= 0x8;

	UART5_CTL_R = 0x100;
	UART5_IBRD_R = 0x82;
	UART5_FBRD_R = 0xD;
	UART5_LCRH_R = 0x60;
	UART5_CTL_R = 0x101;
}
void IMU_init(void)
{
	NVIC_EN1_R = 0x10000000;                    // uart 4

	GPIO_PORTJ_AFSEL_R |= 0x1;
	GPIO_PORTJ_PCTL_R |= 0x1;
	GPIO_PORTJ_DEN_R |= 0x1;

	UART4_CTL_R = 0x200;
	UART4_IBRD_R = 0x82;
	UART4_FBRD_R = 0xD;
	UART4_LCRH_R = 0x60;
	UART4_IM_R = 0x10;
	UART4_RIS_R = 0x10;
	UART4_MIS_R = 0x10;
	UART4_CTL_R = 0x201;
}
int main(void)
{
	System80Mhz();

	SYSCTL_RCGCUART_R = 0x30;
	SYSCTL_RCGCGPIO_R = 0x2fff;
	uart();
	IMU_init();
    while(1)
	{
		if((UART5_FR_R & 0x20)==0x00)
    	{
			i=i%4;
			UART5_DR_R = data[i];
			i++;
    	}
	}
	return 0;
}
/*
int data[]={0,170,85,240};
int i=0;

int main(void)
{
	System80Mhz();

	SYSCTL_RCGCUART_R = 0x20;
	SYSCTL_RCGCGPIO_R = 0x100;

	GPIO_PORTJ_AFSEL_R = 0xC;
	GPIO_PORTJ_PCTL_R = 0x1100;
	GPIO_PORTJ_DEN_R = 0x8;

	UART5_CTL_R = 0x100;
	UART5_IBRD_R = 0x82;
	UART5_FBRD_R = 0xD;
	UART5_LCRH_R = 0x60;
	UART5_CTL_R = 0x101;
    while(1)
	{
		if((UART5_FR_R & 0x20)==0x00)
    	{
			i=i%4;
			UART5_DR_R = data[i];
			i++;
    	}
	}
	return 0;
}
*/
