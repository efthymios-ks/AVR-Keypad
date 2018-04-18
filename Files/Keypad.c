#include "Keypad.h"

//----- Auxiliary data -----------
volatile char __KP_ISR_Buffer[Keypad_ISR_Max];

#if (Keypad_Size == 33)
	#define __Keypad_Rows		3
	#define __Keypad_Columns	3
#elif (Keypad_Size == 43)
	#define __Keypad_Rows		4
	#define __Keypad_Columns	3
#elif (Keypad_Size == 44)
	#define __Keypad_Rows		4
	#define __Keypad_Columns	4
#endif

#if (Keypad_Size == 43)
	const char __KP_Map[4][4] PROGMEM =
	{
		{Key_1, Key_2, Key_3, Key_None},
		{Key_4, Key_5, Key_6, Key_None},
		{Key_7, Key_8, Key_9, Key_None},
		{Key_E, Key_0, Key_F, Key_None}
	};
#elif ((Keypad_Size == 33) || (Keypad_Size == 44))
	const char __KP_Map[4][4] PROGMEM =
	{
		{Key_1, Key_2, Key_3, Key_A},
		{Key_4, Key_5, Key_6, Key_B},
		{Key_7, Key_8, Key_9, Key_C},
		{Key_E, Key_0, Key_F, Key_D}
	};
#endif
//--------------------------------

//----- Prototypes -----------------//
static uint8_t ReadRows(void);
static uint8_t ReadColumns(void);
static void ToggleRC(void);
//----------------------------------//

//----- Functions ------------------------//
//Setup for keypad. 
void KP_Setup(void)
{
	//Input rows
	PinMode(Keypad_R0, Input);
	PinMode(Keypad_R1, Input);
	PinMode(Keypad_R2, Input);
	#if (__Keypad_Rows == 4)
		PinMode(Keypad_R3, Input);
	#endif
	
	//Output columns
	PinMode(Keypad_C0, Output);
	PinMode(Keypad_C1, Output);
	PinMode(Keypad_C2, Output);
	#if (__Keypad_Columns == 4)
		PinMode(Keypad_C3, Output);
	#endif
	
	//Pull-up resistor rows
	DigitalWrite(Keypad_R0, High);
	DigitalWrite(Keypad_R1, High);
	DigitalWrite(Keypad_R2, High);
	#if (__Keypad_Rows == 4)
		DigitalWrite(Keypad_R3, High);
	#endif
	
	//Low level outputs
	DigitalWrite(Keypad_C0, Low);
	DigitalWrite(Keypad_C1, Low);
	DigitalWrite(Keypad_C2, Low);
	#if (__Keypad_Columns == 4)
		DigitalWrite(Keypad_C3, Low);
	#endif
}

//Update keypad buffer for debouncing, if used. Must be called in timer ISR.
void KP_ISR(void)
{
	volatile static uint8_t i = 0;
	
	__KP_ISR_Buffer[i++] = KP_GetKey();
	
	if (i >= Keypad_ISR_Max)
		i = 0;
}

//Read key from keypad without debounce. Returns Key_0 to Key_F. 
enum KeypadKey_t KP_GetKey(void)
{
	volatile enum KeypadKey_t key = Key_None;
	volatile uint8_t r, c;
	r = c = 0;
	
	//1. Check if button is pressed
	//Get rows' status
	r = ~ReadRows();
	if (r)
	{
		//Get columns' status
		ToggleRC();
		c = ~ReadColumns();
		ToggleRC();
		
		//2. Find the row
		if (BitCheck(r, 0))
			r = 0;
		else if (BitCheck(r, 1))
			r = 1;
		else if (BitCheck(r, 2))
		r = 2;
		#if (__Keypad_Rows ==  4)
			else if (BitCheck(r, 3))
				r = 3;
		#endif
		
		//3. Find the column
		if (BitCheck(c, 4))
			c = 0;
		else if (BitCheck(c, 5))
			c = 1;
		else if (BitCheck(c, 6))
			c = 2;
		#if (__Keypad_Columns == 4)
			else if (BitCheck(c, 7))
				c = 3;
		#endif
		
		//Read key from keypad map
		key = pgm_read_byte(&(__KP_Map[r][c]));
	}
	
