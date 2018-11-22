/*******************************************************************************
* File Name: Peak_Detector_B_Mixer_1.c  
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the MIXER Component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Peak_Detector_B_Mixer_1.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (Peak_Detector_B_Mixer_1_LO_SOURCE == Peak_Detector_B_Mixer_1_LO_SOURCE_INTERNAL)
    #include "Peak_Detector_B_Mixer_1_aclk.h"
#endif /* Peak_Detector_B_Mixer_1_LO_SOURCE */

/* Fixed configuration of SC Block only performed once */
uint8 Peak_Detector_B_Mixer_1_initVar = 0u;

/* Only for PSoC5A */
#if (CY_PSOC5A)
    static Peak_Detector_B_Mixer_1_backupStruct Peak_Detector_B_Mixer_1_P5backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Peak_Detector_B_Mixer_1_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  Peak_Detector_B_Mixer_1_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Peak_Detector_B_Mixer_1_Init(void) 
{
    float LOf = Peak_Detector_B_Mixer_1_LO_CLOCK_FREQ;
    
    /* Configure SC Block based on selected Mixer type */
    /* Continuous Time (up) mixer */
    #if (Peak_Detector_B_Mixer_1_MIXER_TYPE == Peak_Detector_B_Mixer_1_CTMIXER) 
        /* SC Block mode -  - SCxx_CR0[3:1] */
        Peak_Detector_B_Mixer_1_CR0_REG = Peak_Detector_B_Mixer_1_MODE_CTMIXER;   

        /* SC Block CR1 */ 
        Peak_Detector_B_Mixer_1_CR1_REG = (Peak_Detector_B_Mixer_1_COMP_4P35PF  |
                                Peak_Detector_B_Mixer_1_DIV2_DISABLE |
                                Peak_Detector_B_Mixer_1_GAIN_0DB);                                 

        /* 
            Set SC Block resistor values based on Local Oscillator being above 
            or below 100kHz - controled by r20_40 (Rmix) bit for CT mode mixer
            and SC Block
        */

        if (LOf < Peak_Detector_B_Mixer_1_LO_CLOCK_FREQ_100_KHz)
        {
            Peak_Detector_B_Mixer_1_CR2_REG = (Peak_Detector_B_Mixer_1_BIAS_LOW |
										Peak_Detector_B_Mixer_1_REDC_01 |
										Peak_Detector_B_Mixer_1_GNDVREF_DI |
										Peak_Detector_B_Mixer_1_R20_40B_40K);
        }
        else
        {
            Peak_Detector_B_Mixer_1_CR2_REG = (Peak_Detector_B_Mixer_1_BIAS_LOW |
										Peak_Detector_B_Mixer_1_REDC_01 |
										Peak_Detector_B_Mixer_1_GNDVREF_DI |
										Peak_Detector_B_Mixer_1_R20_40B_20K);
        }
    #else
        /* Discrete Time (down) mixer */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        Peak_Detector_B_Mixer_1_CR0_REG = Peak_Detector_B_Mixer_1_MODE_DTMIXER;       

        /* SC Block CR1 */ 
        Peak_Detector_B_Mixer_1_CR1_REG = (Peak_Detector_B_Mixer_1_COMP_4P35PF  |
                                Peak_Detector_B_Mixer_1_DIV2_ENABLE |
                                Peak_Detector_B_Mixer_1_GAIN_0DB);

        /* 
            Set SC Block resistor values based on Local Oscillator beign above 
            or below 100kHz - set r20_40 (input resitance) and rval (feedback) 
            resistor values seperately for DT mode and SC Block
        */
        if (LOf < Peak_Detector_B_Mixer_1_LO_CLOCK_FREQ_100_KHz)
        {
            Peak_Detector_B_Mixer_1_CR2_REG = (Peak_Detector_B_Mixer_1_BIAS_LOW |
										Peak_Detector_B_Mixer_1_GNDVREF_DI |
										Peak_Detector_B_Mixer_1_R20_40B_40K |
										Peak_Detector_B_Mixer_1_RVAL_40K); 
        }
        else
        {
            Peak_Detector_B_Mixer_1_CR2_REG = (Peak_Detector_B_Mixer_1_BIAS_LOW |
										Peak_Detector_B_Mixer_1_GNDVREF_DI |
										Peak_Detector_B_Mixer_1_R20_40B_20K |
										Peak_Detector_B_Mixer_1_RVAL_20K);
        }
    #endif /* end if - Mixer Type */

    /* Enable SC Block clocking */
    Peak_Detector_B_Mixer_1_CLK_REG |= Peak_Detector_B_Mixer_1_CLK_EN;

    /* Set default power */
    Peak_Detector_B_Mixer_1_SetPower(Peak_Detector_B_Mixer_1_INIT_POWER);
    
    /* Set 50 % Duty cycle for LO clock if LO source is internal */
    #if(Peak_Detector_B_Mixer_1_LO_SOURCE == Peak_Detector_B_Mixer_1_LO_SOURCE_INTERNAL)
        Peak_Detector_B_Mixer_1_aclk_SetMode(CYCLK_DUTY);
    #endif /* Peak_Detector_B_Mixer_1_LO_SOURCE == Peak_Detector_B_Mixer_1_LO_SOURCE_INTERNAL */

}


