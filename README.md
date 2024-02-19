# Smart Railway System

In this project, we have developed a Smart Railway System utilizing advanced IoT technology for both upper-level software and low-level hardware. 

The project focuses on enhancing traveler satisfaction during train journeys by incorporating various smart features within the train carts:

1. Smart Doors: Automated doors that open when the train approaches a station platform and stops.
2. PIR Sensors: These sensors detect occupancy within the train cart, allowing for intelligent control of lighting to conserve energy when the cart is empty.
3. Flame Sensor: Rapidly detects fire occurrences, triggering alarms for prompt response by train operators and nearby stations.
4. Temperature and Humidity Sensors: Collect environmental data for regulating air quality via the air conditioning system, particularly beneficial for energy conservation in off-grid systems.
5. GPS: Provides real-time location tracking of the train.
6. Communication Interface: Facilitates data exchange and control between microcontrollers.

This branch of the repository specifically contains the low-level software developed for the Black Pill board utilizing the STM32F401CCU6 microprocessor. It comprises:

1. **MCAL (Microcontroller Abstraction Layer)**: Incorporates core peripherals and vendor-specific peripherals such as GPIO, SPI, RCC, NVIC, and Timers.
2. **HAL (Hardware Abstraction Layer)**: Includes drivers for essential sensors like the Flame Sensor, Temperature Sensor (DHT11), a HAL Timer Interface, and facilitates communication between the STM32 and Raspberry Pi. Additionally, it provides drivers for peripherals required by the Raspberry Pi Model 3, such as GPS.
3. **freeRTOS[TM]**: The selected operating system to manage tasks and ensure efficient operation of the system.
