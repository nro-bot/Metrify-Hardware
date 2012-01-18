/*
    1-14-09
    Copyright Spark Fun Electronics© 2009
    
    NOTE: If you enable the receiver (set CE high), the receiver will start monitoring the air. With the CRC
    set to 8 bit (default) the receiver will find all sorts of junk in the air with a correct CRC tag. Our recommendation
    is to either transmit a resonably constant stream of data, use 16-bit CRC, and/or use additional header/end bytes in
    the payload to verify incoming packets.
    
    config_setup word bits found on pages 13-15

	24:63 40-bit address #1
	
	23: 1 Payloads have a 5-byte (40-bit) address
    22: 0
    21: 1
    20: 0
    19: 0
    18: 0
    17: 1 16-Bit CRC
    16: 1 CRC Enabled

    15: 0 One channel receive
    14: 1 ShockBurst Mode
    13: 1 1Mbps Transmission Rate
    12: 0 16MHz Crystal
    11: 1 16MHz Crystal
    10: 1 16MHz Crystal
    9: 1 RF Output Power (-5dBm)
    8: 0 RF Output Power

    7: 0 Channel select (channel 2)
    6: 0
    5: 0
    4: 0
    3: 0
    2: 1
    1: 0
    0: 1 Receive mode

    config_setup = 0x00A36E05; //0b.1010.0011. 0110.1110. 0000.0101; //Look at pages 13-15 for more bit info

	This config setup is designed to work with nRF24L01 ICs (though we've had some diffuculty actually getting it to work)
	1) 40-bit adddresses
	2) 16-bit CRC
	3) Default address: 0xE7E7E7E7E7 (5 bytes)
	4) 1Mbps shock burst
*/

#define _01A_PORT	PORTD
#define _01A_PORT_DD	DDRD
#define _01A_PORT_PIN PIND

#define _01A_DR	6
#define _01A_CLK  5
#define _01A_CS   2
#define _01A_CE   1
#define _01A_DATA 7

#define RF_DELAY	5


void rx_data_nRF2401A(void);
void tx_data_nRF2401A(void);
void config_rx_nRF2401A(void);
void config_tx_nRF2401A(void);

uint8_t rf_rx_array[4];
uint8_t rf_tx_array[4];

//This will clock out the current payload into the data_array
void rx_data_nRF2401A(void)
{
    uint8_t i, j, temp;
	
	temp = 0;
	
	cbi(PORTB, _01A_CE);//Power down RF Front end

    //Clock in data, we are setup for 32-bit payloads
    for(i = 0 ; i < 4 ; i++) //4 bytes
    {
        for(j = 0 ; j < 8 ; j++) //8 bits each
        {
            temp <<= 1;
			if(PIND & (1<<_01A_DATA)) temp |= 1;

			sbi(PORTB, _01A_CLK);

			cbi(PORTB, _01A_CLK);
        }

        rf_rx_array[i] = temp; //Store this byte
    }

    sbi(PORTB, _01A_CE); //Power up RF Front end
}

//This sends out the data stored in the data_array
//data_array must be setup before calling this function
void tx_data_nRF2401A(void)
{
    uint8_t i, j, temp, rf_address;

    sbi(PORTB, _01A_CE); //_01A_CE = 1;
    delay_us(RF_DELAY);

    //Clock in address
	for (j = 0; j < 5; j++)
	{
		rf_address = 0b11100111; //Power-on Default for all units (on page 11)
	
		for(i = 0 ; i < 8 ; i++)
		{
			if(rf_address & 0x80)
				sbi(PORTD, _01A_DATA);
			else
				cbi(PORTD, _01A_DATA);
	
			sbi(PORTB, _01A_CLK); //_01A_CLK = 1; 
			delay_us(RF_DELAY);
			cbi(PORTB, _01A_CLK); //_01A_CLK = 0;
			
			rf_address <<= 1;
		}
	}	
    
    //Clock in the data_array
    for(i = 0 ; i < 4 ; i++) //4 bytes
    {
        temp = rf_tx_array[i];
        
        for(j = 0 ; j < 8 ; j++) //One bit at a time
        {
			if(temp & 0x80)
				sbi(PORTD, _01A_DATA);
			else
				cbi(PORTD, _01A_DATA);
			
			sbi(PORTB, _01A_CLK); //_01A_CLK = 1; 
			delay_us(RF_DELAY);
			cbi(PORTB, _01A_CLK); //_01A_CLK = 0;
	
            temp <<= 1;
        }
    }
    
	cbi(PORTB, _01A_CE); //_01A_CE = 0; //Start transmission   
}

