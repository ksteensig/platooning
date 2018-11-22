/*******************************************************************************
* File Name: CompB.c
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

#include "CompB.h"

static CompB_backupStruct CompB_backup;


/*******************************************************************************
* Function Name: CompB_SaveConfig
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
void CompB_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: CompB_RestoreConfig
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
void CompB_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: CompB_Sleep
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
*  CompB_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void CompB_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(CompB_ACT_PWR_EN == (CompB_PWRMGR & CompB_ACT_PWR_EN))
    {
        /* Comp is enabled */
        CompB_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        CompB_backup.enableState = 0u;
    }    
    
    CompB_Stop();
    CompB_SaveConfig();
}


/*******************************************************************************
* Function Name: CompB_Wakeup
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
*  CompB_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CompB_Wakeup(void) 
{
    CompB_RestoreConfig();
    
    if(CompB_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        CompB_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
