/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/******************************************* SWC: SPI ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/** Error States **/
#define SPI_ErrorClkPhase					13
#define SPI_ErrorClkPolarity				14
#define SPI_ErrorBaudRate					15
#define SPI_ErrorFormatTrans				16
#define SPI_ErrorSlaveSoftwareSelection		17
#define SPI_ErrorDataFormat					18
#define SPI_ErrorEnable						19

typedef struct
{
	u32	CR1;		// SPI control register 1 (not used in I2S mode)
	u32	CR2;		// SPI control register 2
	u32	SR;			// SPI status register
	u32	DR;			// SPI data register
	u32	CRCPR;		// SPI CRC polynomial register (not used in I2S mode)
	u32	RXCRCR;		// SPI RX CRC register (not used in I2S mode)
	u32 TXCRCR;		// SPI TX CRC register (not used in I2S mode)
	u32 I2SCFGR;	// SPI_I2S configuration register
	u32 I2SPR;		// SPI_I2S PreScaler register
}SPI_MemoryMap;

#define	SPI1		( (volatile SPI_MemoryMap *)(0x40013000) )
#define	SPI2		( (volatile SPI_MemoryMap *)(0x40003800) )
#define	SPI3		( (volatile SPI_MemoryMap *)(0x40003C00) )
/****************************************************/
/* Define Which SPI you will Use:					*/
/*          -> SPI1									*/
/*          -> SPI2									*/
/*          -> SPI6									*/
/****************************************************/

/************************************************************/
/* FIRST: Define: Master Mode								*/
/*															*/
/* OR: Define: Slave Mode									*/
/*			1- En/Dis able Slave SoftWare Selection			*/
/*			2- Select/UnSelect The Slave					*/
/* THEN: Initialize:										*/
/*		1- Clock Phase										*/
/*		2- Clock Polarity									*/
/*		3- Clock BaudRate									*/
/*		4- Frame Format										*/
/*		5- Data Format										*/
/*		6- Enable or Disable SPI							*/
/*															*/
/*															*/
/************************************************************/

#define SPI_LeadingEdge    0
#define SPI_TrailingEdge   1

#define SPI_LowIDLE    0
#define SPI_HighIDLE   1

#define SPI_SlaveConfig    0
#define SPI_MasterConfig   1

#define SPI_fPCLK2		0
#define SPI_fPCLK4		1
#define SPI_fPCLK8		2
#define SPI_fPCLK16		3
#define SPI_fPCLK32		4
#define SPI_fPCLK64		5
#define SPI_fPCLK128	6
#define SPI_fPCLK256	7

#define SPI_MSBTrans    0
#define SPI_LSBTrans	1

#define SPI_DisSoftSlaveManag		0
#define SPI_EnSoftSlaveManag		1

#define SPI_UnSelectSlave	0
#define SPI_SelectSlave		1

#define SPI_Data8Bits		0
#define SPI_Data16Bits		1

#define SPI_Disable		0
#define SPI_Enable		1

void SPI_u8MasterMode (volatile SPI_MemoryMap *SPIx);
u8 SPI_u8SlaveMode (volatile SPI_MemoryMap *SPIx, u8 u8SoftSlavManag, u8 u8SlavSelect);
u8 SPI_u8Initialization(volatile SPI_MemoryMap *SPIx, u8 u8ClkPhase, u8 u8ClkPolarity, u8 u8BaudRate, u8 u8FrameFormat, u8 u8DataFormat , u8 u8Enable);
void SPI_voidTransmit(volatile SPI_MemoryMap *SPIx, u16 u16Data);
u16 SPI_u16Receive(volatile SPI_MemoryMap *SPIx);

#endif
