#include "STD_Types.h"
#include "BitOperations.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "SPI_Interface.h"
#include "DigitalSensor_Interface.h"
#include "DHT11_Interface.h"
#include "Link_Interface.h"
#include "FreeRTOS.h"
#include "task.h"

DigitalSensor LM393 = {DigitalSensor_PORTB, DigitalSensor_PIN0};
DigitalSensor PIR = {DigitalSensor_PORTB, DigitalSensor_PIN2};

u8 PIR_ReadingValue;
u8 FireSensor_ReadingValue;
u8 SwitchReading;
u8 Humidity;
s8 Temperature;
u8 DHT11_errorCode;

void FireSensing(void* pvParameters)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount (); // Get Last Time the Task Started
	while(1)
	{
		FireSensor_ReadingValue = 0;
		FireSensor_ReadingValue = DigitalSensor_u8Sensing(LM393);

		vTaskDelayUntil(&xLastWakeTime, 100); // Schedule the Task Every 0.1sec
	 }
}

void FireAction(void* pvParameters)
{
	LinkMessage_t Message;

	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount (); // Get the Last Time the Task Started
	while(1)
	{
		GPIO_u8SetPinValue (GPIO_PORTA, GPIO_PIN0, !FireSensor_ReadingValue);

		// Send the Reading to the Queue to send it to the Raspberry
		Message.source = LINK_SOURCE_FLAME;
		Message.type = LINK_FLAME_TYPE_READING;
		Message.data = !FireSensor_ReadingValue;
		Link_voidEnqueueMessage(Message);


		vTaskDelayUntil(&xLastWakeTime, 100); // Schedule the Task Every 0.1sec
	 }
}

void PIRSensing(void* pvParameters)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount (); // Get Last Time the Task Started
	while(1)
	{
		PIR_ReadingValue = 0;
		PIR_ReadingValue = DigitalSensor_u8Sensing(PIR);

		vTaskDelayUntil(&xLastWakeTime, 1000); // Schedule the Task Every 1sec
	 }
}

void PIRAction(void* pvParameters)
{
	LinkMessage_t Message;

	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount (); // Get the Last Time the Task Started
	while(1)
	{
		GPIO_u8SetPinValue (GPIO_PORTA, GPIO_PIN2, PIR_ReadingValue);

		// Send the Reading to the Queue to send it to the Raspberry
		Message.source = LINK_SOURCE_PIR;
		Message.type = LINK_PIR_TYPE_READING;
		Message.data = PIR_ReadingValue;
		Link_voidEnqueueMessage(Message);

		vTaskDelayUntil(&xLastWakeTime, 1000); // Schedule the Task Every 1sec
	 }
}

void DoorSystemSensing(void* pvParameters)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount (); // Get the Last Time the Task Started
	while(1)
	{
		SwitchReading = 1;
		GPIO_u8GetPinValue (GPIO_PORTB, GPIO_PIN1, &SwitchReading);

		vTaskDelayUntil(&xLastWakeTime, 1000); // Schedule the Task Every 1sec
	}
}

void DoorSystemAction(void* pvParameters)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount (); // Get the Last Time the Task Started
	while(1)
	{
		GPIO_u8SetPinValue (GPIO_PORTA, GPIO_PIN1, !SwitchReading);

		vTaskDelayUntil(&xLastWakeTime, 1000); // Schedule the Task Every 1sec
	}
}

void TempSensing(void* pvParameters)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount (); // Get the Last Time the Task Started
	while(1)
	{
		DHT11_errorCode = DHT11_voidRawDataUpdate();
		DHT11_u8GetReadings(&Humidity, &Temperature);

		vTaskDelayUntil(&xLastWakeTime, 2000); // Schedule the Task Every 2sec
	}
}

void TempAction(void* pvParameters)
{
	LinkMessage_t Message;

	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount (); // Get the Last Time the Task Started
	while(1)
	{
		Message.source = LINK_SOURCE_DHT11;
		if (DHT11_errorCode == 0)
		{
			if (Temperature > 25)
			{
				GPIO_u8SetPinValue (GPIO_PORTA, GPIO_PIN4, GPIO_HIGH); // Blue LED to Declare that The Cool Air Condition is ON
				GPIO_u8SetPinValue (GPIO_PORTA, GPIO_PIN5, GPIO_LOW);
			}
			else if (Temperature < 25)
			{
				GPIO_u8SetPinValue (GPIO_PORTA, GPIO_PIN5, GPIO_HIGH); // Red LED to Declare that The Heat Air Condition is ON
				GPIO_u8SetPinValue (GPIO_PORTA, GPIO_PIN4, GPIO_LOW);
			}
			else
			{
				GPIO_u8SetPinValue (GPIO_PORTA, GPIO_PIN4, GPIO_LOW);
				GPIO_u8SetPinValue (GPIO_PORTA, GPIO_PIN5, GPIO_LOW);
			}

			// Send the Reading to the Queue to send it to the Raspberry
			Message.type = LINK_DHT11_TYPE_TEMPERATURE;
			Message.data = Temperature;
			Link_voidEnqueueMessage(Message);

			Message.type = LINK_DHT11_TYPE_HUMIDITY;
			Message.data = Humidity;
			Link_voidEnqueueMessage(Message);

			Message.type = LINK_DHT11_TYPE_ERROR;
			Message.data = DHT11_errorCode;
			Link_voidEnqueueMessage(Message);
		}
		else
		{
			Message.type = LINK_DHT11_TYPE_ERROR;
			Message.data = DHT11_errorCode;
			Link_voidEnqueueMessage(Message);
		}
		vTaskDelayUntil(&xLastWakeTime, 2000); // Schedule the Task Every 2sec
	}
}

