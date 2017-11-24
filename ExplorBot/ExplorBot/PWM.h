/*
 * PWM.h
 * Header for the use of the PWM of the AVR XMEGA B1 platform
	Funciones para el uso del PWM de la plataforma AVR XMEGA B1
 * Created: 29/10/2017 
	Version: 1.1
 *  Author: Alejandro Castro Martinez 
 */ 
/*
	====> El PWM esta configurado para el timer tipo 0 TCE0
	*Puerto E
		-> CH_A = PE0
		-> CH_B = PE1
		-> CH_C = PE2
		-> CH_D = PE3
*/

#ifndef PWM_H_
#define PWM_H_

//	****	****	****DEFINICIONES****	****	****//

//Configuracion de la forma de onda utilizada para el PWM
typedef enum WAVEFORM waveform;
enum WAVEFORM
{
	NORMAL = 0x00,	
	FREQUENCY = 0x01,
	SINGLE_SLOPE = 0x03,
	DUAL_SLOPE_TOP = 0x05,
	DUAL_SLOPE_BOTH = 0X06,
	DUAL_SLOPE_BOTTOM = 0X07
};

//Configuracion del prescaler para el PWM 
typedef enum PRESCALER_PWM prescaler_PWM;
enum PRESCALER_PWM
{
	PWM_DISABLED = 0x00,
	DIV1_PWM = 0x01,
	DIV2_PWM = 0x02,
	DIV4_PWM = 0x03,
	DIV8_PWM = 0X04,
	DIV64_PWM = 0X05,
	DIV256_PWM = 0X06,
	DIV1024_PWM = 0X07
};

//Configuracion de los canales de salida del PWM
typedef enum CH_PWM pwm_ch;
enum CH_PWM
{
	CH_A = 0X10,
	CH_B = 0X20,
	CH_C = 0X40,
	CH_D = 0X80
};

//	****	****	****FUNCIONES****	****	****//

//Prescalizacion del PWM
uint8_t setPrescaler_PWM (prescaler_PWM prescale);

//Periodo del Timer 
/*
* Periodo = FrecuenciaCPU / preescalizacion / frecuenciaPWM 
	=> FrecuenciaPWM = frecuencia deseada 
	Retorno: 1=> Correcta asignacion 0=>Error
*/
uint8_t setPer_PWM (uint16_t period);

//Forma de la onda generada
uint8_t setWaveform_PWM (waveform wave);

//Set the duty cicle
uint8_t setDutyCicle(pwm_ch channel, uint16_t duty_cicle);

//Ciclo util del canal A
/*
	CCxBUF = Periodo * cicloUtil / 100
*/
uint8_t setDutyCicle_CHA (uint16_t duty_cicle);

//Ciclo util del canal B
/*
	CCxBUF = Periodo * cicloUtil / 100
*/
uint8_t setDutyCicle_CHB (uint16_t duty_cicle);

//Ciclo util del canal C
/*
	CCxBUF = Periodo * cicloUtil / 100
*/
uint8_t setDutyCicle_CHC (uint16_t duty_cicle);

//Ciclo util del canal D
/*
	CCxBUF = Periodo * cicloUtil / 100
*/
uint8_t setDutyCicle_CHD (uint16_t duty_cicle);

//Enable the channel 
void enableCh(pwm_ch channel);

//Habilitar el canal A
void enableChA();

//Habilitar el canal B
void enableChB();

//Habilitar el canal C
void enableChC();

//Habilitar el canal D
void enableChD();

//Disable the channel
void disableCh(pwm_ch channel);

//Deshabilitar el canal A
void disableChA();

//Deshabilitar el canal B
void disableChB();

//Deshabilitar el canal C
void disableChC();

//Deshabilitar el canal D
void disableChD();

#endif /* PWM_H_ */