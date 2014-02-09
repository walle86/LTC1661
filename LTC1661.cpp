/* 
	LTC1661.h - Arduino Library for Linear Technology LTC1661CN8 10bit dual DAC
	
	This Library provides functions to set both outputs of the LTC1661.
	
	Maximum SPI frequency is 16.7MHz at 4.5-5.5V, and 10MHz at 2.7-5.5V.
	Arduino standard SPI frequency is 4MHz (SPI_CLOCK_DIV4) so no change is needed.
	
	version 1.0 (Feb 9, 2014)
	Created by Stefan Wallnoefer, Feb 8, 2014.
	Copyright (c) 2014 Stefan Wallnoefer(walle86) under The MIT License (MIT)
	for other librarys and sketches look at https://github.com/walle86/ 
*/

#include <SPI.h>
#include <LTC1661.h>
#include <Arduino.h>

//Arduino standard pin as CS, Arduino standard SPIpins
LTC1661::LTC1661(int CS) {
	_CS = CS;
	_ArduinoSPI = true;
	pinMode(_CS, OUTPUT);
	digitalWrite(_CS, HIGH);	//deactivate Chipselect
	SPI.begin();
	_resolution = 10;
	_highValue = pow(2, _resolution) - 1;
}
/*non Arduino standard pin as CS (Daisy Chain not possible, no Data out)
	Chipselect in main Program, Arduino standard SPIpins
	*/
LTC1661::LTC1661() {
	_CS = -1;  //no pin with this number on Arduino
	_ArduinoSPI = true;
	SPI.begin();
	_resolution = 10;
	_highValue = pow(2, _resolution) - 1;
}
//Arduino standard pin as CS, non Arduino standard SPIpins
LTC1661::LTC1661(int CS, int DIN, int SCK) {
	_CS = CS;
	pinMode(_CS, OUTPUT);
	digitalWrite(_CS, HIGH);	//deactivate Chipselect
	_ArduinoSPI = false;
	_DIN = DIN;
	_SCK = SCK;
	pinMode(_DIN, OUTPUT);
	digitalWrite(_DIN, LOW);
	pinMode(_SCK, OUTPUT);
	digitalWrite(_SCK, LOW);
	_resolution = 10;
	_highValue = pow(2, _resolution) - 1;
}

//non Arduino standard pin as CS, non Arduino standard SPIpins
LTC1661::LTC1661( int DIN, int SCK) {
	_CS = -1;
	_ArduinoSPI = false;
	_DIN = DIN;
	_SCK = SCK;
	pinMode(_DIN, OUTPUT);
	digitalWrite(_DIN, LOW);
	pinMode(_SCK, OUTPUT);
	digitalWrite(_SCK, LOW);
	_resolution = 10;
	_highValue = pow(2, _resolution) - 1;
}

void LTC1661::sendData(unsigned int data){
	if (_ArduinoSPI){
		digitalWrite(_CS, LOW); //Select DAC
		SPI.transfer(data >> 8);
		SPI.transfer(data);
		digitalWrite(_CS, HIGH);
	}
	else{
		digitalWrite(_CS,LOW); //Select DAC
		// write bits
		for (int i=15; i>=0; i--){
			digitalWrite(_DIN,(data&1<<i) > 0 ? 1 : 0);
			//cycle clock
			digitalWrite(_SCK,HIGH);
			digitalWrite(_SCK,LOW);
  	}
  	digitalWrite(_CS, HIGH);
	}
}

