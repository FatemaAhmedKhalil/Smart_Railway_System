/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Armia Khairy ************************************/
/****************************************** Layer: HAL *****************************************/
/****************************************** SWC: DHT11 *****************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef DHT11_CONFIG_H_
#define DHT11_CONFIG_H_


#define DHT11_CLK_FREQ      25000000UL // System frequency, it shouldn't be a static number defined here.
#define DHT11_GPIO_PORT     GPIO_PORTB // To enable the Peripheral
#define DHT11_GPIO_PIN      GPIO_PIN3  // Connected PIN
#define DHT11_TIM_NUM       TIM2       // Timer Mode

//Pre-scaler Value to make the clock work in 1KHz, doesn't work if the system frequency is larger than 65,535,999 Hz
#define DHT11_TIM_PSC_1KHz (DHT11_CLK_FREQ/1000-1)
//Pre-scaler Value to make the clock run in 1MHz
#define DHT11_TIM_PSC_1MHz (DHT11_CLK_FREQ/1000000-1)

#define DHT11_RCC_GPIO_PORT RCC_GPIOA

//Use only TIM2, TIM3, TIM4 or TIM5 as the others are more complicated to work with RCC Bus
#if DHT11_TIM_NUM == TIM1 || DHT11_TIM_NUM == TIM9 || DHT11_TIM_NUM == TIM10 || DHT11_TIM_NUM == TIM11
#define DHT11_RCC_BUS RCC_APB2
#else
#define DHT11_RCC_BUS RCC_APB1
#endif

#if DHT11_TIM_NUM == TIM2
#define DHT11_RCC_PERIPHERAL    RCC_TIM2

#elif DHT11_TIM_NUM == TIM3
#define DHT11_RCC_PERIPHERAL    RCC_TIM3

#elif DHT11_TIM_NUM == TIM4
#define DHT11_RCC_PERIPHERAL    RCC_TIM4

#elif DHT11_TIM_NUM == TIM5
#define DHT11_RCC_PERIPHERAL    RCC_TIM5

#endif

//Finds Vector Table Address from NVIC
#if DHT11_TIM_NUM == TIM2
#define DHT11_TIM_NVIC_ID    NVIC_TIM2

#elif DHT11_TIM_NUM == TIM3
#define DHT11_TIM_NVIC_ID    NVIC_TIM3

#elif DHT11_TIM_NUM == TIM4
#define DHT11_TIM_NVIC_ID    NVIC_TIM4

#elif DHT11_TIM_NUM == TIM5
#define DHT11_TIM_NVIC_ID    NVIC_TIM5
#endif

#endif

