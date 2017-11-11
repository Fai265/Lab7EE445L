#include "tm4c123gh6pm.h"
#include <stdint.h>
#include ".\Fan.h"
//Peltier Transistor - PD2

void PeltierTransistor_Init(void){
	int delay;
  SYSCTL_RCGC2_R |= 0x00000008;     // 1) activate clock for Port D
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTD_AMSEL_R = 0x00;        // 3) disable analog on PD
  GPIO_PORTD_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PD4-0
  GPIO_PORTD_DIR_R |= 0x04;         // 5) PD2 out
  GPIO_PORTD_AFSEL_R &= ~0x04;      // 6) disable alt funct on PD7-0
  //GPIO_PORTF_PUR_R = 0x11;        // enable pull-up on PD0 and PD4
  GPIO_PORTD_DEN_R |= 0x04;         // 7) enable digital I/O on PD2
}

void Switch_Init_Testing(void){
	int delay;
	SYSCTL_RCGC2_R |= 0x00000002;     // 1) activate clock for Port B
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog on PB
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PB0
  GPIO_PORTB_DIR_R &= ~0x01;        // 5) PD2 out
  GPIO_PORTB_AFSEL_R &= ~0x01;        // 6) disable alt funct on PB0
  //GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PD0 and PD4
  GPIO_PORTB_DEN_R |= 0x01;          // 7) enable digital I/O on PB0
}

void PeltierOn(int tempData){
	//int temperature=tempData*1000/4096*3.3;
	//int On = (GPIO_PORTB_DATA_R & 0x01);
	int minTemp=500; //this number can be changed later based on more testing if needed
	if(tempData<minTemp){
		FanOn();
		GPIO_PORTD_DATA_R |= 0x04; //turns on the transistor connected to Peltier 
	}
	else{
		GPIO_PORTD_DATA_R &= ~0x04; //turns on the transistor connected to Peltier 
	}
}


