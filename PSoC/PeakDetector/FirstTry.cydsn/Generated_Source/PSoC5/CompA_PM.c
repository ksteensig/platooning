/*******************************************************************************
* File Name: CompA.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "CompA.h"

static CompA_backupStruct CompA_backup;


/*******************************************************************************
* Function Name: CompA_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void CompA_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: CompA_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
********************************************************************************/
void CompA_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: CompA_Sleep
********************************************************************************
*
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
* Global variables:
*  CompA_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void CompA_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(CompA_ACT_PWR_EN == (CompA_PWRMGR & CompA_ACT_PWR_EN))
    {
        /* Comp is enabled */
        CompA_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        CompA_backup.enableState = 0u;
    }    
    
    CompA_Stop();
    CompA_SaveConfig();
}


/*******************************************************************************
* Function Name: CompA_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  CompA_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CompA_Wakeup(void) 
{
    CompA_RestoreConfig();
    
    if(CompA_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        CompA_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
