#include <avr/io.h>
void delay_us(unsigned int x)//(uint8_t x)
{
	TIFR2 = 0x01; //Clear any interrupt flags on Timer2
	
    TCNT2 = 256 - x; //256 - 125 = 131 : Preload timer 2 for x clicks. Should be 1us per click
	//Init Timer0
    //TCCR0B = (1<<CS00); //Set Prescaler to No Prescaling (assume we are running at internal 1MHz). CS00=1 
	TCCR2B = (1<<CS20); //Set Prescaler to 1. CS20=1

	while( (TIFR2 & (1<<TOV2)) == 0);
}

//General short delays
void delay_ms(uint16_t x)
{
	
	for (; x > 0 ; x--)
	{
		delay_us(250);
		delay_us(250);
		delay_us(250);
		delay_us(250);
	}
}

