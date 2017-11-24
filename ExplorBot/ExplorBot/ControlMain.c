/*
 * ControlMain.c
 * Implementation of the functions declared in ControlMain.h
 Implementacion de las funciones que se encuentran en ControlMain.h
 * Created: 31/10/2017
	Version: 1.0
 *  Author: Alejandro Castro Martinez
 */ 

//	****	****	****LIBRERIAS****	****	****//
#include <avr/io.h>
#include "ControlMain.h"

//	****	****	****FUNCIONES****	****	****//

//Set led specified as an output
void setLed (leds led){
	LEDPORT.DIRSET = led;
}

//Turn on the specified led
void onLed (leds led){
	LEDPORT.OUTCLR = led;
}

//Turn off the specified led
void offLed (leds led){
	LEDPORT.OUTSET = led;
}

//Toggle the value of specified led
void toggleLed (leds led){
	LEDPORT.OUTTGL = led;
}

//Config the touch button specified
void config_touch (touch csTouch){
	BUTTONSPORT.DIRCLR = csTouch;
	switch(csTouch){
		case TOUCH_0:
			BUTTONSPORT.PIN0CTRL |= T_PULLUP_CONF;
		break;
		case TOUCH_1:
			BUTTONSPORT.PIN1CTRL |= T_PULLUP_CONF;
		break;
		case TOUCH_2:
			BUTTONSPORT.PIN2CTRL |= T_PULLUP_CONF;
		break;
		case TOUCH_3:
			BUTTONSPORT.PIN3CTRL |= T_PULLUP_CONF;
		break;
	}
}

//Si un boton especificado es presionado
/*
	Retorno: 1=>Presionado 0=>No presionado
*/
uint8_t isPressed(touch csTouch){
	return ((BUTTONSPORT.IN & csTouch) == 0) ? 1 : 0;
}