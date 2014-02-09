/* 
	LTC1661.h - Arduino Library for Linear Technology LTC1661CN8 10bit dual DAC
	Created by Stefan Wallnoefer, Feb 8, 2014.
	Copyright (c) 2014 Stefan Wallnoefer(walle86) under The MIT License (MIT)
	
	This Library provides functions to set both outputs of the LTC1661
	
*/

#include <SPI.h>
#include <LTC1661.h>
#include <Arduino.h>

LTC1661::LTC1661(int CS) {
	_CS = CS;
	pinMode(_CS, OUTPUT);
	digitalWrite(_CS, HIGH);	//deactivate Chipselect
	SPI.begin();
}

void LTC1661::sleep() {
	digitalWrite(_CS, LOW); 						//activate Chipselect
	SPI.transfer(SLEEP);
	SPI.transfer(0x00);									//to get tu 16bit inputword
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::wakeUp() {
	digitalWrite(_CS, LOW); 						//activate Chipselect
	SPI.transfer(WAKE);
	SPI.transfer(0x00);									//to get tu 16bit inputword
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::update() {
	digitalWrite(_CS, LOW); 						//activate Chipselect
	SPI.transfer(UPDATE);
	SPI.transfer(0x00);									//to get tu 16bit inputword
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

//Data as int

void LTC1661::loadA(int valueA) {
	valueA = constrain(valueA, 0, 1023); //constrain Value
	
	digitalWrite(_CS, LOW); 						//activate Chipselect
	SPI.transfer(LOADA | valueA >> 6);	//4 commandbits + 4 highest databits
	SPI.transfer(valueA << 2);					//6 lowest databits + 2 dont care bits
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::loadB(int valueB) {
	valueB = constrain(valueB, 0, 1023); //constrain Value
	
	digitalWrite(_CS, LOW); 						//activate Chipselect
	SPI.transfer(LOADB | valueB >> 6);	//4 commandbits + 4 highest databits
	SPI.transfer(valueB << 2);					//6 lowest databits + 2 dont care bits
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::loUpA(int valueA) {
	valueA = constrain(valueA, 0, 1023); //constrain Value
	
	digitalWrite(_CS, LOW); 						//activate Chipselect
	SPI.transfer(LOUPA | valueA >> 6);	//4 commandbits + 4 highest databits
	SPI.transfer(valueA << 2);					//6 lowest databits + 2 dont care bits
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::loUpB(int valueB) {
	valueB = constrain(valueB, 0, 1023); //constrain Value
	
	digitalWrite(_CS, LOW); 						//activate Chipselect
	SPI.transfer(LOUPB | valueB >> 6);	//4 commandbits + 4 highest databits
	SPI.transfer(valueB << 2);					//6 lowest databits + 2 dont care bits
	digitalWrite(_CS, HIGH); 						//deactivate Chipselect
}

void LTC1661::loUp(int value) {
	value = constrain(value, 0, 1023); //constrain Value
	
	digitalWrite(_CS, LOW); 						//activate Chipselect
	SPI.transfer(LOUP | value >> 6);		//4 commandbits + 4 highest databits
	SPI.transfer(value << 2);						//6 lowest databits + 2 dont care bits
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

void LTC1661::loadCH(int value, char channel) {
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

void LTC1661::loUpCH(int value, char channel) {
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

//Data as float in Vout/Vref

void LTC1661::loadA(float valueA) {
	int value = round(1023 * valueA);
	loadA(value);
}

void LTC1661::loadB(float valueB) {
	int value = round(1023 * valueB);
	loadB(value);
}

void LTC1661::loUpA(float valueA) {
	int value = round(1023 * valueA);
	loUpA(value);
}

void LTC1661::loUpB(float valueB) {
	int value = round(1023 * valueB);
	loUpB(value);
}

void LTC1661::loUp(float valueIn) {
	int value = round(1023 * valueIn);
	loUp(value);
}

void LTC1661::load(float valueA, float valueB) {
	loadA(valueA);
	loadB(valueB);
}

void LTC1661::loUp(float valueA, float valueB) {
	loUpA(valueA);
	loUpB(valueB);
}

void LTC1661::loadCH(float value, char channel) {
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

void LTC1661::loUpCH(float value, char channel) {
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

//Data as double in Vout/Vref
//if you only write for example loadA(0.9), it will be send as double

void LTC1661::loadA(double valueA) {
	int value = round(1023 * valueA);
	loadA(value);
}

void LTC1661::loadB(double valueB) {
	int value = round(1023 * valueB);
	loadB(value);
}

void LTC1661::loUpA(double valueA) {
	int value = round(1023 * valueA);
	loUpA(value);
}

void LTC1661::loUpB(double valueB) {
	int value = round(1023 * valueB);
	loUpB(value);
}

void LTC1661::loUp(double valueIn) {
	int value = round(1023 * valueIn);
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

void LTC1661::loadCH(double value, char channel) {
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

void LTC1661::loUpCH(double value, char channel) {
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

int LTC1661::getCSPin() {
	return _CS;
}
	