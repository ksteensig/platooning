/******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version 1.0
*
*  Description: 
*   API for controlling the maximum peak detector.
*
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <CYDEVICE.H>
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_Comp_1.h"
#include "`$INSTANCE_NAME`_Sample_Hold.h"

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
* Summary:
*   Enables the peak detector component.
*
*
* Parameters:
*   void.
*
* Return:
*   void.
*   
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
	`$INSTANCE_NAME`_Sample_Hold_Start();
	`$INSTANCE_NAME`_Comp_1_Start();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
* Summary:
*   Disables the peak detector component.
*
*
* Parameters:
*   void.
*
* Return:
*   void.
*   
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
	`$INSTANCE_NAME`_Sample_Hold_Stop();
	`$INSTANCE_NAME`_Comp_1_Stop();
}

/* [] END OF FILE */
