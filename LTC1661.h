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

#ifndef LTC1661_h
#define LTC1661_h

#include <SPI.h>
#include <Arduino.h>

//Controle Functions
#define LOADA		0x1000		//Load Input Register A with Data, DAC Outputs Unchanged, Power-Down Status Unchanged
#define LOADB		0x2000		//Load Input Register B with Data, DAC Outputs Unchanged, Power-Down Status Unchanged
#define UPDATE	0x8000		//Load Both DAC Regs with Existing Contents of Input Regs, Outputs Update, Part Wakes Up
#define LOUPA		0x9000		//Load Input Reg A, Load DAC Regs with New Contents of Input Reg A and Existing Contents of Reg B, Outputs Update, Part Wakes Up
#define LOUPB		0xA000		//Load Input Reg B, Load DAC Regs with Existing Contents of Input Reg A and New Contents of Reg B, Outputs Update, Part Wakes Up
#define WAKE		0xD000		//Part Wakes Up, Input and DAC Regs Unchanged, DAC Outputs Reflect Existing Contents of DAC Regs
#define SLEEP		0xE000		//Goes to Sleep, Input and DAC Regs Unchanged, DAC Outputs Set to High Impedance State
#define LOUP		0xF000		//Load Both Input Regs, Load Both DAC Regs with New Contents of Input Regs. Outputs Update, Part Wakes Up

class LTC1661
{
	public:
		//constructor
		LTC1661();
		LTC1661(int CS);
		LTC1661(int DIN, int SCK);
		LTC1661(int CS, int DIN, int SCK);
		//controll Commands
		void sleep();
		void wakeUp();
		void update();
		
		//digtial Write
		void dWrite(char channel, int state);
		
		//Data as int
		void loadA(int valueA);
		void loadB(int valueB);
		void loUpA(int valueA);
		void loUpB(int valueB);
		void loUp(int value);
		void load(int valueA, int valueB);
		void loUp(int valueA, int valueB);
		void loadCH(char channel, int value);
		void loUpCH(char channel, int value);
		
		//Data as double (also float) 0...1 in Vout/Vref
		void loadA(double valueA);
		void loadB(double valueB);
		void loUpA(double valueA);
		void loUpB(double valueB);
		void loUp(double valueIn);
		void load(double valueA, double valueB);
		void loUp(double valueA, double valueB);
		void loadCH(char channel, double value);
		void loUpCH(char channel, double value);
		
		//other stuff
		int getCSPin();
		void setCSPin(int CS);
			
	private:
		int _CS;
		int _DIN;
		int _SCK;
		boolean _ArduinoSPI;
		int _resolution;
		int _highValue;
		
		void sendData(unsigned int data);
};

#endif