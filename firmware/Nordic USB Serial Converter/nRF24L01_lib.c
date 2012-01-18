/*
    1-14-09
    Copyright Spark Fun Electronics© 2009
	
	Basic nRF24L01 operating functions
	
	Check the Nordic Documentation for the nRF24L01 for more information
	on the command structure
*/

#define L01_PORT		PORTB
#define L01_PORT_PIN	PINB
#define L01_PORT_DD	DDRB
#define L01_IRQ_PORT	PIND

#define L01_CE	1 //Output
#define L01_CSN	2 //Output
#define L01_SCK	5 //Output
#define MOSI	3 //Output
#define MISO 4 //Input
#define RX_IRQ	2 //Input

#define RF_DELAY	5

uint8_t data_array[5];

//Initializes ATMega168 pins
void init_24L01_pins(void);

//Configures nRF24L01 for recieve mode
void config_rx_nRF24L01(void);

//Gets data from 24L01 and puts it in rf_rx_array, resets all ints
void rx_data_nRF24L01(void);

//Set up nRF24L01 as a transmitter, does not actually send the data,
//(need to call tx_data_nRF24L01() for that)
uint8_t config_tx_nRF24L01(void);

//Sends command to nRF
uint8_t send_byte(uint8_t cmd);

//Sends command to nRF, returns status byte
uint8_t send_command(uint8_t cmd, uint8_t data);

//Sends a number of bytes of payload
void tx_send_payload(uint8_t cmd, uint8_t bytes);

//This sends out the data stored in the data_array
//data_array must be setup before calling this function
void tx_data_nRF24L01(void);

//Basic SPI to nRF
uint8_t tx_spi_byte(uint8_t outgoing);

//Initializes ATMega168 pins
void init_24L01_pins(void)
{
	//1 = Output, 0 = Input
	L01_PORT_DD |= ((1<<L01_CE) | (1<<L01_CSN) | (1<<MOSI) | (1<<L01_SCK));

	//Enable pull-up resistors (page 74)
	L01_PORT = 0b11111111;

	cbi(L01_PORT, L01_CE); //Stand by mode
}


//Sends a string out through nRF
void transmit_string(char * string_out)
{
	uint8_t i;
	
	for(i = 0 ; string_out[i] != '\0' ; i++)
	{
		data_array[1] = string_out[i];
		tx_data_nRF24L01();
		delay_ms(5);
	}

	data_array[1] = '\0';
	tx_data_nRF24L01();
	delay_ms(5);
}

//This sends out the data stored in the data_array
//data_array must be setup before calling this function
void tx_data_nRF24L01(void)
{
	send_command(0x27, 0x7E); //Clear any interrupts
	
	send_command(0x20, 0x7A); //Power up and be a transmitter

	send_byte(0xE1); //Clear TX Fifo
	
	tx_send_payload(0xA0, 4); //Clock in 4 byte payload of data_array

    sbi(L01_PORT, L01_CE); //Pulse CE to start transmission
    delay_ms(1);
    cbi(L01_PORT, L01_CE);
}

//Set up nRF24L01 as a transmitter, does not actually send the data,
//(need to call tx_data_nRF24L01() for that)
uint8_t config_tx_nRF24L01(void)
{
    cbi(L01_PORT, L01_CE); //Go into standby mode
	
	send_command(0x20, 0x7C); //16 bit CRC enabled, be a transmitter

	send_command(0x21, 0x00); //Disable auto acknowledge on all pipes

	send_command(0x24, 0x00); //Disable auto-retransmit

	send_command(0x23, 0x03); //Set address width to 5bytes (default, not really needed)

	send_command(0x26, 0x07); //Air data rate 1Mbit, 0dBm, Setup LNA

	send_command(0x25, 0x02); //RF Channel 2 (default, not really needed)
	
	
	data_array[0] = 0xE7;
	data_array[1] = 0xE7;
	data_array[2] = 0xE7;
	data_array[3] = 0xE7;
	data_array[4] = 0xE7;
	tx_send_payload(0x30, 5); //Set TX address
	
	send_command(0x20, 0x7A); //Power up, be a transmitter

	return(send_byte(0xFF));
}

