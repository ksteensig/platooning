/*******************************************************************************
* File Name: PWMHBro_PM.c
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

#include "PWMHBro.h"

static PWMHBro_backupStruct PWMHBro_backup;


/*******************************************************************************
* Function Name: PWMHBro_SaveConfig
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
*  PWMHBro_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWMHBro_SaveConfig(void) 
{

    #if(!PWMHBro_UsingFixedFunction)
        #if(!PWMHBro_PWMModeIsCenterAligned)
            PWMHBro_backup.PWMPeriod = PWMHBro_ReadPeriod();
        #endif /* (!PWMHBro_PWMModeIsCenterAligned) */
        PWMHBro_backup.PWMUdb = PWMHBro_ReadCounter();
        #if (PWMHBro_UseStatus)
            PWMHBro_backup.InterruptMaskValue = PWMHBro_STATUS_MASK;
        #endif /* (PWMHBro_UseStatus) */

        #if(PWMHBro_DeadBandMode == PWMHBro__B_PWM__DBM_256_CLOCKS || \
            PWMHBro_DeadBandMode == PWMHBro__B_PWM__DBM_2_4_CLOCKS)
            PWMHBro_backup.PWMdeadBandValue = PWMHBro_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWMHBro_KillModeMinTime)
             PWMHBro_backup.PWMKillCounterPeriod = PWMHBro_ReadKillTime();
        #endif /* (PWMHBro_KillModeMinTime) */

        #if(PWMHBro_UseControl)
            PWMHBro_backup.PWMControlRegister = PWMHBro_ReadControlRegister();
        #endif /* (PWMHBro_UseControl) */
    #endif  /* (!PWMHBro_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMHBro_RestoreConfig
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
*  PWMHBro_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWMHBro_RestoreConfig(void) 
{
        #if(!PWMHBro_UsingFixedFunction)
            #if(!PWMHBro_PWMModeIsCenterAligned)
                PWMHBro_WritePeriod(PWMHBro_backup.PWMPeriod);
            #endif /* (!PWMHBro_PWMModeIsCenterAligned) */

            PWMHBro_WriteCounter(PWMHBro_backup.PWMUdb);

            #if (PWMHBro_UseStatus)
                PWMHBro_STATUS_MASK = PWMHBro_backup.InterruptMaskValue;
            #endif /* (PWMHBro_UseStatus) */

            #if(PWMHBro_DeadBandMode == PWMHBro__B_PWM__DBM_256_CLOCKS || \
                PWMHBro_DeadBandMode == PWMHBro__B_PWM__DBM_2_4_CLOCKS)
                PWMHBro_WriteDeadTime(PWMHBro_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWMHBro_KillModeMinTime)
                PWMHBro_WriteKillTime(PWMHBro_backup.PWMKillCounterPeriod);
            #endif /* (PWMHBro_KillModeMinTime) */

            #if(PWMHBro_UseControl)
                PWMHBro_WriteControlRegister(PWMHBro_backup.PWMControlRegister);
            #endif /* (PWMHBro_UseControl) */
        #endif  /* (!PWMHBro_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWMHBro_Sleep
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
*  PWMHBro_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWMHBro_Sleep(void) 
{
    #if(PWMHBro_UseControl)
        if(PWMHBro_CTRL_ENABLE == (PWMHBro_CONTROL & PWMHBro_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWMHBro_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWMHBro_backup.PWMEnableState = 0u;
        }
    #endif /* (PWMHBro_UseControl) */

    /* Stop component */
    PWMHBro_Stop();

    /* Save registers configuration */
    PWMHBro_SaveConfig();
}


/*******************************************************************************
* Function Name: PWMHBro_Wakeup
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
*  PWMHBro_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWMHBro_Wakeup(void) 
{
     /* Restore registers values */
    PWMHBro_RestoreConfig();

    if(PWMHBro_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWMHBro_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
