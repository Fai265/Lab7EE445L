// Timer0A.h
// Initializes Timer0A at 100 Hz
// Handles Timer0A interrupts to sample ADC.
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017


void Timer0A_Init(void);

void Timer0A_Handler(void);

/***************************************************************
sensorRead(uint8_t)
	Uses a busy-wait spin to cause software averaging on 1000 ADC
	values.

inputs:
	sensorSel - Selector number to choose which sensor to sample.
	Selector number corresponds to the port number.
		0 - Moisture sensor
		1 - Light sensor
		2 - Temperature sensor

outputs:
	1000 averaged ADC values.
***************************************************************/
int sensorRead(uint8_t);
