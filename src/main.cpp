//
//    FILE: dht_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.07
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: https://arduino.cc/playground/Main/DHTLib
//
// Released to the public domain
//
#include <Arduino.h>
#include <dht.h>
#include <LiquidCrystal.h>
#include <switch.h>
#include <RelayHeater.h>

LiquidCrystal lcd(10, 12, 22, 23, 24, 25);

dht DHT;

typedef enum {
waitPress, debouncePress, waitRelease, debounceRelease
} states;
volatile states state = waitPress;

typedef enum {
READ, SET
} lcdStates;       //default lcd state is read mode
volatile lcdStates lcdState = READ;

#define DHT11_PIN A0

int atomizationPin = A2;
int heatlampPin = A1;

//default settings of termperature and humdity
double setHum = 75.0;
double setTemp = 27.0;

void setup(){
  initSwitch0();
  initSwitch1();
  initSwitch2();
  Serial.begin(9600);
  pinMode(atomizationPin, OUTPUT);
  pinMode(heatlampPin, OUTPUT);
  lcd.begin(16,2);
}

void loop()
{
  sei();

  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature setting = ");
  Serial.print(setTemp);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity setting = ");
  Serial.print(setHum);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1500);

  //display function when display is in read mode
  if (lcdState == READ) {
    lcd.setCursor(0,0); 
    lcd.print("Temp: ");
    lcd.print(DHT.temperature);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(DHT.humidity);
    lcd.print("%");
    delay(1500);
  }

  //display function when display is in set mode
  else if (lcdState == SET) {
    lcd.setCursor(0,0); 
    lcd.print("TempX: ");
    lcd.print(setTemp);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(setHum);
    lcd.print("%");
    delay(1500);
  }

   switch(state) {
      case waitPress:
        //Serial.println("wait for press");
        break;

      case debouncePress:
        delay(1);
        //Serial.println("debounce press");
        state = waitRelease;
        break;

      case waitRelease:
        //Serial.println("wait release");
        break;

      case debounceRelease:
        delay(1);
        //Serial.println("debounce release");
        state = waitPress;
        break;
    }

    //automation for turning on atomizer in response to sensor detecting humidity lower than user setting
    if (DHT.humidity < setHum) {
      Serial.print("atomizing");
      digitalWrite(atomizationPin, HIGH);
      delay(3000); //on for 3 seconds
      digitalWrite(atomizationPin, LOW);
      
    }
        //automation for turning on relay for heat lamp in response to sensor detecting temperature lower than user setting
    if (DHT.temperature < setTemp) {
      Serial.print("heating");
      heatSwitchOn();
      delay(10000); //on for 3 seconds
      heatSwitchOff();
    }
}

ISR(PCINT0_vect){
  //manage debounce state
  if (state == waitPress) {
      state = debouncePress;
    }
    //finalizing debounce and thus switch action
    else if(state == waitRelease){
      //toggle state of lcd between read and write
      if (lcdState == READ)
          lcdState = SET;
      else if (lcdState == SET)
          lcdState = READ;
      Serial.print("Switch 0");
      state = debounceRelease;
    }
}

ISR(PCINT1_vect){
  //manage debounce state
  if (state == waitPress) {
      state = debouncePress;
    }
    //finalizing debounce and thus switch action
    else if(state == waitRelease){
      Serial.print("Switch 1");
      //when in set mode allows increase of the humidity setting, resetting to 20 after 100
      if (lcdState == SET) {
          setHum++;
          if (setHum >= 100.0) 
              setHum = 20.0;
      }
      state = debounceRelease;
    }
}

ISR(PCINT2_vect){
  //manage debounce state
if (state == waitPress) {
    state = debouncePress;
  }
  //finalizing debounce and thus switch action
  else if(state == waitRelease){
    Serial.print("Switch 2");
    //when in set mode allows the increase of the temperature, resetting to 20 after 40
    if (lcdState == SET) {
        setHum++;
        if (setTemp >= 40.0) 
            setHum = 20.0;
        state = debounceRelease;
    }
  }
}
