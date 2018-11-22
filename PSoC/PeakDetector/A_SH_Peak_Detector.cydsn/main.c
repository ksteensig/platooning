/******************************************************************************
* File Name: Main.c
* Version 1.0
*
*  Description:
*   Sample & Hold based peak detector example. Details in AN60321.
*
*  Input: P0[0] - Analog input. For sample clock speed of 100 kHz, a 3 kHz 
*					1V p-p sine wave input works well for demonstration. 
*  Output: P1[7] - Digital output. 
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <device.h>

void main()
{
	/* Start S&H-based peak detector: */
	Peak_Detector_1_Start();

    /* CYGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
