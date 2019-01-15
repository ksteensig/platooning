/*******************************************************************************
* File Name: steeringTimer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "steeringTimer.h"

static steeringTimer_backupStruct steeringTimer_backup;


/*******************************************************************************
* Function Name: steeringTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  steeringTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void steeringTimer_SaveConfig(void) 
{
    #if (!steeringTimer_UsingFixedFunction)
        steeringTimer_backup.TimerUdb = steeringTimer_ReadCounter();
        steeringTimer_backup.InterruptMaskValue = steeringTimer_STATUS_MASK;
        #if (steeringTimer_UsingHWCaptureCounter)
            steeringTimer_backup.TimerCaptureCounter = steeringTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!steeringTimer_UDB_CONTROL_REG_REMOVED)
            steeringTimer_backup.TimerControlRegister = steeringTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: steeringTimer_RestoreConfig
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
* Global variables:
*  steeringTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void steeringTimer_RestoreConfig(void) 
{   
    #if (!steeringTimer_UsingFixedFunction)

        steeringTimer_WriteCounter(steeringTimer_backup.TimerUdb);
        steeringTimer_STATUS_MASK =steeringTimer_backup.InterruptMaskValue;
        #if (steeringTimer_UsingHWCaptureCounter)
            steeringTimer_SetCaptureCount(steeringTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!steeringTimer_UDB_CONTROL_REG_REMOVED)
            steeringTimer_WriteControlRegister(steeringTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: steeringTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  steeringTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void steeringTimer_Sleep(void) 
{
    #if(!steeringTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(steeringTimer_CTRL_ENABLE == (steeringTimer_CONTROL & steeringTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            steeringTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            steeringTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    steeringTimer_Stop();
    steeringTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: steeringTimer_Wakeup
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
*  steeringTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void steeringTimer_Wakeup(void) 
{
    steeringTimer_RestoreConfig();
    #if(!steeringTimer_UDB_CONTROL_REG_REMOVED)
        if(steeringTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                steeringTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
