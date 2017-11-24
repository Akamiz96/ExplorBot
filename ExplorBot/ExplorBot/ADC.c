/*
 * ADC.c
 *
 * Created: 8/11/2017 11:49:30 a. m.
 *  Author: kstro96
 */ 
#include <avr/io.h>
#include "ADC.h"

//Valores de configuracion del ADC
uint8_t ADC_config(){
	ADC_CalibrationValues_Load(&ADCB);	//Moves calibration values from memory to CALL/CALH.
	ADCB.CTRLB = 0x04;					//no limit current, unsigned, no freerun, 8 bit resolution
	ADCB.REFCTRL = 0x00;				//internal reference voltage of 1 volt
	ADCB.SAMPCTRL = 0x3F;				//Configurates the maximum sample time
	ADCB.CH0.CTRL=0x01 ;				//single ended, gain factor x1
	ADCB.CTRLA |= 0x01;
	return 1;
}

void ADC_enable(){
	ADCB.CTRLA |=0x01;					//Enables ADC
}
//Comenzar conversion ADC
void ADC_start(){
	ADCB.CH0.CTRL|=0x80;	//Starts an ADC conversion
}

//Lista la conversion del ADC
uint8_t ADC_conversionReady(){
	return ((ADCB.CH0.INTFLAGS & 0x01) !=0) ? 1 : 0;
}

//Bajar bandera del ADC
void ADC_clearFlag(){
	ADCB.CH0.INTFLAGS |= 0x01; //Clears the ADC flag 
}

//Obtener valor del ADC
void ADC_result(uint8_t *res, state st){
	
}