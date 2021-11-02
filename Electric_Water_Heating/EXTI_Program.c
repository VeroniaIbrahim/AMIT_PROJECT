/*
 * EXTI_Program.c
 *
 *  Created on: Sep 12, 2021
 *      Author: vero
 */


#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"EXTI_Private.h"
#include "EXTI_Interface.h"

#define EXTI_FALLING_EDGE        0
#define EXTI_RISING_EDGE         1
#define EXTI_ANY_LOGICAL_CHANGE  2
#define EXTI_LOW_LEVEL           3

void (*CallBackFun0)(void);
void (*CallBackFun1)(void);
void (*CallBackFun2)(void);

void EXTI_voidINT0_Init(void)
{
	/*select Sense Control (Falling edge)*/
	SET_BIT(MCUCR,1);
	CLR_BIT(MCUCR,0);
	/*Enable PIE INT0*/
	SET_BIT(GICR,6);
}
void EXTI_voidINT1_Init(void)
{
	/*select Sense Control (Rising edge)*/
	SET_BIT(MCUCR,2);
	SET_BIT(MCUCR,3);
	/*Enable PIE INT1*/
	SET_BIT(GICR,7);
}
void EXTI_voidINT2_Init(void)
{
	/*select Sense Control (Falling edge)*/
	CLR_BIT(MCUCSR,6); //MCUCSR
	/*Enable PIE INT2*/
	SET_BIT(GICR,5);
}

void EXTI_voidSet_SenseControl(u8 Copy_u8SenseControl)
{
	switch (Copy_u8SenseControl)
	{
	case EXTI_FALLING_EDGE:
		SET_BIT(MCUCR,1);
		CLR_BIT(MCUCR,0);
		break;

	case EXTI_RISING_EDGE:
		SET_BIT(MCUCR,2);
		SET_BIT(MCUCR,3);
		break;

	case EXTI_ANY_LOGICAL_CHANGE:
		CLR_BIT(MCUCR,1);
		SET_BIT(MCUCR,3);
		break;

	case EXTI_LOW_LEVEL:
		CLR_BIT(MCUCR,1);
		CLR_BIT(MCUCR,0);
		break;
	default:
		break;

	}
}

void EXT0_voidSet_CallBackFunction(void(*Copy_voidP_CallBackFun)(void))
{
	CallBackFun0=Copy_voidP_CallBackFun;
}
void EXT1_voidSet_CallBackFunction(void(*Copy_voidP_CallBackFun)(void))
{
	CallBackFun1=Copy_voidP_CallBackFun;
}
void EXT2_voidSet_CallBackFunction(void(*Copy_voidP_CallBackFun)(void))
{
	CallBackFun2=Copy_voidP_CallBackFun;
}
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	CallBackFun0();
}
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	CallBackFun1();
}
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	CallBackFun2();
}

