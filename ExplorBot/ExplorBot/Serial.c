#include <avr/io.h>
#include "Serial.h"
/*			METHODS				*/

//Init the USART, in MODE, number of parity bits, stop bits, data bits and the baud rate (BSEL and BSCALE)
/*
	Return => 
		0 -> All values were set correct
		1 -> The value of the bscale was incorrect
*/
uint8_t SerialInit (cmode usartMode, pmode parityBits, sbmode stopBits, chsize dataBits, int bscaleValue, uint16_t bselValue){
	USARTPORT.DIRSET = 0x08;		//Pin 3 (TXD0) as output
	USARTPORT.DIRCLR = 0x04;		//Pin 2 (RXD0) as input
	USARTC0.CTRLC = usartMode | parityBits | stopBits | dataBits;
	USARTC0.BAUDCTRLA = bselValue;
	bselValue = bselValue >> (2 * SHIFT_FACTOR);
	USARTC0.BAUDCTRLB = bselValue;
	if(bscaleValue >= -7 && bscaleValue <= 7){
		bscaleValue = bscaleValue << SHIFT_FACTOR;
		USARTC0.BAUDCTRLB |= bscaleValue;
		USARTC0.CTRLB |= 0x10;			//Enables USART reception
		USARTC0.CTRLB |= 0x08;			//Enables USART transmission
		return 0;
	}
	return 1;
}
// Check if a the Rx Buffer has a value and returns the number of data available
uint8_t SerialDataAvailable(){
	return rxsize;
}
// Transmit a single value of data (the data is stored in Tx buffer)
/*
	Retorno: 0 => se guardo el dato exitosamente
			 1 => no se guardo el dato
*/
uint8_t SerialSimpleDataTransmit(uint8_t data){
	if(txsize < BUFFER_MAX_SIZE){
		txBuff[(txhead + txsize) % BUFFER_MAX_SIZE] = data;
		txsize++;
		return 0;
	}
	return 1;
}
// Transmits a single value of data a number (the data is stored in Tx buffer)
uint8_t SerialNumberTransmit(uint16_t number){
	char stringData[10];
	if(sprintf(stringData, "%u", number) > 0)
		if(SerialDataTransmit(stringData) == 0)
			return 0;
	return 1;
}
// Transmit a string characters of data (the data is stored in Tx buffer)
/*
	Retorno 0 => Se completo la transmision 
			1 => NO se completo la transmision
*/
uint8_t SerialDataTransmit(char *stringData){
	while(*stringData != '\0'){
		if(SerialSimpleDataTransmit(*stringData) != 0)
			return 1;
		stringData++;
	}
	return 0;
}
// returns the value of the first data stored in the Rx buffer (the data also is deleted from the Rx buffer)
uint8_t SerialDataRead(){
	uint8_t data = 0x00;
	if(SerialDataAvailable() > 0){
		data = rxBuff[rxhead];
		rxhead++;
		if(rxhead == BUFFER_MAX_SIZE)
			rxhead = 0;
		rxsize--;
	}
	return data;
}
//If a data is received by the USART is stored in the Rx Buffer. and if  the channel is free, transmits the next value of the Tx buffer.
void SerialFlush(){
	//Transmision Libre
	if((USARTC0.STATUS & 0x20) != 0 && txsize > 0){
		USARTC0.DATA = txBuff[txhead];
		txhead++;
		if(txhead == BUFFER_MAX_SIZE)
			txhead = 0;
		txsize--;
	}
	
	//Recepcion nueva
	if((USARTC0.STATUS & 0x80) != 0){
		if(rxsize < BUFFER_MAX_SIZE){
			rxBuff[(rxhead + rxsize) % BUFFER_MAX_SIZE] = USARTC0.DATA;
			rxsize++;
		}
	}
}
