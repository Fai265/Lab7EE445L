// LightSensor.c
// Runs on LM4F120/TM4C123
// Monitors and manages light level in box
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017

#include <stdint.h>
#include "Timer0A.h"
#include "tm4c123gh6pm.h"

#define PD1 (*((volatile uint32_t *)0x40007008))

uint32_t lightLower = 0;
uint32_t lightUpper = 0;

/***************************************************************
lightInit()
	Initializes lower and upper thresholds for light level.

inputs:
	lowerThresh - (0 <=> 4096) value of lower threshold.
	upperThresh - (0 <=> 4096) value of upper threshold.
	
	REQ: lowerThresh < upperThresh

outputs:
	none
***************************************************************/
void lightInit(uint32_t lowerThresh, uint32_t upperThresh){
	if(lowerThresh < upperThresh){
		lightLower = lowerThresh;
		lightUpper = upperThresh;
	}
	else{
		lightLower = 0;
		lightUpper = 4096;
	}
}

/***************************************************************
checkLight()
	Uses 64x ADC hardware averaging over 1000 samples to check the
	current light level.

inputs:
	none

outputs:
	-1 - Light level too low.
	0  - Light level nominal.
	1  - Light level too high.
***************************************************************/
int8_t checkLight(void){
	int lightLevel = sensorRead(1);
	if(lightLevel < lightLower){
		return -1;
	}
	if(lightLevel > lightUpper){
		return 1;
	}
	return 0;
}

/***************************************************************
rotateMotor(uint8_t)
	Toggles motor.

inputs:
	none

outputs:
	none
***************************************************************/
void rotateMotor(){
	PD1 ^= 0x02;
}
