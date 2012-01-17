//Derived from:
//
// hello.button.45.c
//
// button hello-world
//    9600 baud FTDI interface
//
// Neil Gershenfeld
// 10/31/10
//
// (c) Massachusetts Institute of Technology 2010
// Permission granted for experimental and personal use;
// license for commercial sale available from MIT.
//

// 17 Jan 2012, nouyang:
// hello.button.44.c: modified original hello.button.45.c for an 
// attiny44 board with a 20Mhz crystal, where PA3 leads to a pushbutton
// and PA1 leads to the RX out via rs232 headers for an ftdi cable
// 
// Original: attiny45, PB4 = button, PB2 = rx
// board image: http://academy.cba.mit.edu/classes/input_devices/button/hello.button.45.png

// Should output "d" or "u" depend on pushbutton state to serial terminal.
// Hardware steps: make (drill or etch) and populate Mas.863 Week6 board
// Connect usbtiny AVR programmer to board ISP headers via female-female ribbon cable
// Connect board to computer usb port using ftdi RS232>USB cable 
// Software steps: (in linux/mac/cygwin) cd to correct directory. 
// First time (for the board) only, set fuses for 20mhz crystal:
// make -f ftditest.make  program-usbtiny-fuses
// Then just run
// make -f ftditest.make program-usbtiny
// from then on to compile and load the program onto the attiny
// Edit the first line in ftditest.make if you want to compile and load a different program file than
// "hello.button.44.c"

// hello.button.44.c: sch image: https://picasaweb.google.com/113942194695013581888/MAS863Week7#5669702774053070114
// hello.button.44.c: brd image: https://picasaweb.google.com/113942194695013581888/MAS863Week7#5669702774078546434
// Cable hookup: missing the two usbA to miniB cables, but the idea: https://picasaweb.google.com/113942194695013581888/MAS863Week7#5672312997543459426
// see akane sano's week 5 "embedded programming" notes for good documentation

#include <avr/io.h>
#include <util/delay.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set
#define bit_delay_time 8.5 // bit delay for 115200 with overhead
//#define bit_delay_time 100 // bit delay for 9600 with overhead
#define bit_delay() _delay_us(bit_delay_time) // RS232 bit delay
#define half_bit_delay() _delay_us(bit_delay_time/2) // RS232 half bit delay

#define input_port PORTA
#define input_direction DDRA
#define input_pin (1 << PA3)
#define input_pins PINA
#define serial_port PORTA
#define serial_direction DDRA
#define serial_pin_out (1 << PA1)

//~ #define serial_port PORTA
//~ #define serial_direction DDRA
//~ #define serial_pins PINA
//~ #define serial_pin_in (1 << PA0)
//~ #define serial_pin_out (1 << PA1)


void put_char(volatile unsigned char *port, unsigned char pin, char txchar) {
   //
   // send character in txchar on port pin
   //    assumes line driver (inverts bits)
   //
   // start bit
   //
   clear(*port,pin);
   bit_delay();
   //
   // unrolled loop to write data bits
   //
   if bit_test(txchar,0)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,1)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,2)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,3)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,4)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,5)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,6)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,7)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   //
   // stop bit
   //
   set(*port,pin);
   bit_delay();
   //
   // char delay
   //
   bit_delay();
   }

int main(void) {
   //
   // main
   //
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // initialize pins
   //
   set(serial_port, serial_pin_out);
   output(serial_direction, serial_pin_out);
   set(input_port, input_pin); // turn on pull-up
   input(input_direction, input_pin);
   //
   // main loop
   //
   while (1) {
      //
      // wait for button down
      //
      while (0 != pin_test(input_pins,input_pin))
         ;
      put_char(&serial_port, serial_pin_out, 'd');
      //
      // wait for button up
      //
      while (0 == pin_test(input_pins,input_pin))
         ;
      put_char(&serial_port, serial_pin_out, 'u');
      }
   }
