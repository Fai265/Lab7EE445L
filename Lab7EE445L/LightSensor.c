// LightSensor.c
// Runs on LM4F120/TM4C123
// Monitors and manages light level in box
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017

#include <stdint.h>
#include "Timer0A.h"
#include "tm4c123gh6pm.h"

#define PD1 (*((volatile uint32_t *)0x40007008))

uint32_t LightLower = 0;
uint32_t LightUpper = 0;

/***************************************************************
Light_Init()
	Initializes lower and upper thresholds for light level.

inputs:
	lowerThresh - (0 <=> 4096) value of lower threshold.
	upperThresh - (0 <=> 4096) value of upper threshold.
	
	REQ: lowerThresh < upperThresh

outputs:
	none
***************************************************************/
void Light_Init(uint32_t lowerThresh, uint32_t upperThresh){
	if(lowerThresh < upperThresh){
		LightLower = lowerThresh;
		LightUpper = upperThresh;
	}
	else{
		LightLower = 0;
		LightUpper = 4096;
	}
}

/***************************************************************
Check_Light()
	Uses 64x ADC hardware averaging over 1000 samples to check the
	current light level.

inputs:
	none

outputs:
	-1 - Light level too low.
	0  - Light level nominal.
	1  - Light level too high.
***************************************************************/
int8_t Check_Light(void){
	int lightLevel = sensorRead(1);
	if(lightLevel < LightLower){
		return -1;
	}
	if(lightLevel > LightUpper){
		return 1;
	}
	return 0;
}

/***************************************************************
Rotate_Motor(uint8_t)
	Toggles motor.

inputs:
	none

outputs:
	none
***************************************************************/
void Rotate_Motor(){
	PD1 ^= 0x02;
}
