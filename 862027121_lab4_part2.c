/*	Author: David MEndez
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


//inputs = pin outputs = port

    /* Insert your solution below */
	enum AddSub_States {AddSub_SMStart, AddSub_Init, AddSub_Hold, AddSub_HoldTwo, AddSub_Zero, AddSub_Current, AddSub_Increment, AddSub_Decrement, AddSub_Reset} AddSub_State;
	
	void TickFct_AddSub(void)
	{//statrt of tick function
		switch(AddSub_State) // transitions
		{ // start of transitions
			case AddSub_SMStart:
				AddSub_State = AddSub_Init;
				break;
			
			case AddSub_Init:
				AddSub_State = AddSub_Hold;
				break;
		
			case AddSub_Hold:
				if (PINA == 0x00)
				{				//start of first if statement
					AddSub_State = AddSub_Hold;
				} 				//end of first if statement
				else if(PINA == 0x01)
				{				//start of second if statement 
					AddSub_State = AddSub_Increment;
				}				//end of secodn if statement
				else if(PINA == 0x02)
				{
					AddSub_State = AddSub_Decrement;
				}
				break;

			case AddSub_Increment:
				//if(PINA == 0x01){
				AddSub_State = AddSub_HoldTwo;
				break;
			
			case AddSub_HoldTwo:
				if(PINA == 0x03){
				AddSub_State = AddSub_Zero;}
				else if(PINA == 0x00)
				{AddSub_State = AddSub_Current;}
				//else if(PINA != 0x01){
				//AddSub_State = AddSub_Increment;}
				break;
			
			case AddSub_Zero:
				AddSub_State = AddSub_Current;
				break;

			case AddSub_Current:
				if(PINA == 0x00)
				{AddSub_State = AddSub_Current;}
				else if(PINA == 0x02)
				{AddSub_State = AddSub_Decrement;}
				else if(PINA == 0x01)
				{AddSub_State = AddSub_Increment;}
				break;

			case AddSub_Decrement:
				//if(PINA == 0x02){
				AddSub_State = AddSub_HoldTwo;
				break;

			//case AddSub_Reset:
			//	AddSub_State = AddSub_Hold;
			//	break;
			default:
				AddSub_State  = AddSub_SMStart;
				break;
		} //end of transitions

		switch(AddSub_State)
		{ // statrt of state actions
			case AddSub_SMStart:
				//PORTC = 0x00;
				break;
			
			case AddSub_Init:
				//PORTC = 0x00;
				break;
			
			case AddSub_Hold: 
				//PORTC = PORTC;
				PORTC = 0x07;
				break;

			case AddSub_HoldTwo:
				//PORTC = PORTC;
				break;

			case AddSub_Zero:
				PORTC = 0x00;
				break;

			case AddSub_Current:
				//PORTC = PORTC;
				break;

			case AddSub_Increment:
				if(PORTC <= 0x08){
				PORTC = PORTC + 1;}
				//else {PORTC = PORTC;}
				break;

			case AddSub_Decrement:
				if(PORTC > 0x01){
				PORTC = PORTC - 1;}
				//else {PORTC = PORTC;}
				break;
		
			//case AddSub_Reset:	
			//	PORTC = 0x00;
			//	break;
					
			default:
				break;
		} // end of state actions
	}// end of tick function
int main() 
{
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //inputs
	DDRC = 0xFF; PORTC = 0x00; //outputs
   	
		PORTC = 0x07;	
		AddSub_State = AddSub_SMStart;
    		
		while (1) 
		{            
			TickFct_AddSub();
		}
return 1;
}

