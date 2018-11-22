/*******************************************************************************
* File Name: ADC_A_PM.c
* Version 3.0
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_A.h"


/***************************************
* Local data allocation
***************************************/

static ADC_A_BACKUP_STRUCT  ADC_A_backup =
{
    ADC_A_DISABLED
};


/*******************************************************************************
* Function Name: ADC_A_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_A_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_A_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_A_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_A_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The ADC_A_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_A_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ADC_A_Sleep(void)
{
    if((ADC_A_PWRMGR_SAR_REG  & ADC_A_ACT_PWR_SAR_EN) != 0u)
    {
        if((ADC_A_SAR_CSR0_REG & ADC_A_SAR_SOF_START_CONV) != 0u)
        {
            ADC_A_backup.enableState = ADC_A_ENABLED | ADC_A_STARTED;
        }
        else
        {
            ADC_A_backup.enableState = ADC_A_ENABLED;
        }
        ADC_A_Stop();
    }
    else
    {
        ADC_A_backup.enableState = ADC_A_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_A_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  ADC_A_Sleep() was called. If the component was enabled before the
*  ADC_A_Sleep() function was called, the
*  ADC_A_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_A_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ADC_A_Wakeup(void)
{
    if(ADC_A_backup.enableState != ADC_A_DISABLED)
    {
        ADC_A_Enable();
        #if(ADC_A_DEFAULT_CONV_MODE != ADC_A__HARDWARE_TRIGGER)
            if((ADC_A_backup.enableState & ADC_A_STARTED) != 0u)
            {
                ADC_A_StartConvert();
            }
        #endif /* End ADC_A_DEFAULT_CONV_MODE != ADC_A__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
