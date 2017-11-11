#include "tm4c123gh6pm.h"
#include <stdint.h>

void FanOn(void){
	GPIO_PORTD_DATA_R |= 0x08; //turns on the transistor connected to PD3
}

void FanOff(){
	GPIO_PORTD_DATA_R &= ~0x08; //turns on the transistor connected to PD3
}
