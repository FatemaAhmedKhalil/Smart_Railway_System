/***********************************************************************************************/
/***********************************************************************************************/
/************************************** Author: Armia Khairy ***********************************/
/****************************************** Layer: MCAL ****************************************/
/***************************************** SWC: Timer ******************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"
#include <TIM_Register.h>
#include <TIM_Private.h>
#include <TIM_Interface.h>

/**
 * @brief Error Codes are the following
 * 0            : Success
 * 1            : Invalid Timer Choice in Write Mode
 * [~1] : Invalid Timer Choice in Read  Mode
 * 2            : Wrong Value to enter
 */
const u32 _TIM_ARR[]=	{_RSVD,
					  	 TIM1_StartAddress, TIM2_StartAddress, TIM3_StartAddress,
						 TIM4_StartAddress, TIM5_StartAddress,_RSVD,_RSVD,_RSVD,
					  	 TIM9_StartAddress, TIM10_StartAddress, TIM11_StartAddress}; // Private Global Variables

/**
 * @brief Reads Associated Timer's Current counting value 
 * 
 * @param Copy_u8Timer Associated Timer Value
 * @return u32 value of the timer, it's 16 bit except for timer 5
 */
force_inline u32 MTIM_u32ReadCounterValue(u8 Copy_u8Timer)
{
	return TIM(Copy_u8Timer)->CNT;
}

force_inline void MTIM_voidResetCounterValue(u8 Copy_u8Timer)
{
	TIM(Copy_u8Timer)->CNT = 0;
}

force_inline void MTIM_voidSetPrescaler(u8 Copy_u8Timer, u32 Copy_PrescalerValue)
{
	TIM(Copy_u8Timer)->PSC = Copy_PrescalerValue;
}

force_inline void MTIM_voidSetAutoReloadValue(u8 Copy_u8Timer, u32 Copy_AutoReloadValue)
{
	TIM(Copy_u8Timer)->ARR = Copy_AutoReloadValue;
}

/*** CR1 Register Configs ***/
// CEN
/**
 * @brief Enables the associated timer from CEN Bit in CR1 Register.
 * 
 * @param Copy_u8Timer Associated Timer
 * @return u8 Error code
 */
force_inline void MTIM_voidEnableTimer(u8 Copy_u8Timer)
{
	SET_BIT(TIM(Copy_u8Timer)->CR1, 0);
}

force_inline void MTIM_voidDisableTimer(u8 Copy_u8Timer)
{
	CLR_BIT(TIM(Copy_u8Timer)->CR1, 0);
}

// UDIS
force_inline void MTIM_voidDisableUpdateEvent(u8 Copy_u8Timer)
{
	SET_BIT(TIM(Copy_u8Timer)->CR1, 1);
}

force_inline void MTIM_voidEnableUpdateEvent(u8 Copy_u8Timer)
{
	CLR_BIT(TIM(Copy_u8Timer)->CR1, 1);
}

// URS
void MTIM_voidChangeUpdateRequestSource(u8 Copy_u8Timer, u8 Copy_u8Source)
{
	if (Copy_u8Source==0)
		CLR_BIT(TIM(Copy_u8Timer)->CR1,2);
	else
		SET_BIT(TIM(Copy_u8Timer)->CR1,2);
}

// OPM
force_inline void MTIM_voidEnableOnePulseMode(u8 Copy_u8Timer)
{
	SET_BIT(TIM(Copy_u8Timer)->CR1,3);
}

force_inline void MTIM_voidDisableOnePulseMode(u8 Copy_u8Timer)
{
	CLR_BIT(TIM(Copy_u8Timer)->CR1,3);
}

// DIR
void MTIM_voidSetDirection(u8 Copy_u8Timer, u8 Copy_u8Direction)
{
	switch (Copy_u8Direction)
	{
		case TIM_DIR_UP:
		CLR_BIT(TIM(Copy_u8Timer)->CR1,4);
		break;

		case TIM_DIR_DOWN:
		SET_BIT(TIM(Copy_u8Timer)->CR1,4);
		break;
	}
}

// ARPE
force_inline void MTIM_voidEnableAutoReloadPreload(u8 Copy_u8Timer)
{
	SET_BIT(TIM(Copy_u8Timer)->CR1, 7);
}

force_inline void MTIM_voidDisableAutoReloadPreload(u8 Copy_u8Timer)
{
	SET_BIT(TIM(Copy_u8Timer)->CR1, 7);
}

// CKD
/**
 * @brief Set Clock Division Mode
 * 
 * @param Copy_u8Timer Assosiated Timer Number.
 * @param Copy_u8Mode Options=[TIM_CDV_1=0b00, TIM_CDV_2=0b01, TIM_CDV_4=0b10]
 * @return Error code
 */
force_inline void MTIM_voidSetClockDivisionMode(u8 Copy_u8Timer,u32 Copy_u8Mode)
{
	TIM(Copy_u8Timer)->CR1 |= Copy_u8Mode << 8; 
}

/**
 * @brief Enables Associated timer's Update interrupt flag by setting
 * UIE bit in DIER.
 * 
 * @param Copy_u8Timer 
 * @return u8 Error code
 */
force_inline void MTIM_voidEnableUpdateInterrupt(u8 Copy_u8Timer)
{
	SET_BIT(TIM(Copy_u8Timer)->DIER,0);
}

/**
 * @brief Disables Associated timer's Update interrupt flag by clearing
 * UIE bit in DIER.
 * 
 * @param Copy_u8Timer Associated Timer
 * @return u8 Error code
 */
force_inline void MTIM_voidDisableUpdateInterrupt(u8 Copy_u8Timer)
{
	CLR_BIT(TIM(Copy_u8Timer)->DIER,0);
}

/**
 * @brief Generates an Update Event in the Timer. Can be used for
 * Updating the shadow registers with its preloaded values and 
 * resetting the counter.
 * @param Copy_u8Timer Associated Timer
 * @return u8 Error code.
 */
force_inline void MTIM_voidUpdateGeneration(u8 Copy_u8Timer)
{
	SET_BIT(TIM(Copy_u8Timer)->EGR, 0);
}

force_inline void MTIM_voidclearUpdateInterrupt(u8 Copy_u8Timer)
{
	CLR_BIT(TIM(Copy_u8Timer)->SR, 0);
}

force_inline u8 MTIM_u8ReadUpdateInterrupt(u8 Copy_u8Timer)
{
	return GET_BIT(TIM(Copy_u8Timer)->SR, 0);
}

//**** Private Functions ****//
// u32 TimerBaseAddress(u8 Copy_TimerNumber)
// {
//     switch (Copy_TimerNumber)
//     {
//     case TIM1 :  return TIM1_StartAddress ;
//     case TIM2 :  return TIM2_StartAddress ;
//     case TIM3 :  return TIM3_StartAddress ;
//     case TIM4 :  return TIM4_StartAddress ;
//     case TIM5 :  return TIM5_StartAddress ;
//     case TIM9 :  return TIM9_StartAddress ;
//     case TIM10:  return TIM10_StartAddress;
//     case TIM11:  return TIM11_StartAddress;
//     }
//     return 0;
// }
