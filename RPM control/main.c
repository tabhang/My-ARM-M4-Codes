/*#include<stdint.h>
#include<math.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

volatile float rpm=0,req_rpm=0,duty=0,value=0,error=0,setpoint=0,kp=0,p=0;
volatile int y,x,curr=0,prev=0,k=0;
volatile long int enc_count=0;


void PID(void)
{
	setpoint=req_rpm;
	error=setpoint-rpm;
	p=kp*error;

	if(req_rpm==0)
	{
		duty=0;
		if (rpm>0)
		{
			GPIO_PORTH_DATA_R |= 0x2;
			p=p*(-1);
		}
		else
		{
			GPIO_PORTH_DATA_R &= ~0x2;
		}
		duty=duty+(p/6.15);
		duty=round(duty);
		if(duty>=99)
		{
			duty = 98;
		}
		if(duty<=0)
		{
			duty= 1;
		}
		value=99-duty;
	}
	else
	{
		while (rpm>(req_rpm+31))
		{
			GPIO_PORTH_DATA_R &= ~0x2;
			p=p*(-1);
			duty=(duty)-(p/6.15);
			GPIO_PORTG_DATA_R = 0xff;
			break;
		}
		while(rpm<(req_rpm+31))
		{
			GPIO_PORTH_DATA_R = 0x2;
			duty=(duty)+(p/6.15);
			GPIO_PORTG_DATA_R = 0;
			break;
		}
		duty=round(duty);
		if(duty>=99)
		{
			duty = 98;
		}
		if(duty<=0)
		{
			duty= 1;
		}
		value=98-duty;
	}
}
ISR1()
{
	x=(GPIO_PORTE_DATA_R & 0x1)==0x1;
	if((x))
	{
		enc_count++;                                       //encoder count
	}
	else
	{
		enc_count--;
	}
	GPIO_PORTK_ICR_R = 0x1;
}
ISR2()
{
	curr=enc_count;                    // 770Hz
	y=curr-prev;
	prev=curr;
	rpm=(y*1000*60)/10500;                                      //(puls////e f///req*60)/enc/////_c///ount
	PID();

	PWM0_0_CMPA_R = value;

	TIMER0_ICR_R = 0x10;
}

void PWM_init(void)
{
	GPIO_PORTH_DIR_R  =0xFF;
	GPIO_PORTH_DEN_R = 0xFF;                    // pin H0
	GPIO_PORTH_AFSEL_R = 0x1;
	GPIO_PORTH_PCTL_R = 0x4;

	SYSCTL_RCC_R = 0x100000;

	PWM0_0_GENA_R = 0x8C;
	PWM0_0_LOAD_R = 99;                         //32kHz
	PWM0_0_CTL_R = 0x1;
	PWM0_ENABLE_R = 0x1;
}

void timer_init(void)
{
	NVIC_EN0_R = 0x80000;

	TIMER0_CTL_R = 0;
	TIMER0_CFG_R = 0;
	TIMER0_TAMR_R = 0x32;
	TIMER0_TAILR_R = 8305;
	TIMER0_IMR_R = 0x10;
	TIMER0_CTL_R = 0x1;
	TIMER0_TAMATCHR_R = 4152;
}
void encoder_init(void)
{
	GPIO_PORTK_DIR_R =0;
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

int main(void)

{
	System80Mhz();

	SYSCTL_RCGC0_R |= 0x100000;          // pwm en
	SYSCTL_RCGC2_R |= 0x80;          //port h clock pwm
	SYSCTL_RCGCTIMER_R = 0x1;
	SYSCTL_RCGCGPIO_R = 0x2F0;

	encoder_init();
	timer_init();
	PWM_init();

	GPIO_PORTG_DIR_R = 255;
	GPIO_PORTG_DEN_R = 255;
	while(1)
	{
	}
	return 0;
 }




*/




























#include<stdint.h>
#include<math.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

volatile float rpm=0,req_rpm=0,duty=0,value=0,error=0,setpoint=0,kp=0.08,p=0;
volatile int y,x,curr=0,prev=0,k=0;
volatile long int enc_count=0;


void PID(void)
{
	setpoint=req_rpm;
	error=setpoint-rpm;
	p=kp*error;

	if(req_rpm==0)
	{
		duty=0;
		if (rpm>0)
		{
			GPIO_PORTH_DATA_R &= ~0x2;
			p=p*(-1);
		}
		else
		{
			GPIO_PORTH_DATA_R = 0x2;
		}
		duty=duty+(p/6.15);
		duty=round(duty);
		if(duty>=99)
		{
			duty = 98;
		}
		if(duty<=0)
		{
			duty= 1;
		}
		value=99-duty;
	}
	else
	{
		while (rpm>(req_rpm+31))
		{
			GPIO_PORTH_DATA_R &= ~0x2;
			p=p*(-1);
			duty=(duty)-(p/6.15);
			break;
		}
		while(rpm<(req_rpm+31))
		{
			GPIO_PORTH_DATA_R = 0x2;
			duty=(duty)+(p/6.15);
			break;
		}
		duty=round(duty);
		if(duty>=99)
		{
			duty = 98;
		}
		if(duty<=0)
		{
			duty= 1;
		}
		value=98-duty;
	}
}
ISR1()
{
	x=(GPIO_PORTE_DATA_R & 0x1)==0x1;
	if((x))
	{
		enc_count++;                                       //encoder count
	}
	else
	{
		enc_count--;
	}
	GPIO_PORTK_ICR_R = 0x1;
}
ISR2()
{
	GPIO_PORTG_DATA_R ^= 255;
	curr=enc_count;                    // 770Hz
	y=curr-prev;
	prev=curr;
	rpm=(y*1000*60)/10500;                                      //(puls////e f///req*60)/enc/////_c///ount
	PID();

	PWM0_0_CMPA_R = 49;

	TIMER0_ICR_R = 0x10;
}

void PWM_init(void)
{
	GPIO_PORTH_DIR_R  =0xFF;
	GPIO_PORTH_DEN_R = 0xFF;                    // pin H0
	GPIO_PORTH_AFSEL_R = 0x1;
	GPIO_PORTH_PCTL_R = 0x4;

	SYSCTL_RCC_R |=0x100000;

	PWM0_0_GENA_R = 0x8C;
	PWM0_0_LOAD_R = 99;                         //32kHz
	PWM0_0_CTL_R = 0x1;
	PWM0_ENABLE_R = 0x1;
}

void timer_init(void)
{
	NVIC_EN0_R = 0x80000;

	TIMER0_CTL_R = 0;
	TIMER0_CFG_R = 0;
	TIMER0_TAMR_R = 0x32;
	TIMER0_TAILR_R = 8305;
	TIMER0_IMR_R = 0x10;
	TIMER0_CTL_R = 0x1;
	TIMER0_TAMATCHR_R = 4152;
}
void encoder_init(void)
{
	GPIO_PORTK_DIR_R =0;
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

int main(void)

{
	System80Mhz();

	SYSCTL_RCGC0_R |= 0x100000;          // pwm en
	SYSCTL_RCGC2_R |= 0x80;          //port h clock pwm
	SYSCTL_RCGCTIMER_R = 0x1;
	SYSCTL_RCGCGPIO_R = 0x2fff;

	encoder_init();
	timer_init();
	PWM_init();

	GPIO_PORTG_DIR_R = 255;
	GPIO_PORTG_DEN_R = 255;
	while(1)
	{
	}
	return 0;
 }