void LTC1661::sleep() {
	digitalWrite(_CS, LOW); 						//activate Chipselect
	sendData(SLEEP);
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::wakeUp() {
	digitalWrite(_CS, LOW); 						//activate Chipselect
	sendData(WAKE);
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::update() {
	digitalWrite(_CS, LOW); 						//activate Chipselect
	sendData(UPDATE);
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

//Data as int

void LTC1661::loadA(int valueA) {
	valueA = constrain(valueA, 0, _highValue); //constrain Value
	
	digitalWrite(_CS, LOW); 						//activate Chipselect
	sendData(LOADA | valueA << 2);	//4 commandbits + 10 databits + 2 dont care bits
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::loadB(int valueB) {
	valueB = constrain(valueB, 0, _highValue); //constrain Value
	
	digitalWrite(_CS, LOW); 						//activate Chipselect
	sendData(LOADB | valueB << 2);	//4 commandbits + 10 databits + 2 dont care bits
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::loUpA(int valueA) {
	valueA = constrain(valueA, 0, _highValue); //constrain Value
	
	digitalWrite(_CS, LOW); 						//activate Chipselect
	sendData(LOUPA | valueA << 2);	//4 commandbits + 10 databits + 2 dont care bits
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::loUpB(int valueB) {
	valueB = constrain(valueB, 0, _highValue); //constrain Value
	
	digitalWrite(_CS, LOW); 						//activate Chipselect
	sendData(LOUPB | valueB << 2);	//4 commandbits + 10 databits + 2 dont care bits
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::loUp(int value) {
	value = constrain(value, 0, _highValue); //constrain Value
	
	digitalWrite(_CS, LOW); 						//activate Chipselect
	sendData(LOUP | value << 2);	//4 commandbits + 10 databits + 2 dont care bits
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::load(int valueA, int valueB) {
	loadA(valueA);
	loadB(valueB);
}

void LTC1661::loUp(int valueA, int valueB) {
	loUpA(valueA);
	loUpB(valueB);
}

void LTC1661::loadCH(char channel, int value) {
	switch (channel) {
		case 0:		//0 for Channel A
			loadA(value);
			break;
		case 1:		//1 for Channel B
			loadB(value);
			break;
		case 'A':
			loadA(value);
			break;
		case 'B':
			loadB(value);
			break;
	}
}

void LTC1661::loUpCH(char channel, int value) {
	switch (channel) {
		case 0:		//0 for Channel A
			loUpA(value);
			break;
		case 1:		//1 for Channel B
			loUpB(value);
			break;
		case 'A':
			loUpA(value);
			break;
		case 'B':
			loUpB(value);
			break;
	}
}

//Data as double in Vout/Vref
//if you only write for example loadA(0.9), it will be send as double

void LTC1661::loadA(double valueA) {
	int value = round(_highValue * valueA);
	loadA(value);
}

void LTC1661::loadB(double valueB) {
	int value = round(_highValue * valueB);
	loadB(value);
}

void LTC1661::loUpA(double valueA) {
	int value = round(_highValue * valueA);
	loUpA(value);
}

void LTC1661::loUpB(double valueB) {
	int value = round(_highValue * valueB);
	loUpB(value);
}

void LTC1661::loUp(double valueIn) {
	int value = round(_highValue * valueIn);
	loUp(value);
}

void LTC1661::load(double valueA, double valueB) {
	loadA(valueA);
	loadB(valueB);
}

void LTC1661::loUp(double valueA, double valueB) {
	loUpA(valueA);
	loUpB(valueB);
}

void LTC1661::loadCH(char channel, double value) {
	switch (channel) {
		case 0:		//0 for Channel A
			loadA(value);
			break;
		case 1:		//1 for Channel B
			loadB(value);
			break;
		case 'A':
			loadA(value);
			break;
		case 'B':
			loadB(value);
			break;
	}
}

void LTC1661::loUpCH(char channel, double value) {
	switch (channel) {
		case 0:		//0 for Channel A
			loUpA(value);
			break;
		case 1:		//1 for Channel B
			loUpB(value);
			break;
		case 'A':
			loUpA(value);
			break;
		case 'B':
			loUpB(value);
			break;
	}
}

void LTC1661::dWrite(char channel, int state){
	if(state == LOW){
		loUpCH(channel, 0);
	}
	else{
		loUpCH(channel, _highValue);
	}
	delayMicroseconds(30);	//delay to get a stable output
}

int LTC1661::getCSPin() {
	return _CS;
}

void LTC1661::setCSPin(int CS){
	_CS = CS;
}