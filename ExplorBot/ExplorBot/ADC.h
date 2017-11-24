/*
 * ADC.h
 *
 * Created: 8/11/2017 
 *  Author: Alejandro Castro 
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "ControlMain.h"

//Valores de configuracion del ADC
uint8_t ADC_config();

//Habilitar ADC
void ADC_enable();

//Comenzar conversion ADC
void ADC_start();

//Lista la conversion del ADC
uint8_t ADC_conversionReady();

//Bajar bandera del ADC
void ADC_clearFlag();

//Obtener valor del ADC
void ADC_result(uint8_t *res, state st);

#endif /* ADC_H_ */