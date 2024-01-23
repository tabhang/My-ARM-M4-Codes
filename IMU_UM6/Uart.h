/*-----------------------------------------------------------------------------------------------------------------------*/
/*                                             																			 */
/*                                                                                                                       */
/*                                            																		     */
/*																														 */
/*                                            																			 */
/*                                            																			 */
/*                                            																			 */
/*                                            																			 */
/*      MIT   TECH   TEAM  ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> M4 Cortex Library (uart.h)              			         */
/*                                     27/07/2015      																	 */
/*                                            																			 */
/*                                            																	         */
/*                                            																			 */
/*                                            																			 */
/*                                            																		     */
/*                                            																			 */
/*                                            																			 */
/*                                            																			 */
/*                                            																			 */
/*-----------------------------------------------------------------------------------------------------------------------*/

#include<math.h>

volatile float fbaud=0 ;
#define RX_INT_ON 1
#define RX_INT_OFF 0
#define RX_ON 1
#define RX_OFF 0
#define TX_ON 1
#define TX_OFF 0

void EnableUART0(int rxint , double baud, int rx , int tx)
{

   if(!rxint)
   {
	     SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;
	     SYSCTL_RCGCUART_R |= 0x1;
		 delay(1000);
		 ClockPortA();
		 delay(1000);
		 UART0_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
		 fbaud = ((80000000)/((16)*(baud)));
		 UART0_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
		 UART0_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
		 UART0_LCRH_R = 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
		 UART0_CTL_R |= 0x00000001;    // enable UART

		 if(rx)
		 {
		 GPIO_PORTA_AFSEL_R |= 0x01;    // enable alt funct on PC5-4
		 GPIO_PORTA_DEN_R |= 0x01;      // configure PC5-4 as UART1
		 GPIO_PORTA_PCTL_R |=   GPIO_PCTL_PA0_U0RX ;
		 GPIO_PORTA_AMSEL_R &= ~0x01;
		 }
		 if(tx)
		 {
		 GPIO_PORTA_AFSEL_R |= 0x02;    // enable alt funct on PC5-4
		 GPIO_PORTA_DEN_R |= 0x02;      // configure PC5-4 as UART1
		 GPIO_PORTA_PCTL_R |=  GPIO_PCTL_PA1_U0TX ;
		 GPIO_PORTA_AMSEL_R &= ~0x02;
		 }
   }
   else
   {
	      ClockPortA();
	      SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;
	      SYSCTL_RCGCUART_R |= 0x1 ; // activate UART0
	 	  delay(1000);
	 	  UART0_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
	 	  fbaud = ((80000000)/((16)*(baud)));
	 	  UART0_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
	 	  UART0_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
	 	  UART0_LCRH_R |= 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
	 	  UART0_CTL_R |= 0x201 ;       // enable UART
	 	  GPIO_PORTA_AFSEL_R |= 0x01;    // enable alt funct on PA
	 	  GPIO_PORTA_DEN_R |= 0x01;      // configure PA0 as UAR01
	 	  GPIO_PORTA_PCTL_R |=   GPIO_PCTL_PA0_U0RX ;
	 	  GPIO_PORTA_AMSEL_R &= ~0x01;
	 	  UART0_IM_R |= 0x10;//receive interrupt
	 	  UART0_IFLS_R  |= 0x10; // USELESS
	 	  NVIC_EN0_R |=   NVIC_EN0_INT5 ;// ENABLE interrupt uart 0

   }

	 
	 
}
void EnableUART1(int rxint , double baud, int rx , int tx)
{

   if(!rxint)
   {
	     SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1;
		 SYSCTL_RCGCUART_R |= 0x2;
		 delay(1000);
		 ClockPortC();
		 delay(1000);
		 UART1_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
		 fbaud = ((80000000)/((16)*(baud)));
		 UART1_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
		 UART1_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
		 UART1_LCRH_R = 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
		 UART1_CTL_R |= 0x00000001;    // enable UART

		 if(rx)
		 {
		 GPIO_PORTC_AFSEL_R |= 0x10;    // enable alt funct on PC5-4
		 GPIO_PORTC_DEN_R |= 0x10;      // configure PC5-4 as UART1
		 GPIO_PORTC_PCTL_R |=   GPIO_PCTL_PC4_U1RX ;
		 GPIO_PORTC_AMSEL_R &= ~0x10;
		 }
		 if(tx)
		 {
		 GPIO_PORTC_AFSEL_R |= 0x20;    // enable alt funct on PC5-4
		 GPIO_PORTC_DEN_R |= 0x20;      // configure PC5-4 as UART1
		 GPIO_PORTC_PCTL_R |=  GPIO_PCTL_PC5_U1TX ;
		 GPIO_PORTC_AMSEL_R &= ~0x20;
		 }
   }
   else
   {
	      ClockPortC();
	      SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1;
	      SYSCTL_RCGCUART_R |= 0x02 ; // activate UART0
	 	  delay(1000);
	 	  UART1_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
	 	  fbaud = ((80000000)/((16)*(baud)));
	 	  UART1_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
	 	  UART1_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
	 	  UART1_LCRH_R |= 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
	 	  UART1_CTL_R |= 0x201 ;       // enable UART
	 	  GPIO_PORTC_AFSEL_R |= 0x10;    // enable alt funct on PA
	 	  GPIO_PORTC_DEN_R |= 0x10;      // configure PA0 as UAR01
	 	  GPIO_PORTC_PCTL_R |=   GPIO_PCTL_PC4_U1RX ;
	 	  GPIO_PORTC_AMSEL_R &= ~0x10;
	 	  UART1_IM_R |= 0x10;//receive interrupt
	 	  UART1_IFLS_R  |= 0x10; // USELESS
	 	  NVIC_EN0_R |=   NVIC_EN0_INT6 ;// ENABLE interrupt uart 0

   }



}

