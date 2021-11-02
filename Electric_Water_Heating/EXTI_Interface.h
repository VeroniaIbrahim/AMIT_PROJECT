/*
 * EXTI_Interface.h
 *
 *  Created on: Sep 12, 2021
 *      Author: vero
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

void EXTI_voidINT0_Init(void);
void EXTI_voidINT1_Init(void);
void EXTI_voidINT2_Init(void);
void EXTI_voidSet_SenseControl(u8 Copy_u8SenseControl);
void EXT0_voidSet_CallBackFunction(void(*Copy_voidP_CallBackFun)(void));
void EXT1_voidSet_CallBackFunction(void(*Copy_voidP_CallBackFun)(void));
void EXT2_voidSet_CallBackFunction(void(*Copy_voidP_CallBackFun)(void));



#endif /* EXTI_INTERFACE_H_ */

