#ifndef MY_SERIAL_H
#define MY_SERIAL_H

#include <stdio.h>
// THIS LIBRARY ONLY WORKS WITH THE PORTC USART

/*			Definitions			*/
#define DATA_RECEIVED		(USARTC0.STATUS & 0x80)		//Rx Notification Flag
#define TRANSMIT_READY		(USARTC0.STATUS & 0x20)		//Tx Ready Flag
#define RECEIVER_ENABLE		0x10						//Rx Enable bit
#define TRANSMITTER_ENABLE	0x08						//Tx Enable bit
#define SHIFT_FACTOR		4							//Shift bits factor for adjust Baud Registers
#define BUFFER_MAX_SIZE		256							//Maximun number of data stored in the buffer.
#define USARTPORT PORTC

typedef enum CMODE cmode;
enum CMODE
{
	ASYNCHRONOUS = 0x00,	//Asynchronous USART
	SYNCRHONOUS	 = 0x40,	//Synchronous USART
	IRCOM_MODE	 = 0x80,	//IRCOM
	MSPI		 = 0xC0		//Master SPI
};

typedef enum PMODE pmode;
enum PMODE
{
	DISABLED = 0x00,	//No parity Bit
	EVEN	 = 0x20,	//Enable, Even Parity
	ODD		 = 0x30		//Enable, Odd Parity
};

typedef enum SBMODE sbmode;
enum SBMODE
{
	ONE_SB = 0x00,	// 1 Stop Bit
	TWO_SB = 0x08  // 2 Stop Bits
};
typedef enum CHSIZE chsize;
enum CHSIZE
{
	CH_5BIT = 0x00,		//5 bits of Data
	CH_6BIT = 0x01,		//6 bits of Data
	CH_7BIT = 0x02,		//7 bits of Data
	CH_8BIT = 0x03		//8 bits of Data
	//CH_9BIT = 0x07		//9 bits of Data aren't implemented
};

/*			Variables			 */

static char txBuff [BUFFER_MAX_SIZE];		//Transmission Buffer
static uint8_t txhead = 0;					//Head of data on Tx Buffer
static uint8_t txsize = 0;					//Amount of data on Tx Buffer

static char rxBuff [BUFFER_MAX_SIZE];		//Reception Buffer
static uint8_t rxhead = 0;					//Head of data on Tx Buffer
static uint8_t rxsize = 0;					//Amount of data on Rx Buffer

/*			METHODS				*/

//Init the USART, in MODE, number of parity bits, stop bits, data bits and the baud rate (BSEL and BSCALE)
uint8_t SerialInit (cmode usartMode, pmode parityBits, sbmode stopBits, chsize dataBits, int bscaleValue, uint16_t bselValue);
// Check if a the Rx Buffer has a value and returns the number of data available
uint8_t SerialDataAvailable();
// Transmits a single value of data (the data is stored in Tx buffer)
uint8_t SerialSimpleDataTransmit(uint8_t data);
// Transmits a single value of data a number (the data is stored in Tx buffer)
uint8_t SerialNumberTransmit(uint16_t number);
// Transmits a string characters of data (the data is stored in Tx buffer)
uint8_t SerialDataTransmit(char *stringData);
// returns the value of the first data stored in the Rx buffer (the data also is deleted from the Rx buffer)
uint8_t SerialDataRead();
//If a data is received by the USART is stored in the Rx Buffer. and if  the channel is free, transmits the next value of the Rx buffer.
void SerialFlush();

#endif