void EnableUART2(int rxint , double baud, int rx , int tx)
{

   if(!rxint)
   {
	     SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART2;
		 SYSCTL_RCGCUART_R |= 0x04;
		 delay(1000);
		 ClockPortD();
		 delay(1000);
		 UART2_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
		 fbaud = ((80000000)/((16)*(baud)));
		 UART2_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
		 UART2_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
		 UART2_LCRH_R = 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
		 UART2_CTL_R |= 0x00000001;    // enable UART

		 if(rx)
		 {
		 GPIO_PORTD_AFSEL_R |= 0x40;    // enable alt funct on PC5-4
		 GPIO_PORTD_DEN_R |= 0x40;      // configure PC5-4 as UART1
		 GPIO_PORTD_PCTL_R |=   GPIO_PCTL_PD6_U2RX ;
		 GPIO_PORTD_AMSEL_R &= ~0x40;
		 }
		 if(tx)
		 {
		 GPIO_PORTD_AFSEL_R |= 0x80;    // enable alt funct on PC5-4
		 GPIO_PORTD_DEN_R |= 0x80;      // configure PC5-4 as UART1
		 GPIO_PORTD_PCTL_R |=  GPIO_PCTL_PD7_U2TX ;
		 GPIO_PORTD_AMSEL_R &= ~0x80;
		 }
   }
   else
   {
	      ClockPortD();
	      SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART2;
	      SYSCTL_RCGCUART_R |= 0x4 ; // activate UART0
	 	  delay(1000);
	 	  UART2_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
	 	  fbaud = ((80000000)/((16)*(baud)));
	 	  UART2_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
	 	  UART2_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
	 	  UART2_LCRH_R |= 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
	 	  UART2_CTL_R |= 0x201 ;       // enable UART
	 	  GPIO_PORTD_AFSEL_R |= 0x40;    // enable alt funct on PA
	 	  GPIO_PORTD_DEN_R |= 0x40;      // configure PA0 as UAR01
	 	  GPIO_PORTD_PCTL_R |=   GPIO_PCTL_PD6_U2RX ;
	 	  GPIO_PORTD_AMSEL_R &= ~0x40;
	 	  UART2_IM_R |= 0x10;//receive interrupt
	 	  UART2_IFLS_R  |= 0x10; // USELESS
	 	  NVIC_EN1_R |= NVIC_EN0_INT1 ;// ENABLE interrupt uart 0

   }



}

