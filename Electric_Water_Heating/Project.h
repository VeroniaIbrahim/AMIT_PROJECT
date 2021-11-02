/*
 * Project.h
 *
 *  Created on: 21 Oct 2021
 *      Author: Viro
 */

#ifndef PROJECT_H_
#define PROJECT_H_


void project_init 			   (void);
void Temp_Setting_Mode         (void);
void Heater_ON                 (void);
void Heater_OFF                (void);
void CoolingElement_ON         (void);
void CoolingElement_OFF 	   (void);
void Toggle_led 			   (void);
void Button_APP 			   (void);
void UP_Button 				   (void);
void DOWN_Button 			   (void);
void ADC_SensorTemperature     (void);
void Timer1_Interrupt_Function (void);
void Save_SetTemp_To_EEPROM    (u8 Copy_u8SetTemp);
void   SevenSegmenet_Blink     (void);
u8   Return_ReadingOfSensor    (void);
u8   Return_SetTemp            (void);
u8   Return_Mode(void);
void compare_temp              (u8 Copy_u8SetTemp , u8 Copy_u8SensedTemp);


#endif /* PROJECT_H_ */
