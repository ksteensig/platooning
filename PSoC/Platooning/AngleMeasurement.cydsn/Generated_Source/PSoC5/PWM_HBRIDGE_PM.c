/*******************************************************************************
* File Name: PWM_HBRIDGE_PM.c
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

#include "PWM_HBRIDGE.h"

static PWM_HBRIDGE_backupStruct PWM_HBRIDGE_backup;


/*******************************************************************************
* Function Name: PWM_HBRIDGE_SaveConfig
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
*  PWM_HBRIDGE_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_HBRIDGE_SaveConfig(void) 
{

    #if(!PWM_HBRIDGE_UsingFixedFunction)
        #if(!PWM_HBRIDGE_PWMModeIsCenterAligned)
            PWM_HBRIDGE_backup.PWMPeriod = PWM_HBRIDGE_ReadPeriod();
        #endif /* (!PWM_HBRIDGE_PWMModeIsCenterAligned) */
        PWM_HBRIDGE_backup.PWMUdb = PWM_HBRIDGE_ReadCounter();
        #if (PWM_HBRIDGE_UseStatus)
            PWM_HBRIDGE_backup.InterruptMaskValue = PWM_HBRIDGE_STATUS_MASK;
        #endif /* (PWM_HBRIDGE_UseStatus) */

        #if(PWM_HBRIDGE_DeadBandMode == PWM_HBRIDGE__B_PWM__DBM_256_CLOCKS || \
            PWM_HBRIDGE_DeadBandMode == PWM_HBRIDGE__B_PWM__DBM_2_4_CLOCKS)
            PWM_HBRIDGE_backup.PWMdeadBandValue = PWM_HBRIDGE_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_HBRIDGE_KillModeMinTime)
             PWM_HBRIDGE_backup.PWMKillCounterPeriod = PWM_HBRIDGE_ReadKillTime();
        #endif /* (PWM_HBRIDGE_KillModeMinTime) */

        #if(PWM_HBRIDGE_UseControl)
            PWM_HBRIDGE_backup.PWMControlRegister = PWM_HBRIDGE_ReadControlRegister();
        #endif /* (PWM_HBRIDGE_UseControl) */
    #endif  /* (!PWM_HBRIDGE_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_HBRIDGE_RestoreConfig
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
*  PWM_HBRIDGE_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_HBRIDGE_RestoreConfig(void) 
{
        #if(!PWM_HBRIDGE_UsingFixedFunction)
            #if(!PWM_HBRIDGE_PWMModeIsCenterAligned)
                PWM_HBRIDGE_WritePeriod(PWM_HBRIDGE_backup.PWMPeriod);
            #endif /* (!PWM_HBRIDGE_PWMModeIsCenterAligned) */

            PWM_HBRIDGE_WriteCounter(PWM_HBRIDGE_backup.PWMUdb);

            #if (PWM_HBRIDGE_UseStatus)
                PWM_HBRIDGE_STATUS_MASK = PWM_HBRIDGE_backup.InterruptMaskValue;
            #endif /* (PWM_HBRIDGE_UseStatus) */

            #if(PWM_HBRIDGE_DeadBandMode == PWM_HBRIDGE__B_PWM__DBM_256_CLOCKS || \
                PWM_HBRIDGE_DeadBandMode == PWM_HBRIDGE__B_PWM__DBM_2_4_CLOCKS)
                PWM_HBRIDGE_WriteDeadTime(PWM_HBRIDGE_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_HBRIDGE_KillModeMinTime)
                PWM_HBRIDGE_WriteKillTime(PWM_HBRIDGE_backup.PWMKillCounterPeriod);
            #endif /* (PWM_HBRIDGE_KillModeMinTime) */

            #if(PWM_HBRIDGE_UseControl)
                PWM_HBRIDGE_WriteControlRegister(PWM_HBRIDGE_backup.PWMControlRegister);
            #endif /* (PWM_HBRIDGE_UseControl) */
        #endif  /* (!PWM_HBRIDGE_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_HBRIDGE_Sleep
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
*  PWM_HBRIDGE_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_HBRIDGE_Sleep(void) 
{
    #if(PWM_HBRIDGE_UseControl)
        if(PWM_HBRIDGE_CTRL_ENABLE == (PWM_HBRIDGE_CONTROL & PWM_HBRIDGE_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_HBRIDGE_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_HBRIDGE_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_HBRIDGE_UseControl) */

    /* Stop component */
    PWM_HBRIDGE_Stop();

    /* Save registers configuration */
    PWM_HBRIDGE_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_HBRIDGE_Wakeup
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
*  PWM_HBRIDGE_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_HBRIDGE_Wakeup(void) 
{
     /* Restore registers values */
    PWM_HBRIDGE_RestoreConfig();

    if(PWM_HBRIDGE_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_HBRIDGE_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
