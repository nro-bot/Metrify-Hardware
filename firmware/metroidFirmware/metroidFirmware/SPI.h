/*
 * IncFile1.h
 *
 * Created: 1/16/2012 4:45:30 PM
 *  Author: mspatz
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_





#endif /* INCFILE1_H_ */


void SPI_MasterInit(void)
{
/* Set MOSI and SCK output, all others input */
DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
/* Enable SPI, Master, set clock rate fck/16, sed data order to MSB*/
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<DORD);

}
void SPI_MasterTransmit(char cData)
{
/* Start transmission */
SPDR = cData;
/* Wait for transmission complete */
while(!(SPSR & (1<<SPIF)))
;
}
void SPI_SetMode(char mode){
SPCR &= ~(0b11) << CPHA;
SPCR |= mode << CPHA;
}

