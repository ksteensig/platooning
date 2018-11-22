/*******************************************************************************
* File Name: MixerA_PM.c  
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

#include "MixerA.h"

static MixerA_backupStruct  MixerA_backup;


/*******************************************************************************
* Function Name: MixerA_SaveConfig
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
void MixerA_SaveConfig(void) 
{
    /* Nothing to save before entering into sleep mode as all the registers used 
       here are retension registers. */
}


/*******************************************************************************
* Function Name: MixerA_RestoreConfig
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
void MixerA_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************
* Function Name: MixerA_Sleep
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
*  MixerA_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void MixerA_Sleep(void) 
{
    /* Save Mixer enable state */
    if((MixerA_PM_ACT_CFG_REG & MixerA_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        MixerA_backup.enableState = 1u;
        /* Stop the configuration */
        MixerA_Stop();
    }
    else
    {
        /* Component is disabled */
        MixerA_backup.enableState = 0u;
    }
    /* Saves the user configuration */
    MixerA_SaveConfig();
}


/*******************************************************************************
* Function Name: MixerA_Wakeup
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
*  MixerA_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void MixerA_Wakeup(void) 
{
    /* Restore the user configuration */
    MixerA_RestoreConfig();
    
    /* Enable's the component operation */
    if(MixerA_backup.enableState == 1u)
    {
        MixerA_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
