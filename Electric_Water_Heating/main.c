/*
 * main.c
 *
 *  Created on: 20 Oct 2021
 *      Author: Viro
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "SevenSegment_Interface.h"
#include "ON_OFF_Button_Interface.h"
#include "TWI_Interface.h"
#include "EEPROM_Interface.h"
#include "ADC_Interface.h"
#include "GIE_Interface.h"
#include "EXTI_Interface.h"
#include "TIMER_Config.h"
#include "TIMER1_Config.h"
#include "TIMER1_Interface.h"
#include "ADC_Config.h"
#include "ADC_Interface.h"
#include "Project.h"
#include "TIMER_Interface.h"



int main (void)
{

	project_init();
	EEPROM_Init();
	u8 SensorReading;
	u8 SetTemp;
	while(1)
	{
		SensorReading = Return_ReadingOfSensor();
		SetTemp = Return_SetTemp();
		compare_temp(SetTemp , SensorReading);
		EEPROM_Read_Byte(0,&SetTemp);
	}
	return 0;
}





