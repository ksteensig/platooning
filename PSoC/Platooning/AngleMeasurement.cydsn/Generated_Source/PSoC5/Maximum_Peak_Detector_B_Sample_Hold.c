/*******************************************************************************
* File Name: Maximum_Peak_Detector_B_Sample_Hold.c  
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

#include "Maximum_Peak_Detector_B_Sample_Hold.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE == Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE_INTERNAL)
    #include "Maximum_Peak_Detector_B_Sample_Hold_aclk.h"
#endif /* Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE */

/* Fixed configuration of SC Block only performed once */
uint8 Maximum_Peak_Detector_B_Sample_Hold_initVar = 0u;

/* Only for PSoC5A */
#if (CY_PSOC5A)
    static Maximum_Peak_Detector_B_Sample_Hold_backupStruct Maximum_Peak_Detector_B_Sample_Hold_P5backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Maximum_Peak_Detector_B_Sample_Hold_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  Maximum_Peak_Detector_B_Sample_Hold_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Maximum_Peak_Detector_B_Sample_Hold_Init(void) 
{
    float LOf = Maximum_Peak_Detector_B_Sample_Hold_LO_CLOCK_FREQ;
    
    /* Configure SC Block based on selected Mixer type */
    /* Continuous Time (up) mixer */
    #if (Maximum_Peak_Detector_B_Sample_Hold_MIXER_TYPE == Maximum_Peak_Detector_B_Sample_Hold_CTMIXER) 
        /* SC Block mode -  - SCxx_CR0[3:1] */
        Maximum_Peak_Detector_B_Sample_Hold_CR0_REG = Maximum_Peak_Detector_B_Sample_Hold_MODE_CTMIXER;   

        /* SC Block CR1 */ 
        Maximum_Peak_Detector_B_Sample_Hold_CR1_REG = (Maximum_Peak_Detector_B_Sample_Hold_COMP_4P35PF  |
                                Maximum_Peak_Detector_B_Sample_Hold_DIV2_DISABLE |
                                Maximum_Peak_Detector_B_Sample_Hold_GAIN_0DB);                                 

        /* 
            Set SC Block resistor values based on Local Oscillator being above 
            or below 100kHz - controled by r20_40 (Rmix) bit for CT mode mixer
            and SC Block
        */

        if (LOf < Maximum_Peak_Detector_B_Sample_Hold_LO_CLOCK_FREQ_100_KHz)
        {
            Maximum_Peak_Detector_B_Sample_Hold_CR2_REG = (Maximum_Peak_Detector_B_Sample_Hold_BIAS_LOW |
										Maximum_Peak_Detector_B_Sample_Hold_REDC_01 |
										Maximum_Peak_Detector_B_Sample_Hold_GNDVREF_DI |
										Maximum_Peak_Detector_B_Sample_Hold_R20_40B_40K);
        }
        else
        {
            Maximum_Peak_Detector_B_Sample_Hold_CR2_REG = (Maximum_Peak_Detector_B_Sample_Hold_BIAS_LOW |
										Maximum_Peak_Detector_B_Sample_Hold_REDC_01 |
										Maximum_Peak_Detector_B_Sample_Hold_GNDVREF_DI |
										Maximum_Peak_Detector_B_Sample_Hold_R20_40B_20K);
        }
    #else
        /* Discrete Time (down) mixer */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        Maximum_Peak_Detector_B_Sample_Hold_CR0_REG = Maximum_Peak_Detector_B_Sample_Hold_MODE_DTMIXER;       

        /* SC Block CR1 */ 
        Maximum_Peak_Detector_B_Sample_Hold_CR1_REG = (Maximum_Peak_Detector_B_Sample_Hold_COMP_4P35PF  |
                                Maximum_Peak_Detector_B_Sample_Hold_DIV2_ENABLE |
                                Maximum_Peak_Detector_B_Sample_Hold_GAIN_0DB);

        /* 
            Set SC Block resistor values based on Local Oscillator beign above 
            or below 100kHz - set r20_40 (input resitance) and rval (feedback) 
            resistor values seperately for DT mode and SC Block
        */
        if (LOf < Maximum_Peak_Detector_B_Sample_Hold_LO_CLOCK_FREQ_100_KHz)
        {
            Maximum_Peak_Detector_B_Sample_Hold_CR2_REG = (Maximum_Peak_Detector_B_Sample_Hold_BIAS_LOW |
										Maximum_Peak_Detector_B_Sample_Hold_GNDVREF_DI |
										Maximum_Peak_Detector_B_Sample_Hold_R20_40B_40K |
										Maximum_Peak_Detector_B_Sample_Hold_RVAL_40K); 
        }
        else
        {
            Maximum_Peak_Detector_B_Sample_Hold_CR2_REG = (Maximum_Peak_Detector_B_Sample_Hold_BIAS_LOW |
										Maximum_Peak_Detector_B_Sample_Hold_GNDVREF_DI |
										Maximum_Peak_Detector_B_Sample_Hold_R20_40B_20K |
										Maximum_Peak_Detector_B_Sample_Hold_RVAL_20K);
        }
    #endif /* end if - Mixer Type */

    /* Enable SC Block clocking */
    Maximum_Peak_Detector_B_Sample_Hold_CLK_REG |= Maximum_Peak_Detector_B_Sample_Hold_CLK_EN;

    /* Set default power */
    Maximum_Peak_Detector_B_Sample_Hold_SetPower(Maximum_Peak_Detector_B_Sample_Hold_INIT_POWER);
    
    /* Set 50 % Duty cycle for LO clock if LO source is internal */
    #if(Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE == Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE_INTERNAL)
        Maximum_Peak_Detector_B_Sample_Hold_aclk_SetMode(CYCLK_DUTY);
    #endif /* Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE == Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE_INTERNAL */

}


