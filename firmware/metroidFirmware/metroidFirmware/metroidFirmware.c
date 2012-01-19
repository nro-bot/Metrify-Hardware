/*
 * metroidFirmware.c
 *
 * Created: 1/16/2012 3:37:42 PM
 *  Author: mspatz
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h> 
//#include <avr/interrupt.h>
//#include <avr/sleep.h>

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)(~(1 << mask)))


#include "delays.h"
#include "nRF24L01_lib.h"

//hackey variables
char buttonstate = 0;
char prevButtonState = 0;
char message[4];



int main(void)
{
//Initialize pins
 init_24L01_pins();
 //pullups on port C
 //DDRC = 0xFF;
 PORTC = 0xFF;
 #define ButtonPin 0
 
	char i = 0;
    while(1)
    {
		prevButtonState = buttonstate;
		buttonstate = (PINC & 0b1<<ButtonPin);
		
		if (!buttonstate && prevButtonState){
			i++;
			if (i >= 100) i = 0;
		}
		

		itoa(i,message,10);
		message[2] = '\n';
		message[3] = '\r';
		
        //continually transmit
		config_tx_nRF24L01();
		data_array[0] = message[0];//rf_tx_array[0];
		data_array[1] = message[1];//rf_tx_array[1];
		data_array[2] = message[2];//rf_tx_array[2];
		data_array[3] = message[3];//rf_tx_array[3];
		tx_data_nRF24L01();
		delay_ms(50);	
    }
}