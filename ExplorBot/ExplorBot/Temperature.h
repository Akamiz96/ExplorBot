/*
 * Temperature.h
 *	Header for the use of the temperature sensor of the AVR XMEGA B1 platform
	Funciones para el uso del sensor de temperatura de la plataforma AVR XMEGA B1
 * Created: 25/10/2017
	Version: 1.1
 *  Author: Alejandro Castro Martinez
 */ 


#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

//	****	****	****DEFINICIONES****	****	****//

//Define the temperature sensor port
#define Temp_Sensor_Port PORTB

//Define the temperature sensor mask
#define Temp_Sensor_Mask 0x01

//	****	****	****FUNCIONES****	****	****//

//Get the value of the temperature at the position specified
uint8_t getTemp(uint8_t position);


#endif /* TEMPERATURE_H_ */