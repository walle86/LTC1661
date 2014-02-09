LTC1661
=======

Adruino Library for Linear Technology LTC1661 10bit dual DAC
Created by Stefan Wallnoefer, January 9, 2014.

This Library provides functions to set both (VOUT A and VOUT B) outputs of the LTC1661

Functions:

	LTC1661(CS): constructor, Chipselctpin as argument
	
	sleep(): Goes to Sleep, Input and DAC Regs Unchanged, DAC Outputs Set to High Impedance State
	wakeUp(): Part Wakes Up, Input and DAC Regs Unchanged, DAC Outputs Reflect Existing Contents of DAC Regs
	update(): Load Both DAC Regs with Existing Contents of Input Regs, Outputs Update, Part Wakes Up

	
	Variables for all functions:
		value of type int (0...1023) or float/double (0...1.0)
		channel of type char ('A' or 'B') or int (0 or 1)
	loadA(value): Load Input Register A with Data, DAC Outputs Unchanged, Power-Down Status Unchanged
	loadB(value): Load Input Register B with Data, DAC Outputs Unchanged, Power-Down Status Unchanged
	loUpA(value): Load Input Reg A, Load DAC Regs with New Contents of Input Reg A and Existing Contents of Reg B, Outputs Update, Part Wakes Up
	loUpB(value): Load Input Reg B, Load DAC Regs with New Contents of Input Reg B and Existing Contents of Reg A, Outputs Update, Part Wakes Up
	loUp(value):  Load Both Input Regs with same Data, Load Both DAC Regs with New Contents of Input Regs. Outputs Update, Part Wakes Up
	load(valueA, valueB): Load Both Input Regs with diffrent Data ,DAC Outputs Unchanged, Power-Down Status Unchanged
	loUp(valueA, valueB): Load Both Input Regs with diffrent Data, Load Both DAC Regs with New Contents of Input Regs. Outputs Update, Part Wakes Up
	loadCH(value, channel): Load Input Register of selcted Channel with Data, DAC Outputs Unchanged, Power-Down Status Unchanged
	loUpCH(value, channel): Load Input Reg of selcted Channel, Load DAC Regs with New Contents of Input Reg of selcted Channel and Existing Contents of Reg of the other Channel, 
	                        Outputs Update, Part Wakes Up


Copyright (c) 2014 Stefan Wallnoefer(walle86) under The MIT License (MIT)