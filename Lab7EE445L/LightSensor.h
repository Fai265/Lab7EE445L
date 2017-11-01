// LightSensor.h
// Runs on LM4F120/TM4C123
// Monitors and manages light level in box
// Cooper Carnahan and Faisal Mahmood
// November 1, 2017

uint32_t checkLight(void);

//takes a 0 to start turning
//takes a 1 to stop turning
void rotateMotor(uint8_t);