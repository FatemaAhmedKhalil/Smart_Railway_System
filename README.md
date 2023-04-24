# Smart Railway System
This branch in this Repository includes the main code runs by the Raspberry Pi to control the whole project.

**The Rasspberry Pi is considered as the main computer of the project**
1) The Raspberry Pi takes messages from the STM32 at every cart by SPI communication protocol and sends the data to the server to show the state of every cart which is done by the help of all sensors and devices in the embedded branch.
2) The Raspberry Pi also control the system by functions for every system *GPS, Reciving from STM of every cart and sending data to the server*.