/*******************************************************************************
* Function Name: Peak_Detector_B_Mixer_1_Enable
********************************************************************************
*  
* Summary: 
*  Enables the Mixer block operation
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Peak_Detector_B_Mixer_1_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(Peak_Detector_B_Mixer_1_P5backup.enableState == 1u)
        {
            Peak_Detector_B_Mixer_1_CR1_REG = Peak_Detector_B_Mixer_1_P5backup.scCR1Reg;
            Peak_Detector_B_Mixer_1_CR2_REG = Peak_Detector_B_Mixer_1_P5backup.scCR2Reg;
            Peak_Detector_B_Mixer_1_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */
    
    /* Enable power to SC block in active mode */
    Peak_Detector_B_Mixer_1_PM_ACT_CFG_REG |= Peak_Detector_B_Mixer_1_ACT_PWR_EN;

    /* Enable power to SC block in Alternative active mode */
    Peak_Detector_B_Mixer_1_PM_STBY_CFG_REG |= Peak_Detector_B_Mixer_1_STBY_PWR_EN;
    
    /* Enable LO_Internal clock if LO source is choosen as internal */
    #if(Peak_Detector_B_Mixer_1_LO_SOURCE == Peak_Detector_B_Mixer_1_LO_SOURCE_INTERNAL)
        /* Enable power to the LO clock */
        Peak_Detector_B_Mixer_1_PWRMGR_ACLK_REG |= Peak_Detector_B_Mixer_1_ACT_PWR_ACLK_EN;        
        Peak_Detector_B_Mixer_1_STBY_PWRMGR_ACLK_REG |= Peak_Detector_B_Mixer_1_STBY_PWR_ACLK_EN;
        /* Enable the clock */
        Peak_Detector_B_Mixer_1_aclk_Enable();        
    #endif /* Peak_Detector_B_Mixer_1_LO_SOURCE == Peak_Detector_B_Mixer_1_LO_SOURCE_INTERNAL */

    Peak_Detector_B_Mixer_1_PUMP_CR1_REG |= Peak_Detector_B_Mixer_1_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                Peak_Detector_B_Mixer_1_BSTCLK_REG &= (uint8)(~Peak_Detector_B_Mixer_1_BST_CLK_INDEX_MASK);
                Peak_Detector_B_Mixer_1_BSTCLK_REG |= Peak_Detector_B_Mixer_1_BST_CLK_EN | CyScBoostClk__INDEX;
                Peak_Detector_B_Mixer_1_SC_MISC_REG |= Peak_Detector_B_Mixer_1_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                Peak_Detector_B_Mixer_1_BSTCLK_REG &= (uint8)(~Peak_Detector_B_Mixer_1_BST_CLK_EN);
                Peak_Detector_B_Mixer_1_SC_MISC_REG &= (uint8)(~Peak_Detector_B_Mixer_1_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: Peak_Detector_B_Mixer_1_Start
********************************************************************************
*
* Summary:
*  The start function initializes the SC block control registers based on the
*  Mixer type selected and and enables power to the SC block
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Global variables:
*  Peak_Detector_B_Mixer_1_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Theory: 
*  Full initialization of the SC Block configuration registers is only perfomed 
*  the first time the routine executes - global variable 
*  Peak_Detector_B_Mixer_1_initVar is used indicate that the static configuration has 
*  been completed.
*
*******************************************************************************/
void Peak_Detector_B_Mixer_1_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Peak_Detector_B_Mixer_1_initVar == 0u)
    {
        Peak_Detector_B_Mixer_1_Init();
        Peak_Detector_B_Mixer_1_initVar = 1u;
    }
    /* Enable the power to the block */
    Peak_Detector_B_Mixer_1_Enable();
    
}


