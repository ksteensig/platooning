/*******************************************************************************
* File Name: Maximum_Peak_Detector_A_Sample_Hold_PM.c  
* Version 2.0
*
* Description:
*  This file provides the power manager source code to the API for 
*  the MIXER component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Maximum_Peak_Detector_A_Sample_Hold.h"

static Maximum_Peak_Detector_A_Sample_Hold_backupStruct  Maximum_Peak_Detector_A_Sample_Hold_backup;


/*******************************************************************************
* Function Name: Maximum_Peak_Detector_A_Sample_Hold_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  void.
*
* Return: 
*  void.
*
*******************************************************************************/
void Maximum_Peak_Detector_A_Sample_Hold_SaveConfig(void) 
{
    /* Nothing to save before entering into sleep mode as all the registers used 
       here are retension registers. */
}


/*******************************************************************************
* Function Name: Maximum_Peak_Detector_A_Sample_Hold_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void.
*
* Return: 
*  void
*
*******************************************************************************/
void Maximum_Peak_Detector_A_Sample_Hold_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************
* Function Name: Maximum_Peak_Detector_A_Sample_Hold_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  Maximum_Peak_Detector_A_Sample_Hold_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Maximum_Peak_Detector_A_Sample_Hold_Sleep(void) 
{
    /* Save Mixer enable state */
    if((Maximum_Peak_Detector_A_Sample_Hold_PM_ACT_CFG_REG & Maximum_Peak_Detector_A_Sample_Hold_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        Maximum_Peak_Detector_A_Sample_Hold_backup.enableState = 1u;
        /* Stop the configuration */
        Maximum_Peak_Detector_A_Sample_Hold_Stop();
    }
    else
    {
        /* Component is disabled */
        Maximum_Peak_Detector_A_Sample_Hold_backup.enableState = 0u;
    }
    /* Saves the user configuration */
    Maximum_Peak_Detector_A_Sample_Hold_SaveConfig();
}


/*******************************************************************************
* Function Name: Maximum_Peak_Detector_A_Sample_Hold_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  void
*
* Global variables:
*  Maximum_Peak_Detector_A_Sample_Hold_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Maximum_Peak_Detector_A_Sample_Hold_Wakeup(void) 
{
    /* Restore the user configuration */
    Maximum_Peak_Detector_A_Sample_Hold_RestoreConfig();
    
    /* Enable's the component operation */
    if(Maximum_Peak_Detector_A_Sample_Hold_backup.enableState == 1u)
    {
        Maximum_Peak_Detector_A_Sample_Hold_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
