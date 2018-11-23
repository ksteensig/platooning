/*******************************************************************************
* File Name: Comp_B.c
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

#include "Comp_B.h"

static Comp_B_backupStruct Comp_B_backup;


/*******************************************************************************
* Function Name: Comp_B_SaveConfig
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
void Comp_B_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: Comp_B_RestoreConfig
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
void Comp_B_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: Comp_B_Sleep
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
*  Comp_B_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void Comp_B_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(Comp_B_ACT_PWR_EN == (Comp_B_PWRMGR & Comp_B_ACT_PWR_EN))
    {
        /* Comp is enabled */
        Comp_B_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        Comp_B_backup.enableState = 0u;
    }    
    
    Comp_B_Stop();
    Comp_B_SaveConfig();
}


/*******************************************************************************
* Function Name: Comp_B_Wakeup
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
*  Comp_B_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Comp_B_Wakeup(void) 
{
    Comp_B_RestoreConfig();
    
    if(Comp_B_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        Comp_B_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