/*******************************************************************************
* Function Name: Maximum_Peak_Detector_B_Sample_Hold_Enable
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
void Maximum_Peak_Detector_B_Sample_Hold_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(Maximum_Peak_Detector_B_Sample_Hold_P5backup.enableState == 1u)
        {
            Maximum_Peak_Detector_B_Sample_Hold_CR1_REG = Maximum_Peak_Detector_B_Sample_Hold_P5backup.scCR1Reg;
            Maximum_Peak_Detector_B_Sample_Hold_CR2_REG = Maximum_Peak_Detector_B_Sample_Hold_P5backup.scCR2Reg;
            Maximum_Peak_Detector_B_Sample_Hold_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */
    
    /* Enable power to SC block in active mode */
    Maximum_Peak_Detector_B_Sample_Hold_PM_ACT_CFG_REG |= Maximum_Peak_Detector_B_Sample_Hold_ACT_PWR_EN;

    /* Enable power to SC block in Alternative active mode */
    Maximum_Peak_Detector_B_Sample_Hold_PM_STBY_CFG_REG |= Maximum_Peak_Detector_B_Sample_Hold_STBY_PWR_EN;
    
    /* Enable LO_Internal clock if LO source is choosen as internal */
    #if(Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE == Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE_INTERNAL)
        /* Enable power to the LO clock */
        Maximum_Peak_Detector_B_Sample_Hold_PWRMGR_ACLK_REG |= Maximum_Peak_Detector_B_Sample_Hold_ACT_PWR_ACLK_EN;        
        Maximum_Peak_Detector_B_Sample_Hold_STBY_PWRMGR_ACLK_REG |= Maximum_Peak_Detector_B_Sample_Hold_STBY_PWR_ACLK_EN;
        /* Enable the clock */
        Maximum_Peak_Detector_B_Sample_Hold_aclk_Enable();        
    #endif /* Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE == Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE_INTERNAL */

    Maximum_Peak_Detector_B_Sample_Hold_PUMP_CR1_REG |= Maximum_Peak_Detector_B_Sample_Hold_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                Maximum_Peak_Detector_B_Sample_Hold_BSTCLK_REG &= (uint8)(~Maximum_Peak_Detector_B_Sample_Hold_BST_CLK_INDEX_MASK);
                Maximum_Peak_Detector_B_Sample_Hold_BSTCLK_REG |= Maximum_Peak_Detector_B_Sample_Hold_BST_CLK_EN | CyScBoostClk__INDEX;
                Maximum_Peak_Detector_B_Sample_Hold_SC_MISC_REG |= Maximum_Peak_Detector_B_Sample_Hold_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                Maximum_Peak_Detector_B_Sample_Hold_BSTCLK_REG &= (uint8)(~Maximum_Peak_Detector_B_Sample_Hold_BST_CLK_EN);
                Maximum_Peak_Detector_B_Sample_Hold_SC_MISC_REG &= (uint8)(~Maximum_Peak_Detector_B_Sample_Hold_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: Maximum_Peak_Detector_B_Sample_Hold_Start
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
*  Maximum_Peak_Detector_B_Sample_Hold_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Theory: 
*  Full initialization of the SC Block configuration registers is only perfomed 
*  the first time the routine executes - global variable 
*  Maximum_Peak_Detector_B_Sample_Hold_initVar is used indicate that the static configuration has 
*  been completed.
*
*******************************************************************************/
void Maximum_Peak_Detector_B_Sample_Hold_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Maximum_Peak_Detector_B_Sample_Hold_initVar == 0u)
    {
        Maximum_Peak_Detector_B_Sample_Hold_Init();
        Maximum_Peak_Detector_B_Sample_Hold_initVar = 1u;
    }
    /* Enable the power to the block */
    Maximum_Peak_Detector_B_Sample_Hold_Enable();
    
}


