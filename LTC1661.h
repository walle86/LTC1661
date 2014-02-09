/* 
	LTC1661.h - Arduino Library for Linear Technology LTC1661CN8 10bit dual DAC
	Created by Stefan Wallnoefer, Feb 8, 2014.
	Copyright (c) 2014 Stefan Wallnoefer(walle86) under The MIT License (MIT)
	
	This Library provides functions to set both outputs of the LTC1661
	
*/

#ifndef LTC1661_h
#define LTC1661_h

#include <SPI.h>
#include <Arduino.h>

//Controle Functions
#define LOADA		0x10		//Load Input Register A with Data, DAC Outputs Unchanged, Power-Down Status Unchanged
#define LOADB		0x20		//Load Input Register B with Data, DAC Outputs Unchanged, Power-Down Status Unchanged
#define UPDATE	0x80		//Load Both DAC Regs with Existing Contents of Input Regs, Outputs Update, Part Wakes Up
#define LOUPA		0x90		//Load Input Reg A, Load DAC Regs with New Contents of Input Reg A and Existing Contents of Reg B, Outputs Update, Part Wakes Up
#define LOUPB		0xA0		//Load Input Reg B, Load DAC Regs with Existing Contents of Input Reg A and New Contents of Reg B, Outputs Update, Part Wakes Up
#define WAKE		0xD0		//Part Wakes Up, Input and DAC Regs Unchanged, DAC Outputs Reflect Existing Contents of DAC Regs
#define SLEEP		0xE0		//Goes to Sleep, Input and DAC Regs Unchanged, DAC Outputs Set to High Impedance State
#define LOUP		0xF0		//Load Both Input Regs, Load Both DAC Regs with New Contents of Input Regs. Outputs Update, Part Wakes Up

class LTC1661
{
	public:
		//constructor
		LTC1661(int CS);
		
		//controll Commands
		void sleep();
		void wakeUp();
		void update();
		
		//Data as int
		void loadA(int valueA);
		void loadB(int valueB);
		void loUpA(int valueA);
		void loUpB(int valueB);
		void loUp(int value);
		void load(int valueA, int valueB);
		void loUp(int valueA, int valueB);
		void loadCH(int value, char channel);
		void loUpCH(int value, char channel);
		
		//Data as float 0...1 in Vout/Vref
		void loadA(float valueA);
		void loadB(float valueB);
		void loUpA(float valueA);
		void loUpB(float valueB);
		void loUp(float valueIn);
		void load(float valueA, float valueB);
		void loUp(float valueA, float valueB);
		void loadCH(float value, char channel);
		void loUpCH(float value, char channel);
		
		//Data as double 0...1 in Vout/Vref
		void loadA(double valueA);
		void loadB(double valueB);
		void loUpA(double valueA);
		void loUpB(double valueB);
		void loUp(double valueIn);
		void load(double valueA, double valueB);
		void loUp(double valueA, double valueB);
		void loadCH(double value, char channel);
		void loUpCH(double value, char channel);
		
		//other stuff
		int getCSPin();
			
	private:
		int _CS;
};

#endif
	