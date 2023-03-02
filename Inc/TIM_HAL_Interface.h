/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Armia Khairy ************************************/
/****************************************** Layer: HAL *****************************************/
/****************************************** SWC: Timer *****************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef TIM_HAL_INTERFACE_H_
#define TIM_HAL_INTERFACE_H_

void HTIM_voidResetTimer(u8 Copy_u8Timer);
void HTIM_voidChangeAndUpdateTiming(u8 Copy_u8Timer,u32 Copy_u32AutoReloadValue, u32 Copy_u16Prescaler, u8 IsInterruptEnabled);
void HTIM_voidResetAndUpdateTiming(u8 Copy_u8Timer,u32 Copy_u32AutoReloadValue, u32 Copy_u16Prescaler);
void HTIM_voidDelayMilliseconds(u8 Copy_u8Timer, u32 Copy_u32Milliseconds);

#endif
