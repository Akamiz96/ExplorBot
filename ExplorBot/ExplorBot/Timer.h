/*
	IF DEF
*/
#ifndef TIMER_H
#define  TIMER_H

/*
	INCLUDES
*/

/*
	DEFINICIONES
*/
#define TIMER_FLAG 0x01 //Mascara para revisar el bit OVFIF
#define FLAG_C_READY ((TCC0.INTFLAGS & TIMER_FLAG) != 0) //Condicion para saber si el TIMER C cumplio el tiempo
#define FLAG_E_READY ((TCE0.INTFLAGS & TIMER_FLAG) != 0) //Condicion para saber si el TIMER E cumplio el tiempo

/*
	Variables
*/
typedef enum TIMER timerport;
enum TIMER {timer_c, timer_e};
	
typedef enum PRESCALER prescaler_sel;
enum PRESCALER{
	no_timer = 0x00, //No Timer
	prescaler_1 = 0x01, //CLK
	prescaler_2 = 0x02, //CLK/2
	prescaler_4 = 0x03, //CLK/4
	prescaler_8 = 0x04, //CLK/8
	prescaler_64 = 0x05, //CLK/64
	prescaler_256 = 0x06, //CLK/256
	prescaler_1024 = 0x07 //CLK/1024
	};
	
	prescaler_sel timerCPrescale;
	prescaler_sel timerEPrescale;
	
/*
	Metodos/Funciones
*/

	uint8_t timerDisable (timerport port); 
	uint8_t timerEnable (timerport port);
	uint8_t setTimerData (timerport port, uint16_t period, prescaler_sel prescaler);
	uint8_t timerDone (timerport timer);
	uint8_t timerCleanFlag (timerport timer);
	/* Challenge */
	uint8_t setMillis (timerport port, float milliseconds);
	
/*
	end if
*/
#endif
