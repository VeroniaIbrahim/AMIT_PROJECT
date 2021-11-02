/*
 * ON_OFF_Button_Program.c
 *
 *  Created on: 20 Oct 2021
 *      Author: Viro
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ON_OFF_Button_Interface.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"
#include<util/delay.h>


u8 INC_5_BUTTON(u8 Copy_u8LastValue)
{
	u8 NewNumber = 5;
	if (Copy_u8LastValue > 0 && Copy_u8LastValue < 95)
	{
		NewNumber = Copy_u8LastValue+5;
	}
	else
	{
		//nothing
	}

	return NewNumber;
}
u8 DEC_5_BUTTON(u8 Copy_u8LastValue)
{
	u8 NewNumber = 99;
	if (Copy_u8LastValue >=5 && Copy_u8LastValue <= 99)
	{
		NewNumber = Copy_u8LastValue-5;
	}
	else
	{
		//nothing
	}
	return NewNumber;
}
