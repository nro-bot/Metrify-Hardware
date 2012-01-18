/*
 * metroidFirmware.c
 *
 * Created: 1/16/2012 3:37:42 PM
 *  Author: mspatz
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <avr/sleep.h>

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)(~(1 << mask)))


#include "delays.h"
#include "nRF24L01_lib.h"



int main(void)
{
//Initialize pins
 init_24L01_pins();
	
    while(1)
    {
        //continually transmit
		config_tx_nRF24L01();
		data_array[0] = 0b01001000;//rf_tx_array[0];
		data_array[1] = 0b01000001;//rf_tx_array[1];
		data_array[2] = 0b01001001;//rf_tx_array[2];
		data_array[3] = 0b10100000;//rf_tx_array[3];
		tx_data_nRF24L01();
		config_rx_nRF24L01();
		delay_ms(500);	
    }
}