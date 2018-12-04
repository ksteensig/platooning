/*******************************************************************************
* File Name: Peak_Detector_1_Mixer_1_PM.c  
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

#include "Peak_Detector_1_Mixer_1.h"

static Peak_Detector_1_Mixer_1_backupStruct  Peak_Detector_1_Mixer_1_backup;


/*******************************************************************************
* Function Name: Peak_Detector_1_Mixer_1_SaveConfig
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
void Peak_Detector_1_Mixer_1_SaveConfig(void) 
{
    /* Nothing to save before entering into sleep mode as all the registers used 
       here are retension registers. */
}


/*******************************************************************************
* Function Name: Peak_Detector_1_Mixer_1_RestoreConfig
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
void Peak_Detector_1_Mixer_1_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************
* Function Name: Peak_Detector_1_Mixer_1_Sleep
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
*  Peak_Detector_1_Mixer_1_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Peak_Detector_1_Mixer_1_Sleep(void) 
{
    /* Save Mixer enable state */
    if((Peak_Detector_1_Mixer_1_PM_ACT_CFG_REG & Peak_Detector_1_Mixer_1_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        Peak_Detector_1_Mixer_1_backup.enableState = 1u;
        /* Stop the configuration */
        Peak_Detector_1_Mixer_1_Stop();
    }
    else
    {
        /* Component is disabled */
        Peak_Detector_1_Mixer_1_backup.enableState = 0u;
    }
    /* Saves the user configuration */
    Peak_Detector_1_Mixer_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Peak_Detector_1_Mixer_1_Wakeup
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
*  Peak_Detector_1_Mixer_1_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Peak_Detector_1_Mixer_1_Wakeup(void) 
{
    /* Restore the user configuration */
    Peak_Detector_1_Mixer_1_RestoreConfig();
    
    /* Enable's the component operation */
    if(Peak_Detector_1_Mixer_1_backup.enableState == 1u)
    {
        Peak_Detector_1_Mixer_1_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
