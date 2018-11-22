/******************************************************************************
* File Name: Peak_Detector_A.c
* Version 1.0
*
*  Description:
*   API for controlling the peak detector.
*
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <CYDEVICE.H>
#include "Peak_Detector_A.h"
#include "Peak_Detector_A_Comp_1.h"
#include "Peak_Detector_A_Mixer_1.h"


/*******************************************************************************
* Function Name: Peak_Detector_A_Start
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
void Peak_Detector_A_Start(void)
{
	Peak_Detector_A_Mixer_1_Start();
	Peak_Detector_A_Comp_1_Start();
}

/*******************************************************************************
* Function Name: Peak_Detector_A_Stop
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
void Peak_Detector_A_Stop(void)
{
	Peak_Detector_A_Mixer_1_Stop();
	Peak_Detector_A_Comp_1_Stop();
}

/* [] END OF FILE */
