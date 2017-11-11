// TemperatureSensor.c
// Runs on LM4F120/TM4C123
// Monitors and manages temperature level in box
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017

#include <stdint.h>
#include "Timer0A.h"
#include "tm4c123gh6pm.h"

#define PD3 (*((volatile uint32_t *)0x4000700F))
#define PD2 (*((volatile uint32_t *)0x4000700C))

uint32_t temperatureLower = 0;
uint32_t temperatureUpper = 0;

/***************************************************************
PeltierTransistor_Init()
	Initializes PD2 for output to the Peltier System.

inputs:
	none

outputs:
	none
***************************************************************/
void PeltierTransistor_Init(void){
	int delay = 0;
  SYSCTL_RCGC2_R |= 0x00000008;     // 1) activate clock for Port D
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTD_AMSEL_R = 0x00;        // 3) disable analog on PD
  GPIO_PORTD_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PD4-0
  GPIO_PORTD_DIR_R |= 0x04;         // 5) PD2 out
  GPIO_PORTD_AFSEL_R &= ~0x04;      // 6) disable alt funct on PD7-0
  //GPIO_PORTF_PUR_R = 0x11;        // enable pull-up on PD0 and PD4
  GPIO_PORTD_DEN_R |= 0x04;         // 7) enable digital I/O on PD2
}

/***************************************************************
temperatureInit()
	Initializes lower and upper thresholds for temperature level.

inputs:
	lowerThresh - (0 <=> 4096) value of lower threshold.
	upperThresh - (0 <=> 4096) value of upper threshold.
	
	REQ: lowerThresh < upperThresh

outputs:
	none
***************************************************************/
void temperatureInit(uint32_t lowerThresh, uint32_t upperThresh){
	if(lowerThresh < upperThresh){
		temperatureLower = lowerThresh;
		temperatureUpper = upperThresh;
	}
	else{
		temperatureLower = 0;
		temperatureUpper = 4096;
	}
}

/***************************************************************
checktemperature()
	Uses 64x ADC hardware averaging over 1000 samples to check the
	current temperature level.

inputs:
	none

outputs:
	-1 - temperature level too low.
	0  - temperature level nominal.
	1  - temperature level too high.
***************************************************************/
int8_t checkTemperature(void){
	int temperatureLevel = sensorRead(3);
	if(temperatureLevel < temperatureLower){
		return -1;
	}
	if(temperatureLevel > temperatureUpper){
		return 1;
	}
	return 0;
}

/***************************************************************
FanOn()
	Turns on the transistor which controls the current to the fan.

inputs:
	none
outputs:
	none
***************************************************************/
void FanOn(void){
	PD3 |= 0x08; //turns on the transistor connected to fan
}

/***************************************************************
FanOff()
	Turns off the transistor which controls the current to the fan

inputs:
	none
outputs:
	none
***************************************************************/
void FanOff(void){
	PD3 &= ~0x08; //turns off the transistor connected to fan
}

/***************************************************************
powerPeltier()
	Turns the heating element and fan on/off depending on the temp
	of the system.

inputs:
	tempData - the temperature reading of the ADC

outputs:
	none
***************************************************************/
void powerPeltier(int tempData){
	if(tempData == -1){					 //Temperature too low
		FanOn();
		PD2 |= 0x04; //turns on the transistor connected to Peltier 
	}
	else{
		FanOff();
		PD2 &= ~0x04; //turns off the transistor connected to Peltier 
	}
}
