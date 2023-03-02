/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Fatema Ahmed ************************************/
/***************************************** Layer: MCAL *****************************************/
/******************************************* SWC: SPI ******************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_Types.h"
#include "BitOperations.h"

#include "SPI_Config.h"
#include "SPI_Private.h"
#include "SPI_Interface.h"

u8 SPI_u8Initialization(volatile SPI_MemoryMap *SPIx, u8 u8ClkPhase, u8 u8ClkPolarity, u8 u8BaudRate, u8 u8FrameFormat, u8 u8DataFormat , u8 u8Enable)
{
	u8 ErrorState = 0;
	
	// Initialize Baud Rate PreScaler
	SPIx->CR1 |= (u8BaudRate << 3);

	// Initialize SPI Clock Polarity
	if (u8ClkPolarity == SPI_LowIDLE)
	CLR_BIT(SPIx->CR1, CPOL);
	else if (u8ClkPolarity == SPI_HighIDLE)
	SET_BIT(SPIx->CR1, CPOL);
	else
	{
		ErrorState = SPI_ErrorClkPolarity;
		return ErrorState;
	}

	// Initialize SPI Clock Phase
	if (u8ClkPhase == SPI_LeadingEdge)
	CLR_BIT(SPIx->CR1, CPHA);
	else if (u8ClkPhase == SPI_TrailingEdge)
	SET_BIT(SPIx->CR1, CPHA);
	else
	{
		ErrorState = SPI_ErrorClkPhase;
		return ErrorState;
	}
	
	// Data Format
	if (u8DataFormat == SPI_Data8Bits)
	CLR_BIT(SPIx->CR1, DFF);
	else if (u8DataFormat == SPI_Data16Bits)
	SET_BIT(SPIx->CR1, DFF);
	else
	{
		ErrorState = SPI_ErrorDataFormat;
		return ErrorState;
	}
	
	// Initialize Frame Format MSB/LSB first
	if (u8FrameFormat == SPI_MSBTrans)
	CLR_BIT(SPIx->CR1, LSBFIRST);
	else if (u8FrameFormat == SPI_LSBTrans)
	SET_BIT(SPIx->CR1, LSBFIRST);
	else
	{
		ErrorState = SPI_ErrorFormatTrans;
		return ErrorState;
	}
	
	// Enable/Disable SPI Peripheral
	if (u8Enable == SPI_Disable)
	CLR_BIT(SPIx->CR1, SPE);
	else if (u8Enable == SPI_Enable)
	SET_BIT(SPIx->CR1, SPE);
	else
	{
		ErrorState = SPI_ErrorEnable;
		return ErrorState;
	}

	return ErrorState;
}

void SPI_u8MasterMode (volatile SPI_MemoryMap *SPIx)
{
	SET_BIT(SPIx->CR1, MSTR);
	SET_BIT(SPIx->CR1, SSM);
	SET_BIT(SPIx->CR1, SSI);
}

u8 SPI_u8SlaveMode (volatile SPI_MemoryMap *SPIx, u8 u8SoftSlavManag, u8 u8SlavSelect)
{
	u8 ErrorState = 0;

	// Select Slave Config
	CLR_BIT(SPIx->CR1, MSTR);

	// Software Slave Management
	if (u8SoftSlavManag == SPI_DisSoftSlaveManag)
	CLR_BIT(SPIx->CR1, SSM);
	else if (u8SoftSlavManag == SPI_EnSoftSlaveManag)
	SET_BIT(SPIx->CR1, SSM);
	else
	{
		ErrorState = SPI_ErrorSlaveSoftwareSelection;
		return ErrorState;
	}

	// Select Slave By Software
	if (u8SlavSelect == SPI_UnSelectSlave)
	CLR_BIT(SPIx->CR1, SSI);
	else if (u8SlavSelect == SPI_SelectSlave)
	SET_BIT(SPIx->CR1, SSI);
	else
	{
		ErrorState = SPI_ErrorSlaveSoftwareSelection;
		return ErrorState;
	}

	return ErrorState;
}

void SPI_voidTransmit(volatile SPI_MemoryMap *SPIx, u16 u16Data)
{
	SPIx->DR = u16Data ;

	while(GET_BIT(SPIx->SR, TXE) == 0) {} // SPI1 is not empty
	while(GET_BIT(SPIx->SR, BSY) == 1) {} // SPI1 is busy in communication or Tx buffer is not empty
}

u16 SPI_u16Receive(volatile SPI_MemoryMap *SPIx)
{
	return SPIx->DR;
}
