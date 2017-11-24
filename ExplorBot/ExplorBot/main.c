
/*
 * ExplorBot
 *	Robot de exploracion de zonas de dificil acceso 
	Construido en base a la plataforma SumoBot. 
 * Created: 25/10/2017
 *	Version: 2.0
 * Autor : Alejandro Castro Martinez 
 */ 

/*
 =>	Explorbot.c (main.c)
		* Programa ejecutable de la plataforma Explorbot
*/

//	****	****	****LIBRERIAS****	****	****//
#include <avr/io.h>
#include "Serial.h"
#include "RTC.h"
#include "PWM.h"
#include "Temperature.h"
#include "Light.h"
#include "Air.h"
#include "ControlMain.h"
#include "ADC.h"
#include "Timer.h"

//====	====	====Programa principal====	====	====///
#define PWM PORTE
int main(void)
{
	//	****	****	****DEFINICION VARIABLES****	****	****//
		//FSM inicialization
	RTC_state config_state = IDLE_CONFIG;
	motor_action motorAction = IDLE_MOTOR;
	data_action dataAction = IDLE_START;
	system_action systemAction = SYS_CONFIG;
		
		//Variables para el control de presion de botones
	//Variable para el control del boton de inicio. 
	uint8_t startButton = 0;
	
		//Variables de paso de estados 
	uint8_t start = 0;
	
	//Variable para determinar cual es el sensor el cual sigue para la medicion
	data_action nextData = TEMPERATURE;
	
	//Variable que indica cuantos datos han sido guardados en el sistema
	uint16_t dataCounter = 0;
	
	//Variable para indicar que ya termino de poner los datos en el buffer de transmision
	uint8_t finishData = 0;
	/*
	//
	VALORES MOTOR IZQUIERDO
	TCE0.CCABUF = 4290; //Full Stop
	TCE0.CCBBUF = 3000; //Full Backwards
	TCE0.CCCBUF = 5000; //Full Forwards
	
	VALORES MOTOR DERECHO
	TCE0.CCABUF = 5150; //Full Stop
	TCE0.CCBBUF = 6000; //Full Backwards
	TCE0.CCCBUF = 4000; //Full Forwards
	*/
	while (1)
	{
		//Maquina de estados finitos para el estado del sistema. 
		switch(systemAction){
			/*
				Caso para la configuración del sistema 
				en primera instancia como lo son salidas y entradas de sensores
				y demás para la primera parte de la ejecucion del sistema. 
			*/
			case SYS_CONFIG:
				//Configuracion del Timer de espera de inicio.
				setTimerData(timer_c,125000,prescaler_4);
				timerEnable(timer_c);
				
				//LEDS Setup
				setLed(LED_0); setLed(LED_1); setLed(LED_2); setLed(LED_3);
				offLed(LED_0); offLed(LED_1); offLed(LED_2); offLed(LED_3);
				
				//Declaracion salida PIN0 y PIN1 del PORTA
				PORTA.DIRCLR = 0x01;
				PORTC.DIRCLR = 0x01;
				PORTB.DIRCLR = 0x0F;
				PORTA.DIRCLR = 0x80;
				//Configuracion de la salida PWM para los motores
 				PWM.DIRSET = 0x07;
 				PWM.OUTCLR = 0x07;
 				setWaveform_PWM(SINGLE_SLOPE);
 				setPrescaler_PWM(DIV1_PWM);
 				setPer_PWM(40000);
				
				//Cambio de estado: sistema y RTC
				systemAction = IDLE_RESPONSE;
				config_state = RTC_ENABLE_STATE;
				
				//Resetear la cantidad de datos tomados 
				dataCounter = 0;
			break;
			//Caso de espera para arrancar el recorrido. 
			case IDLE_RESPONSE:
				if(timerDone(timer_c)){
					timerCleanFlag(timer_c);
					toggleLed(LED_1);
					
					//Antirrebote del boton de inicio
					if((PORTA.IN & 0x01) != 0){
						if(startButton == 0){
							startButton = 1;	
						}
					}
					else{
						if(startButton == 1){
							start = 1;
						}
					}
				}
				if(start == 1){
					//Ya se cambio de estado por ende se pone esta variable en 0 para la proxima ejecucion. 
					start = 0;
					startButton = 0;
					//Habilitar motores para su funcionamiento
					enableChA();
					enableChB();
					//Parar los motores 
					setDutyCicle(RIGHTMOTOR, 5150);
					setDutyCicle(LEFTMOTOR, 4280);
					//Deshabilitar timer de espera
					timerDisable(timer_c);
					offLed(LED_1);
					//Verificar que el RTC se terminó de configurar
					if(config_state == IDLE_CONFIG){
						//Cambio de estado cuando ya se completo la configuracion del RTC
						systemAction = EN_ROUTE;
						//Reinciar el RTC
						RTC.CNT = 0x00;
					}
				}
			break;
			//Caso para cuando el recorrido empieza. 
			case EN_ROUTE:
				//Condicional para la terminacion del tiempo del recorrido
				if(RTC_overflowReady() == 1){
					//Cambio de estados relacionados para relacion correcta
					motorAction = STOP;
					dataAction = IDLE_ADC;
					systemAction = CONFIG_TRANSMIT;
					offLed(LED_0);
				}else{
					onLed(LED_0);
					//Condicional de encontrar algo (Activacion del sensor de proximidad)
					if((PORTC.IN & 0x01) != 0){
						motorAction = TURN_RIGHT;
					}
					else 
						motorAction = FORWARD;
				}
			break;
			//Estado para realizar la deshabilitacion de los canales PWM y activar canal de visualizacion
			case CONFIG_TRANSMIT:
			//Deshabilitar los canales de PWM 
				disableChA();
				disableChB();
				//Cambiar de estado a espera de transmision de datos
				systemAction = IDLE_TRANSMIT;
				//Habilitar timer para generar pulsos de informacion de espera.
				setTimerData(timer_c,125000,prescaler_4); 
				timerEnable(timer_c);
				offLed(LED_1);
			break;
			//Estado para espera de que la transmision se encuentra lista para empezar. 
			case IDLE_TRANSMIT:
					if(timerDone(timer_c)){
						timerCleanFlag(timer_c);
						toggleLed(LED_2);
						//Antirrebote del boton de inicio
						if((PORTA.IN & 0x01) != 0){
							if(startButton == 0){
								startButton = 1;
							}
						}
						else{
							if(startButton == 1){
								start = 1;
							}
						}
					}
					if(start == 1){
						start = 0;
						startButton = 0;
						offLed(LED_2);
						systemAction = TRANSMIT;
						timerDisable(timer_c);
						SerialInit(ASYNCHRONOUS,DISABLED,ONE_SB,CH_8BIT,0,12);
					}
			break;
			//Caso para transmitir los datos del sistema recogidos durante el recorrido. 
			case TRANSMIT:
				//Verificar que exista espacio para transmitir datos 
// 				if(txsize > BUFFER_MAX_SIZE - 20){
// 					SerialFlush();
// 					onLed(LED_0);
// 				}
// 				else{
// 					if(dataCounter > 0){
// 						onLed(LED_1);
// 						switch(dataRegister[dataCounter].dataType){
// 							case IDLE_START:
// 							case IDLE_TAKE:
// 							case IDLE_ADC:
// 							break;
// 							case TEMPERATURE:
// 								SerialDataTransmit("/Temperatura: ");
// 								SerialNumberTransmit(dataRegister[dataCounter].Temperature_Condition);
// 								SerialDataTransmit("->");
// 								SerialNumberTransmit(dataRegister[dataCounter].timeTaken);
// 								SerialFlush();
// 							break;
// 							case AIR:
// 								SerialDataTransmit("/Aire: ");
// 								switch(dataRegister[dataCounter].airSubstance){
// 									case ALCOHOL:
// 									SerialDataTransmit("Alcohol");
// 									break;
// 									case CO2:
// 									SerialDataTransmit("CO2");
// 									break;
// 									case NONE:
// 									SerialDataTransmit("NONE");
// 									break;
// 									case SMOKE:
// 									SerialDataTransmit("Humo");
// 									break;	
// 								}
// 								SerialDataTransmit("->");
// 								SerialNumberTransmit(dataRegister[dataCounter].timeTaken);
// 								SerialFlush();
// 							break;
// 							case LIGHT:
// 								SerialDataTransmit("/Aire: ");
// 								switch(dataRegister[dataCounter].light_condition){
// 									case HIGH:
// 									SerialDataTransmit("Alto");
// 									break;
// 									case MEDIUM_LOW:
// 									SerialDataTransmit("Media baja");
// 									break;
// 									case LOW_MEDIUM:
// 									SerialDataTransmit("Baja media");
// 									break;
// 									case LOW:
// 									SerialDataTransmit("Baja");
// 									break;
// 								}
// 								SerialDataTransmit("->");
// 								SerialNumberTransmit(dataRegister[dataCounter].timeTaken);
// 								SerialFlush();
// 							break;
// 						}
// 						dataCounter--;
// 					}
// 					else{
// 						while(txsize > 0){
// 							SerialFlush();
// 						}
// 					}
// 				}
if(dataCounter > 0)
SerialNumberTransmit(10);
				SerialFlush();
			break;
		}
		//Maquina de estados finitos para el manejo de los motores
		switch(motorAction){
			//Caso de espera de los motores
			case IDLE_MOTOR:
			break;
			//Caso para parar los motores 
			case STOP:
				setDutyCicle(RIGHTMOTOR, 0);
				setDutyCicle(LEFTMOTOR, 0);
				motorAction = IDLE_MOTOR;
			break;
			//Caso para avanzar los motores 
			case FORWARD:
				setDutyCicle(RIGHTMOTOR, 4000);
				setDutyCicle(LEFTMOTOR, 5000);
				motorAction = IDLE_MOTOR;
			break;
			//Caso para retroceder los motores
			//ERROR EN LA CARACTERIZACION DEL CICLO UTIL PARA RETROCEDER.
			case BACKWARDS:
				setDutyCicle(RIGHTMOTOR, 6000);
				setDutyCicle(LEFTMOTOR, 3000);
				motorAction = IDLE_MOTOR;
			break;
			//Caso para un giro a la derecha sobre su eje de los motores
			case TURN_RIGHT:
				setDutyCicle(RIGHTMOTOR, 6000);
				setDutyCicle(LEFTMOTOR, 5000);
				motorAction = IDLE_MOTOR;
			break;
			//Caso para un giro a la izquierda sobre su eje de los motores
			case TURN_LEFT:
				setDutyCicle(RIGHTMOTOR, 4000);
				setDutyCicle(LEFTMOTOR, 3000);
				motorAction = IDLE_MOTOR;
			break;
		}
		//Maquina de estados finitos para el manejo de los datos
		switch(dataAction){
			//Caso de espera para iniciar la toma de datos
			case IDLE_START:
				ADC_CalibrationValues_Load(&ADCB);	//Moves calibration values from memory to CALL/CALH.
				ADCB.CTRLB = 0x04;					//no limit current, unsigned, no freerun, 8 bit resolution
				ADCB.REFCTRL = 0x00;				//internal reference voltage of 1 volt
				ADCB.SAMPCTRL = 0x3F;				//Configurates the maximum sample time
				ADCB.CH0.CTRL=0x01 ;				//single ended, gain factor x1
				ADCB.CTRLA |=0x01;
				ADCB.CH0.MUXCTRL= 0x00; //Selects pin 0 of PORTB as the ADC input (temperature sensor)
				ADCB.CH0.CTRL|=0x80;
				dataAction = IDLE_TAKE;
			break;
			//Caso de espera para determinar cual es el siguiente dato a tomar. 
			case IDLE_TAKE:
				//Si el recorrido esta en accion significa que debe tomar datos de los sensores.
				if(systemAction == EN_ROUTE){
					switch(nextData){
						case TEMPERATURE:
							if((ADCB.CH0.INTFLAGS & 0x01) !=0){
								ADCB.CH0.INTFLAGS |= 0x01;
								dataRegister[dataCounter].dataType = TEMPERATURE;
								dataRegister[dataCounter].Temperature_Condition = getTemp(ADCB.CH0.RESL);
								dataCounter ++;
								ADCB.CH0.MUXCTRL= 0x71; //Selects pin 3 of PORTB as the ADC input (air sensor)
								nextData = AIR;
								ADCB.CH0.CTRL|=0x80;
							}
						break;
						case AIR:
							if((ADCB.CH0.INTFLAGS & 0x01) !=0){
								ADCB.CH0.INTFLAGS |= 0x01;
								dataRegister[dataCounter].airQuality = getAirQuality(ADCB.CH0.RESL);
								dataRegister[dataCounter].airSubstance = getAirSubstance(dataRegister[dataCounter].airQuality);
								dataCounter ++;
								nextData = LIGHT;
								ADCB.CH0.MUXCTRL= 0x10;			//Selects pin 2 of PORTB as the ADC input (light sensor)
								ADCB.CH0.CTRL|=0x80;
							}
						break;
						case LIGHT:
							if((ADCB.CH0.INTFLAGS & 0x01) !=0){
								ADCB.CH0.INTFLAGS |= 0x01;
								dataRegister[dataCounter].dataType = LIGHT;
								dataRegister[dataCounter].light_condition = LightStatus(ADCB.CH0.RESL);
								dataCounter ++;
								nextData = TEMPERATURE;
								ADCB.CH0.MUXCTRL= 0x00; //Selects pin 0 of PORTB as the ADC input (temperature sensor)
								ADCB.CH0.CTRL|=0x80;
							}
						break;
					}
					dataRegister[dataCounter].timeTaken = RTC.CNT;
				}
			break;
			//Caso para tomar el dato de temperatura
			case TEMPERATURE:
				
			break;
			//Caso para tomar el dato de calidad del aire
			case AIR:
				
			break;
			//Caso para tomar el dato de nivel de luz
			case LIGHT:
				
			break;
			//Caso para seleccionar siguiente dato a ser tomado.  
			case IDLE_ADC:
// 				switch(nextData){
// 					case IDLE_START:
// 					case IDLE_TAKE:
// 					case IDLE_ADC:
// 					break;
// 					case TEMPERATURE:
// 						nextData = AIR;
// 					break;
// 					case AIR:
// 						nextData = LIGHT;
// 					break;
// 					case LIGHT:
// 						nextData = TEMPERATURE;
// 					break;
// 				}
// 				dataAction = IDLE_TAKE;
			break;
		}
		//Maquina de estados finitos para el manejo del RTC
		switch(config_state)
		{
			case RTC_ENABLE_STATE: // Turn on the RTC
				RTC_setClock(UPL_1KHZ);
				enable_RTC();
				RTC_setPrescaler(RTC_DIV1);
				config_state = PER_CONFIG;
			break;
			case PER_CONFIG: // Period of 30 seconds
				if (!RTC_isBusy())
				{
					RTC_setPer(30720);
					config_state = CNT_CONFIG;
				}
			break;
			case CNT_CONFIG: // Change of the CNT register every 1 second
				if (!RTC_isBusy())
				{
					RTC_setCompare(RTC_getCompare() + 1024);
					config_state = IDLE_CONFIG;
					//Estado de los motores para parar. 
					motorAction = STOP;
				}
			break;
			case IDLE_CONFIG: //idle state
			break;
		}
	}
}
