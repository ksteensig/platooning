/******************************************************************************
* File Name: Maximum_Peak_Detector_B.c
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
#include "Maximum_Peak_Detector_B.h"
#include "Maximum_Peak_Detector_B_Comp_1.h"
#include "Maximum_Peak_Detector_B_Sample_Hold.h"

/*******************************************************************************
* Function Name: Maximum_Peak_Detector_B_Start
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
void Maximum_Peak_Detector_B_Start(void)
{
	Maximum_Peak_Detector_B_Sample_Hold_Start();
	Maximum_Peak_Detector_B_Comp_1_Start();
}

/*******************************************************************************
* Function Name: Maximum_Peak_Detector_B_Stop
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
void Maximum_Peak_Detector_B_Stop(void)
{
	Maximum_Peak_Detector_B_Sample_Hold_Stop();
	Maximum_Peak_Detector_B_Comp_1_Stop();
}

/* [] END OF FILE */
