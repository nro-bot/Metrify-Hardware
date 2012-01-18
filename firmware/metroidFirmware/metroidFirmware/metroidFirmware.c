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



#include nRF24L01_lib.c
#include delays.c

int main(void)
{
	//setup radio for transmission
	
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}