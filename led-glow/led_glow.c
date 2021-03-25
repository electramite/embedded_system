#include<mega16.h>
void main(){
PORTA = 0b00000000;
DDRA = 0b00001000;
while (1)
      {  PORTA.3 = 1;

      }

}