/***********************************************************************************************/
/***********************************************************************************************/
/****************************** Author: Fatema Ahmed & Armia Khairy ****************************/
/***************************************** Layer: MCAL *****************************************/
/****************************************** SWC: GPIO ******************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef GPIO_Interface
#define GPIO_Interface

/** Error States **/
#define GPIO_ErrorCheckPerphiralRange	4
#define GPIO_ErrorPinsOutPut			5

/********************************************************/
/* Define												*/
/*		1) For Port A Pins = (0 : 15)				    */
/*		2) For Port B Pins = (1 : 15)			   	    */
/*		3) For Port C Pins = (13 : 15)				    */
/********************************************************/
#define GPIO_HIGH  1
#define GPIO_LOW   0

#define GPIO_PORTA	1
#define GPIO_PORTB	2
#define GPIO_PORTC	3

#define GPIO_PIN0	0
#define GPIO_PIN1	1
#define GPIO_PIN2	2
#define GPIO_PIN3	3
#define GPIO_PIN4	4
#define GPIO_PIN5	5
#define GPIO_PIN6	6
#define GPIO_PIN7	7
#define GPIO_PIN8	8
#define GPIO_PIN9	9
#define GPIO_PIN10	10
#define GPIO_PIN11	11
#define GPIO_PIN12	12
#define GPIO_PIN13	13
#define GPIO_PIN14	14
#define GPIO_PIN15	15

//GPIO MODER MODES
#define GPIO_MODER_INPUT        0b00
#define GPIO_MODER_OUTPUT       0b01
#define GPIO_MODER_ALTERNATE    0b10
#define GPIO_MODER_ANALOG       0b11

//GPIO OTYPER Modes
#define GPIO_OTYPER_PUSH_PULL   0
#define GPIO_OTYPER_OPEN_DRAIN  1

//GPIO PUPDR Modes
#define GPIO_PUPDR_NO           0b00
#define GPIO_PUPDR_PULLUP       0b01
#define GPIO_PUPDR_PULLDOWN     0b10

u8 GPIO_u8SetPinValue (u8 u8Port, u8 u8Pin, u8 u8Value);

u8 GPIO_u8FastControlPinValue (u8 u8Port, u8 u8Pin, u8 u8Status);

u8 GPIO_u8SetPortValue (u8 u8Port, u8 u8Value);

u8 GPIO_u8GetPinValue (u8 u8Port, u8 u8Pin, u8* pu8Value);

u8 GPIO_u8TogglePinValue(u8 u8Port, u8 u8Pin);

u8 GPIO_u8SetGPIOPinMode(u8 u8Port,u8 u8Pin, u8 u8Mode);

u8 GPIO_u8SetOutputPinMode(u8 u8Port,u8 u8Pin, u8 u8Mode);

u8 GPIO_u8SetPullResMode(u8 u8Port,u8 u8Pin, u8 u8Mode);

/********************************************************************/
/* Select Alternative Function										*/
/*		    SYSTEM: AF0			 USART6: AF8						*/
/*		TIM1/TIM2: AF1			I2C2..3: AF9						*/
/*		   TIM3..5: AF2			 OTG_FS: AF10						*/
/*	      TIM9..11: AF3				   : AF11						*/
/*		   I2C1..3: AF4			   SDIO: AF12						*/
/*		   SPI1..4: AF5				   : AF13						*/
/*			  SPI3: AF6			       : AF14						*/
/*		 USART1..2: AF7		   EVENYOUT: AF15						*/
/********************************************************************/
#define AF0		0000
#define AF1		0001
#define AF2		0010
#define AF3		0011
#define AF4		0100
#define AF5		0101
#define AF6		0110
#define AF7		0111
#define	AF8		1000
#define	AF9		1001
#define	AF10	1010
#define	AF11	1011
#define	AF12	1100
#define	AF13	1101
#define	AF14	1110
#define	AF15	1111

u8 GPIO_voidSetAlternativeFunction(u8 u8Port, u8 u8Pin, u8 u8AlternateFunction);

#endif
