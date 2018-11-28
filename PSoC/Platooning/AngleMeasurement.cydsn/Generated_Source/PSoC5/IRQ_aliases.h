/*******************************************************************************
* File Name: IRQ.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_IRQ_ALIASES_H) /* Pins IRQ_ALIASES_H */
#define CY_PINS_IRQ_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define IRQ_0			(IRQ__0__PC)
#define IRQ_0_INTR	((uint16)((uint16)0x0001u << IRQ__0__SHIFT))

#define IRQ_INTR_ALL	 ((uint16)(IRQ_0_INTR))

#endif /* End Pins IRQ_ALIASES_H */


/* [] END OF FILE */
