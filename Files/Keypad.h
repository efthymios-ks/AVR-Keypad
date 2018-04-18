#ifndef KEYPAD_H_INCLUDED
#define KEYPAD_H_INCLUDED
/*
||
||  Filename:	 		KEYPAD.h
||  Title: 			    Keypad Driver
||  Author: 			Efthymios Koktsidis
||	Email:				efthymios.ks@gmail.com
||  Compiler:		 	AVR-GCC
||	Description: 
||	This library can drive 3x3, 4x3 and 4x4 keypads.
||
*/

//----- Headers ------------//
#include <inttypes.h> 
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "IO_Macros.h"
#include "Keypad_Settings.h"
//--------------------------//

//----- Auxiliary definitions -----//
enum KeypadKey_t
{
	Key_Pressed	= 0xFF,
	Key_None	= 0x00,
	Key_0		= '0',
	Key_1		= '1',
	Key_2		= '2',
	Key_3		= '3',
	Key_4		= '4',
	Key_5		= '5',
	Key_6		= '6',
	Key_7		= '7',
	Key_8		= '8',
	Key_9		= '9',
	Key_A		= 'A',
	Key_B		= 'B',
	Key_C		= 'C',
	Key_D		= 'D',
	Key_E		= 'E',
	Key_F		= 'F'
};
//---------------------------------//

//----- Declaration of functions --------------//
void KP_Setup(void);
void KP_ISR(void);

enum KeypadKey_t KP_GetKey(void);
enum KeypadKey_t KP_KeyPressed(void);
void KP_WaitRelease(void);

enum KeypadKey_t KP_GetKeyISR(void);
enum KeypadKey_t KP_KeyPressedISR(void);
void KP_WaitReleaseISR(void);
//----------------------------------------------//
#endif