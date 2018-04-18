//Headers
#include <avr/interrupt.h>
#include "Keypad.h"

//Prototypes
void Timer0_Setup(void);
ISR(TIMER0_COMP_vect);

int main(void)
{
	//Variables
	volatile char key = Key_None;	//IMPORTANT - If used with interrupt debouncing, must be volatile.

	//Setup
	KP_Setup();						//Setup keypad
	Timer0_Setup();					//Setup timer0 to call interrupt every 1ms @ Fclk = 8MHz
	sei();
		
	//Loop
	while (1 == 1)
	{
		//Read key value from ISR sequence
		key = KP_GetKeyISR();
		
		//If key is pressed
		if (key != Key_None)
		{
			//Print it
			//LCD_GotoXY(5, 0);
			//LCD_PrintChar(key);
			
			//Wait until key is released
			KP_WaitReleaseISR();
		}	
	}
	
	return 0;
}

//Timer0 setup
void Timer0_Setup(void)
{
	OCR0 = 124;
	TCNT0 = 0;
	bitSet(TCCR0, WGM01);
	bitSet(TCCR0, CS01);
	bitSet(TCCR0, CS00);
	bitSet(TIMSK, OCIE0);	
}

//Timer0 interrupt service routine
ISR(TIMER0_COMP_vect)
{
	KP_ISR();
}
