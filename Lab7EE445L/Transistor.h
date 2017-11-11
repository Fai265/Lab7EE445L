// Transistor.h
// Runs on LM4F120/TM4C123
// Initializations for output ports.
// Cooper Carnahan and Faisal Mahmood
// November 10, 2017

// Hardware Configuration:
// Solenoid Transistor - PD0
// Motor Transistor    - PD1
// Peltier Transistor  - PD2
// Fan Transistor      - PD3

/***************************************************************
SolenoidTransistor_Init()
	Intitializes PD0 which controls the transistor to the solenoid

inputs:
	none
	
outputs:
	none
***************************************************************/
void SolenoidTransistor_Init(void);


/***************************************************************
MotorTransistor_Init()
	Intitializes PD1 which controls the transistor to the motor

inputs:
	none
	
outputs:
	none
***************************************************************/
void MotorTransistor_Init(void);


/***************************************************************
PeltierTransistor_Init()
	Intitializes PD2 which controls the transistor to the Peltier
	heating unit

inputs:
	none
	
outputs:
	none
***************************************************************/
void PeltierTransistor_Init(void);


/***************************************************************
FanTransistor_Init()
	Intitializes PD3 which controls the transistor to the fan

inputs:
	none
	
outputs:
	none
***************************************************************/
void FanTransistor_Init(void);


/***************************************************************
Transistor_Init()
	Initializes all the transistor controls to the system (PD0-PD3)

inputs:
	none
	
outputs:
	none
***************************************************************/
void Transistor_Init(void);