void EnableUART3(int rxint , double baud, int rx , int tx)
{

   if(!rxint)
   {
	    // SYSCTL_RCGC2_R |= SYSCTL_RCGC2_UART3;
		 SYSCTL_RCGCUART_R |= 0x8 ;
		 delay(1000);
		 ClockPortC();
		 delay(1000);
		 UART3_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
		 fbaud = ((80000000)/((16)*(baud)));
		 UART3_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
		 UART3_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
		 UART3_LCRH_R = 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
		 UART3_CTL_R |= 0x00000001;    // enable UART

		 if(rx)
		 {
		 GPIO_PORTC_AFSEL_R |= 0x40;    // enable alt funct on PC5-4
		 GPIO_PORTC_DEN_R |= 0x40;      // configure PC5-4 as UART1
		 GPIO_PORTC_PCTL_R |=   GPIO_PCTL_PC6_U3RX ;
		 GPIO_PORTC_AMSEL_R &= ~0x40;
		 }
		 if(tx)
		 {
		 GPIO_PORTC_AFSEL_R |= 0x80;    // enable alt funct on PC5-4
		 GPIO_PORTC_DEN_R |= 0x80;      // configure PC5-4 as UART1
		 GPIO_PORTC_PCTL_R |=  GPIO_PCTL_PC7_U3TX ;
		 GPIO_PORTC_AMSEL_R &= ~0x80;
		 }
   }
   else
   {
	      ClockPortC();
	      SYSCTL_RCGCUART_R |= 0x8 ; // activate UART0
	 	  delay(1000);
	 	  UART3_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
	 	  fbaud = ((80000000)/((16)*(baud)));
	 	  UART3_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
	 	  UART3_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
	 	  UART3_LCRH_R |= 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
	 	  UART3_CTL_R |= 0x201 ;       // enable UART
	 	  GPIO_PORTC_AFSEL_R |= 0x40;    // enable alt funct on PA
	 	  GPIO_PORTC_DEN_R |= 0x40;      // configure PA0 as UAR01
	 	  GPIO_PORTC_PCTL_R |=   GPIO_PCTL_PC6_U3RX ;
	 	  GPIO_PORTC_AMSEL_R &= ~0x40;
	 	  UART3_IM_R |= 0x10;//receive interrupt
	 	  UART3_IFLS_R  |= 0x10; // USELESS
	 	  NVIC_EN1_R |=   NVIC_EN0_INT27 ;// ENABLE interrupt uart 0

   }



}

void EnableUART4(int rxint , double baud, int rx , int tx)
{

   if(!rxint)
   {
		 SYSCTL_RCGCUART_R |= 0x10;
		 delay(1000);
		 ClockPortJ();
		 delay(1000);
		 UART4_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
		 fbaud = ((80000000)/((16)*(baud)));
		 UART4_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
		 UART4_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
		 UART4_LCRH_R = 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
		 UART4_CTL_R |= 0x00000001;    // enable UART

		 if(rx)
		 {
		 GPIO_PORTJ_AFSEL_R |= 0x01;    // enable alt funct on PC5-4
		 GPIO_PORTJ_DEN_R |= 0x01;      // configure PC5-4 as UART1
		 GPIO_PORTJ_PCTL_R |=   GPIO_PCTL_PJ0_U4RX ;
		 GPIO_PORTJ_AMSEL_R &= ~0x01;
		 }
		 if(tx)
		 {
		 GPIO_PORTJ_AFSEL_R |= 0x02;    // enable alt funct on PC5-4
		 GPIO_PORTJ_DEN_R |= 0x02;      // configure PC5-4 as UART1
		 GPIO_PORTJ_PCTL_R |=  GPIO_PCTL_PJ1_U4TX ;
		 GPIO_PORTJ_AMSEL_R &= ~0x02;
		 }
   }
   else
   {
	      ClockPortJ();
	      SYSCTL_RCGCUART_R |= 0x10 ; // activate UART0
	 	  delay(1000);
	 	  UART4_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
	 	  fbaud = ((80000000)/((16)*(baud)));
	 	  UART4_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
	 	  UART4_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
	 	  UART4_LCRH_R |= 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
	 	  UART4_CTL_R |= 0x201 ;       // enable UART
	 	  GPIO_PORTJ_AFSEL_R |= 0x01;    // enable alt funct on PA
	 	  GPIO_PORTJ_DEN_R |= 0x01;      // configure PA0 as UAR01
	 	  GPIO_PORTJ_PCTL_R |=   GPIO_PCTL_PJ0_U4RX ;
	 	  GPIO_PORTJ_AMSEL_R &= ~0x01;
	 	  UART4_IM_R |= 0x10;//receive interrupt
	 	  UART4_IFLS_R  |= 0x10; // USELESS
	 	  NVIC_EN1_R |=   NVIC_EN0_INT28 ;// ENABLE interrupt uart 0

   }



}


