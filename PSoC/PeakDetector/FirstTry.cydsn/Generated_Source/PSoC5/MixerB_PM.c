/*******************************************************************************
* File Name: MixerB_PM.c  
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

#include "MixerB.h"

static MixerB_backupStruct  MixerB_backup;


/*******************************************************************************
* Function Name: MixerB_SaveConfig
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
void MixerB_SaveConfig(void) 
{
    /* Nothing to save before entering into sleep mode as all the registers used 
       here are retension registers. */
}


/*******************************************************************************
* Function Name: MixerB_RestoreConfig
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
void MixerB_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************
* Function Name: MixerB_Sleep
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
*  MixerB_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void MixerB_Sleep(void) 
{
    /* Save Mixer enable state */
    if((MixerB_PM_ACT_CFG_REG & MixerB_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        MixerB_backup.enableState = 1u;
        /* Stop the configuration */
        MixerB_Stop();
    }
    else
    {
        /* Component is disabled */
        MixerB_backup.enableState = 0u;
    }
    /* Saves the user configuration */
    MixerB_SaveConfig();
}


/*******************************************************************************
* Function Name: MixerB_Wakeup
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
*  MixerB_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void MixerB_Wakeup(void) 
{
    /* Restore the user configuration */
    MixerB_RestoreConfig();
    
    /* Enable's the component operation */
    if(MixerB_backup.enableState == 1u)
    {
        MixerB_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
