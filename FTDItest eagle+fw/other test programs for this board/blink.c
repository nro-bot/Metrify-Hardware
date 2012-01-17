//LED blink
#include "avr/io.h" 
#include "util/delay.h" 
int main(){
      DDRA=_BV(PA7); //128 deximal
      while(1){
		PORTA=_BV(PA7);//LED ON
		_delay_ms(500);
		PORTA=0;
		_delay_ms(500);//LED OFF
      }
}
