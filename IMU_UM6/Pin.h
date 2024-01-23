/*-----------------------------------------------------------------------------------------------------------------------*/
/*                                             																			 */
/*                                                                                                                       */
/*                                            																		     */
/*																														 */
/*                                            																			 */
/*                                            																			 */
/*                                            																			 */
/*                                            																			 */
/*      MIT   TECH   TEAM  ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> M4 Cortex Library (General.io.h)              			 */												   
/*                                     29/11/2014      																	 */
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

#define PIN0 0x01
#define PIN1 0x02
#define PIN2 0x04
#define PIN3 0x08
#define PIN4 0x10
#define PIN5 0x20
#define PIN6 0x40
#define PIN7 0x80


#define F_on 1
#define H_on 1
#define F_off 0
#define H_off 0
#define G_on 1
#define G_off 0
void ClockPortA()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0 ; //Enables PortA and gives it clock 

}



void ClockPortB()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1 ; //Enables PortB and gives it clock 

}

 

void ClockPortC()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2 ; //Enables PortC and gives it clock 
}



void ClockPortD()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3 ; //Enables PortD and gives it clock 

}



void ClockPortE()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4 ; //Enables PortE and gives it clock 

}



void ClockPortF()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5 ; //Enables PortF and gives it clock 
}



void ClockPortG()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R6 ; //Enables PortG and gives it clock 
}



void ClockPortH()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R7 ; //Enables PortH and gives it clock 
}



void ClockPortJ()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R8 ; //Enables PortJ and gives it clock 
}



void ClockPortK()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R9 ; //Enables PortK and gives it clock 
}



void ClockPortL()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10 ; //Enables PortL and gives it clock 

}



void ClockPortM()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R11 ; //Enables PortM and gives it clock 

}



void ClockPortN()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R12 ; //Enables PortN and gives it clock 

}



void ClockPortP()
{
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R13 ; //Enables PortP and gives it clock 

}


void DigitalSetA(int pin) // Digital Mode enable PortA
{

GPIO_PORTA_DEN_R |= pin ; 

}


void DigitalSetB(int pin) // Digital Mode enable PortB
{

GPIO_PORTB_DEN_R |= pin ; 

}




void DigitalSetC(int pin) // Digital Mode enable PortC
{

GPIO_PORTC_DEN_R |= pin ; 

}




void DigitalSetD(int pin) //Digital Mode enable PortD
{

GPIO_PORTD_DEN_R |= pin ; 

}




void DigitalSetE(int pin) //Digital Mode enable PortE
{

GPIO_PORTE_DEN_R |= pin ; 

}




void DigitalSetF(int pin)  //Digital Mode enable PortF
{

GPIO_PORTF_DEN_R |= pin ; 

}




void DigitalSetG(int pin)  //Digital Mode enable PortG
{

GPIO_PORTG_DEN_R |= pin ; 

}




void DigitalSetH(int pin) //Digital Mode enable PortH
{

GPIO_PORTH_DEN_R |= pin ; 

}



void DigitalSetK(int pin) //Digital Mode enable PortK
{

GPIO_PORTK_DEN_R |= pin ; 

}



void DigitalSetL(int pin) //Digital Mode enable PortL
{

GPIO_PORTL_DEN_R |= pin ; 

}



void DigitalSetM(int pin) //Digital Mode enable PortM
{

GPIO_PORTM_DEN_R |= pin ; 

}



void DigitalSetN(int pin) //Digital Mode enable PortN
{

GPIO_PORTN_DEN_R |= pin ; 

}



void DigitalSetP(int pin) //Digital Mode enable PortP
{

GPIO_PORTP_DEN_R |= pin ; 

}



void DigitalClearA(int pin) // Digital Mode enable PortA
{

GPIO_PORTA_DEN_R  &= ~pin; 

}


void DigitalClearB(int pin) // Digital Mode enable PortB
{

GPIO_PORTB_DEN_R  &= ~pin;

}




void DigitalClearC(int pin) // Digital Mode enable PortC
{

GPIO_PORTC_DEN_R  &= ~pin;

}




void DigitalClearD(int pin) //Digital Mode enable PortD
{

GPIO_PORTD_DEN_R  &= ~pin;
}




void DigitalClearE(int pin) //Digital Mode enable PortE
{

GPIO_PORTE_DEN_R  &= ~pin;

}




void DigitalClearF(int pin)  //Digital Mode enable PortF
{

GPIO_PORTF_DEN_R  &= ~pin;

}




void DigitalClearG(int pin)  //Digital Mode enable PortG
{

GPIO_PORTG_DEN_R  &= ~pin;
}




void DigitalClearH(int pin) //Digital Mode enable PortH
{

GPIO_PORTH_DEN_R  &= ~pin;

}



void DigitalClearK(int pin) //Digital Mode enable PortK
{

GPIO_PORTK_DEN_R  &= ~pin;
}



void DigitalClearL(int pin) //Digital Mode enable PortL
{

GPIO_PORTL_DEN_R  &= ~pin;

}



void DigitalClearM(int pin) //Digital Mode enable PortM
{

GPIO_PORTM_DEN_R  &= ~pin;

}



void DigitalClearN(int pin) //Digital Mode enable PortN
{

GPIO_PORTN_DEN_R  &= ~pin;
}



void DigitalClearP(int pin) //Digital Mode enable PortP
{

GPIO_PORTP_DEN_R  &= ~pin;

}



void InputA(int pin) // Input PortA
{

GPIO_PORTA_DIR_R  &= ~pin; 

}


void InputB(int pin) // Input PortB
{

GPIO_PORTB_DIR_R  &= ~pin;

}




void InputC(int pin) // Input PortC
{

GPIO_PORTC_DIR_R  &= ~pin;

}