void SendMessege(void* pvParameters)
{
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount (); // Get the Last Time the Task Started
	while(1)
	{
		u8 RX = 0;
		RX = Link_u8SendMessage(); // Send the Message
		vTaskDelayUntil(&xLastWakeTime, 200); // Schedule the Task Every 50ms
	}
}

int main()
{
	RCC_u8SystemClkInitialization();
	RCC_u8Enable	(RCC_AHB1, RCC_GPIOA);
	RCC_u8Enable	(RCC_AHB1, RCC_GPIOB);
	RCC_u8Enable	(RCC_APB1, RCC_SPI2);

	/** Initialize Fire System GPIO **/
	GPIO_u8SetGPIOPinMode	(GPIO_PORTB, GPIO_PIN0, GPIO_MODER_INPUT);
	GPIO_u8SetGPIOPinMode	(GPIO_PORTA, GPIO_PIN0, GPIO_MODER_OUTPUT);

	/** Initialize Door System GPIO **/
	GPIO_u8SetGPIOPinMode	(GPIO_PORTB, GPIO_PIN1, GPIO_MODER_INPUT);
	GPIO_u8SetOutputPinMode	(GPIO_PORTB, GPIO_PIN1, GPIO_OTYPER_PUSH_PULL);
	GPIO_u8SetPullResMode	(GPIO_PORTB, GPIO_PIN1, GPIO_PUPDR_PULLUP);
	GPIO_u8SetPinValue 		(GPIO_PORTB, GPIO_PIN1, GPIO_HIGH);
	GPIO_u8SetGPIOPinMode	(GPIO_PORTA, GPIO_PIN1, GPIO_MODER_OUTPUT);

	/** Initialize PIR System GPIO **/
	GPIO_u8SetGPIOPinMode	(GPIO_PORTB, GPIO_PIN2, GPIO_MODER_INPUT);
	GPIO_u8SetGPIOPinMode	(GPIO_PORTA, GPIO_PIN2, GPIO_MODER_OUTPUT);

	/** Initialize Temperature System OUTPUT GPIO **/
	GPIO_u8SetGPIOPinMode	(GPIO_PORTA, GPIO_PIN4, GPIO_MODER_OUTPUT);
	GPIO_u8SetGPIOPinMode	(GPIO_PORTA, GPIO_PIN5, GPIO_MODER_OUTPUT);

	/** Initialize SPI2 Pins **/
	GPIO_u8SetGPIOPinMode			(GPIO_PORTB, GPIO_PIN12, GPIO_MODER_ALTERNATE);
	GPIO_voidSetAlternativeFunction	(GPIO_PORTB, GPIO_PIN12, AF5); // SPI2 NSS
	GPIO_u8SetPinOutputSpeed		(GPIO_PORTB, GPIO_PIN12, Very_High_Speed);

	GPIO_u8SetGPIOPinMode			(GPIO_PORTB, GPIO_PIN13, GPIO_MODER_ALTERNATE);
	GPIO_voidSetAlternativeFunction	(GPIO_PORTB, GPIO_PIN13, AF5); // SPI2 SCK
	GPIO_u8SetPinOutputSpeed		(GPIO_PORTB, GPIO_PIN13, Very_High_Speed);

	GPIO_u8SetGPIOPinMode			(GPIO_PORTB, GPIO_PIN14, GPIO_MODER_ALTERNATE);
	GPIO_voidSetAlternativeFunction	(GPIO_PORTB, GPIO_PIN14, AF5); // SPI2 MISO
	GPIO_u8SetPinOutputSpeed		(GPIO_PORTB, GPIO_PIN14, Very_High_Speed);

	GPIO_u8SetGPIOPinMode			(GPIO_PORTB, GPIO_PIN15, GPIO_MODER_ALTERNATE);
	GPIO_voidSetAlternativeFunction	(GPIO_PORTB, GPIO_PIN15, AF5); // SPI2 MOSI
	GPIO_u8SetPinOutputSpeed		(GPIO_PORTB, GPIO_PIN15, Very_High_Speed);

	/** Initialize SPI2 **/
	SPI_u8SlaveMode (SPI2, SPI_DisSoftSlaveManag, SPI_SelectSlave);
	SPI_u8Initialization(SPI2, SPI_LeadingEdge,
							   SPI_LowIDLE,
							   SPI_fPCLK2,
							   SPI_MSBTrans,
							   SPI_Data8Bits,
							   SPI_Enable);

	/** Initialize DHT11 **/
	DHT11_voidInitialize();

	/********** Create the Tasks **********/
	// Fire System Has The Highest Priority
	xTaskCreate	(FireSensing, NULL, 100, NULL, 7, NULL);
	xTaskCreate	(FireAction,  NULL, 100, NULL, 6, NULL);

	// Then People Detection
	xTaskCreate	(DoorSystemSensing, NULL, 100, NULL, 5, NULL);
	xTaskCreate	(PIRSensing, 	    NULL, 100, NULL, 5, NULL);

	// Then Door will Take the Desire Action to Open or Close
	xTaskCreate	(DoorSystemAction, NULL, 100, NULL, 4, NULL);

	// Then PIR will Take the Desire Action to Turn On the Light or Turn it Off
	xTaskCreate	(PIRAction, NULL, 100, NULL, 4, NULL);

	// Then Temperature Sensor will Sense the Temperature of the Train Car to Balance it with The Air Condition
	xTaskCreate	(TempSensing, NULL, 100, NULL, 3, NULL);
	xTaskCreate	(TempAction,  NULL, 100, NULL, 2, NULL);

	// Communicate with the Raspberry Pi
	xTaskCreate	(SendMessege, NULL, 100, NULL, 8, NULL);

	/* Start Scheduler */
	vTaskStartScheduler();


	while(1)
	{

	}
}
