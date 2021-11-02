/*
 * SevenSegment_Program.c
 *
 *  Created on: 20 Oct 2021
 *      Author: Viro
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SevenSegment_Interface.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "Project.h"
#include <util/delay.h>


void SevenSegment_INIT (void)
{
	// seven segment initialisation
	DIO_u8SetPinDirection(DIO_PIN4 , DIO_PORTA , PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN5 , DIO_PORTA , PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN6 , DIO_PORTA , PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN7 , DIO_PORTA , PIN_OUTPUT);

	DIO_u8SetPinDirection(DIO_PIN0 , DIO_PORTB , PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN1 , DIO_PORTB , PIN_OUTPUT);
}
void SevenSegment_ON (void)
{
	u8 Mode = Return_Mode();
	if (Mode ==1)
	{
		DIO_u8SetPinValue(DIO_PIN0 , DIO_PORTB , PIN_HIGH);
		DIO_u8SetPinValue(DIO_PIN1 , DIO_PORTB , PIN_HIGH);
	}

}
void SevenSegment_OFF (void)
{
	DIO_u8SetPinValue(DIO_PIN0 , DIO_PORTB , PIN_LOW);
	DIO_u8SetPinValue(DIO_PIN1 , DIO_PORTB , PIN_LOW);
}

void Send_Number(u8 Copy_u8Number)
{
	for(u8 i=0 ; i<20 ; i++)
	{
		u8 Tenth  , unit ;

		unit = Copy_u8Number%10 ;
		Tenth = (Copy_u8Number - unit)/10 ;

		SET_BIT(PORTB , 0);
		SET_BIT(PORTB , 1);
		Tenth<<= 4;
//		DIO_u8SetPortValue(DIO_PORTA , Tenth);
		PORTA &= 0x0F;
		PORTA |= Tenth;
		CLR_BIT(PORTB , 0);
		SET_BIT(PORTB , 1);
		_delay_ms(10);
		SET_BIT(PORTB , 0);
		CLR_BIT(PORTB , 1);
		unit<<= 4;
//		DIO_u8SetPortValue(DIO_PORTA , unit);
		PORTA &= 0x0F;
		PORTA |= unit;
		_delay_ms(10);
		SET_BIT(PORTB , 0);
		SET_BIT(PORTB , 1);
	}

}
