// Transistor.c
// Runs on LM4F120/TM4C123
// Initializations for output ports.
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017

// Solenoid Transistor - PD0
// Motor Transistor    - PD1
// Peltier Transistor  - PD2
// Fan Transistor      - PD3

#include "tm4c123gh6pm.h"
#include <stdint.h>

/***************************************************************
SolenoidTransistor_Init()
	Intitializes PD0 which controls the transistor to the solenoid

inputs:
	none
	
outputs:
	none
***************************************************************/
void SolenoidTransistor_Init(void){
  GPIO_PORTD_DIR_R |= 0x01;         // 5) PD0 out
  GPIO_PORTD_DEN_R |= 0x01;         // 7) enable digital I/O on PD0
}

/***************************************************************
MotorTransistor_Init()
	Intitializes PD1 which controls the transistor to the motor

inputs:
	none
	
outputs:
	none
***************************************************************/
void MotorTransistor_Init(void){
  GPIO_PORTD_DIR_R |= 0x02;         // 5) PD1 out
  GPIO_PORTD_DEN_R |= 0x02;         // 7) enable digital I/O on PD1
}

/***************************************************************
PeltierTransistor_Init()
	Intitializes PD2 which controls the transistor to the Peltier
	heating unit

inputs:
	none
	
outputs:
	none
***************************************************************/
void PeltierTransistor_Init(void){
  GPIO_PORTD_DIR_R |= 0x04;         // 5) PD2 out
  GPIO_PORTD_DEN_R |= 0x04;         // 7) enable digital I/O on PD2
}

/***************************************************************
FanTransistor_Init()
	Intitializes PD3 which controls the transistor to the fan

inputs:
	none
	
outputs:
	none
***************************************************************/
void FanTransistor_Init(void){
  GPIO_PORTD_DIR_R |= 0x08;         // 5) PD3 out
  GPIO_PORTD_DEN_R |= 0x04;         // 7) enable digital I/O on PD3
}

/***************************************************************
Transistor_Init()
	Initializes all the transistor controls to the system (PD0-PD3)

inputs:
	none
	
outputs:
	none
***************************************************************/
void Transistor_Init(void){
	int delay;
  SYSCTL_RCGC2_R |= 0x00000008;     // 1) activate clock for Port D
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTD_AMSEL_R = 0x00;        // 3) disable analog on PD
	GPIO_PORTD_AFSEL_R &= ~0x04;      // 6) disable alt funct on PD7-0
  GPIO_PORTD_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PD4-0
	SolenoidTransistor_Init();
	MotorTransistor_Init();
	PeltierTransistor_Init();
	PeltierTransistor_Init();
}