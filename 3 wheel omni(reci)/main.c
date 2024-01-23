#include<stdint.h>
#include<math.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

#define R 0.3
//#define kp 0.5
// uart reciver variables
volatile int data[4],i=0,sign,v3_int=0;
volatile float v3_frac=0,v3=0;

// encoder 3 variables
volatile int x3,y3,curr3=0,prev3=0,enc_count3=0;

//rpm control variables
volatile float setpoint3,error3,p3,duty3,value3,crpm3=0,rpm3,kp=0.1;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ISR_uart()
{
	i=i%4;
	data[i] = UART5_DR_R;

	if (data[i]==222)
	{
		sign = data[(i+1)%4];
		v3_int = data[(i+2)%4];
		v3_frac = data[(i+3)%4];
	}
	i++;
	v3 = v3_int+(v3_frac/100);
	if (sign==0)
	{
		v3=v3*(-1);
	}
	else if(sign==1)
	{
		v3=v3;
	}
	crpm3 = (v3*7*60/2*22*0.03);
	if(crpm3>0)
	{
		GPIO_PORTH_DATA_R &= ~0x2;
		//GPIO_PORTH_DATA_R |= 0x2;
	}
	else
	{
		crpm3= -1*crpm3;
		GPIO_PORTH_DATA_R |= 0x2;
		//GPIO_PORTH_DATA_R &= ~0x2;
	}
	UART5_ICR_R = 0x10;
}
ISR_encoder3()
{
	x3=(GPIO_PORTE_DATA_R & 0x1)==0x1;
	if((x3))
	{
		enc_count3++;                                       //encoder count
	}
	else
	{
		enc_count3--;
	}

	GPIO_PORTK_ICR_R = 0x1;
}
ISR_timer()
{

	curr3=enc_count3;
	y3=curr3-prev3;
	prev3=curr3;
	if(y3<0)
	{
		y3=-1*y3;
	}
	rpm3=(y3*1000*60)/10500;
	setpoint3=crpm3;
	error3=setpoint3-rpm3;
	p3=kp*error3;
	duty3=duty3+(p3/4);
	duty3=round(duty3);
	if(duty3>=99)
	{
		duty3 = 99;
	}
	if(duty3<=0)
	{
		duty3= 1;
	}
	value3=2499-24*duty3;

	PWM0_0_CMPA_R = value3;
	TIMER0_ICR_R = 0x10;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PWM_init(void)
{
	GPIO_PORTH_DIR_R |=0xff;
	GPIO_PORTH_DEN_R |= 0xff;
	GPIO_PORTH_AFSEL_R |= 0x1;
	GPIO_PORTH_PCTL_R |= 0x4;

	SYSCTL_RCC_R &= ~0x1E0000;

	PWM0_0_GENA_R = 0x8C;
	PWM0_0_LOAD_R = 2499;
	PWM0_0_CTL_R = 0x1;

	PWM0_ENABLE_R = 0x1;
}
void encoder_init(void)
{
	GPIO_PORTK_DIR_R |=0x6;
	GPIO_PORTK_DEN_R |= 0xF;
	GPIO_PORTK_PUR_R |= 0x1;                  //encoder ch1
	GPIO_PORTK_DATA_R |= 0x1;

	GPIO_PORTE_DIR_R = 0;
	GPIO_PORTE_DEN_R |= 0x1;
	GPIO_PORTE_PUR_R |= 0x1;                 //encoder ch2
	GPIO_PORTE_DATA_R |= 0x1;

	NVIC_EN0_R |= 0x10;
	NVIC_EN1_R |= 0x800000;

	GPIO_PORTK_IM_R |= 0x1;
	GPIO_PORTK_IEV_R | 0x1;
}
void timer_init(void)
{
	NVIC_EN0_R |= 0x80000;

	TIMER0_CTL_R = 0;
	TIMER0_CFG_R = 0;
	TIMER0_TAMR_R = 0x32;
	TIMER0_TAILR_R = 207792;
	TIMER0_IMR_R = 0x10;
	TIMER0_CTL_R = 0x1;
	TIMER0_TAMATCHR_R = 103896;
}
void uart_init(void)
{
	NVIC_EN1_R = 0x20000000;

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

	SYSCTL_RCGC0_R |= 0x100000;
	SYSCTL_RCGC2_R |= 0x80;
	SYSCTL_RCGCUART_R = 0x20;
	SYSCTL_RCGCTIMER_R = 0x1;
	SYSCTL_RCGCGPIO_R = 0x2FFF;
	
	uart_init();
	encoder_init();
	PWM_init();
	timer_init();
	while(1)
	{

	}
	return 0;
}
