#include <avr/io.h>
#include "Timer.h"

uint8_t timerDisable (timerport port){
	switch(port){
		case timer_c:
			timerCPrescale = TCC0.CTRLA;
			TCC0.CTRLA = no_timer;
			return 1;
		case timer_e:
			timerCPrescale = TCE0.CTRLA;
			TCE0.CTRLA = no_timer;
			return 1;
		default:
			return 0;
	}
}
uint8_t timerEnable (timerport port){
	switch(port){
		case timer_c:
			TCC0.CTRLA = timerCPrescale;
			return 1;
		case timer_e:
			TCE0.CTRLA = timerEPrescale;
			return 1;
		default:
			return 0;
	}
}
uint8_t setTimerData (timerport port, uint16_t period, prescaler_sel prescale){
	switch(port){
		case timer_c:
			TCC0.CTRLA = prescale;
			timerCPrescale = prescale;
			TCC0.PER = period;
			return 1;
		case timer_e:
			TCE0.CTRLA = prescale;
			timerEPrescale = prescale;
			TCE0.PER = period;
			return 1;
		default:
			return 0;
	}
}
uint8_t timerDone (timerport timer){
	switch(timer){
		case timer_c:
			if(FLAG_C_READY){
				return 1;
			}
			else{
				return 0;
			}
		case timer_e:
			if(FLAG_E_READY){
				return 1;
			}
			else{
				return 0;
			}
		default:
		return 0;
	}
}
uint8_t timerCleanFlag (timerport timer){
	switch(timer){
		case timer_c:
			TCC0.INTFLAGS |= TIMER_FLAG;
			return 1;
		case timer_e:
			TCE0.INTFLAGS |= TIMER_FLAG;
			return 1;
		default:
		return 0;
	}
}
uint8_t setMillis (timerport port, float milliseconds){
	if(milliseconds < 0 && milliseconds > 33553.92){
		return 0;
	}
	float beforePrescale = (milliseconds * 2) * 1000.0;
	int menorResiduo, resultadoDivision = 0;
	prescaler_sel prescaler;
	menorResiduo = beforePrescale + 1;
	if(milliseconds >= 0 && milliseconds <= 32.7675){
		if((int)beforePrescale % 1 < menorResiduo && beforePrescale / 1 <= 65535){
			menorResiduo = (int)beforePrescale % 1;
			resultadoDivision = beforePrescale / 1;
			prescaler = prescaler_1;
		}
	}
	if(milliseconds >= 0 && milliseconds <= 65.535){
		if((int)beforePrescale % 2 < menorResiduo && beforePrescale / 2 <= 65535){
			menorResiduo = (int)beforePrescale % 2;
			resultadoDivision = beforePrescale / 2;
			prescaler = prescaler_2;
		}
	}
	if(milliseconds >= 0 && milliseconds <= 131.07){
		if((int)beforePrescale % 4 < menorResiduo && beforePrescale / 4 <= 65535){
			menorResiduo = (int)beforePrescale % 4;
			resultadoDivision = beforePrescale / 4;
			prescaler = prescaler_4;
		}
	}
	if(milliseconds >= 0 && milliseconds <= 262.14){
		if((int)beforePrescale % 8 < menorResiduo && beforePrescale / 8 <= 65535){
			menorResiduo = (int)beforePrescale % 8;
			resultadoDivision = beforePrescale / 8;
			prescaler = prescaler_8;
		}
	}
	if(milliseconds >= 0 && milliseconds <= 2097.12){
		if((int)beforePrescale % 64 < menorResiduo && beforePrescale / 64 <= 65535){
			menorResiduo = (int)beforePrescale % 64;
			resultadoDivision = beforePrescale / 64;
			prescaler = prescaler_64;
		}
	}
	if(milliseconds >= 0 && milliseconds <= 8388.48){
		if((int)beforePrescale % 256 < menorResiduo && beforePrescale / 256 <= 65535){
			menorResiduo = (int)beforePrescale % 256;
			resultadoDivision = beforePrescale / 256;
			prescaler = prescaler_256;
		}
	}
	if(milliseconds >= 0 && milliseconds <= 33553.92){
		if((int)beforePrescale % 1024 < menorResiduo && beforePrescale / 1024 <= 65535){
			menorResiduo = (int)beforePrescale % 1024;
			resultadoDivision = beforePrescale / 1024;
			prescaler = prescaler_1024;
		}
	}
	if(menorResiduo < beforePrescale){
		setTimerData(port, resultadoDivision, prescaler);	
	}
	else{
		return 0;
	}
}