/*******************************************************************************
* Function Name: Maximum_Peak_Detector_B_Sample_Hold_Stop
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
void Maximum_Peak_Detector_B_Sample_Hold_Stop(void) 
{       
    /* Disble power to the Amp in Active mode template */
    Maximum_Peak_Detector_B_Sample_Hold_PM_ACT_CFG_REG &= (uint8)(~Maximum_Peak_Detector_B_Sample_Hold_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    Maximum_Peak_Detector_B_Sample_Hold_PM_STBY_CFG_REG &= (uint8)(~Maximum_Peak_Detector_B_Sample_Hold_STBY_PWR_EN);
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            Maximum_Peak_Detector_B_Sample_Hold_BSTCLK_REG &= (uint8)(~Maximum_Peak_Detector_B_Sample_Hold_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((Maximum_Peak_Detector_B_Sample_Hold_PM_ACT_CFG_REG & Maximum_Peak_Detector_B_Sample_Hold_PM_ACT_CFG_MASK) == 0u)
            {
                Maximum_Peak_Detector_B_Sample_Hold_SC_MISC_REG &= (uint8)(~Maximum_Peak_Detector_B_Sample_Hold_PUMP_FORCE);
                Maximum_Peak_Detector_B_Sample_Hold_PUMP_CR1_REG &= (uint8)(~Maximum_Peak_Detector_B_Sample_Hold_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* This sets Sample and hold in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        Maximum_Peak_Detector_B_Sample_Hold_P5backup.scCR1Reg = Maximum_Peak_Detector_B_Sample_Hold_CR1_REG;
        Maximum_Peak_Detector_B_Sample_Hold_P5backup.scCR2Reg = Maximum_Peak_Detector_B_Sample_Hold_CR2_REG;
        Maximum_Peak_Detector_B_Sample_Hold_CR1_REG = 0x00u;
        Maximum_Peak_Detector_B_Sample_Hold_CR2_REG = 0x00u;
        Maximum_Peak_Detector_B_Sample_Hold_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */  
    
    /* Disable aclk */
    #if(Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE == Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE_INTERNAL)
        /* Disable power to clock */
        Maximum_Peak_Detector_B_Sample_Hold_PWRMGR_ACLK_REG &= (uint8)(~Maximum_Peak_Detector_B_Sample_Hold_ACT_PWR_ACLK_EN);
        Maximum_Peak_Detector_B_Sample_Hold_STBY_PWRMGR_ACLK_REG &= (uint8)(~Maximum_Peak_Detector_B_Sample_Hold_STBY_PWR_ACLK_EN);
        /* Disable the clock */
        Maximum_Peak_Detector_B_Sample_Hold_aclk_Disable();
    #endif /* Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE == Maximum_Peak_Detector_B_Sample_Hold_LO_SOURCE_INTERNAL */
}


/*******************************************************************************
* Function Name: Maximum_Peak_Detector_B_Sample_Hold_SetPower
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
void Maximum_Peak_Detector_B_Sample_Hold_SetPower(uint8 power) 
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */    
    tmpCR = Maximum_Peak_Detector_B_Sample_Hold_CR1_REG & (uint8)(~Maximum_Peak_Detector_B_Sample_Hold_DRIVE_MASK);
    tmpCR |= (power & Maximum_Peak_Detector_B_Sample_Hold_DRIVE_MASK);
    Maximum_Peak_Detector_B_Sample_Hold_CR1_REG = tmpCR;  
}


/* [] END OF FILE */
