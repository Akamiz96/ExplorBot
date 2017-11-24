/*
 * Air.c
 * Implementation of the functions declared in Air.h
	Implementacion de las funciones que se encuentran en Air.h
 * Created: 25/10/2017
 *  Author: Alejandro Castro Martinez
 */ 

//	****	****	****LIBRERIAS****	****	****//
#include <avr/io.h>
#include "Air.h"

//	****	****	****FUNCIONES****	****	****//
//obtener el valor en voltaje del sensor de acuerdo al maximo valor de conversion
float getAirQuality(uint8_t ADC_Value){
	float airQualityValue = ADC_Value / 255.0;
	return airQualityValue;
}

//Obtener posible sustancia presente en el aire
Air_Substance getAirSubstance(float value){
	if(value >= 0 && value <= 0.25)
		return NONE;
	if(value > 0.25 && value <= 0.4)
		return CO2;
	if(value > 0.4 && value <= 0.75)
		return ALCOHOL;
	if(value > 0.75)
		return SMOKE;
}