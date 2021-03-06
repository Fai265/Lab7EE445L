// main.c
// Runs on LM4F120/TM4C123
// UART runs at 115,200 baud rate 
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017


#include <stdint.h> // C99 variable types
#include "ADCSWTrigger.h"
#include "uart.h"
#include "PLL.h"
#include "TemperatureSensor.h"

uint32_t tempData;
uint32_t lightData;
uint32_t moistData;

int main(void){
//  PLL_Init(Bus80MHz);   // 80 MHz
//  UART_Init();              // initialize UART device
//  ADC0_Init();
//	Switch_Init_Testing();
//	PeltierTransistor_Init();
//  while(1){
//    tempData = ADC0_InSeq3();
//		PeltierOn(tempData);
//		UART_OutString("\n\rTemperature data =");
//    UART_OutUDec(tempData);
//		/*
//		lightData = ADC0_InSeq2();
//		moistData = ADC0_InSeq1();

//		
//		UART_OutString("\n\rLight data =");
//    UART_OutUDec(lightData);
//		
//		UART_OutString("\n\rMoisture data =");
//    UART_OutUDec(moistData);
//		*/
//  }
}


