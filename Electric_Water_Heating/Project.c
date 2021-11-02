/*
 * Project.c
 *
 *  Created on: 21 Oct 2021
 *      Author: Viro
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"
#include "SevenSegment_Interface.h"
#include "ON_OFF_Button_Interface.h"
#include "EEPROM_Interface.h"
#include "EXTI_Interface.h"
#include "Project.h"
#include "GIE_Interface.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"
#include "TIMER_Config.h"
#include "TIMER_Interface.h"
#include "TIMER1_Config.h"
#include "TIMER1_Interface.h"
#include "ADC_Config.h"
#include "ADC_Interface.h"
#include <util/delay.h>

u8  SetTemp       = 60;
u8  UpButton      = 1 ;
u8  DownButton    = 1 ;
u8  ON_OFF_Button = 1 ;
u8  LastState_1   = 0 ;
u8  LastState_2   = 0 ;
u8  Flag;
u8  TempDisp=0;
u8  Mode = 0;
u8 Display_num;
u16 Flag1 =0;
f32 Sensor_Reading=0;





void project_init (void)
{
	//BUTTON INITIALISATION
	DIO_u8SetPinDirection(DIO_PIN5 , DIO_PORTD , PIN_INPUT);
	DIO_u8SetPinDirection(DIO_PIN6 , DIO_PORTD , PIN_INPUT);

	//PULLUP BUTTONS
	DIO_u8SetPinValue(DIO_PIN5 , DIO_PORTD , PIN_HIGH);
	DIO_u8SetPinValue(DIO_PIN6 , DIO_PORTD , PIN_HIGH);
	DIO_u8SetPinValue(DIO_PIN2 , DIO_PORTB , PIN_HIGH);

	//Set EXT0 PIN as an interrupt
	DIO_u8SetPinDirection(DIO_PIN2 , DIO_PORTD , PIN_INPUT);
	EXT0_voidSet_CallBackFunction(&UP_Button);
	EXTI_voidINT0_Init();

	//Set EXT1 PIN as an interrupt
	DIO_u8SetPinDirection(DIO_PIN3 , DIO_PORTD , PIN_INPUT);
	EXT1_voidSet_CallBackFunction(&DOWN_Button);
	EXTI_voidINT1_Init();

	//Set EXT2 PIN as an interrupt
	DIO_u8SetPinDirection(DIO_PIN2 , DIO_PORTB , PIN_INPUT);
	EXT2_voidSet_CallBackFunction(&Button_APP);
	EXTI_voidINT2_Init();

	//EEPROM AND TWI
//	EEPROM_Init();

	//LED
	DIO_u8SetPinDirection(DIO_PIN7 , DIO_PORTC , PIN_OUTPUT);
	DIO_u8SetPinValue(DIO_PIN7 , DIO_PORTC , PIN_LOW);
	DIO_u8SetPinDirection(DIO_PIN2 , DIO_PORTC , PIN_OUTPUT);
	DIO_u8SetPinValue(DIO_PIN2 , DIO_PORTC , PIN_LOW);

	//fan
	DIO_u8SetPinDirection(DIO_PIN1 , DIO_PORTA , PIN_OUTPUT);

	//heater
	DIO_u8SetPinDirection(DIO_PIN4 , DIO_PORTD , PIN_OUTPUT);

	//init test LED
	DIO_u8SetPinDirection(DIO_PIN4,DIO_PORTB,PIN_OUTPUT);

	//Enable timer led
	DIO_u8SetPinDirection(DIO_PIN5,DIO_PORTD,PIN_OUTPUT);

	SevenSegment_INIT();

	//Timer0 Initialisation
	//TIMER0_voidSet_CallBackFunction(&Temp_Setting_Mode);
	TIMER0_voidSetCTCValue(100);
	TIMER0_voidInit();

	//Timer1 Initialisation
	TIMER1_voidCallBackFunction(&Timer1_Interrupt_Function);
	TIMER1_voidSetOCR1AValue(150);
	TIMER1_voidInit();

	//ADC Initialisation
	ADC_voidSet_CallBackFunction(&ADC_SensorTemperature);
	ADC_voidInit_Interrupt();

	//ENABLE GLOBAL INTERRUPT
	GIE_voidEnable();

}

void Temp_Setting_Mode(void)
{
//	u8 de7k = SetTemp;
//	ADC_INTERRUPT_DISABLE();
//	Send_Number(de7k);
//	SevenSegment_OFF();
//	_delay_ms(500);
//
//	Send_Number(de7k);
//	_delay_ms(500);
//	SevenSegment_OFF();
//	_delay_ms(500);
//
//	Send_Number(de7k);
//	_delay_ms(500);
//	SevenSegment_OFF();
//	_delay_ms(500);
//
//	Send_Number(de7k);
//	_delay_ms(500);
//
//	SevenSegment_OFF();
//
//		_delay_ms(500);
//		SevenSegment_ON();
//		Send_Number(de7k);
//
//
//	ADC_INTERRUPT_ENABLE();


	if (Mode == 1 )
	{
		if(Flag1==1000) //600 to blink
		{
			DIO_u8SetPinValue(DIO_PIN4,DIO_PORTB,PIN_HIGH);
			_delay_ms(1000);
			Send_Number(SetTemp);
			Flag1=0;
		}
		else
		{
			Flag1++;
			DIO_u8SetPinValue(DIO_PIN4,DIO_PORTB,PIN_LOW);
		}
	}
	else
	{
		//NOTHING
	}
}

void compare_temp (u8 Copy_u8SetTemp , u8 Copy_u8SensedTemp)
{
	if (Mode == 1)
	{
		if (Copy_u8SetTemp > Copy_u8SensedTemp)
		{
			Heater_ON();
			CoolingElement_OFF();
			Toggle_led();
		}
		else if (Copy_u8SetTemp < Copy_u8SensedTemp)
		{
			Heater_OFF();
			CoolingElement_ON();
			DIO_u8SetPinValue(DIO_PIN7 , DIO_PORTC , PIN_HIGH);
		}
		else if (Copy_u8SetTemp == Copy_u8SensedTemp)
		{
			Heater_OFF();
			CoolingElement_OFF();
		}
		else
		{
			//NOTHING
		}
	}
	else{

	}
}
void Toggle_led (void)
{
		DIO_u8SetPinValue(DIO_PIN7 , DIO_PORTC , PIN_HIGH);
		_delay_ms(1000);
		DIO_u8SetPinValue(DIO_PIN7 , DIO_PORTC , PIN_LOW);
		_delay_ms(1000);
}
void Heater_ON (void)
{
	DIO_u8SetPinValue(DIO_PIN4 ,DIO_PORTD,PIN_HIGH);
}
void Heater_OFF (void)
{
	DIO_u8SetPinValue(DIO_PIN4 , DIO_PORTD , PIN_LOW);
}
void CoolingElement_ON (void)
{
	DIO_u8SetPinValue(DIO_PIN1 , DIO_PORTA , PIN_HIGH);
}
void CoolingElement_OFF (void)
{
	DIO_u8SetPinValue(DIO_PIN1 , DIO_PORTA , PIN_LOW);
}

void Button_APP (void)
{
	static u8 Count=1;
	if ((Count%2 == 0)) //OFF
	{
		Heater_OFF();
		CoolingElement_OFF();
		SevenSegment_OFF();
		//SET LED OFF
		DIO_u8SetPinValue(DIO_PIN7 , DIO_PORTC , PIN_LOW);
		EEPROM_Write_Byte(0,SetTemp);
		Flag = 1;
		Mode = 0;
	}
	else if ((Count%2) != 0) //ON
	{
		SevenSegment_ON();
		Send_Number(1);
		Flag = 2;
		Mode = 1;
	}
	Count++ ;
}
void UP_Button (void)
{
	if (Mode ==1)
	{
		Send_Number(SetTemp);
		if ((SetTemp<75)) //limit of temp
		{
			SetTemp=INC_5_BUTTON(SetTemp); //assign to the previous number of set number the new increased value
			Send_Number(SetTemp); //function send the new number to the seven segment
			Temp_Setting_Mode();

		}
		else
		{
			Send_Number(SetTemp);
		}
	}
}

void DOWN_Button (void)
{
	if (Mode==1)
	{
		Send_Number(SetTemp);
		if ((SetTemp>35))
		{
			SetTemp=DEC_5_BUTTON(SetTemp);
			Send_Number(SetTemp);
			Temp_Setting_Mode();

		}
		else
		{
			Send_Number(SetTemp);
		}
	}
}

void ADC_SensorTemperature(void)
{
	/*ya5od 10 aryat w ygib average bt3hom w b3d kda y3mlhom convert*/
	if (Mode == 1)
	{
		u8 Temperature_Ten_Readings[10]={};
		static u8 Count_Readings=0;
		u16 Temp_Total = 0;

		for (Count_Readings=0 ; Count_Readings <10 ;  Count_Readings ++)
		{
			Temperature_Ten_Readings[Count_Readings]=ADC_u16DigitalRead();

			if (Count_Readings ==9)
			{
				for(u8 i=0 ; i<10 ; i++)
				{
					Temp_Total += Temperature_Ten_Readings[i];
				}
				Sensor_Reading = Temp_Total/10;
				Sensor_Reading = (Sensor_Reading/2.074)+1;
			}
		}
	}
}
void Timer1_Interrupt_Function(void)
{
	if (Mode == 1)
	{
		ADC_u16StartConversion_Interrupt(0);
		Send_Number(Sensor_Reading);
	}
}

u8 Return_ReadingOfSensor (void)
{
	return Sensor_Reading;
}

u8 Return_SetTemp (void)
{
	return SetTemp;
}

u8 Return_Mode(void)
{
	return Mode;
}



