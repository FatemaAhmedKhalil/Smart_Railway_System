/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Armia Khairy ************************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: Timer *****************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef TIM_REGISTERS_H_
#define TIM_REGISTERS_H_

//==Start Addresses

//Advanced Control Timers
//Connected to APB2 Bus
#define TIM1_StartAddress	0x40010000 

//=General Purpose Timers
//Connected to APB1 Bus
#define TIM2_StartAddress	0x40000000
#define TIM3_StartAddress	0x40000400
#define TIM4_StartAddress	0x40000800
#define TIM5_StartAddress	0x40000C00

//Connected to APB2 Bus
#define TIM9_StartAddress	0x40014000
#define TIM10_StartAddress	0x40014400
#define TIM11_StartAddress	0x40014800
//Each Timer Reserves 0x400 Memory Map Size (1024 Bytes)

//Base Address Array for Optimization
#define _RSVD 0

// Timer Register map
typedef struct
{
	u32 CR1;	//Control Register 1
	u32 CR2;	//Control Register 2
	u32 SMCR;	//Slave Mode Control Register
	u32 DIER;	//DMA/Interrupt Enable Register
	u32 SR;		//Status Register
	u32 EGR;	//Event Generation Register
	u32 CCMR1;	//Capture/Compare mode Register 1
	u32 CCMR2;	//Capture/Compare mode Register 2
	u32 CCER;	//Capture/Compare Enable Register
	u32 CNT;	//Counter
	u32 PSC;	//Prescaler
	u32 ARR;	//Auto-Reload Register
	u32 RCR;	//Repitition Counter Register, Only Available for TIM1
	u32 CCR[4]; //Capture/Compare Register 1
	u32 BDTR;	//Break and Dead-Time Register, Only Available for TIM1
	u32 DCR;	//DMA Control Register
	u32 DMAR;	//DMA AddRess for full transfer
	u32 OR;		//Different for each timer.s
}TIMx_MemoryMap;

#define _TIM1  ((volatile TIMx_MemoryMap*)( TIM1_StartAddress) )
#define _TIM2  ((volatile TIMx_MemoryMap*)( TIM2_StartAddress) )
#define _TIM3  ((volatile TIMx_MemoryMap*)( TIM3_StartAddress) )
#define _TIM4  ((volatile TIMx_MemoryMap*)( TIM4_StartAddress) )
#define _TIM5  ((volatile TIMx_MemoryMap*)( TIM5_StartAddress) )
#define _TIM9  ((volatile TIMx_MemoryMap*)( TIM9_StartAddress) )
#define _TIM10 ((volatile TIMx_MemoryMap*)(TIM10_StartAddress) )
#define _TIM11 ((volatile TIMx_MemoryMap*)(TIM11_StartAddress) )

#endif
