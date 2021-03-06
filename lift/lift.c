#include <mega16.h>
#include <delay.h>
int num[] = {0x3F, 0x30, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
int dest = 0;
int prsnt = 0;

void main() {
PORTB = 0b00011111;
DDRB = 0b00000000; // for switches

PORTD = 0b00000000;
DDRD = 0b01111111; // for 7-seg

PORTC = 0b00000000;
DDRC = 0b00000101;

    while(1){ 
    if(PINB.0 == 0){
        dest = 0;
        PORTD = num[dest];
        delay_ms(400);
    }
    if(PINB.1 == 0){
        dest = 1;
        PORTD = num[dest];
        delay_ms(400);
    }
    if(PINB.2 == 0){
        dest = 2;
        PORTD = num[dest];
        delay_ms(400);
    }
    if(PINB.3 == 0){
        dest = 3;
        PORTD = num[dest];
        delay_ms(400);
    }
    
    
    
    if(PINB.4 == 0){
        while(dest > prsnt && dest >=0){
            PORTC = 0b00000001;
            delay_ms((dest-prsnt)*2000);
            PORTC = 0b00000000;
            prsnt = dest;
            dest = -1;    
        }
        while(dest < prsnt && dest >=0){
            PORTC = 0b00000000;
            delay_ms((prsnt - dest)*2000);
            PORTC = 0b00000001;
            prsnt = dest;
            dest = -1;    
        }
    
        
    }
    }







}