void EnableUART5(int rxint , double baud, int rx , int tx)
{

   if(!rxint)
   {
		 SYSCTL_RCGCUART_R |= 0x20;
		 delay(1000);
		 ClockPortJ();
		 delay(1000);
		 UART5_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
		 fbaud = ((80000000)/((16)*(baud)));
		 UART5_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
		 UART5_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
		 UART5_LCRH_R = 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
		 UART5_CTL_R |= 0x00000001;    // enable UART

		 if(rx)
		 {
		 GPIO_PORTJ_AFSEL_R |= 0x04;    // enable alt funct on PC5-4
		 GPIO_PORTJ_DEN_R |= 0x04;      // configure PC5-4 as UART1
		 GPIO_PORTJ_PCTL_R |=   GPIO_PCTL_PJ2_U5RX ;
		 GPIO_PORTJ_AMSEL_R &= ~0x04;
		 }
		 if(tx)
		 {
		 GPIO_PORTJ_AFSEL_R |= 0x08;    // enable alt funct on PC5-4
		 GPIO_PORTJ_DEN_R |= 0x08;      // configure PC5-4 as UART1
		 GPIO_PORTJ_PCTL_R |=  GPIO_PCTL_PJ3_U5TX ;
		 GPIO_PORTJ_AMSEL_R &= ~0x08;
		 }
   }
   else
   {
	      ClockPortJ();
	      SYSCTL_RCGCUART_R |= 0x20 ; // activate UART0
	 	  delay(1000);
	 	  UART5_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
	 	  fbaud = ((80000000)/((16)*(baud)));
	 	  UART5_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
	 	  UART5_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
	 	  UART5_LCRH_R |= 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
	 	  UART5_CTL_R |= 0x201 ;       // enable UART
	 	  GPIO_PORTJ_AFSEL_R |= 0x04;    // enable alt funct on PA
	 	  GPIO_PORTJ_DEN_R |= 0x04;      // configure PA0 as UAR01
	 	  GPIO_PORTJ_PCTL_R |=   GPIO_PCTL_PJ2_U5RX ;
	 	  GPIO_PORTJ_AMSEL_R &= ~0x04;
	 	  UART5_IM_R |= 0x10;//receive interrupt
	 	  UART5_IFLS_R  |= 0x10; // USELESS
	 	  NVIC_EN1_R |=   NVIC_EN0_INT29 ;// ENABLE interrupt uart 0

   }



}

