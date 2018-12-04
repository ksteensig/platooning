/*******************************************************************************
* File Name: PWM_H_BRIDGE_PM.c
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

#include "PWM_H_BRIDGE.h"

static PWM_H_BRIDGE_backupStruct PWM_H_BRIDGE_backup;


/*******************************************************************************
* Function Name: PWM_H_BRIDGE_SaveConfig
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
*  PWM_H_BRIDGE_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_H_BRIDGE_SaveConfig(void) 
{

    #if(!PWM_H_BRIDGE_UsingFixedFunction)
        #if(!PWM_H_BRIDGE_PWMModeIsCenterAligned)
            PWM_H_BRIDGE_backup.PWMPeriod = PWM_H_BRIDGE_ReadPeriod();
        #endif /* (!PWM_H_BRIDGE_PWMModeIsCenterAligned) */
        PWM_H_BRIDGE_backup.PWMUdb = PWM_H_BRIDGE_ReadCounter();
        #if (PWM_H_BRIDGE_UseStatus)
            PWM_H_BRIDGE_backup.InterruptMaskValue = PWM_H_BRIDGE_STATUS_MASK;
        #endif /* (PWM_H_BRIDGE_UseStatus) */

        #if(PWM_H_BRIDGE_DeadBandMode == PWM_H_BRIDGE__B_PWM__DBM_256_CLOCKS || \
            PWM_H_BRIDGE_DeadBandMode == PWM_H_BRIDGE__B_PWM__DBM_2_4_CLOCKS)
            PWM_H_BRIDGE_backup.PWMdeadBandValue = PWM_H_BRIDGE_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_H_BRIDGE_KillModeMinTime)
             PWM_H_BRIDGE_backup.PWMKillCounterPeriod = PWM_H_BRIDGE_ReadKillTime();
        #endif /* (PWM_H_BRIDGE_KillModeMinTime) */

        #if(PWM_H_BRIDGE_UseControl)
            PWM_H_BRIDGE_backup.PWMControlRegister = PWM_H_BRIDGE_ReadControlRegister();
        #endif /* (PWM_H_BRIDGE_UseControl) */
    #endif  /* (!PWM_H_BRIDGE_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_H_BRIDGE_RestoreConfig
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
*  PWM_H_BRIDGE_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_H_BRIDGE_RestoreConfig(void) 
{
        #if(!PWM_H_BRIDGE_UsingFixedFunction)
            #if(!PWM_H_BRIDGE_PWMModeIsCenterAligned)
                PWM_H_BRIDGE_WritePeriod(PWM_H_BRIDGE_backup.PWMPeriod);
            #endif /* (!PWM_H_BRIDGE_PWMModeIsCenterAligned) */

            PWM_H_BRIDGE_WriteCounter(PWM_H_BRIDGE_backup.PWMUdb);

            #if (PWM_H_BRIDGE_UseStatus)
                PWM_H_BRIDGE_STATUS_MASK = PWM_H_BRIDGE_backup.InterruptMaskValue;
            #endif /* (PWM_H_BRIDGE_UseStatus) */

            #if(PWM_H_BRIDGE_DeadBandMode == PWM_H_BRIDGE__B_PWM__DBM_256_CLOCKS || \
                PWM_H_BRIDGE_DeadBandMode == PWM_H_BRIDGE__B_PWM__DBM_2_4_CLOCKS)
                PWM_H_BRIDGE_WriteDeadTime(PWM_H_BRIDGE_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_H_BRIDGE_KillModeMinTime)
                PWM_H_BRIDGE_WriteKillTime(PWM_H_BRIDGE_backup.PWMKillCounterPeriod);
            #endif /* (PWM_H_BRIDGE_KillModeMinTime) */

            #if(PWM_H_BRIDGE_UseControl)
                PWM_H_BRIDGE_WriteControlRegister(PWM_H_BRIDGE_backup.PWMControlRegister);
            #endif /* (PWM_H_BRIDGE_UseControl) */
        #endif  /* (!PWM_H_BRIDGE_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_H_BRIDGE_Sleep
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
*  PWM_H_BRIDGE_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_H_BRIDGE_Sleep(void) 
{
    #if(PWM_H_BRIDGE_UseControl)
        if(PWM_H_BRIDGE_CTRL_ENABLE == (PWM_H_BRIDGE_CONTROL & PWM_H_BRIDGE_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_H_BRIDGE_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_H_BRIDGE_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_H_BRIDGE_UseControl) */

    /* Stop component */
    PWM_H_BRIDGE_Stop();

    /* Save registers configuration */
    PWM_H_BRIDGE_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_H_BRIDGE_Wakeup
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
*  PWM_H_BRIDGE_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_H_BRIDGE_Wakeup(void) 
{
     /* Restore registers values */
    PWM_H_BRIDGE_RestoreConfig();

    if(PWM_H_BRIDGE_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_H_BRIDGE_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
