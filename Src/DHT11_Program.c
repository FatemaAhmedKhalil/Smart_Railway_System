/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Armia Khairy ************************************/
/****************************************** Layer: HAL *****************************************/
/****************************************** SWC: DHT11 *****************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"

#include "NVIC_Interface.h"
#include "RCC_Interface.h"
#include "TIM_Interface.h"
#include "GPIO_Register.h"
#include "GPIO_Interface.h"

#include "TIM_HAL_Interface.h"

#include "DHT11_Config.h"
#include "DHT11_Private.h"
#include "DHT11_Interface.h"

/**
 * Notes : This program is intended to be used by an OS,
 * The First delay for this program must be at least 2 seconds
 * The Periodicity for anew reading must be at least 1 second
 * 
 */

//******************************* Interface Functions *******************************//

/**
 * @brief Function that Start the required peripherals for DHT11
 * 
 */

static u8 u8TempReading=0;
static u32 u8TimeInstance1=0, u8TimeInstance2=0, u8PulseDuration=0;

void DHT11_voidInitialize(void)
{
    // Clear Data stack
    DHT11_DATA[0] = DHT11_DATA[1] = DHT11_DATA[2] = DHT11_DATA[3] = DHT11_DATA[4] = 0;

    // Turn On the RCC for desired Timer
    RCC_u8Enable(DHT11_RCC_BUS, DHT11_RCC_PERIPHERAL);  //Enables Dedicated Timer  bus

    // Enable GPIO
    GPIO_u8SetGPIOPinMode(DHT11_GPIO_PORT, DHT11_GPIO_PIN, GPIO_MODER_OUTPUT);
    GPIO_u8FastControlPinValue(DHT11_GPIO_PORT, DHT11_GPIO_PIN,GPIO_HIGH);

    // Setting Timer Up but not start it
    MTIM_voidSetPrescaler(TIM2,DHT11_TIM_PSC_1MHz);	    //Set the pre-scaler
	MTIM_voidUpdateGeneration(TIM2);			        //Update Counters and Shadow Registers
	MTIM_voidclearUpdateInterrupt(TIM2);		        //Clears Update Interrupt Flag
}

void DHT11_voidRawDataUpdate()
{

    // Sends 18ms 0 volt pulse.
    (void)GPIO_u8SetGPIOPinMode(DHT11_GPIO_PORT, DHT11_GPIO_PIN, GPIO_MODER_OUTPUT);
    (void)GPIO_u8FastControlPinValue(DHT11_GPIO_PORT, DHT11_GPIO_PIN,GPIO_LOW);

    // DHT11_delay_MilliSeconds(18);
    HTIM_voidDelayMilliseconds(DHT11_TIM_NUM,18);

    // Converting the GPIO Pin to Input with Pull up resistor mode
    // HTIM_voidChangeAndUpdateTiming(DHT11_TIM_NUM, 0xFFFF, DHT11_TIM_PSC_1MHz,0);
    // Set Microseconds Timer

    // DHT11_voidSetTimerMode(0xFFFF, DHT11_TIM_PSC_1MHz);
    HTIM_voidChangeAndUpdateTiming(DHT11_TIM_NUM, 0xFFFF, DHT11_TIM_PSC_1MHz,0);
    (void)GPIO_u8SetGPIOPinMode(DHT11_GPIO_PORT, DHT11_GPIO_PIN, GPIO_MODER_INPUT);
    (void)GPIO_u8SetPullResMode(DHT11_GPIO_PORT, DHT11_GPIO_PIN, GPIO_PUPDR_PULLUP);

    {
    		/**** Critical Section, Must not be interrupted *****/

        //This will take up to 4960 micro-seconds to fully perform this section.
        //To ensure that there is communication, DHT11 sends an 80usec low pulse, then 
        //80 usec high pulse, if they were not detected, it means the sensor is not 
        //working properly

        //Using the timer as a clock to measure the elapsed time in
        //DHT11_u8Decoder, This is needed to determine the pulse duration
        //This or using a Input Capture mode, which is more complicated to perform under
        //an OS.

        
        //First Reading Delay, wait until it reads HIGH and start measuring
        //while (u8TempReading==GPIO_LOW) asm("NOP");

        //*** Checking a HIGH pulse
        u8TimeInstance1 = MTIM_u32ReadCounterValue(DHT11_TIM_NUM);
        do
        {
            u8TempReading = DHT11_DATA_FastRead;
        }
        while( u8TempReading == GPIO_HIGH && MTIM_u8ReadUpdateInterrupt(DHT11_TIM_NUM) == 0 );
        u8TimeInstance2 = MTIM_u32ReadCounterValue(DHT11_TIM_NUM);
        
        u8PulseDuration = u8TimeInstance2-u8TimeInstance1;
        if (u8PulseDuration > 42  || MTIM_u8ReadUpdateInterrupt(DHT11_TIM_NUM) == 1) // add an error range of 2usec
        {
        	// Time Out, Means Not working
            return; // Exit with error
        }

        //**** Checking the LOW 80 usec pulse
        u8TimeInstance1 = MTIM_u32ReadCounterValue(DHT11_TIM_NUM);
        do
        {
            u8TempReading=DHT11_DATA_FastRead;
        }
        while (u8TempReading == GPIO_LOW && MTIM_u8ReadUpdateInterrupt(DHT11_TIM_NUM) == 0);
        u8TimeInstance2 = MTIM_u32ReadCounterValue(DHT11_TIM_NUM);
        u8PulseDuration = u8TimeInstance2 - u8TimeInstance1;
        if (u8PulseDuration>82  || MTIM_u8ReadUpdateInterrupt(DHT11_TIM_NUM) == 1) // add an error range of 2usec
        {
        	// Time Out, Means Not working
            return; // Exit with error
        }

        //**** Checking the HIGH 80 usec pulse
        u8TimeInstance1 = MTIM_u32ReadCounterValue(DHT11_TIM_NUM);
        do
        {
            GPIO_u8GetPinValue(DHT11_GPIO_PORT, DHT11_GPIO_PIN, &u8TempReading);
        }
        while (u8TempReading == GPIO_HIGH && MTIM_u8ReadUpdateInterrupt(DHT11_TIM_NUM) == 0);
        u8TimeInstance2 = MTIM_u32ReadCounterValue(DHT11_TIM_NUM);

        u8PulseDuration = u8TimeInstance2-u8TimeInstance1;
        if (u8PulseDuration > 90 || MTIM_u8ReadUpdateInterrupt(DHT11_TIM_NUM) == 1 ) // add an error range of 2usec
        {
        	// Time Out, Means Not working
            return; // Exit with error
        }


        // If the sensor was working, It will now start receiving data.
        for (u8 i = 0; i<40; i++)
        {
            DHT11_DATA[i/8] <<= 1;
            DHT11_DATA[i/8] += DHT11_u8Decoder();
        }
    // End of Critical Section
    }

    // Run the timer to a WHOLE SECOND until this function is available again
    GPIO_u8SetGPIOPinMode(DHT11_GPIO_PORT, DHT11_GPIO_PIN, GPIO_MODER_OUTPUT);
    GPIO_u8SetPinValue(DHT11_GPIO_PORT, DHT11_GPIO_PIN,GPIO_HIGH);

    //return 0;
}

