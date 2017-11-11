// TemperatureSensor.c
// Runs on LM4F120/TM4C123
// Monitors and manages temperature level in box
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017

/***************************************************************
PeltierTransistor_Init()
	Initializes PD2 for output to the Peltier System.

inputs:
	none

outputs:
	none
***************************************************************/
void PeltierTransistor_Init(void);

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
void temperatureInit(uint32_t lowerThresh, uint32_t upperThresh);

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
int8_t checkTemperature(void);

/***************************************************************
powerPeltier()
	Turns the heating element and fan on/off depending on the temp
	of the system.

inputs:
	tempData - the temperature reading of the ADC

outputs:
	none
***************************************************************/
void powerPeltier(int tempData);

/***************************************************************
FanOn()
	Turns on the transistor which controls the current to the fan.

inputs:
	none
outputs:
	none
***************************************************************/
void FanOn(void);

/***************************************************************
FanOff()
	Turns off the transistor which controls the current to the fan

inputs:
	none
outputs:
	none
***************************************************************/
void FanOff(void);

