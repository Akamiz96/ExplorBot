/*
 * ControlMain.h
 *	This archive contains different structures and functions added to the main program 
	Este archivo contiene diferentes estructuras y funciones adicionadas al programa principal 
 * Created: 31/10/2017 
	Version: 1.1
 *  Author: Alejandro Castro Martinez
 */ 


#ifndef CONTROLMAIN_H_
#define CONTROLMAIN_H_

//	****	****	****DEFINICIONES****	****	****//
#include "Light.h"
#include "Air.h"
//Definicion del tiempo de recorrido (EN SEGUNDOS)
#define DEFAULT_TRACK_TIME 30

//Definicion de la mayor cantidad de datos tomados durante el recorrido
#define  MAX_DATA 500

//Definir puerto de los leds incluidos en el Xmega B1
#define LEDPORT PORTB

//Definir puerto de los touch incluidos en la tarjeta Xmega B1
#define BUTTONSPORT PORTE

//Definir puerto para el manejo de los motores (TCE0)
#define MOTORPORT TCE0

//Definir Canal para el control del motor derecho
#define RIGHTMOTOR CH_A

//Definir Canal para el control del motor izquierdo 
#define LEFTMOTOR CH_B

//Definir las constantes para los leds incluidos en el Xmega B1
typedef enum LEDS leds;
enum LEDS
{
	LED_0 = 0x10,
	LED_1 = 0x20,
	LED_2 = 0x40,
	LED_3 = 0x80
};

//Definir las constantes para los touch incluidos en el Xmega B1
typedef enum TOUCH touch;
enum TOUCH
{
	TOUCH_0 = 0x01,
	TOUCH_1 = 0x02,
	TOUCH_2 = 0x04,
	TOUCH_3 = 0x08
};

//Definicion de la configuracion PULL-UP para los pulsadores
#define T_PULLUP_CONF 0x18

//Definicion de los estados de la MEF
typedef enum STATE state;
enum STATE
{
	COUNT,
	NO_COUNT
};

//Definicion de los posibles movimientos del robot
typedef enum MOTOR_ACTION motor_action;
enum MOTOR_ACTION
{
	IDLE_MOTOR,
	FORWARD, 
	BACKWARDS,
	TURN_RIGHT,
	TURN_LEFT,
	STOP	
};

//Definicion de las posibles acciones del ADC del robot
typedef enum DATA_ACTION data_action;
enum DATA_ACTION
{
	IDLE_START,
	IDLE_TAKE,
	TEMPERATURE,
	AIR,
	LIGHT,
	IDLE_ADC
};

//Definicion de las posibles acciones del ADC del robot
typedef enum SYSTEM_ACTION system_action;
enum SYSTEM_ACTION
{
	SYS_CONFIG,
	IDLE_RESPONSE,
	EN_ROUTE,
	CONFIG_TRANSMIT,
	IDLE_TRANSMIT,
	TRANSMIT
};

//Definicion de la estructura de almacenamiento de los datos tomados durante el recorrido
typedef struct Data{
	data_action dataType;
	uint16_t timeTaken;
	Light_Condition light_condition;
	uint8_t Temperature_Condition;
	float airQuality;
	Air_Substance airSubstance;
}dataInfo;

//Variable para guardar datos tomados durante el recorrido
dataInfo dataRegister[MAX_DATA];

//	****	****	****FUNCIONES****	****	****//

//Set led specified as an output
void setLed (leds led);

//Turn on the specified led 
void onLed (leds led);

//Turn off the specified led
void offLed (leds led);

//Toggle the value of specified led
void toggleLed (leds led);

//Config the touch button specified
void config_touch (touch csTouch);

//Si un boton especificado es presionado
/*
	Retorno: 1=>Presionado 0=>No presionado
*/
uint8_t isPressed(touch csTouch);

#endif /* CONTROLMAIN_H_ */