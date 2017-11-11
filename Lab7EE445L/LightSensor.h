// LightSensor.h
// Runs on LM4F120/TM4C123
// Monitors and manages light level in box
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017

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
void Light_Init(uint32_t, uint32_t);

/***************************************************************
Check_Light()
	Uses 64x ADC hardware averaging over 1000 samples to check the
	current light level.

inputs:
	none

outputs:
	Digital 0-4096 value of the light level.
***************************************************************/
int32_t Check_Light(void);

/***************************************************************
Rotate_Motor()
	Toggles the motor;

inputs:
	none

outputs:
	none
***************************************************************/
void Rotate_Motor();