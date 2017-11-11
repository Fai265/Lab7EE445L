// WaterLevel.h
// Runs on LM4F120/TM4C123
// Monitors and manages moisture level in box
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017

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
void moistureInit(uint32_t, uint32_t);

/***************************************************************
checkmoisture()
	Uses 64x ADC hardware averaging over 1000 samples to check the
	current moisture level.

inputs:
	none

outputs:
	Digital 0-4096 value of the moisture level.
***************************************************************/
int32_t checkMoisture(void);

/***************************************************************
flowValve()
	Toggles the valve.

inputs:
	none

outputs:
	none
***************************************************************/
void flowValve();