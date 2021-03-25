#include <mega16.h>
#include <delay.h>
#include <mylcd.h>

void main(){
PORTD = 0b00000001;
DDRD = 0b00000000;
lcd_init();
while(1){

    if(PIND.0 == 0)
    {   lcd_xy(0, 4); 
        lcd_s("lawdi");
        delay_ms(5000);
        lcd_cmd(0x01);
    }   



}
}