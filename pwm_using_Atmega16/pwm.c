#include <mega16.h>
#include <delay.h>
int p = 0;

void main(){
PORTB = 0b00000000;
DDRB = 0b00001000;

TCCR0 = 0b01101010;
while(1) {

 for (p=0;p<=255;p++)
     {
     OCR0 = p;
     delay_ms(500);
     }
 for (p=255;p>0;p--)
     {
     OCR0 = p;
     delay_ms(500);
     }

}




}