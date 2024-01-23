#include<stdint.h>
#include<math.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

volatile float angle=0;                                     // IMU
volatile int next_byte,imu_data,intger;

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
void IMU_init(void)
{
	NVIC_EN1_R = 0x10000000;                    // uart 4

	GPIO_PORTJ_AFSEL_R = 0x1;
	GPIO_PORTJ_PCTL_R = 0x1;
	GPIO_PORTJ_DEN_R = 0x1;

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

	SYSCTL_RCGCUART_R = 0x10;
	IMU_init();
	while(1)
	{
	}
	return 0;
}
/*ISR_IMU()
{
	imu_data=UART5_DR_R;
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

	UART5_ICR_R = 0x10;
}
void IMU_init(void)
{
	NVIC_EN1_R = 0x20000000;                    // uart 5

	GPIO_PORTJ_AFSEL_R = 0xC;
	GPIO_PORTJ_PCTL_R = 0x1100;
	GPIO_PORTJ_DEN_R = 0x4;

	UART5_CTL_R = 0x200;
	UART5_IBRD_R = 0x82;
	UART5_FBRD_R = 0xD;
	UART5_LCRH_R = 0x60;
	UART5_IM_R = 0x10;
	UART5_RIS_R = 0x10;
	UART5_MIS_R = 0x10;
	UART5_CTL_R = 0x201;
}
int main(void)
{
	System80Mhz();

	SYSCTL_RCGCUART_R = 0x20;
	IMU_init();
	while(1)
	{
	}
	return 0;
}*/