//2.4G Configuration - Receiver
//This setups up a RF-24G for receiving at 1mbps
void config_rx_nRF2401A(void)
{
    uint8_t i, j;
    uint32_t config_setup;

    //During configuration of the receiver, we need _01A_DATA as an output
    //1 = output, 0 = input
    _01A_PORT_DD |= (1<<_01A_DATA);  //(_01A_DR is input) (_01A_DATA is output)

    //Config Mode
    cbi(PORTB, _01A_CE); //_01A_CE = 0; _01A_CS = 1;
    delay_us(RF_DELAY);
	sbi(PORTB, _01A_CS);
    
    //Delay of 5us from CS to Data (page 30) is taken care of by the for loop
    delay_us(RF_DELAY);
	
    //Setup configuration bank	
	//Channel 1 40-bit (5-byte) address setup
    for(j = 0 ; j < 5 ; j++)
	{
		config_setup = 0xE7;

		for(i = 0 ; i < 8 ; i++)
		{
			if(config_setup & 0x80)
				sbi(_01A_PORT, _01A_DATA);
			else
				cbi(_01A_PORT, _01A_DATA);

			sbi(PORTB, _01A_CLK);
			delay_us(RF_DELAY);
			cbi(PORTB, _01A_CLK);
			
			config_setup <<= 1;
		}
	}
	
	
	//Lower 24 bit setup
    //Set last bit for receive mode
	//config_setup = 0x00A36E05; //0b.1010.0011. 0110.1110. 0000.0101; 
	config_setup = 0xA36E05;

    for(i = 0 ; i < 24 ; i++)
    {
		if(config_setup & 0x00800000)
			sbi(_01A_PORT, _01A_DATA);
		else
			cbi(_01A_PORT, _01A_DATA);

		sbi(PORTB, _01A_CLK);
		delay_us(RF_DELAY);
		cbi(PORTB, _01A_CLK);
        
        config_setup <<= 1;
    }
    
    //Configuration is actived on falling edge of CS (page 10)
    cbi(PORTB, _01A_CE); //_01A_CE = 0; _01A_CS = 0;
    delay_us(RF_DELAY);
	cbi(PORTB, _01A_CS);
    delay_us(RF_DELAY);
    
    //After configuration of the receiver, we need _01A_DATA as an input
    //1 = output, 0 = input
    _01A_PORT_DD &= ~((1<<_01A_DR)|(1<<_01A_DATA));  //(_01A_DR is input) (_01A_DATA is input)

    //Start monitoring the air
    sbi(PORTB, _01A_CE); //_01A_CE = 1; _01A_CS = 0;
    delay_us(RF_DELAY);
	cbi(PORTB, _01A_CS);
}    

//2.4G Configuration - Transmitter
//This sets up one RF-24G for shockburst transmission
void config_tx_nRF2401A(void)
{
    uint8_t i;
    uint32_t config_setup;
	
	_01A_PORT_DD |= (1<<_01A_DATA);

    //Config Mode
    cbi(PORTB, _01A_CE); //_01A_CE = 0; 
    delay_us(RF_DELAY);
	sbi(PORTB, _01A_CS); //_01A_CS = 1;
    
    //Delay of 5us from CS to Data (page 30) is taken care of by the for loop
    delay_us(RF_DELAY);
	
	config_setup = 0xA36E04;
    //Setup configuration word
    //config_setup = 0x00A36E04; //0b.0010.0011.0110.1110.0000.0100; //Look at pages 13-15 for more bit info

    for(i = 0 ; i < 24 ; i++)
    {
		if(config_setup & 0x00800000)
			sbi(_01A_PORT, _01A_DATA);
		else
			cbi(_01A_PORT, _01A_DATA);
		
		sbi(PORTB, _01A_CLK); //_01A_CLK = 1;
		delay_us(RF_DELAY);
		cbi(PORTB, _01A_CLK); //_01A_CLK = 0; 

        config_setup <<= 1;
    }
    
    //Configuration is actived on falling edge of CS (page 10)
    cbi(PORTB, _01A_CE); //_01A_CE = 0; 
    delay_us(RF_DELAY);
	cbi(PORTB, _01A_CS); //_01A_CS = 0;
}

