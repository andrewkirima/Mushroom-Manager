// Author: Joshua Massee, Richelle Javier, AliAlmeely, Andrew Kirima 
// Net ID: joshmassee
// Date: 
// Assignment: Final Project - Mushroom Manager
//
// Description: 
// 

//----------------------------------------------------------------------//

#include <avr/io.h>
#include <util/delay.h>
#include "RelayHeater.h"

//causes relay switch to connect, thereby connecting heat lamp
void heatSwitchOn() {
   DDRF |= (1<< DDF1);
   PORTF &= ~(1 << PORTF1);
}

//causes relay switch to disconnect, thereby disconnecting the lamp
void heatSwitchOff() {
    //PORTF &= ~(1 << PORTF0);
    //DDRF &= ~(1<< DDF0);
    PORTF |= (1 << PORTF1);
}