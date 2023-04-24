/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Armia Khairy ************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: Timer *****************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef TIM_INTERFACE_H_
#define TIM_INTERFACE_H_

// Available Timers
#define TIM1    1	//AC, APB2
#define TIM2    2	//GP, APB1
#define TIM3    3	//GP, APB1
#define TIM4    4	//GP, APB1
#define TIM5    5	//GP, APB1
#define TIM9    9	//GP, APB2
#define TIM10   10	//GP, APB2
#define TIM11   11	//GP, APB2

//Direction Mode
#define TIM_DIR_UP   0
#define TIM_DIR_DOWN 1

//Update Interrupt Configuration
#define TIM_URS_OVERFLOW_ONLY   1
#define TIM_URS_DEFAULT         0

/**** Time-Base Unit Registers ****/
// Counter Register
u32 MTIM_u32ReadCounterValue(u8 Copy_u8Timer);
void MTIM_voidResetCounterValue(u8 Copy_u8Timer);

// Pre-scaler Register
void MTIM_voidSetPrescaler(u8 Copy_u8Timer, u32 Copy_PrescalerValue);
u32 MTIM_u32ReadPrescaler(u8 Copy_u8Timer);

// Auto-Reload Register
void MTIM_voidSetAutoReloadValue(u8 Copy_u8Timer, u32 Copy_AutoReloadValue);
u32 MTIM_u32ReadAutoReloadValue(u8 Copy_u8Timer);

// Repetition Counter Register, Exclusive to Advanced TIM1
u32 MTIM_u8ReadRepititionCounter(u8 Copy_u8Timer);
void MTIM_voidSetRepititionValue(u8 Copy_u8Timer, u32 Copy_u8RepititionValue);

/**** Timer Configurations ****/
// CR1 Config
// CEN Bit: Counter Enable
void MTIM_voidEnableTimer(u8 Copy_u8Timer);
void MTIM_voidDisableTimer(u8 Copy_u8Timer);

// UDIS: Update Event Disable
void MTIM_voidEnableUpdateEvent(u8 Copy_u8Timer);
void MTIM_voidDisableUpdateEvent(u8 Copy_u8Timer);

// URS: Update Request Source
void MTIM_voidChangeUpdateRequestSource(u8 Copy_u8Timer, u8 Copy_u8Source);

// OPM: One Pulse Mode
void MTIM_voidEnableOPM(u8 Copy_u8Timer);
void MTIM_voidDisableOPM(u8 Copy_u8Timer);

// DIR: Direction
void MTIM_voidSetDirection(u8 Copy_u8Timer, u8 u8Direction);

// Center-Aligned Mode Selection
void MTIM_voidSetCenterAlighnedMode(u8 Copy_u8Timer);

// ARPE: Auto Reload Pre-load Enable
void MTIM_voidEnableAutoReloadPreload(u8 Copy_u8Timer);
void MTIM_voidDisableAutoReloadPreload(u8 Copy_u8Timer);

// CKD: Clock Division
void MTIM_voidSetClockDivisionMode(u8 Copy_u8Timer, u32 Copy_u8Mode);

// CR2 Config
// SMCR
// Slave Mode Selection
void MTIM_voidSlaveModeSelect(u8 Copy_Timer, u8 Copy_u8Selection);

// Trigger Selection
void MTIM_voidTriggerSelection(u8 Copy_Timer, u8 Copy_u8Selection);

// Master/Slave Mode
// External Trigger Filter
void MTIM_voidSetExternalTriggerFilterMode(u8 Copy_Timer, u8 Copy_u8Selection);

// External Trigger Pre-scaler
void MTIM_voidSetExternalTriggerPrescaler(u8 Copy_Timer, u8 Copy_u8Selection);

// External Clock EnableDisable
void MTIM_voidEnableExternalClock(u8 Copy_Timer);
void MTIM_voidDisableExternalClock(u8 Copy_Timer);

// External Trigger Polarity
void MTIM_voidSetExternalTriggerPolarity(u8 Copy_Timer, u8 Copy_u8Selection);

/**** Interrupts Configurations ****/
// DIER
// Update Interrupt
void MTIM_voidEnableUpdateInterrupt(u8 Copy_u8Timer);
void MTIM_voidDisableUpdateInterrupt(u8 Copy_u8Timer);

// Break Interrupt
void MTIM_voidEnableBreakInterrupt(u8 Copy_u8Timer);
void MTIM_voidDisableBreakInterrupt(u8 Copy_u8Timer);

// Trigger Interrupt
void MTIM_voidEnableTriggerInterrupt(u8 Copy_u8Timer);
void MTIM_voidDisableTriggerInterrupt(u8 Copy_u8Timer);

// TIMx_EGR: Software Event Generation
void MTIM_voidUpdateGeneration(u8 Copy_u8Timer);
void MTIM_voidTriggerGeneration(u8 Copy_u8Timer);
void MTIM_voidBreakGeneration(u8 Copy_u8Timer);

// SR: Status Register
u8 MTIM_u8ReadUpdateInterrupt(u8 Copy_u8Timer);
void MTIM_voidclearUpdateInterrupt(u8 Copy_u8Timer);

u8 MTIM_u8ReadBreakInterrupt(u8 Copy_u8Timer);
void MTIM_voidclearBreakInterrupt(u8 Copy_u8Timer);

u8 MTIM_u8ReadTriggerInterrupt(u8 Copy_u8Timer);
void MTIM_voidclearTriggerInterrupt(u8 Copy_u8Timer);

#endif
