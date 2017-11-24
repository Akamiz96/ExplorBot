/*
 * RTC.c
 * Implementation of the functions declared in RTC.h
	Implementacion de las funciones que se encuentran en RTC.h
 * Created: 29/10/2017 
	version: 1.1
 *  Author: Alejandro Castro Martinez
 */ 

//	****	****	****LIBRERIAS****	****	****//
#include <avr/io.h>
#include "RTC.h"

//	****	****	****FUNCIONES****	****	****//

/*
	Seleccionar el reloj a utilizar para el RTC
		Retorno: 0=>Correcta asignacion 1=>Error
*/
uint8_t RTC_setClock(RTC_clk selection){
	CLK.RTCCTRL |= selection;
	return 0;
}

//Habilitar RTC
void enable_RTC(){
	CLK.RTCCTRL |= RTC_ENABLE;
}

/*
	Seleccionar el prescaler para el reloj del RTC
		Retorno: 0=>Correcta asignacion 1=>Error
*/
uint8_t RTC_setPrescaler(RTC_prescaler prescale)
{
	RTC.CTRL |= prescale;
	return 0;
}

/*
	Retorna si el RTC se encuentra ocupado 
		Retorno: 0=>Libre 1=>Ocupado
*/
uint8_t RTC_isBusy(){
	return ((RTC.STATUS == 0) ? 0 : 1);
}

/*
	Retorna si el compare se encuentra listo
		Retorno: 0=>No listo 1=>Listo
*/
uint8_t RTC_compareReady(){
	return ((RTC.INTFLAGS & RTC_COMPARE) != 0) ? 1 : 0;
}

/*
	Retorna si el overflow se encuentra listo
		Retorno: 0=>No listo 1=>Listo
*/
uint8_t RTC_overflowReady(){
	return ((RTC.INTFLAGS & RTC_OVERFLOW) != 0) ? 1 : 0;
}

/*
	Bajar la bandera del compare del RTC
*/
void RTC_compareFlagDown(){
	RTC_COMPARE_DOWN;
}

/*
	Bajar la bandera del overflow del RTC
*/
void RTC_overflowFlagDown(){
	RTC_OVERFLOW_DOWN;
}

/*
	Periodo del RTC 
	Retorno: 0=> Error 1=>Correcta Asignacion
*/
uint8_t RTC_setPer (uint16_t period){
	if(period <= 65535 && period >= 0){
		RTC.PER = period;
		return 1;
	}
	return 0;
}

//Obtener el valor que tiene el conteo del RTC
uint16_t RTC_getCnt(){
	return RTC.CNT;
}

//Poner el valor de comparacion
void RTC_setCompare(uint16_t compareValue){
	RTC.COMP = compareValue;
}

//Obtener valor de comparacion
uint16_t RTC_getCompare(){
	return RTC.COMP;
}