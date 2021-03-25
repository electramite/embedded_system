#include <mega16.h>
#include <delay.h>
int count = 0;
int num[] = {0x3F, 0x30, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
void main(){
PORTC = 0b00000000;
DDRC = 0b01000001; // POWER_LED- 0, COUNTER_LED- 1

PORTA = 0b10100000;
DDRA = 0b00001001; // START_BUTTON - 0, COUNTER_BUTTON - 2

PORTD = 0b00000000;
DDRD = 0b11111111;

PORTA.0 = 1;
PORTD = num[0];
while(1){
    if(PINA.7 == 0){
        count = count + 1;
        
        if(count > 9){
            count = 0;
        }
        PORTD = num[count];
        delay_ms(400);
    }
    if(PINA.5 == 0){ 
        delay_ms(400);
        while(count > 0){
            PORTA.3 = 1;
            PORTC.6 = 1;
            PORTD = num[count];
            delay_ms(500);
            PORTA.3 = 0;
            
            delay_ms(500);
            count = count - 1;
        }
        PORTC.6 = 0;
        PORTD = num[0];

    }


    }
}