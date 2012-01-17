//button for LED
#include "avr/io.h"
#include "util/delay.h"

int main(){
       DDRA=_BV(PA7); //128 deximal //LED
       while(1){
               if(PINA &  _BV(PA3)){//button high
                      PORTA=0;
               }else
               {//button low
                       PORTA=_BV(PA7);
               }
       }
}