/*******************************************************************************
* Function Name: Peak_Detector_B_Mixer_1_Stop
********************************************************************************
*
* Summary:
*  Disables power to SC block.
*
* Parameters:  
*  void 
*
* Return: 
*  void 
*
*******************************************************************************/
void Peak_Detector_B_Mixer_1_Stop(void) 
{       
    /* Disble power to the Amp in Active mode template */
    Peak_Detector_B_Mixer_1_PM_ACT_CFG_REG &= (uint8)(~Peak_Detector_B_Mixer_1_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    Peak_Detector_B_Mixer_1_PM_STBY_CFG_REG &= (uint8)(~Peak_Detector_B_Mixer_1_STBY_PWR_EN);
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            Peak_Detector_B_Mixer_1_BSTCLK_REG &= (uint8)(~Peak_Detector_B_Mixer_1_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((Peak_Detector_B_Mixer_1_PM_ACT_CFG_REG & Peak_Detector_B_Mixer_1_PM_ACT_CFG_MASK) == 0u)
            {
                Peak_Detector_B_Mixer_1_SC_MISC_REG &= (uint8)(~Peak_Detector_B_Mixer_1_PUMP_FORCE);
                Peak_Detector_B_Mixer_1_PUMP_CR1_REG &= (uint8)(~Peak_Detector_B_Mixer_1_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* This sets Sample and hold in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        Peak_Detector_B_Mixer_1_P5backup.scCR1Reg = Peak_Detector_B_Mixer_1_CR1_REG;
        Peak_Detector_B_Mixer_1_P5backup.scCR2Reg = Peak_Detector_B_Mixer_1_CR2_REG;
        Peak_Detector_B_Mixer_1_CR1_REG = 0x00u;
        Peak_Detector_B_Mixer_1_CR2_REG = 0x00u;
        Peak_Detector_B_Mixer_1_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */  
    
    /* Disable aclk */
    #if(Peak_Detector_B_Mixer_1_LO_SOURCE == Peak_Detector_B_Mixer_1_LO_SOURCE_INTERNAL)
        /* Disable power to clock */
        Peak_Detector_B_Mixer_1_PWRMGR_ACLK_REG &= (uint8)(~Peak_Detector_B_Mixer_1_ACT_PWR_ACLK_EN);
        Peak_Detector_B_Mixer_1_STBY_PWRMGR_ACLK_REG &= (uint8)(~Peak_Detector_B_Mixer_1_STBY_PWR_ACLK_EN);
        /* Disable the clock */
        Peak_Detector_B_Mixer_1_aclk_Disable();
    #endif /* Peak_Detector_B_Mixer_1_LO_SOURCE == Peak_Detector_B_Mixer_1_LO_SOURCE_INTERNAL */
}


/*******************************************************************************
* Function Name: Peak_Detector_B_Mixer_1_SetPower
********************************************************************************
*
* Summary:
*  Set the drive power of the MIXER
*
* Parameters:  
*  power:  Sets power level between (0) and (3) high power
*
* Return: 
*  void 
*
*******************************************************************************/
void Peak_Detector_B_Mixer_1_SetPower(uint8 power) 
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */    
    tmpCR = Peak_Detector_B_Mixer_1_CR1_REG & (uint8)(~Peak_Detector_B_Mixer_1_DRIVE_MASK);
    tmpCR |= (power & Peak_Detector_B_Mixer_1_DRIVE_MASK);
    Peak_Detector_B_Mixer_1_CR1_REG = tmpCR;  
}


/* [] END OF FILE */
