/***********************************************************************************************/
/***********************************************************************************************/
/*************************************** Author: Mai Ahmed *************************************/
/***************************************** Layer: HAL ******************************************/
/*********************************** Component: DigitalSensors *********************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

/*************************************************************************************************/
/** Define The Port used in the Hardware  -->  GPIO_A or GPIO_B or GPIO_C			**/
/**												**/
/** Define The Pin used in the Hardware   -->  PIN0 or PIN1 or PIN2 or PIN3 or .......		**/
/**												**/
/*************************************************************************************************/
#ifndef DIGITALSENSOR_INTERFACE_H_
#define DIGITALSENSOR_INTERFACE_H_

typedef struct _DigitalSensor_ DigitalSensor;
struct _DigitalSensor_
{
	u8 PORT:2;
	u8 PIN:4;
};

#define DigitalSensor_PORTA	1
#define DigitalSensor_PORTB	2
#define DigitalSensor_PORTC	3

#define DigitalSensor_PIN0		0
#define DigitalSensor_PIN1		1
#define DigitalSensor_PIN2		2
#define DigitalSensor_PIN3		3
#define DigitalSensor_PIN4		4
#define DigitalSensor_PIN5		5
#define DigitalSensor_PIN6		6
#define DigitalSensor_PIN7		7
#define DigitalSensor_PIN8		8
#define DigitalSensor_PIN9		9
#define DigitalSensor_PIN10		10
#define DigitalSensor_PIN11		11
#define DigitalSensor_PIN12		12
#define DigitalSensor_PIN13		13
#define DigitalSensor_PIN14		14
#define DigitalSensor_PIN15		15

/*************************/
/** Note:               **/
/**     Give Low Value  **/
/*************************/
u8 DigitalSensor_u8Sensing(DigitalSensor Sensor);

#endif
