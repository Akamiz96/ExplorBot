/*
 * Light.c
 * Implementation of the functions declared in Light.h
	Implementacion de las funciones que se encuentran en Light.h
 * Created: 25/10/2017
	Version: 1.1
 *  Author: Alejandro Castro Martinez
 */
 
//	****	****	****LIBRERIAS****	****	****//
#include <avr/io.h>
#include "Light.h"

//	****	****	****FUNCIONES****	****	****//

//Return the light condition of the environment
Light_Condition LightStatus(uint8_t ADC_Value){
	if(ADC_Value >= 0 && ADC_Value < 64)
		return HIGH;
	if(ADC_Value >= 64 && ADC_Value < 128)
		return MEDIUM_LOW;
	if(ADC_Value >= 128 && ADC_Value < 192)
		return LOW_MEDIUM;
	if(ADC_Value >= 192 && ADC_Value <= 255)
		return LOW;
	return L_NOT_DEFINE;
}