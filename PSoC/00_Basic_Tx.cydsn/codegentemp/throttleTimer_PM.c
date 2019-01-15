/*******************************************************************************
* File Name: throttleTimer_PM.c
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

#include "throttleTimer.h"

static throttleTimer_backupStruct throttleTimer_backup;


/*******************************************************************************
* Function Name: throttleTimer_SaveConfig
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
*  throttleTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void throttleTimer_SaveConfig(void) 
{
    #if (!throttleTimer_UsingFixedFunction)
        throttleTimer_backup.TimerUdb = throttleTimer_ReadCounter();
        throttleTimer_backup.InterruptMaskValue = throttleTimer_STATUS_MASK;
        #if (throttleTimer_UsingHWCaptureCounter)
            throttleTimer_backup.TimerCaptureCounter = throttleTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!throttleTimer_UDB_CONTROL_REG_REMOVED)
            throttleTimer_backup.TimerControlRegister = throttleTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: throttleTimer_RestoreConfig
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
*  throttleTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void throttleTimer_RestoreConfig(void) 
{   
    #if (!throttleTimer_UsingFixedFunction)

        throttleTimer_WriteCounter(throttleTimer_backup.TimerUdb);
        throttleTimer_STATUS_MASK =throttleTimer_backup.InterruptMaskValue;
        #if (throttleTimer_UsingHWCaptureCounter)
            throttleTimer_SetCaptureCount(throttleTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!throttleTimer_UDB_CONTROL_REG_REMOVED)
            throttleTimer_WriteControlRegister(throttleTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: throttleTimer_Sleep
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
*  throttleTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void throttleTimer_Sleep(void) 
{
    #if(!throttleTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(throttleTimer_CTRL_ENABLE == (throttleTimer_CONTROL & throttleTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            throttleTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            throttleTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    throttleTimer_Stop();
    throttleTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: throttleTimer_Wakeup
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
*  throttleTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void throttleTimer_Wakeup(void) 
{
    throttleTimer_RestoreConfig();
    #if(!throttleTimer_UDB_CONTROL_REG_REMOVED)
        if(throttleTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                throttleTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
