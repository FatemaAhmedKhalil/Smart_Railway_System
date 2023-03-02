/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Armia Khairy ************************************/
/****************************************** Layer: HAL *****************************************/
/****************************************** SWC: Timer *****************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"
#include "RCC_Interface.h"
#include "RCC_Register.h"
#include "TIM_Interface.h"
#include "TIM_Register.h"
#include "GPIO_Interface.h"
#include "TIM_HAL_Interface.h"
#include "TIM_HAL_Config.h"

/**
 * @brief Resets the timer using RCC Peripheral
 * 
 * @param Copy_u8Timer Timer number
 */
void HTIM_voidResetTimer(u8 Copy_u8Timer)
{
	// Assuming Other Functions work the same, This will write only without reading.
    switch (Copy_u8Timer)
    {
        case TIM1:
//      SET_BIT(RCC->APB2RSTR, 0);
//      CLR_BIT(RCC->APB2RSTR, 0);
        RCC->APB2RSTR=1;
        RCC->APB2RSTR=0;
        break;
        case TIM2:
        case TIM3:
        case TIM4:
        case TIM5:
//      SET_BIT(RCC->APB1RSTR, (Copy_u8Timer-2));
//      CLR_BIT(RCC->APB1RSTR, (Copy_u8Timer-2));
        RCC->APB1RSTR=1<<(Copy_u8Timer-2);
        RCC->APB2RSTR=0;
        break;
        case TIM9:
        case TIM10:
        case TIM11:
//      SET_BIT(RCC->APB2RSTR, (Copy_u8Timer+7));
//      CLR_BIT(RCC->APB2RSTR, (Copy_u8Timer+7));
        RCC->APB2RSTR=1<<(Copy_u8Timer-2);
        RCC->APB2RSTR=0;
    }
}


/**
 * @brief This Function Changes ARR and PSC Registers on the run and Updates the shadow registers.
 * 
 * @param Copy_u8Timer Target Timer Number
 * @param Copy_u32AutoReloadValue New AutoReload Value Register
 * @param Copy_u16Prescaler New Prescaler Value
 * @param IsInterruptEnabled If set to 1, This will disable the timer Update Interrupt while inside
 * the function
 */
void HTIM_voidChangeAndUpdateTiming(u8 Copy_u8Timer,u32 Copy_u32AutoReloadValue, u32 Copy_u16Prescaler,u8 IsInterruptEnabled)
{
    // Stop the Timer
    MTIM_voidDisableTimer(Copy_u8Timer);

    // Pre-load New Pre-scale and auto reload values
    MTIM_voidSetPrescaler(Copy_u8Timer, Copy_u16Prescaler);
    MTIM_voidSetAutoReloadValue(Copy_u8Timer, Copy_u32AutoReloadValue);

    // Disables the Pending flag if it's decided by the user that is on
    if (IsInterruptEnabled == 1)
        MTIM_voidDisableUpdateInterrupt(Copy_u8Timer);
    
    // Update Shadow Registers without raising the timer's pending flag.
    MTIM_voidUpdateGeneration(Copy_u8Timer);
    MTIM_voidclearUpdateInterrupt(Copy_u8Timer);

    if (IsInterruptEnabled == 1)
        MTIM_voidEnableUpdateInterrupt(Copy_u8Timer);

    // Start the timer
    MTIM_voidEnableTimer(Copy_u8Timer);
}

/**
 * @brief Reset the timer and update its Prescaler and Autoreload registers, then it starts the timer.
 * It's different from `HTIM_voidChangeAndUpdateTiming()` because it resets everything while
 * the other does not. 
 * 
 * @param Copy_u8Timer Timer Number.
 * @param Copy_u32AutoReloadValue Auto-Reload Preload Register Value.
 * @param Copy_u16Prescaler Prescaler preload register Value.
 */
void HTIM_voidResetAndUpdateTiming(u8 Copy_u8Timer,u32 Copy_u32AutoReloadValue, u32 Copy_u16Prescaler)
{
    HTIM_voidResetTimer(Copy_u8Timer);

    MTIM_voidSetPrescaler(Copy_u8Timer, Copy_u16Prescaler);
    MTIM_voidSetAutoReloadValue(Copy_u8Timer, Copy_u32AutoReloadValue);

    MTIM_voidEnableTimer(Copy_u8Timer);
}

/**
 * @brief Halts the system for a given input period, and it's is interruptable.
 * Note that it will change The Direction of the timer to DownCounting and Enables
 * then Disables One Pulse Mode, make Sure the interrupt for this input timer is
 * disabled.
 * 
 * @param Copy_u8Timer          Timer Number
 * @param Copy_u32Milliseconds  Halt Time in Milliseconds.
 */
void HTIM_voidDelayMilliseconds(u8 Copy_u8Timer, u32 Copy_u32Milliseconds)
{
    HTIM_voidChangeAndUpdateTiming(Copy_u8Timer, Copy_u32Milliseconds, HTIM_APB1_PSC_1KHZ, 0);

    while(MTIM_u8ReadUpdateInterrupt(Copy_u8Timer) == 0)
    {
        asm("NOP");
    }

    MTIM_voidDisableTimer(Copy_u8Timer);
    MTIM_voidclearUpdateInterrupt(Copy_u8Timer);
}
