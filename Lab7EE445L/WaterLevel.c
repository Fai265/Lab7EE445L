// WaterLevel.c
// Runs on LM4F120/TM4C123
// Monitors and manages moisture level in box
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017

#include <stdint.h>
#include "Timer0A.h"
#include "tm4c123gh6pm.h"

#define PD0 (*((volatile uint32_t *)0x40007004))

uint32_t MoistureLower = 0;
uint32_t MoistureUpper = 0;

/***************************************************************
Moisture_Init()
	Initializes lower and upper thresholds for moisture level.

inputs:
	lowerThresh - (0 <=> 4096) value of lower threshold.
	upperThresh - (0 <=> 4096) value of upper threshold.
	
	REQ: lowerThresh < upperThresh

outputs:
	none
***************************************************************/
void Moisture_Init(uint32_t lowerThresh, uint32_t upperThresh){
	if(lowerThresh < upperThresh){
		MoistureLower = lowerThresh;
		MoistureUpper = upperThresh;
	}
	else{
		MoistureLower = 0;
		MoistureUpper = 4096;
	}
}

/***************************************************************
check_moisture()
	Uses 64x ADC hardware averaging over 1000 samples to check the
	current moisture level.

inputs:
	none

outputs:
	-1 - moisture level too low.
	0  - moisture level nominal.
	1  - moisture level too high.
***************************************************************/
int8_t Check_Moisture(void){
	int moistureLevel = sensorRead(0);
	if(moistureLevel < MoistureLower){
		return -1;
	}
	if(moistureLevel > MoistureUpper){
		return 1;
	}
	return 0;
}

/***************************************************************
Flow_Valve()
	Toggles the valve.

inputs:
	none

outputs:
	none
***************************************************************/
void Flow_Valve(){
	PD0 ^= 0x01;
}
