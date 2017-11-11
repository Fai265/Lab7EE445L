// LightSensor.h
// Runs on LM4F120/TM4C123
// Monitors and manages light level in box
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017

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
void lightInit(uint32_t, uint32_t);

/***************************************************************
checkLight()
	Uses 64x ADC hardware averaging over 1000 samples to check the
	current light level.

inputs:
	none

outputs:
	Digital 0-4096 value of the light level.
***************************************************************/
int32_t checkLight(void);

/***************************************************************
rotateMotor()
	Toggles the motor;

inputs:
	none

outputs:
	none
***************************************************************/
void rotateMotor();