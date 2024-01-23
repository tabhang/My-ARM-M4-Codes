
#include<stdint.h>
#include<math.h>
#include<tm4c123gh6pge.h>
#include<delaym4.h>
#include<80Mhz.h>

#define R 0.3
#define kp_a 0.1
//#define kp 0.5

void equations(float vx,float vy,float w);
void dir(void);

// IMU variables
volatile float angle=0;
volatile int next_byte,imu_data,intger;

// encoder 1 variables
volatile int x1,y1,curr1=0,prev1=0,enc_count1=0;

// encoder 2 variables
volatile int x2,y2,curr2=0,prev2=0,enc_count2=0,enc_count=0;

// equaton variables
volatile float v1=0,v2=0,v3=0,rpm1=0,rpm2=0,rpm3=0,crpm1=0,crpm2=0,crpm3=0,theta,vel_x=0,vel_y=0,k,y;
volatile int x;

// uart trans
int data[]={222,0,0,0};
int i=0;

//rpm control variables
volatile float setpoint1,setpoint2,error1,error2,p1,p2,duty1,duty2,value1,value2,er=0,p,kp=0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ISR_encoder1()
{
	x1=(GPIO_PORTE_DATA_R & 0x1)==0x1;
	if((x1))
	{
		enc_count1++;                                       //encoder count
	}
	else
	{
		enc_count1--;
	}

	GPIO_PORTK_ICR_R = 0x1;
}
ISR_encoder2()
{
	x2=(GPIO_PORTP_DATA_R & 0x4)==0x4;
	if((x2))
	{
		enc_count2++;
		//enc_count2 = (enc_count)/2;
	}
	else
	{
		enc_count2--;
		//enc_count2=(enc_count2)/2;
	}

	GPIO_PORTE_ICR_R = 0x8;
}

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
	}


	UART4_ICR_R = 0x10;
}
ISR_timer()
{
	er=-angle;
	p=kp_a*er;

	//control_1();
	curr1=enc_count1;
	y1=curr1-prev1;
	prev1=curr1;
	if(y1<0)
	{
		y1=-1*y1;
	}
	rpm1=(y1*1000*60)/10500;
	setpoint1=crpm1;
	error1=setpoint1-rpm1;
	p1=kp*error1;
	duty1=duty1+(p1/4);
	duty1=round(duty1);
	if(duty1>=99)
	{
		duty1 = 99;
	}
	if(duty1<=0)
	{
		duty1= 1;
	}
	value1=2499-24*duty1;


	//control_2();
	curr2=enc_count2;
	y2=curr2-prev2;
	prev2=curr2;
	if(y2<0)
	{
		y2=-1*y2;
	}
	rpm2=(y2*1000*30)/10500;
	setpoint2=crpm2;
	error2=setpoint2-rpm2;
	p2=kp*error2;
	duty2=duty2+(p2/4);
	duty2=round(duty2);
	if(duty2>=99)
	{
		duty2 = 99;
	}
	if(duty2<=0)
	{
		duty2= 1;
	}
	value2=2499-24*duty2;

	PWM0_0_CMPA_R = value1;
	PWM0_1_CMPB_R = value2;
	TIMER0_ICR_R = 0x10;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void equations(float vx,float vy,float w)
{
	theta=1.57;
	v3= vx*(-sin(theta)) + vy*(cos(theta))+R*w;
	v2= vx*(-sin(2.094+theta)) + vy*(cos(2.094+theta))+R*w;
	v1= vx*(-sin(4.188+theta)) + vy*(cos(4.188+theta))+R*w;

	/*v3= vx*(-1) + vy*(0)+R*w;
	v2= vx*(0.5) + vy*(-0.866)+R*w;
	v1= vx*(0.5) + vy*(0.866)+R*w;*/
	if(v3<0)
	{
		data[1]=0;

		x=v3*(-1);
		data[2]=x;
		k=v3*(-1);
		y=k-x;
		y=y*100;
		data[3]=y;

	}
	else
	{
		data[1]=1;
		x=v3;
		data[2]=x;
		y=v3-x;
		y=y*100;
		data[3]=y;

	}

	crpm1 = (v1*7*60/2*22*0.03);
	crpm2 = (v2*7*60/2*22*0.03);
	crpm3 = (v3*7*60/2*22*0.03);
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
void encoder_init(void)
{
	GPIO_PORTK_DIR_R |=0x6;
	GPIO_PORTK_DEN_R |= 0xF;
	GPIO_PORTK_PUR_R |= 0x1;                  //encoder1 ch1
	GPIO_PORTK_DATA_R = 0x1;

	GPIO_PORTE_DIR_R = 0;
	GPIO_PORTE_DEN_R |= 0x9;
	GPIO_PORTE_PUR_R |= 0x9;                 //encoder1 ch2
	GPIO_PORTE_DATA_R = 0x9;                //encoder2 ch1

	GPIO_PORTP_DIR_R =0;
	GPIO_PORTP_DEN_R |= 0x4;
	GPIO_PORTP_PUR_R |= 0x4;                  //encoder2 ch2
	GPIO_PORTP_DATA_R = 0x4;

	NVIC_EN0_R |= 0x10;                   // intr on E
	NVIC_EN1_R |= 0x800000;               // intr on K

	GPIO_PORTK_IM_R |= 0x1;
	GPIO_PORTK_IEV_R | 0x1;

	GPIO_PORTE_IM_R |= 0x8;
	GPIO_PORTE_IEV_R | 0x8;
}
void PWM_init(void)
{
	GPIO_PORTH_DIR_R  |=0xFF;
	GPIO_PORTH_DEN_R |= 0xFF;
	GPIO_PORTH_AFSEL_R = 0x9;
	GPIO_PORTH_PCTL_R = 0x4004;

	SYSCTL_RCC_R &= ~0x1E0000;

	PWM0_0_GENA_R = 0x8C;
	PWM0_0_LOAD_R = 2499;
	PWM0_0_CTL_R = 0x1;

	PWM0_1_GENB_R = 0x80C;
	PWM0_1_LOAD_R = 2499;
	PWM0_1_CTL_R = 0x1;
	PWM0_ENABLE_R = 0x9;
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
void dir()
{
	if(crpm1>0)
	{
		GPIO_PORTH_DATA_R &= ~0x2;
		//GPIO_PORTH_DATA_R |= 0x2;
	}
	else
	{
		crpm1= -1*crpm1;
		GPIO_PORTH_DATA_R |= 0x2;
		//GPIO_PORTH_DATA_R &= ~0x2;

	}

	if(crpm2>0)
	{
		GPIO_PORTK_DATA_R &=~0x4;
	}
	else
	{
		crpm2= -1*crpm2;
		GPIO_PORTK_DATA_R |= 0x4;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	System80Mhz();

	SYSCTL_RCGC0_R |= 0x100000;
	SYSCTL_RCGC2_R |= 0x80;
	SYSCTL_RCGCUART_R |= 0x30;
	SYSCTL_RCGCTIMER_R |= 0x1;
	SYSCTL_RCGCGPIO_R |= 0x2FFF;

	uart();
	IMU_init();
	encoder_init();
	PWM_init();
	timer_init();

	GPIO_PORTG_DIR_R=255;
	GPIO_PORTG_DEN_R =255;
	//GPIO_PORTK_DIR_R=255;
	//GPIO_PORTK_DEN_R =255;
	//GPIO_PORTK_DATA_R |= 0x4;
	while(1)
	{
		equations(vel_x,vel_y,-p);
		dir();
		if((UART5_FR_R & 0x20)==0x00)
    	{
			i=i%4;
			UART5_DR_R = data[i];
			i++;
    	}
	}
	return 0;
}
