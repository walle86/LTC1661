/*
  Examples Sketch for LTC1661.h
  
  This example reads the voltage of a Poti on PIN A0 and 
  represents it on VOUT A of the LTC1661
  VOUT B will be set to 5V - VOUT A
  VOUT A will be read on A1 and VOUT B on A2
  
  Pins on LTC1661:

  1 CS/LD chip selct -> D10
  2 SCK -> D13 (SCK pin)
  3 DIN -> D11 (MOSI pin)
  4 REF -> 0V <= VREF <= VCC (to Arduino +5V)
  5 VOUT B -> A2
  6 VCC -> Supply Voltage 2.7V to 5.5V
  7 GND -> GND
  8 VOUT A -> A1
     ___ 
  1 | u | 8 
  2 |   | 7 
  3 |   | 6 
  4 |___| 5 
  
  The rest of circuit:
  * A0 to potentiometer
  
  created 9 Feb 2014
  by Stefan Wallnoefer
  for other librarys and sketches look at
  https://github.com/walle86/ 
*/

#include <SPI.h>
#include <LTC1661.h>

#define chipSelect 10

LTC1661 dac(chipSelect);    //creats an instance with chipSelect as CS Pin

int potiPin = A0, u1Pin = A1, u2Pin = A2;  //Inputpins
int potiRead = 0, potiLast = -10, u1Read = 0, u2Read = 0, u1Write = 0, u2Write = 0;  //read and write Values
float poti = 0, u1 = 0, u2 = 0;    //Values for printing
long lastPrint = 0;


void setup() {
  
  dac.loUp(0); //set both outputs of the LTC1661 to 0 (GND);

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

    dac.loUp(u1Write, u2Write);  //send values and update both OUTPUTS

    /* Some other ways to get the same result
     1)  dac.loUpA(u1Write);
         dac.loUpB(u2Write);
     
     2)  dac.loUpCH(0, u1Write);  0 could also be 'A'
         dac.loUpCH(1, u2Write);  1 could also be 'B'
     
     */

    delayMicroseconds(30); //delay the Output settling time
    
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
}