void InputD(int pin) //Input PortD
{

GPIO_PORTD_DIR_R  &= ~pin;
}




void InputE(int pin) //Input PortE
{

GPIO_PORTE_DIR_R  &= ~pin;

}




void InputF(int pin)  //Input PortF
{

GPIO_PORTF_DIR_R  &= ~pin;

}




void InputG(int pin)  //Input PortG
{

GPIO_PORTG_DIR_R  &= ~pin;
}




void InputH(int pin) //Input PortH
{

GPIO_PORTH_DIR_R  &= ~pin;

}



void InputK(int pin) //Input PortK
{

GPIO_PORTK_DIR_R  &= ~pin;
}



void InputL(int pin) //Input PortL
{

GPIO_PORTL_DIR_R  &= ~pin;

}



void InputM(int pin) //Input PortM
{

GPIO_PORTM_DIR_R  &= ~pin;

}



void InputN(int pin) //Input PortN
{

GPIO_PORTN_DIR_R  &= ~pin;
}



void InputP(int pin) //Input PortP
{

GPIO_PORTP_DIR_R  &= ~pin;

}


void OutputA(int pin) // Output PortA
{

GPIO_PORTA_DIR_R |= pin ; 

}


void OutputB(int pin) // Output PortB
{

GPIO_PORTB_DIR_R |= pin ; 

}




void OutputC(int pin) // Output PortC
{

GPIO_PORTC_DIR_R |= pin ; 

}




void OutputD(int pin) //Output PortD
{

GPIO_PORTD_DIR_R |= pin ; 

}




void OutputE(int pin) //Output PortE
{

GPIO_PORTE_DIR_R |= pin ; 

}




void OutputF(int pin)  //Output PortF
{

GPIO_PORTF_DIR_R |= pin ; 

}




void OutputG(int pin)  //Output PortG
{

GPIO_PORTG_DIR_R |= pin ; 

}




void OutputH(int pin) //Output PortH
{

GPIO_PORTH_DIR_R |= pin ; 

}



void OutputK(int pin) //Output PortK
{

GPIO_PORTK_DIR_R |= pin ; 

}



void OutputL(int pin) //Output PortL
{

GPIO_PORTL_DIR_R |= pin ; 

}



void OutputM(int pin) //Output PortM
{

GPIO_PORTM_DIR_R |= pin ; 

}



void OutputN(int pin) //Output PortN
{

GPIO_PORTN_DIR_R |= pin ; 

}



void OutputP(int pin) //Output PortP
{

GPIO_PORTP_DIR_R |= pin ; 

}


void SetPortA(int pin) // Set data  PortA
{

GPIO_PORTA_DATA_R |= pin ; 

}


void SetPortB(int pin) // Set data PortB
{

GPIO_PORTB_DATA_R |= pin ; 

}




void SetPortC(int pin) // Set data PortC
{

GPIO_PORTC_DATA_R |= pin ; 

}




void SetPortD(int pin) //Set data PortD
{

GPIO_PORTD_DATA_R |= pin ; 

}




void SetPortE(int pin) //Set data PortE
{

GPIO_PORTE_DATA_R |= pin ; 

}




void SetPortF(int pin)  //Set data PortF
{

GPIO_PORTF_DATA_R |= pin ; 

}




void SetPortG(int pin)  //Set data PortG
{

GPIO_PORTG_DATA_R |= pin ; 

}




void SetPortH(int pin) //Set data PortH
{

GPIO_PORTH_DATA_R |= pin ; 

}



void SetPortK(int pin) //Set data PortK
{

GPIO_PORTK_DATA_R |= pin ; 

}



void SetPortL(int pin) //Set data PortL
{

GPIO_PORTL_DATA_R |= pin ; 

}



void SetPortM(int pin) //Set data PortM
{

GPIO_PORTM_DATA_R |= pin ; 

}



void SetPortN(int pin) //Set data PortN
{

GPIO_PORTN_DATA_R |= pin ; 

}



void SetPortP(int pin) //Set data PortP
{

GPIO_PORTP_DATA_R |= pin ; 

}


void ClearPortA(int pin) // Clear data  PortA
{

GPIO_PORTA_DATA_R &= ~pin; 

}


void ClearPortB(int pin) // Clear data PortB
{

GPIO_PORTB_DATA_R &= ~pin;

}




void ClearPortC(int pin) // Clear data PortC
{

GPIO_PORTC_DATA_R &= ~pin;

}




void ClearPortD(int pin) //Clear data PortD
{

GPIO_PORTD_DATA_R &= ~pin;

}




void ClearPortE(int pin) //Clear data PortE
{

GPIO_PORTE_DATA_R &= ~pin; 

}




void ClearPortF(int pin)  //Clear data PortF
{

GPIO_PORTF_DATA_R &= ~pin;

}




void ClearPortG(int pin)  //Clear data PortG
{

GPIO_PORTG_DATA_R &= ~pin; 

}




void ClearPortH(int pin) //Clear data PortH
{

GPIO_PORTH_DATA_R &= ~pin;

}



void ClearPortK(int pin) //Clear data PortK
{

GPIO_PORTK_DATA_R &= ~pin; 

}



void ClearPortL(int pin) //Clear data PortL
{

GPIO_PORTL_DATA_R &= ~pin; 

}



void ClearPortM(int pin) //Clear data PortM
{

GPIO_PORTM_DATA_R &= ~pin;

}



void ClearPortN(int pin) //Clear data PortN
{

GPIO_PORTN_DATA_R &= ~pin; 

}



void ClearPortP(int pin) //Clear data PortP
{

GPIO_PORTP_DATA_R &= ~pin; 

}



