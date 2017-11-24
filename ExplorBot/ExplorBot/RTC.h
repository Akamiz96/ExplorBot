/*
 * RTC.h
 *	Header for the use of the Real time counter (RTC) of the AVR XMEGA B1 platform
	Funciones para el uso del contador de tiempo real (RTC) de la plataforma AVR XMEGA B1
 * Created: 29/10/2017 
	Version 1.1
 *  Author: Alejandro Castro Martinez
 */ 


#ifndef RTC_H_
#define RTC_H_

//	****	****	****DEFINICIONES****	****	****//

//Definicion de la mascara para havbilitar el RTC
#define RTC_ENABLE 0x01

//Definicion de la mascara para el RTC ocupado
#define RTC_BUSY 0x01

//Definicion de la mascara para el compare 
#define RTC_COMPARE 0x02

//Definicion de la mascara para el overflow
#define RTC_OVERFLOW 0x01

//Definicion para bajar bandera de compare 
#define RTC_COMPARE_DOWN RTC.INTFLAGS |= RTC_COMPARE

//Definicion para bajar bandera de overflow
#define RTC_OVERFLOW_DOWN RTC.INTFLAGS |= RTC_OVERFLOW

//Definicion de las fuentes de reloj para el RTC
typedef enum RTC_CLK RTC_clk;
enum RTC_CLK
{
	UPL_1KHZ = 0x00, //1kHz del ULP interno 
	TOSC = 0x02, //1.024kHz del 32.768kHz oscilador interno en TOSC
	RCOSC = 0x04, //1.024kHz del 32.768 oscilador interno 
	TOSC32 = 0x0A, // 32.768kHz oscilador interno en TOSC
	RCOSC32 = 0x0C, // 32.768kHz oscilador interno 
	EXTCLK = 0x0F //Oscilador externo de TOSC1
};

//Configuracion del prescaler para el PWM 
typedef enum RTC_PRESCALER RTC_prescaler;
enum RTC_PRESCALER
{
	RTC_DISABLED = 0x00,
	RTC_DIV1 = 0x01,
	RTC_DIV2 = 0x02,
	RTC_DIV8 = 0X03,
	RTC_DIV16 = 0X04,
	RTC_DIV64 = 0X05,
	RTC_DIV256 = 0X06,
	RTC_DIV1024 = 0X07
};

//Definicion de la maquina de estados para el funcionamiento del RTC
typedef enum RTC_STATE RTC_state;
enum RTC_STATE
{
	RTC_ENABLE_STATE,
	PER_CONFIG,
	CNT_CONFIG,
	IDLE_CONFIG
};

//	****	****	****FUNCIONES****	****	****//
/*
	Seleccionar el reloj a utilizar para el RTC
		Retorno: 0=>Correcta asignacion 1=>Error
*/
uint8_t RTC_setClock(RTC_clk selection);

//Habilitar RTC
void enable_RTC();

/*
	Seleccionar el prescaler para el reloj del RTC
		Retorno: 0=>Correcta asignacion 1=>Error
*/
uint8_t RTC_setPrescaler(RTC_prescaler prescale);

/*
	Retorna si el RTC se encuentra ocupado 
		Retorno: 0=>Libre 1=>Ocupado
*/
uint8_t RTC_isBusy();

/*
	Retorna si el compare se encuentra listo
		Retorno: 0=>No listo 1=>Listo
*/
uint8_t RTC_compareReady();

/*
	Retorna si el overflow se encuentra listo
		Retorno: 0=>No listo 1=>Listo
*/
uint8_t RTC_overflowReady();

/*
	Bajar la bandera del compare del RTC
*/
void RTC_compareFlagDown();

/*
	Bajar la bandera del overflow del RTC
*/
void RTC_overflowFlagDown();

/*
	Periodo del RTC 
	Retorno: 0=> Error 1=>Correcta Asignacion
*/
uint8_t RTC_setPer (uint16_t period);

//Obtener el valor que tiene el conteo del RTC
uint16_t RTC_getCnt();

//Poner el valor de comparacion
void RTC_setCompare(uint16_t compareValue);

//Obtener valor de comparacion 
uint16_t RTC_getCompare();

#endif /* RTC_H_ */