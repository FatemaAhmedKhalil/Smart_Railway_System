/***********************************************************************************************/
/***********************************************************************************************/
/******************************* Author: Fatema Ahmed & Armia Khairy ***************************/
/****************************************** Layer: HAL *****************************************/
/****************************************** SWC: Link ******************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/
#include "STD_Types.h"
#include "BitOperations.h"

#include "SPI_Interface.h"
#include "GPIO_Interface.h"
#include "Link_Config.h"
#include "Link_Private.h"
#include "Link_Interface.h"

#define MAX_QUEUE_SIZE 33

struct
{
    u8  Arr[MAX_QUEUE_SIZE];
    u8  elemNum;
    u8  head;
    u8  tail;
} Private_Queue;


void Link_voidInitQueue()
{
    for (u8 i =0; i < MAX_QUEUE_SIZE; i++)
    {
        Private_Queue.Arr[i] = 0xFF;
    }

    Private_Queue.head = 0;
    Private_Queue.tail = 0;
    Private_Queue.elemNum = 0;
}

void Link_voidInit()
{
	Link_voidInitQueue();
}

u8 Link_u8ReturnQueueSize()
{
	return Private_Queue.elemNum;
}

/** This one is made for 16-bit Messages. **/
// void Link_voidEnqueueMessage(LinkMessage_t Copy_LinkMessage)
// {
    
//     if (Private_Queue.head == Private_Queue.tail || Private_Queue.elemNum == 0)
//     {
//         Private_Queue.Arr[Private_Queue.tail] =
//             (
//             ((u16)(((Copy_LinkMessage.source << 4) | Copy_LinkMessage.type) << 8))
//             |
//             ((u16)Copy_LinkMessage.data)
//             );
//         Private_Queue.tail++;
//         Private_Queue.elemNum++;
//     }

//     else if (Private_Queue.elemNum < MAX_QUEUE_SIZE)
//     {
//         Private_Queue.Arr[Private_Queue.tail] =
//             (
//             ((u16)(((Copy_LinkMessage.source << 4) | Copy_LinkMessage.type)<<8)) |
//             ((u16)Copy_LinkMessage.data)
//             );
//         Private_Queue.tail = (Private_Queue.tail+1)%16;
//         Private_Queue.elemNum++;
//     }
// }

void Link_voidEnqueueMessage(LinkMessage_t Copy_LinkMessage)
{
    u8 u8SourceType = (Copy_LinkMessage.source<<4) | Copy_LinkMessage.type;
    u8 u8CheckSum   = u8SourceType+Copy_LinkMessage.data;

    // Lookup messages from the same SourceType
    for (int i = Private_Queue.head; i != Private_Queue.tail; i = (i+3)%MAX_QUEUE_SIZE)
    {
        if (u8SourceType== Private_Queue.Arr[i])    // If sourceType exists
        {
            if (Copy_LinkMessage.data == Private_Queue.Arr[i+1])
                return;
            else
            {
            	// Update the data if the message has changed
                Copy_LinkMessage.data = Private_Queue.Arr[i+1];
                // Recalculate Checksum
                Private_Queue.Arr[i+2] = u8CheckSum;
                return;
            }
        }
    }

    //
    if (Private_Queue.head == Private_Queue.tail)
    {
        // Add Message Source and Type
        Private_Queue.Arr[Private_Queue.tail] = u8SourceType;

        // Add Message Data
        Private_Queue.Arr[Private_Queue.tail+1] = Copy_LinkMessage.data;

        // Add a Checksum
        Private_Queue.Arr[Private_Queue.tail+2] = u8CheckSum;

        Private_Queue.tail = (Private_Queue.tail+3)%MAX_QUEUE_SIZE;
        Private_Queue.elemNum+=3;
    }
    else if (Private_Queue.elemNum < MAX_QUEUE_SIZE)
    {
        // Add Message Source and Type
        Private_Queue.Arr[Private_Queue.tail] = u8SourceType;

        // Add Message Data
        Private_Queue.Arr[Private_Queue.tail+1] = Copy_LinkMessage.data;

        // Add a Checksum
        Private_Queue.Arr[Private_Queue.tail+2] = u8CheckSum;

        Private_Queue.tail = (Private_Queue.tail+3)%MAX_QUEUE_SIZE;
        Private_Queue.elemNum+=3;
    }
}

u8 Link_u8SendDequeueMessage()
{
	u8 u8Message_send = 0;
	u8 u8Message_recvd= 0;

    u8 RL=0, RH=0;
    u8 tempL=0,tempH=0;

    while (Private_Queue.elemNum > 0)
    {
        // Select the Master
        
    	u8Message_send = Private_Queue.Arr[Private_Queue.head]; // get a copy of the head element
    	u8Message_recvd=SPI_voidTransceive(LINK_RaspberryPi, u8Message_send);
        GPIO_u8FastControlPinValue(LINK_INTERRUPT_PORT, LINK_INTERRUPT_PIN, GPIO_LOW);
        // De-select the master
        
        // Check Message Integrity
        RL = u8Message_recvd&0xF;
        RH = (u8Message_recvd>>4)&0xF;

        // Counts the number of ones in each bit
        for (u8 i=0; i<4; i++)
        {
            tempH+=(RH>>i)&1;
            tempL+=(RL>>i)&1;
        }

        tempH/=2;
        tempL/=2;

        Private_Queue.Arr[Private_Queue.head] = 0xFF;

        Private_Queue.head = (Private_Queue.head+1)%MAX_QUEUE_SIZE;
        Private_Queue.elemNum--;
    }

    GPIO_u8FastControlPinValue(LINK_INTERRUPT_PORT, LINK_INTERRUPT_PIN, GPIO_HIGH);

    if (tempH > tempL)
        return 0xF0;	//Open the left doors.
    else if (tempH < tempL)
        return 0x0F;	//Open the right doors.
    else
    	return 0;		//Do nothing.
}

void Link_u8SendMessageDirectly(LinkMessage_t Copy_LinkMessage)
{
	u16 Message = ((u16)Copy_LinkMessage.data) | ((((u16)Copy_LinkMessage.type) | (((u16)Copy_LinkMessage.source)<<4))<<8);
	SPI_voidTransceive(LINK_RaspberryPi, Message);
}
