/***********************************************************************************************/
/***********************************************************************************************/
/****************************** Author: Fatema Ahmed & Armia Khairy ****************************/
/****************************************** Layer: HAL *****************************************/
/****************************************** SWC: Link ******************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/
#include "STD_Types.h"
#include "BitOperations.h"

#include "SPI_Private.h"
#include "SPI_Interface.h"
#include "GPIO_Interface.h"
#include "Link_Config.h"
#include "Link_Private.h"
#include "Link_Interface.h"

#define MAX_QUEUE_SIZE 32

struct {
    u16 Arr[MAX_QUEUE_SIZE];
    u8  elemNum;
    u8  head;
    u8  tail;
} Private_Queue;


u8 Link_u8ReturnQueueSize()
{
	return Private_Queue.elemNum;
}

void Link_voidInitQueue()
{
    for (u8 i =0; i<MAX_QUEUE_SIZE; i++)
    {
        Private_Queue.Arr[i]=0xFF;
    }
    Private_Queue.head      = 0;
    Private_Queue.tail      = 0;
    Private_Queue.elemNum   = 0;
}

void Link_voidEnqueueMessage(LinkMessage_t Copy_LinkMessage)
{
    
    if (Private_Queue.head == Private_Queue.tail || Private_Queue.elemNum==0)
    {
        Private_Queue.Arr[Private_Queue.tail]= 
            (
            ((u16)(((Copy_LinkMessage.source << 4) | Copy_LinkMessage.type)<<8))
            |
            ((u16)Copy_LinkMessage.data)
            );
        Private_Queue.tail++;
        Private_Queue.elemNum++;
    }
    else if (Private_Queue.elemNum<MAX_QUEUE_SIZE)
    {
        Private_Queue.Arr[Private_Queue.tail]= 
            (
            ((u16)(((Copy_LinkMessage.source << 4) | Copy_LinkMessage.type)<<8)) |
            ((u16)Copy_LinkMessage.data)
            );
        Private_Queue.tail=(Private_Queue.tail+1)%16;
        Private_Queue.elemNum++;
    }
}

u8 Link_u8SendDequeueMessage(volatile u16 *P_u16ReturnVal)
{
	//  returns a copy of the head element.
    if (Private_Queue.elemNum>0)
    {
        *P_u16ReturnVal = Private_Queue.Arr[Private_Queue.head];
        Private_Queue.head=(Private_Queue.head+1)%16;
        Private_Queue.elemNum--;
        return 0;
    }
    else
        return 1;
}

void Link_voidInit()
{
    HLink_Private_voidInitQueue();
}

u8 Link_u8SendMessage()
{
    if (Private_Queue.elemNum==0)
        return 1;

    if (Private_Queue.elemNum>=16 )
    	GPIO_u8FastControlPinValue(GPIO_PORTC, GPIO_PIN13, GPIO_LOW);
    while (Private_Queue.elemNum!=0)
    {
        // Hold the system until SPI is ready to send message.
        while (GET_BIT(LINK_RASPBERRY_PI->SR,TXE) == 0 && GET_BIT(LINK_RASPBERRY_PI->SR,BSY) == 1);
        Link_u8SendDequeueMessage((u16*)&LINK_RASPBERRY_PI->DR);
    }
    return 0;
}

void Link_voidSendMessageDirectly(LinkMessage_t Copy_LinkMessage)
{
    while (GET_BIT(LINK_RASPBERRY_PI->SR,TXE) == 0 && GET_BIT(LINK_RASPBERRY_PI->SR,BSY) == 1);

	LINK_RASPBERRY_PI->DR = ((u16)Copy_LinkMessage.data) | ((((u16)Copy_LinkMessage.type) | (((u16)Copy_LinkMessage.source)<<4))<<8);
}
