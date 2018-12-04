/***************************************************************************
* File Name: DMA_ADC_A_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <DMA_ADC_A_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* DMA_ADC_A__DRQ_CTL_REG
* 
* 
* DMA_ADC_A__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* DMA_ADC_A__NUMBEROF_TDS
* 
* Priority of this channel.
* DMA_ADC_A__PRIORITY
* 
* True if DMA_ADC_A_TERMIN_SEL is used.
* DMA_ADC_A__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* DMA_ADC_A__TERMIN_SEL
* 
* 
* True if DMA_ADC_A_TERMOUT0_SEL is used.
* DMA_ADC_A__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* DMA_ADC_A__TERMOUT0_SEL
* 
* 
* True if DMA_ADC_A_TERMOUT1_SEL is used.
* DMA_ADC_A__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* DMA_ADC_A__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of DMA_ADC_A dma channel */
uint8 DMA_ADC_A_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 DMA_ADC_A_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 DMA_ADC_A_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    DMA_ADC_A_DmaHandle = (uint8)DMA_ADC_A__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(DMA_ADC_A_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)DMA_ADC_A__TERMOUT0_SEL,
                                  (uint8)DMA_ADC_A__TERMOUT1_SEL,
                                  (uint8)DMA_ADC_A__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(DMA_ADC_A_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(DMA_ADC_A_DmaHandle, (uint8)DMA_ADC_A__PRIORITY);
    
    return DMA_ADC_A_DmaHandle;
}

/*********************************************************************
* Function Name: void DMA_ADC_A_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with DMA_ADC_A.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void DMA_ADC_A_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(DMA_ADC_A_DmaHandle);
}

