/*
  Examples Sketch for LTC1661.h
 
 This example reads the voltage of a Poti on PIN A0 and 
 represents it on VOUT A of the LTC1661
 VOUT B will be set to 5V - VOUT A
 VOUT A will be read on A1 and VOUT B on A2
 
 The Outputs will only be updated after a 'U' was send.
 Send a 'S' to set it in sleep mode, and a 'W' to wake it up.
 
 The circuit:
 * A0 to potentiometer
 * GND to Ground
 * REF and VCC to +5V
 * CS/LD - to digital pin 10  (SS pin)
 * DIN - to digital pin 11 (MOSI pin)
 * SCK - to digital pin 13 (SCK pin)
 
 created 9 Jan 2014
 by Stefan Wallnoefer
 
 */

#include <SPI.h>
#include <LTC1661.h>

#define chipSelect 10

LTC1661 dac(chipSelect);    //creats an instance with chipSelect as CS Pin

int potiPin = A0, u1Pin = A1, u2Pin = A2;  //Inputpins
int potiRead = 0, potiLast = -10, u1Read = 0, u2Read = 0, u1Write = 0, u2Write = 0;  //read and write Values
float poti = 0, u1 = 0, u2 = 0;    //Values for printing
long lastPrint = 0;
char serIn;


void setup() {
  
  dac.loUp(0,0); //set both outputs of the LTC1661 to 0 (GND);

  //set INPUT pins
  pinMode(potiPin, INPUT);
  pinMode(u1Pin, INPUT);
  pinMode(u2Pin, INPUT);

  Serial.begin(9600);
  //Print Header
  Serial.println("Poti\tU1\tU2");
}

void loop(){

  potiRead = analogRead(potiPin);

  //only change and print if differenc to last reading is greater or equal 2 to get not so much prints
  //and more then 100ms to last printing
  if(abs(potiRead - potiLast) >= 2 && millis() - lastPrint >= 100) {
    potiLast = potiRead;
    lastPrint = millis();

    poti = potiRead / 1023.0 * 5.0;  //convert reading to a voltage

    Serial.print(poti);
    Serial.print("\t");


    u1Write = potiRead;  //U(VOUTA) = U(Poti)
    u2Write = 1023 - potiRead;  //U(VOUTB) = 5V - U(Poti)

    dac.load(u1Write, u2Write);  //send values but not update OUTPUTS

    /* Some other ways to get the same result
     1)  dac.loadA(u1Write);
         dac.loadB(u2Write);
     
     2)  dac.loadCH(u1Write,0);  0 could also be 'A'
         dac.loadCH(u1Write,1);  1 could also be 'B'
     
     */

    delayMicroseconds(25); //delay to get the outputs to ther wanted Values (20us for 90% stepdown + 5us)

    //read and print outputs of LTC1661
    u1Read = analogRead(u1Pin);
    u1 = u1Read / 1023.0 * 5.0;
    u2Read = analogRead(u2Pin);
    u2 = u2Read / 1023.0 * 5.0;

    Serial.print(u1);
    Serial.print("\t");
    Serial.print(u2);
    Serial.println("\t");
  }

  if(Serial.available() > 0){
    serIn = Serial.read();
    switch(serIn){
    case 'U':
      dac.update();
      Serial.println("LTC1661 outputs updated");
      break;
    case 'W':
      dac.wakeUp();
      Serial.println("LTC1661 wake up");
      break;
    case 'S':
      dac.sleep();
      Serial.println("LTC1661 sleep");
    }
    delayMicroseconds(25);

    //read and print all analog inputs
    potiRead = analogRead(potiPin);
    poti = potiRead / 1023.0 * 5.0; 
    u1Read = analogRead(u1Pin);
    u1 = u1Read / 1023.0 * 5.0;
    u2Read = analogRead(u2Pin);
    u2 = u2Read / 1023.0 * 5.0;
    Serial.print(poti);
    Serial.print("\t");
    Serial.print(u1);
    Serial.print("\t");
    Serial.print(u2);
    Serial.println("\t");
  }      
}


