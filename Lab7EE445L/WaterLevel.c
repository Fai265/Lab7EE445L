// WaterLevel.c
// Runs on LM4F120/TM4C123
// Monitors and manages moisture level in box
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017

#include <stdint.h>
#include "Timer0A.h"
#include "tm4c123gh6pm.h"

#define PD0 (*((volatile uint32_t *)0x40007004))

uint32_t moistureLower = 0;
uint32_t moistureUpper = 0;

/***************************************************************
moistureInit()
	Initializes lower and upper thresholds for moisture level.

inputs:
	lowerThresh - (0 <=> 4096) value of lower threshold.
	upperThresh - (0 <=> 4096) value of upper threshold.
	
	REQ: lowerThresh < upperThresh

outputs:
	none
***************************************************************/
void moistureInit(uint32_t lowerThresh, uint32_t upperThresh){
	if(lowerThresh < upperThresh){
		moistureLower = lowerThresh;
		moistureUpper = upperThresh;
	}
	else{
		moistureLower = 0;
		moistureUpper = 4096;
	}
}

/***************************************************************
checkmoisture()
	Uses 64x ADC hardware averaging over 1000 samples to check the
	current moisture level.

inputs:
	none

outputs:
	-1 - moisture level too low.
	0  - moisture level nominal.
	1  - moisture level too high.
***************************************************************/
int8_t checkMoisture(void){
	int moistureLevel = sensorRead(0);
	if(moistureLevel < moistureLower){
		return -1;
	}
	if(moistureLevel > moistureUpper){
		return 1;
	}
	return 0;
}

/***************************************************************
flowValve()
	Toggles the valve.

inputs:
	none

outputs:
	none
***************************************************************/
void flowValve(){
	PD0 ^= 0x01;
}
