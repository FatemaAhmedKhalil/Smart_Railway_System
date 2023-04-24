# Smart Railway System

In This Project, we designed A smart Railway system that uses smart IoT Technology Developed by us, for both the upper level Software and the low level software and hardware.
This project will be meaningless without the train itself, and to improve travelers’ satisfaction on their trip, the train cart will include some smart features such as 
1)	Smart Doors that automatically opens when it’s in front of the station platform and the train is stopping.	
2)	PIR Sensors to detect whether or not people are inside the cart, which will make it able to smartly turn off the lights when no one in the train cart.
3)	Flame sensor that quickly detects fire in order to sound the alarm to the train operators and other stations.
4)	Temperature and Humidity sensors to collect the readings and send the data to the controller in order to control the air quality using the air conditioners, which will save energy especially for a system that may not be connected to the grid.
5)  Communication between another Microcontrollers to send and control data.

This branch in this Repository includes the Low level software developed for the Black Pill board for **STM32F401CCU6** Microprocessor, which includes:
1) **MCAL** : Includes the core peripherals and the needed vendor peripherals like *GPIO, SPI, RCC, NVIC, Timers and etc...*, 
2) **HAL**: Includes the drivers for *Sensors we need in the project like Flame Sensor, Temperature Sensor DHT11,.. etc, A HAL Timer Interface, and linking between the STM32 and the Rasspberry Pi, and other drivers that we need and in Raspberry Pi Model 3 Like GPS*.
3) **freeRTOS[TM]**: The OS chosen to run this system.