//Sends a number of bytes of payload
void tx_send_payload(uint8_t cmd, uint8_t bytes)
{
	uint8_t i;

	cbi(L01_PORT, L01_CSN); //Select chip
	tx_spi_byte(cmd);
	
	for(i = 0 ; i < bytes ; i++)
		tx_spi_byte(data_array[i]);

	sbi(L01_PORT, L01_CSN); //Deselect chip
}

//Sends command to nRF, returns status byte
uint8_t send_command(uint8_t cmd, uint8_t data)
{
	uint8_t status;

	cbi(L01_PORT, L01_CSN); //Select chip
	tx_spi_byte(cmd);
	status = tx_spi_byte(data);
	sbi(L01_PORT, L01_CSN); //Deselect chip

	return(status);
}

//Sends one byte to nRF
uint8_t send_byte(uint8_t cmd)
{
	uint8_t status;
	
	cbi(L01_PORT, L01_CSN); //Select chip
	status = tx_spi_byte(cmd);
	sbi(L01_PORT, L01_CSN); //Deselect chip
	
	return(status);
}

//Basic SPI to nRF24L01
uint8_t tx_spi_byte(uint8_t outgoing)
{
    uint8_t i, incoming;
	incoming = 0;
	
	
    //Send outgoing byte
    for(i = 0 ; i < 8 ; i++)
    {
		
		if(outgoing & 0b10000000)
			sbi(L01_PORT, MOSI);
		else
			cbi(L01_PORT, MOSI);
		
		sbi(L01_PORT, L01_SCK); //L01_SCK = 1;
		delay_us(RF_DELAY);
		
		//MISO bit is valid after clock goes going high
		incoming <<= 1;
		if(L01_PORT_PIN & (1<<MISO)) incoming |= 0x01; //this line is fucking up
		
		cbi(L01_PORT, L01_SCK); //L01_SCK = 0; 
		delay_us(RF_DELAY);
		
        outgoing <<= 1;
		
    }
	

	return(incoming);
}


//Configures nRF24L01 for recieve mode
void config_rx_nRF24L01(void)
{
	cbi(L01_PORT, L01_CE);//CE = 0
    
	send_command(0x20, 0x3D);//PRX, 16 bit CRC enabled===========================================================
	
    send_command(0x21, 0);//dissable auto-ack for all channels====================================================
	
    send_command(0x26, 0x07);//data rate = 1MB ===============================================================
    
    send_command(0x31, 0x04);//4 byte payload ==============================================================
	
    send_command(0x20, 0x3B);//PWR_UP = 1 ================================================================
    
	sbi(L01_PORT, L01_CE);//CE = 1

}



//Gets data from 24L01 and puts it in rf_rx_array, resets all ints
void rx_data_nRF24L01(void)
{
    uint8_t i, j, data, cmd;

    cmd = 0x61; //Read RX payload ==========================================================================================
    
	cbi(L01_PORT, L01_CSN);//CSN = 0
	delay_us(RF_DELAY);
    
    for(i = 0 ; i < 8 ; i++)
    {
		if(cmd & 0b10000000)
			sbi(L01_PORT, MOSI);
		else
			cbi(L01_PORT, MOSI);
		
		sbi(L01_PORT, L01_SCK); //L01_SCK = 1;
		delay_us(RF_DELAY);

		cbi(L01_PORT, L01_SCK); //L01_SCK = 0; 
		delay_us(RF_DELAY);
		
        cmd <<= 1;
		
    }
    
    for (j = 0; j < 4; j++)
    {
        data = 0;
        
        for(i = 0 ; i < 8 ; i++)
        {
            data <<= 1;
            if(L01_PORT_PIN & (1<<MISO) ) data |= 0x01;
			else data &= 0xFE;

			sbi(L01_PORT, L01_SCK); //L01_SCK = 1;
			delay_us(RF_DELAY);
            
			cbi(L01_PORT, L01_SCK); //L01_SCK = 0; 
			delay_us(RF_DELAY);
        }
		
		rf_rx_array[j] = data;
 
    }
    
    sbi(L01_PORT, L01_CSN);//CSN = 1
    
    send_byte(0xE2);//Flush RX FIFO =============================================================

	send_command(0x27, 0x40);//reset int =========================================================
    
}

