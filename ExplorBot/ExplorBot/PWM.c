/*
 * PWM.c
 * Implementation of the functions declared in PWM.h
  Implementacion de las funciones que se encuentran en PWM.h
 * Created: 29/10/2017 
 *	version: 1.1
 *  Author: Alejandro Castro Martinez
 */

//	****	****	****LIBRERIAS****	****	****//
#include <avr/io.h>
#include "PWM.h"

//	****	****	****FUNCIONES****	****	****//

//Prescalizacion del PWM
uint8_t setPrescaler_PWM (prescaler_PWM prescale){
	TCE0.CTRLA |= prescale;
	return 1;
}

/*
	*Periodo del Timer 
	=> Retorno: 1->Correcta asignacion
				0->Error en la asignacion 
*/
/*
* Periodo = FrecuenciaCPU / preescalizacion / frecuenciaPWM 
	=> FrecuenciaPWM = frecuencia deseada 
*/
uint8_t setPer_PWM (uint16_t period){
	if(period <= 65535 && period >= 0){
		TCE0.PER = period;
		return 1;
	}
	return 0;
}

//Forma de la onda generada
uint8_t setWaveform_PWM (waveform wave){
	TCE0.CTRLB |= wave;
	return 1;
}

//Set the duty cicle
uint8_t setDutyCicle(pwm_ch channel, uint16_t duty_cicle){
	switch(channel){
		case CH_A:
			setDutyCicle_CHA(duty_cicle);
		break;
		case CH_B:
			setDutyCicle_CHB(duty_cicle);
		break;
		case CH_C:
			setDutyCicle_CHC(duty_cicle);
		break;
		case CH_D:
			setDutyCicle_CHD(duty_cicle);
		break;
		default:
			return 0;
		break;
	}
	return 0;
}
/*
	*Ciclo util del canal A 
	=> Retorno: 1->Correcta asignacion
				0->Error en la asignacion 
*/
/*
	CCxBUF = Periodo * cicloUtil / 100
*/
uint8_t setDutyCicle_CHA (uint16_t duty_cicle){
	if(duty_cicle <= 65535 && duty_cicle >= 0){
		TCE0.CCABUF = duty_cicle;
		return 1;
	}
	return 0;
}
/*
	*Ciclo util del canal B 
	=> Retorno: 1->Correcta asignacion
				0->Error en la asignacion 
*/
/*
	CCxBUF = Periodo * cicloUtil / 100
*/
uint8_t setDutyCicle_CHB (uint16_t duty_cicle){
	if(duty_cicle <= 65535 && duty_cicle >= 0){
		TCE0.CCBBUF = duty_cicle;
		return 1;
	}
	return 0;
}
/*
	*Ciclo util del canal C 
	=> Retorno: 1->Correcta asignacion
				0->Error en la asignacion 
*/
/*
	CCxBUF = Periodo * cicloUtil / 100
*/
uint8_t setDutyCicle_CHC (uint16_t duty_cicle){
	if(duty_cicle <= 65535 && duty_cicle >= 0){
		TCE0.CCCBUF = duty_cicle;
		return 1;
	}
	return 0;
}
/*
	*Ciclo util del canal D 
	=> Retorno: 1->Correcta asignacion
				0->Error en la asignacion 
*/
/*
	CCxBUF = Periodo * cicloUtil / 100
*/
uint8_t setDutyCicle_CHD (uint16_t duty_cicle){
	if(duty_cicle <= 65535 && duty_cicle >= 0){
		TCE0.CCDBUF = duty_cicle;
		return 1;
	}
	return 0;
}

//Enable the channel
void enableCh(pwm_ch channel){
	switch(channel){
		case CH_A:
		enableChA();
		break;
		case CH_B:
		enableChB();
		break;
		case CH_C:
		enableChC();
		break;
		case CH_D:
		enableChD();
		break;
	}
}
//Habilitar el canal A
void enableChA(){
	TCE0.CTRLB |= CH_A;
}

//Habilitar el canal B
void enableChB(){
	TCE0.CTRLB |= CH_B;
}

//Habilitar el canal C
void enableChC(){
	TCE0.CTRLB |= CH_C;
}

//Habilitar el canal D
void enableChD(){
	TCE0.CTRLB |= CH_D;
}

//Disable the channel
void disableCh(pwm_ch channel){
	switch(channel){
		case CH_A:
		disableChA();
		break;
		case CH_B:
		disableChB();
		break;
		case CH_C:
		disableChC();
		break;
		case CH_D:
		disableChD();
		break;
	}
}

//Deshabilitar el canal A
void disableChA(){
	TCE0.CTRLB &= ~(CH_A);
}

//Deshabilitar el canal B
void disableChB(){
	TCE0.CTRLB &= ~(CH_B);
}

//Deshabilitar el canal C
void disableChC(){
	TCE0.CTRLB &= ~(CH_C);
}

//Deshabilitar el canal D
void disableChD(){
	TCE0.CTRLB &= ~(CH_D);
}