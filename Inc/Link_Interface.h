/***********************************************************************************************/
/***********************************************************************************************/
/****************************** Author: Fatema Ahmed & Armia Khairy ****************************/
/****************************************** Layer: HAL *****************************************/
/****************************************** SWC: Link ******************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef LINK_INTERFACE_H_
#define LINK_INTERFACE_H_

/** Sources **/
#define LINK_SOURCE_DHT11  0
#define LINK_SOURCE_FLAME  1
#define LINK_SOURCE_PIR    2
#define LINK_SOURCE_DOOR   3

/** Types **/
#define LINK_DHT11_TYPE_HUMIDITY       0
#define LINK_DHT11_TYPE_TEMPERATURE    1
#define LINK_DHT11_TYPE_ERROR          2

#define LINK_FLAME_TYPE_READING        0
#define LINK_PIR_TYPE_READING          0

typedef struct{
    u8 source;
    u8 type;
    u8 data;
} LinkMessage_t;

void HLink_voidInit();
void HLink_voidEnqueueMessage(LinkMessage_t Copy_linkMessage);
void HLink_voidSendMessageDirectly(LinkMessage_t Copy_LinkMessage);
u8 HLink_u8SendMessagefromQueue();
u8 HLink_u8ReturnQueueSize();


#endif