u8 DHT11_u8GetReadings(u8 *pu8Humidity,s8 *ps8Temperature)
{
    if (DHT11_DATA[0] + DHT11_DATA[1] + DHT11_DATA[2] +DHT11_DATA[3] !=DHT11_DATA[4])
	{
    	//Failed Parity Check
		return 2;
	}
	else
    {
		//Successful Parity Check
        *pu8Humidity    = DHT11_DATA[0];
        *ps8Temperature = DHT11_DATA[2];
    }
    return 0;
}

//******************************* Private Functions *******************************//
u8   DHT11_u8Decoder(void)
{
    // Data is sent like this
    // It starts with a 50 us LOW
    // Then 28 to 30 us HIGH, which means 0
    // Or 70 us HIGH, which means 1

    // Use DHT_TIM as a clock to measure the pulse duration using it

    // This is a temporary code until Input Capture Compare mode is implemented in MCAL
    // Me 3 months later: Nothing is more Permanent than a temporary solution lol,
    // but seriously, after understanding the timer, I found that it's not worth the effort
    // to implement it.

    do
    {
    	u8TempReading = DHT11_DATA_FastRead;
    }
    while (u8TempReading == GPIO_LOW && MTIM_u8ReadUpdateInterrupt(DHT11_TIM_NUM) == 0);
    u8TimeInstance1 = MTIM_u32ReadCounterValue(DHT11_TIM_NUM); //The first instance where the input was HIGH
    // Reading the Pulse Duration
    do
    {
    	u8TempReading = DHT11_DATA_FastRead;
    }
    while (u8TempReading == GPIO_HIGH && MTIM_u8ReadUpdateInterrupt(DHT11_TIM_NUM) == 0);
    u8TimeInstance2 = MTIM_u32ReadCounterValue(DHT11_TIM_NUM); // The last  instance where the input was HIGH
    u8PulseDuration = u8TimeInstance2-u8TimeInstance1;

    // The average between 30 and 70 is 50, So this will be the optimal value to compare at
    if (u8PulseDuration >35  || MTIM_u8ReadUpdateInterrupt(DHT11_TIM_NUM)==1)
        return 1;
    else
        return 0;
}

//******************************* Helper Functions *******************************//
//void DHT11_voidSetTimerMode(u16 Copy_u16PulseDuration, u16 Copy_u16Prescaler)
//{
//    //Stop the Timer
//    MTIM_voidDisableTimer(DHT11_TIM_NUM);
//
//    //Pre-load New Pre-scale and auto reload values
//    MTIM_voidSetPrescaler(DHT11_TIM_NUM, Copy_u16Prescaler); //This makes the timer work in 1KHz
//    MTIM_voidSetAutoReloadValue(DHT11_TIM_NUM, Copy_u16PulseDuration);
//
//    //Update Shadow Registers without raising the timer's pending flag
//    //MTIM_voidDisableUpdateInterrupt(DHT11_TIM_NUM);
//    MTIM_voidUpdateGeneration(DHT11_TIM_NUM);
//    MTIM_voidclearUpdateInterrupt(DHT11_TIM_NUM);
//    //MTIM_voidEnableUpdateInterrupt(DHT11_TIM_NUM);
//
//    //Start the timer
//    MTIM_voidEnableTimer(DHT11_TIM_NUM);
//}

// void DHT11_delay_MilliSeconds(u16 Copy_u16Milliseconds)
// {
//     // Add a line to disable global interrupts here.
//     //MTIM_voidDisableUpdateInterrupt(DHT11_TIM_NUM);
//
//     DHT11_voidSetTimerMode(Copy_u16Milliseconds, DHT11_TIM_PSC_1KHz);//Wait 18 milliseconds.
//     while(MTIM_u8ReadUpdateInterrupt(DHT11_TIM_NUM)==0)
//     {
//         asm("NOP"); //Halt Until the timer finishes.
//     }
//     MTIM_voidDisableTimer(DHT11_TIM_NUM);
//     MTIM_voidclearUpdateInterrupt(DHT11_TIM_NUM);
//
//     //Add a line to enable interrupts again
//     //MTIM_voidEnableUpdateInterrupt(DHT11_TIM_NUM);
//
// }
