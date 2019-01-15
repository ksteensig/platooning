/*******************************************************************************
* File Name: PWMServo_PM.c
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

#include "PWMServo.h"

static PWMServo_backupStruct PWMServo_backup;


/*******************************************************************************
* Function Name: PWMServo_SaveConfig
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
*  PWMServo_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWMServo_SaveConfig(void) 
{

    #if(!PWMServo_UsingFixedFunction)
        #if(!PWMServo_PWMModeIsCenterAligned)
            PWMServo_backup.PWMPeriod = PWMServo_ReadPeriod();
        #endif /* (!PWMServo_PWMModeIsCenterAligned) */
        PWMServo_backup.PWMUdb = PWMServo_ReadCounter();
        #if (PWMServo_UseStatus)
            PWMServo_backup.InterruptMaskValue = PWMServo_STATUS_MASK;
        #endif /* (PWMServo_UseStatus) */

        #if(PWMServo_DeadBandMode == PWMServo__B_PWM__DBM_256_CLOCKS || \
            PWMServo_DeadBandMode == PWMServo__B_PWM__DBM_2_4_CLOCKS)
            PWMServo_backup.PWMdeadBandValue = PWMServo_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWMServo_KillModeMinTime)
             PWMServo_backup.PWMKillCounterPeriod = PWMServo_ReadKillTime();
        #endif /* (PWMServo_KillModeMinTime) */

        #if(PWMServo_UseControl)
            PWMServo_backup.PWMControlRegister = PWMServo_ReadControlRegister();
        #endif /* (PWMServo_UseControl) */
    #endif  /* (!PWMServo_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMServo_RestoreConfig
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
*  PWMServo_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWMServo_RestoreConfig(void) 
{
        #if(!PWMServo_UsingFixedFunction)
            #if(!PWMServo_PWMModeIsCenterAligned)
                PWMServo_WritePeriod(PWMServo_backup.PWMPeriod);
            #endif /* (!PWMServo_PWMModeIsCenterAligned) */

            PWMServo_WriteCounter(PWMServo_backup.PWMUdb);

            #if (PWMServo_UseStatus)
                PWMServo_STATUS_MASK = PWMServo_backup.InterruptMaskValue;
            #endif /* (PWMServo_UseStatus) */

            #if(PWMServo_DeadBandMode == PWMServo__B_PWM__DBM_256_CLOCKS || \
                PWMServo_DeadBandMode == PWMServo__B_PWM__DBM_2_4_CLOCKS)
                PWMServo_WriteDeadTime(PWMServo_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWMServo_KillModeMinTime)
                PWMServo_WriteKillTime(PWMServo_backup.PWMKillCounterPeriod);
            #endif /* (PWMServo_KillModeMinTime) */

            #if(PWMServo_UseControl)
                PWMServo_WriteControlRegister(PWMServo_backup.PWMControlRegister);
            #endif /* (PWMServo_UseControl) */
        #endif  /* (!PWMServo_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWMServo_Sleep
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
*  PWMServo_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWMServo_Sleep(void) 
{
    #if(PWMServo_UseControl)
        if(PWMServo_CTRL_ENABLE == (PWMServo_CONTROL & PWMServo_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWMServo_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWMServo_backup.PWMEnableState = 0u;
        }
    #endif /* (PWMServo_UseControl) */

    /* Stop component */
    PWMServo_Stop();

    /* Save registers configuration */
    PWMServo_SaveConfig();
}


/*******************************************************************************
* Function Name: PWMServo_Wakeup
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
*  PWMServo_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWMServo_Wakeup(void) 
{
     /* Restore registers values */
    PWMServo_RestoreConfig();

    if(PWMServo_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWMServo_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
