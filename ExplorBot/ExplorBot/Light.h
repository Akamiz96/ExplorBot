/*
 * Light.h
 *	Header for the use of the light sensor of the AVR XMEGA B1 platform
	Funciones para el uso del sensor de luz de la plataforma AVR XMEGA B1
 * Created: 25/10/2017
	Version: 1.1
 *  Author: Alejandro Castro Martinez
 */ 


#ifndef LIGHT_H_
#define LIGHT_H_

//	****	****	****DEFINICIONES****	****	****//

//Define the light sensor port
#define Light_Sensor_Port PORTB

//Define the mask for the light sensor 
#define Light_Sensor_Mask 0x04

//Define the condition of light in the environment 
typedef enum LIGHT_CONDITION Light_Condition;
enum LIGHT_CONDITION {HIGH, MEDIUM_LOW, LOW_MEDIUM, LOW, L_NOT_DEFINE};

//	****	****	****FUNCIONES****	****	****//

//Return the light condition of the environment
Light_Condition LightStatus(uint8_t ADC_Value);

#endif /* LIGHT_H_ */