	return key;
}

//Check if key is pressed. Returns Key_Pressed or Key_None. 
enum KeypadKey_t KP_KeyPressed(void)
{
	//Read port
	uint8_t port = ~ReadRows();
	
	//If port has any value, then a key was pressed
	if (port)
		port = Key_Pressed;

	return (enum KeypadKey_t)(port);
}

//Wait until no key is held. 
void KP_WaitRelease(void)
{
	while (KP_KeyPressed() != Key_None);
}

//Read debounced key from keypad buffer. Returns Key_0 to Key_F. 
enum KeypadKey_t KP_GetKeyISR(void)
{
	uint8_t i;
	enum KeypadKey_t key = __KP_ISR_Buffer[0];

	//Compare all elements
	for (i = (Keypad_ISR_Max - 1); i >= 1; i--)
		if (__KP_ISR_Buffer[i] != key)
		{
			key = Key_None;
			break;
		}
	
	return key;
}

//Check keypad buffer for any key pressed. Returns Key_Pressed or Key_None. 
enum KeypadKey_t KP_KeyPressedISR(void)
{
	uint8_t status = Key_None;

	if (KP_GetKeyISR() != Key_None)
		status = Key_Pressed;

	return status;
}

//Wait until keypad buffer holds no key. 
void KP_WaitReleaseISR(void)
{
	while (KP_GetKeyISR() != Key_None);
}

//Read keypad's rows. 
static inline uint8_t ReadRows(void)
{
	volatile uint8_t port = 0xF0;

	//Read each pin to its respected place
	port |= DigitalRead(Keypad_R0);
	port |= DigitalRead(Keypad_R1)<<1;
	port |= DigitalRead(Keypad_R2)<<2;
	#if (__Keypad_Rows == 4)
		port |= DigitalRead(Keypad_R3)<<3;
	#else
		port = BitSet(port, 3);
	#endif
	
	return port;
}

//Read keypad's columns. 
static inline uint8_t ReadColumns(void)
{
	volatile uint8_t port = 0x0F;

	//Read each pin to its respected place
	port |= DigitalRead(Keypad_C0)<<4;
	port |= DigitalRead(Keypad_C1)<<5;
	port |= DigitalRead(Keypad_C2)<<6;
	#if (__Keypad_Columns == 4)
		port |= DigitalRead(Keypad_C3)<<7;
	#else
		port = BitSet(port, 7);
	#endif
	
	return port;
}

//Toggle all keypad pins. 
static void ToggleRC(void)
{
	//Toggle pin mode (Inputs <-> Outputs)
	PinModeToggle(Keypad_R0);
	PinModeToggle(Keypad_R1);
	PinModeToggle(Keypad_R2);
	#if (__Keypad_Rows == 4)
		PinModeToggle(Keypad_R3);
	#endif
	PinModeToggle(Keypad_C0);
	PinModeToggle(Keypad_C1);
	PinModeToggle(Keypad_C2);
	#if (__Keypad_Columns == 4)
		PinModeToggle(Keypad_C3);
	#endif
	
	//Toggle pin level (High <-> Low)
	DigitalLevelToggle(Keypad_R0);
	DigitalLevelToggle(Keypad_R1);
	DigitalLevelToggle(Keypad_R2);
	#if (__Keypad_Rows == 4)
		DigitalLevelToggle(Keypad_R3);
	#endif
	DigitalLevelToggle(Keypad_C0);
	DigitalLevelToggle(Keypad_C1);
	DigitalLevelToggle(Keypad_C2);
	#if (__Keypad_Columns == 4)
		DigitalLevelToggle(Keypad_C3);
	#endif
}
//-----------------------------------------//