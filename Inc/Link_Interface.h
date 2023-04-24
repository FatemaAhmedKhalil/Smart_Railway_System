/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
/******************************* Author: Fatema Ahmed & Armia Khairy ***************************/
/****************************************** Layer: HAL *****************************************/
/****************************************** SWC: Link ******************************************/
/**************************************** Version: 1.00 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef LINK_INTERFACE_H_
#define LINK_INTERFACE_H_

typedef struct{
    u8 source;
    u8 type;
    u8 data;
} LinkMessage_t;

/** Sources **/
#define LINK_SOURCE_DHT11  0
#define LINK_SOURCE_FLAME  1
#define LINK_SOURCE_PIR    2
#define LINK_SOURCE_DOOR   3

/** Types **/
#define LINK_DHT11_TYPE_HUMIDITY       2
#define LINK_DHT11_TYPE_TEMPERATURE    1
#define LINK_DHT11_TYPE_ERROR          3

#define LINK_FLAME_TYPE_READING        0
#define LINK_PIR_TYPE_READING          0

void Link_voidInit();
u8 Link_u8ReturnQueueSize();
void Link_voidEnqueueMessage(LinkMessage_t Copy_linkMessage);
u8 Link_u8SendDequeueMessage();
void Link_voidSendMessageDirectly(LinkMessage_t Copy_LinkMessage);

#endif
