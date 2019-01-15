/*******************************************************************************
* File Name: PWMSend_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWMSend.h"

static PWMSend_backupStruct PWMSend_backup;


/*******************************************************************************
* Function Name: PWMSend_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMSend_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWMSend_SaveConfig(void) 
{

    #if(!PWMSend_UsingFixedFunction)
        #if(!PWMSend_PWMModeIsCenterAligned)
            PWMSend_backup.PWMPeriod = PWMSend_ReadPeriod();
        #endif /* (!PWMSend_PWMModeIsCenterAligned) */
        PWMSend_backup.PWMUdb = PWMSend_ReadCounter();
        #if (PWMSend_UseStatus)
            PWMSend_backup.InterruptMaskValue = PWMSend_STATUS_MASK;
        #endif /* (PWMSend_UseStatus) */

        #if(PWMSend_DeadBandMode == PWMSend__B_PWM__DBM_256_CLOCKS || \
            PWMSend_DeadBandMode == PWMSend__B_PWM__DBM_2_4_CLOCKS)
            PWMSend_backup.PWMdeadBandValue = PWMSend_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWMSend_KillModeMinTime)
             PWMSend_backup.PWMKillCounterPeriod = PWMSend_ReadKillTime();
        #endif /* (PWMSend_KillModeMinTime) */

        #if(PWMSend_UseControl)
            PWMSend_backup.PWMControlRegister = PWMSend_ReadControlRegister();
        #endif /* (PWMSend_UseControl) */
    #endif  /* (!PWMSend_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMSend_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMSend_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWMSend_RestoreConfig(void) 
{
        #if(!PWMSend_UsingFixedFunction)
            #if(!PWMSend_PWMModeIsCenterAligned)
                PWMSend_WritePeriod(PWMSend_backup.PWMPeriod);
            #endif /* (!PWMSend_PWMModeIsCenterAligned) */

            PWMSend_WriteCounter(PWMSend_backup.PWMUdb);

            #if (PWMSend_UseStatus)
                PWMSend_STATUS_MASK = PWMSend_backup.InterruptMaskValue;
            #endif /* (PWMSend_UseStatus) */

            #if(PWMSend_DeadBandMode == PWMSend__B_PWM__DBM_256_CLOCKS || \
                PWMSend_DeadBandMode == PWMSend__B_PWM__DBM_2_4_CLOCKS)
                PWMSend_WriteDeadTime(PWMSend_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWMSend_KillModeMinTime)
                PWMSend_WriteKillTime(PWMSend_backup.PWMKillCounterPeriod);
            #endif /* (PWMSend_KillModeMinTime) */

            #if(PWMSend_UseControl)
                PWMSend_WriteControlRegister(PWMSend_backup.PWMControlRegister);
            #endif /* (PWMSend_UseControl) */
        #endif  /* (!PWMSend_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWMSend_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMSend_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWMSend_Sleep(void) 
{
    #if(PWMSend_UseControl)
        if(PWMSend_CTRL_ENABLE == (PWMSend_CONTROL & PWMSend_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWMSend_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWMSend_backup.PWMEnableState = 0u;
        }
    #endif /* (PWMSend_UseControl) */

    /* Stop component */
    PWMSend_Stop();

    /* Save registers configuration */
    PWMSend_SaveConfig();
}


/*******************************************************************************
* Function Name: PWMSend_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMSend_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWMSend_Wakeup(void) 
{
     /* Restore registers values */
    PWMSend_RestoreConfig();

    if(PWMSend_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWMSend_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
