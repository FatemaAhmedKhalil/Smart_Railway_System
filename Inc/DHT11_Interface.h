/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Armia Khairy ************************************/
/****************************************** Layer: HAL *****************************************/
/****************************************** SWC: DHT11 *****************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef DHT11_INTERFACE_H_
#define DHT11_INTERFACE_H_

void DHT11_voidInitialize(void);
void DHT11_voidRawDataUpdate();
u8 DHT11_u8GetReadings(u8 *pu8Humidity,s8 *ps8Temperature);

#if DHT11_GPIO_PORT==GPIO_PORTA
    #define DHT11_DATA_FastRead   GET_BIT(GPIOA->IDR,DHT11_GPIO_PIN)
#elif DHT11_GPIO_PORT==GPIO_PORTB
    #define DHT11_DATA_FastRead   GET_BIT(GPIOB->IDR,DHT11_GPIO_PIN)
#elif DHT11_GPIO_PORT==GPIO_PORTC
    #define DHT11_DATA_FastRead   GET_BIT(GPIOC->IDR,DHT11_GPIO_PIN)
#endif


#endif
