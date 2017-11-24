/*
 * Air.h
 * Header for the use of the air conditions sensor of the AVR XMEGA B1 platform
	Funciones para el uso del sensor de la calidad del aire implementado en la plataforma AVR XMEGA B1
 * Created: 25/10/2017 
	Version: 1.0
 *  Author: Alejandro Castro Martinez
 */ 


#ifndef AIR_H_
#define AIR_H_

//	****	****	****DEFINICIONES****	****	****//

typedef enum AIR_SUBSTANCE Air_Substance;
enum AIR_SUBSTANCE{
	NONE,
	ALCOHOL,
	CO2,
	SMOKE
	};

//	****	****	****FUNCIONES****	****	****//

//obtener el valor en voltaje del sensor de acuerdo al maximo valor de conversion
float getAirQuality(uint8_t ADC_Value);

//Obtener posible sustancia presente en el aire
Air_Substance getAirSubstance(float value);

#endif /* AIR_H_ */