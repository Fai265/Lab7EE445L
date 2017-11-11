// Timer0A.c
// Initializes Timer0A at 100 Hz
// Handles Timer0A interrupts to sample ADC.
// Cooper Carnahan and Faisal Mahmood
// November 1, 2017

#include <stdint.h>
#include "ADCSWTrigger.h"
#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "ADCSWTrigger.h"

static uint8_t intVector = 0x0;	//Bit 0: Check moisture sensor if high
																//Bit 1: Check light sensor if high
																//Bit 2: Check temperature sensor if high
static uint8_t avgRdy = 0;
static short idx = 0;
volatile uint32_t ADCvalue;
static int ADCavg;

void Timer0A_Init(void){
  volatile uint32_t delay;
  DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
  TIMER0_CFG_R = 0;                // configure for 32-bit timer mode
  // **** timer0A initialization ****
  TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD; // configure for periodic mode
  TIMER0_TAILR_R = 80000;     // start value for 1000 Hz interrupts
  TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
  TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer0A=priority 2
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // top 3 bits
  NVIC_EN0_R |= 1<<19;              // enable interrupt 19 in NVIC
}

void Timer0A_Handler(void){
	if(intVector&0x01){		//moisture bit set
		ADCvalue = ADC0_InSeq1();	//Sample PE0
		ADCavg += ADCvalue;
	}
	if(intVector&0x02){		//light bit set
		ADCvalue = ADC0_InSeq2();	//Sample PE1
		ADCavg += ADCvalue;
	}
	if(intVector&0x04){		//temperature bit set
		ADCvalue = ADC0_InSeq3();	//Sample PE2
		ADCavg += ADCvalue;
	}
	idx++;
	if(idx == 999){
		avgRdy = 0;		//Indicates that 1000 samples have been generated
	}
}

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
int sensorRead(uint8_t sensorSel){
	avgRdy = 1;
	idx = 0;
	ADCavg = 0;
	intVector |= 1 << sensorSel;
	while(avgRdy){}	//While set, waits for 1000 samples to generate
	intVector = 0;
	ADCavg /= 1000;
	
	return ADCavg;
}
