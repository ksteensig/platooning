/*******************************************************************************
* File Name: PWM_SERVO_PM.c
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

#include "PWM_SERVO.h"

static PWM_SERVO_backupStruct PWM_SERVO_backup;


/*******************************************************************************
* Function Name: PWM_SERVO_SaveConfig
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
*  PWM_SERVO_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_SERVO_SaveConfig(void) 
{

    #if(!PWM_SERVO_UsingFixedFunction)
        #if(!PWM_SERVO_PWMModeIsCenterAligned)
            PWM_SERVO_backup.PWMPeriod = PWM_SERVO_ReadPeriod();
        #endif /* (!PWM_SERVO_PWMModeIsCenterAligned) */
        PWM_SERVO_backup.PWMUdb = PWM_SERVO_ReadCounter();
        #if (PWM_SERVO_UseStatus)
            PWM_SERVO_backup.InterruptMaskValue = PWM_SERVO_STATUS_MASK;
        #endif /* (PWM_SERVO_UseStatus) */

        #if(PWM_SERVO_DeadBandMode == PWM_SERVO__B_PWM__DBM_256_CLOCKS || \
            PWM_SERVO_DeadBandMode == PWM_SERVO__B_PWM__DBM_2_4_CLOCKS)
            PWM_SERVO_backup.PWMdeadBandValue = PWM_SERVO_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_SERVO_KillModeMinTime)
             PWM_SERVO_backup.PWMKillCounterPeriod = PWM_SERVO_ReadKillTime();
        #endif /* (PWM_SERVO_KillModeMinTime) */

        #if(PWM_SERVO_UseControl)
            PWM_SERVO_backup.PWMControlRegister = PWM_SERVO_ReadControlRegister();
        #endif /* (PWM_SERVO_UseControl) */
    #endif  /* (!PWM_SERVO_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_SERVO_RestoreConfig
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
*  PWM_SERVO_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_SERVO_RestoreConfig(void) 
{
        #if(!PWM_SERVO_UsingFixedFunction)
            #if(!PWM_SERVO_PWMModeIsCenterAligned)
                PWM_SERVO_WritePeriod(PWM_SERVO_backup.PWMPeriod);
            #endif /* (!PWM_SERVO_PWMModeIsCenterAligned) */

            PWM_SERVO_WriteCounter(PWM_SERVO_backup.PWMUdb);

            #if (PWM_SERVO_UseStatus)
                PWM_SERVO_STATUS_MASK = PWM_SERVO_backup.InterruptMaskValue;
            #endif /* (PWM_SERVO_UseStatus) */

            #if(PWM_SERVO_DeadBandMode == PWM_SERVO__B_PWM__DBM_256_CLOCKS || \
                PWM_SERVO_DeadBandMode == PWM_SERVO__B_PWM__DBM_2_4_CLOCKS)
                PWM_SERVO_WriteDeadTime(PWM_SERVO_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_SERVO_KillModeMinTime)
                PWM_SERVO_WriteKillTime(PWM_SERVO_backup.PWMKillCounterPeriod);
            #endif /* (PWM_SERVO_KillModeMinTime) */

            #if(PWM_SERVO_UseControl)
                PWM_SERVO_WriteControlRegister(PWM_SERVO_backup.PWMControlRegister);
            #endif /* (PWM_SERVO_UseControl) */
        #endif  /* (!PWM_SERVO_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_SERVO_Sleep
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
*  PWM_SERVO_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_SERVO_Sleep(void) 
{
    #if(PWM_SERVO_UseControl)
        if(PWM_SERVO_CTRL_ENABLE == (PWM_SERVO_CONTROL & PWM_SERVO_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_SERVO_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_SERVO_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_SERVO_UseControl) */

    /* Stop component */
    PWM_SERVO_Stop();

    /* Save registers configuration */
    PWM_SERVO_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_SERVO_Wakeup
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
*  PWM_SERVO_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_SERVO_Wakeup(void) 
{
     /* Restore registers values */
    PWM_SERVO_RestoreConfig();

    if(PWM_SERVO_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_SERVO_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
