#ifndef KEYPAD_SETTINGS_H_INCLUDED
#define KEYPAD_SETTINGS_H_INCLUDED
/*
||
||  Filename:	 		KEYPAD_Settings.h
||  Title: 			    Keypad Driver
||  Author: 			Efthymios Koktsidis
||	Email:				efthymios.ks@gmail.com
||  Compiler:		 	AVR-GCC
||	Description:		
||	Settings for the keypad driver. Pick the keypad size 
||	and the pinout. 
||								 Keypad Layouts
||				 4x4                   4x3                 3x3
||			[1] [2] [3] [A]		||	[1] [2] [3]		||	[1] [2] [3]
||			[4] [5] [6] [B]		||	[4] [5] [6]		||	[4] [5] [6]
||			[7] [8] [9] [C]		||	[7] [8] [9]		||	[7] [8] [9]
||			[E] [0] [F] [E]		||	[E] [0] [F]		||
||	Code:		  44					43					33
||
*/

//----- Configuration --------------------------//
//Keypad size
#define Keypad_Size			44

//ISR debounce states (1 <= x <= 255)
#define Keypad_ISR_Max		10

//PORT, PIN
#define Keypad_R0			B, 0
#define Keypad_R1			B, 1
#define Keypad_R2			B, 2
#define Keypad_R3			B, 3
#define Keypad_C0			B, 4
#define Keypad_C1			B, 5
#define Keypad_C2			B, 6
#define Keypad_C3			B, 7
//----------------------------------------------//
#endif