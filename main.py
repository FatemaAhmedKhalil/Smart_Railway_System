##******************************##
## Raspberry PI 3 Model B		##
## SPI0 Pins:					##
##			23 GPIO 11	>> SCLK	##
##			19 GPIO 10	>> MOSI	##
##			21 GPIO 9	>> MISO	##
##			24 GPIO 8	>> CE0	##
##			26 GPIO 7	>> CE1	##
## UART Pins:					##
##			00 GPIO 0	>> RX	##
##			00 GPIO 0	>> RX	##
##                              ##
## App & Web key:               ##
## 0 ----> Temp                 ##
## 1 ----> Hum                  ##
## 2 ----> Flame                ##
## 3 ----> Door                 ##
## 4 ----> Light                ##
## 5 ----> GPS                  ##
##******************************##

# Fundamental Python 
import time
import string

# Raspberry Pi Modules
import RPi.GPIO as GPIO
import spidev
import serial

# MQTT Server Interface
import paho.mqtt.client as mqtt

# NMEA Translator 
import pynmea2

# SPI Pins
SPIx = 0
CEx = 0
NSS = 2

# Serial Interface for GPS
GPS=serial.Serial('/dev/serial0', baudrate=9600, timeout=0.5)

# Data
send_byte = 0x0F
rcv_byte  =[]

# MQTT
mqttBroker = 'test.mosquitto.org'

# MQTT Server Initializations
client = mqtt.Client("")
client.connect(mqttBroker)

# Functions
# Sending and Receiving data between Raspberry Pi and STM32 over SPI
def SPI_sendReceiveData(spi_interface,sent_data):
    # Loop 3 times
    for i in range(3):
        GPIO.output(NSS, GPIO.LOW)
        rcv_byte.append(spi_interface.xfer2([sent_data])[0])
        GPIO.output(NSS, GPIO.HIGH)
        
    print(rcv_byte)
    checkSum = (rcv_byte[0]+rcv_byte[1]-rcv_byte[2])
    # If the checksum was successful
    if (checkSum==0):
        rcv_byte.pop()
    # If data was corrupted
    else:
        print("Error")
        rcv_byte.pop()
        rcv_byte.pop()
        rcv_byte.pop()

def GPS_SendData():
    dataOP = pynmea2.NMEAStreamReader()
    reading= GPS.readline().decode('unicode_escape')
    while True:
        if reading[0:6] == "$GPRMC":
            newmsg=pynmea2.parse(reading)
            gpslat=newmsg.latitudee
            gpslong=newmsg.longitude
            client.publish("Train 934", str(5)+","+str(gpslat)+","+str(gpslong))
            
            #return [lat, lng]


def MQTT_sendData(SourceType, Message):
    if 		SourceType==2:
        # DHT11 Humidity reading
        #client.publish("Train 934", "1"+","+str(Message))
        print("Humidity = "+str(Message))
        
    elif	SourceType==1:
        # DHT11 Temperature Reading
        #client.publish("Train 934", "0"+","+str(Message))
        print("Temperature = "+str(Message))
    elif	SourceType==16:
        # Flame Sensor Reading
        #client.publish("Train 934", "2"+","+str(Message))
        print("Flame = "+str(Message))
        pass
    elif	SourceType==32:
        # PIR Sensor Reading
        #client.publish("Train 934", "4"+","+str(Message))
        print("PIR = "+str(Message))
        pass
    elif	SourceType==48:
        # Door State (unused)
        pass
    elif	SourceType==64:
        # GPS Latitude
        pass
    elif	SourceType==65:
        # GPS Longitude
        pass


# main function
def main():
    # Link Initializations
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(NSS, GPIO.OUT)
    GPIO.output(NSS, GPIO.LOW)

    spi = spidev.SpiDev()
    spi.open(SPIx, CEx)
    spi.max_speed_hz = 6250000
    spi.mode = 0b00
    
    # GPS Initializations
    GPS.close()
    GPS.open()

    
    while True:
        # 1. Receive data from stm32
        SPI_sendReceiveData(spi, send_byte)

        # 2. Receive data from GPS

        # 3. Communicatee with MQTT Broker
        while(rcv_byte!=[]):
            source=rcv_byte.pop(0)
            data=rcv_byte.pop(0)
            MQTT_sendData(source,data)
            print("Sent")
            
        time.sleep(1) # Repeat every 250 milliseconds


if __name__ == '__main__':
    main()