void EnableUART6(int rxint , double baud, int rx , int tx)
{

   if(!rxint)
   {
		 SYSCTL_RCGCUART_R |= 0x40;
		 delay(1000);
		 ClockPortJ();
		 delay(1000);
		 UART6_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
		 fbaud = ((80000000)/((16)*(baud)));
		 UART6_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
		 UART6_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
		 UART6_LCRH_R = 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
		 UART6_CTL_R |= 0x00000001;    // enable UART

		 if(rx)
		 {
		 GPIO_PORTJ_AFSEL_R |= 0x10;    // enable alt funct on PC5-4
		 GPIO_PORTJ_DEN_R |= 0x10;      // configure PC5-4 as UART1
		 GPIO_PORTJ_PCTL_R |=   GPIO_PCTL_PJ4_U6RX ;
		 GPIO_PORTJ_AMSEL_R &= ~0x10;
		 }
		 if(tx)
		 {
		 GPIO_PORTJ_AFSEL_R |= 0x20;    // enable alt funct on PC5-4
		 GPIO_PORTJ_DEN_R |= 0x20;      // configure PC5-4 as UART1
		 GPIO_PORTJ_PCTL_R |=  GPIO_PCTL_PJ5_U6TX ;
		 GPIO_PORTJ_AMSEL_R &= ~0x20;
		 }
   }
   else
   {
	      ClockPortJ();
	      SYSCTL_RCGCUART_R |= 0x40 ; // activate UART0
	 	  delay(1000);
	 	  UART6_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
	 	  fbaud = ((80000000)/((16)*(baud)));
	 	  UART6_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
	 	  UART6_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
	 	  UART6_LCRH_R |= 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
	 	  UART6_CTL_R |= 0x201 ;       // enable UART
	 	  GPIO_PORTJ_AFSEL_R |= 0x10;    // enable alt funct on PA
	 	  GPIO_PORTJ_DEN_R |= 0x10;      // configure PA0 as UAR01
	 	  GPIO_PORTJ_PCTL_R |=   GPIO_PCTL_PJ4_U6RX ;
	 	  GPIO_PORTJ_AMSEL_R &= ~0x10;
	 	  UART6_IM_R |= 0x10;//receive interrupt
	 	  UART6_IFLS_R  |= 0x10; // USELESS
	 	  NVIC_EN1_R |=   NVIC_EN0_INT30 ;// ENABLE interrupt uart 0

   }



}

void EnableUART7(int rxint , double baud, int rx , int tx)
{

   if(!rxint)
   {
		 SYSCTL_RCGCUART_R |= 0x80;
		 delay(1000);
		 ClockPortK();
		 delay(1000);
		 UART7_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
		 fbaud = ((80000000)/((16)*(baud)));
		 UART7_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
		 UART7_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
		 UART7_LCRH_R = 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
		 UART7_CTL_R |= 0x00000001;    // enable UART

		 if(rx)
		 {
		 GPIO_PORTK_AFSEL_R |= 0x10;    // enable alt funct on PC5-4
		 GPIO_PORTK_DEN_R |= 0x10;      // configure PC5-4 as UART1
		 GPIO_PORTK_PCTL_R |=   GPIO_PCTL_PK4_U7RX ;
		 GPIO_PORTK_AMSEL_R &= ~0x10;
		 }
		 if(tx)
		 {
		 GPIO_PORTK_AFSEL_R |= 0x20;    // enable alt funct on PC5-4
		 GPIO_PORTK_DEN_R |= 0x20;      // configure PC5-4 as UART1
		 GPIO_PORTK_PCTL_R |=  GPIO_PCTL_PK5_U7TX ;
		 GPIO_PORTK_AMSEL_R &= ~0x20;
		 }
   }
   else
   {
	      ClockPortK();
	      SYSCTL_RCGCUART_R |= 0x80 ; // activate UART0
	 	  delay(1000);
	 	  UART7_CTL_R &= ~UART_CTL_UARTEN;  // disable UART
	 	  fbaud = ((80000000)/((16)*(baud)));
	 	  UART7_IBRD_R = (int)((80000000)/((16)*(baud)));    //520 ;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
	 	  UART7_FBRD_R = (int)(((fmod(fbaud,1.0))*64));   //53 ;     // FBRD = round(0.40278 * 64) = 26
	 	  UART7_LCRH_R |= 0x00000060;  // 8 bit, no parity bits, one stop, FIFOs
	 	  UART7_CTL_R |= 0x201 ;       // enable UART
	 	  GPIO_PORTK_AFSEL_R |= 0x10;    // enable alt funct on PA
	 	  GPIO_PORTK_DEN_R |= 0x10;      // configure PA0 as UAR01
	 	  GPIO_PORTK_PCTL_R |=   GPIO_PCTL_PK4_U7RX ;
	 	  GPIO_PORTK_AMSEL_R &= ~0x10;
	 	  UART7_IM_R |= 0x10;//receive interrupt
	 	  UART7_IFLS_R  |= 0x10; // USELESS
	 	  NVIC_EN1_R |=   NVIC_EN0_INT31 ;// ENABLE interrupt uart 0

   }



}



