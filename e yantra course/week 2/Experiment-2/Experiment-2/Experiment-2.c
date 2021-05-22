#include <avr/io.h> 
#include <avr/interrupt.h>

//Quickly Turn VSYNC On/Off
//Or You Can Change The VSYNC Pin..
#define VSYNC_LOW    PORTD &= ~_BV(6)
#define VSYNC_HIGH   PORTD |= _BV(6)

//Quickly Turn HSYNC On/Off
//Or You Can Change The HSYNC Pin..
#define HSYNC_LOW    PORTD &= ~_BV(7)
#define HSYNC_HIGH   PORTD |= _BV(7)

//RED
#define RED_ON       PORTB |= _BV(4)
#define RED_OFF      PORTB &= ~_BV(4)

//Green
#define GREEN_ON     PORTB |= _BV(3)
#define GREEN_OFF    PORTB &= ~_BV(3)

//BLUE
#define BLUE_ON      PORTB |= _BV(2)
#define BLUE_OFF     PORTB &= ~_BV(2) 
 
#define microsecond_delay   __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t")  
 
int i = 0; 
int color = 0;

void setup() 
{
  //Get Rid Of Dumb Timer0 (millis()/micros() functions)
  TIMSK0 = 0x00; //sbi(TIMSK0, TOIE0);
  DDRB = 0xFF;
  DDRD = 0xFF;

  // initialize timer1 
  cli();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 65536-27;            // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS10);    // 1 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  sei();             // enable all interruptss
  color = 0x10;
}
 
 /*
 In the loop we're just setting what color should be output...
 200 Blue..
 200 Green...
 200 Red.......
 */
 
void loop()
{
   if(i == 1)
     color = 0x04; 
   if(i == 200)
     color = 0x08;
   if(i == 400)
     color = 0x10;     
}
 

 /*
 The Interrupt routine is triggered when Timer1 Overflows. This isn't the best use of interrupts given all the wait statements
 but it's one way to get the proper VGA timing to come out of the Arduino....
 */
 
/// @@@@@@@@@@@@@@@@@@@@@@@@@@@
/// @@@  ISR Timer Routine @@@@
/// @@@@@@@@@@@@@@@@@@@@@@@@@@@
ISR(TIMER1_OVF_vect)
{
          HSYNC_LOW;  //HSYNC Low  
  if(i > 622)
    VSYNC_HIGH;
  else
    VSYNC_LOW;
       
            //Color High
          PORTB = color;

          microsecond_delay;
          __asm__("nop\n\t""nop\n\t""nop\n\t");

            //20uS Color Data          
          //10 uS Delay          
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;

          //10 uS Delay          
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
          microsecond_delay;
     
            //Color Low
          PORTB = 0x00;
          i++;
                             
     if(i==627)
       i=0;   
        

            //3.2uS Horizontal Sync
         TCNT1 = 65536-27;            // preload timer            
          HSYNC_HIGH;  //HSYNC High
}