#include "tm4c123gh6pm.h"
#include <stdint.h>

// Solenoid Transistor - PD0
// Motor Transistor    - PD1
// Peltier Transistor  - PD2
// Fan Transistor      - PD3

void SolenoidTransistor_Init(void){
  GPIO_PORTD_DIR_R |= 0x01;         // 5) PD0 out
  GPIO_PORTD_DEN_R |= 0x01;         // 7) enable digital I/O on PD0
}

void MotorTransistor_Init(void){
  GPIO_PORTD_DIR_R |= 0x02;         // 5) PD1 out
  GPIO_PORTD_DEN_R |= 0x02;         // 7) enable digital I/O on PD1
}

void PeltierTransistor_Init(void){
  GPIO_PORTD_DIR_R |= 0x04;         // 5) PD2 out
  GPIO_PORTD_DEN_R |= 0x04;         // 7) enable digital I/O on PD2
}

void FanTransistor_Init(void){
  GPIO_PORTD_DIR_R |= 0x08;         // 5) PD3 out
  GPIO_PORTD_DEN_R |= 0x04;         // 7) enable digital I/O on PD3
}

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