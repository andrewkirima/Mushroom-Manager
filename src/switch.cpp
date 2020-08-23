// PB1,2,3,4 and 5 Switch
#include "switch.h"

 //PCINT1
 void initSwitch0(){
   DDRB &= ~(1 << DDB1); // Initializes pull-up resistor on PB1 and sets it into input mode
   PORTB |= (1 << PORTB1); // enable pull-up for PORTB1
  

   PCICR |= (1 << PCIE0);      // enable full PCINT
   PCMSK0 |= (1 << PCINT1);    // enable PCINT for PCINT1
 }

 //PCINT23
 void initSwitch2(){
   DDRK &= ~(1 << DDK7); // Initializes pull-up resistor on PK7 and sets it into input mode
   PORTK |= (1 << PORTK7); // enable pull-up for PORTK7

   PCICR |= (1 << PCIE2);      // enable full PCINT
   PCMSK2 |= (1 << PCINT23);    // enable PCINT for PCINT23
 }

//PCINT9
 void initSwitch1(){
   DDRJ &= ~(1 << DDJ0); // Initializes pull-up resistor on PJ0 and sets it into input mode
   PORTJ |= (1 << PORTJ0); // enable pull-up for PORTB3

   PCICR |= (1 << PCIE1);      // enable full PCINT
   PCMSK1 |= (1 << PCINT9);    // enable PCINT for PCINT9
 }
