/*******************************************************************************
* File Name: MixerA.c  
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

#include "MixerA.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (MixerA_LO_SOURCE == MixerA_LO_SOURCE_INTERNAL)
    #include "MixerA_aclk.h"
#endif /* MixerA_LO_SOURCE */

/* Fixed configuration of SC Block only performed once */
uint8 MixerA_initVar = 0u;

/* Only for PSoC5A */
#if (CY_PSOC5A)
    static MixerA_backupStruct MixerA_P5backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: MixerA_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  MixerA_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void MixerA_Init(void) 
{
    float LOf = MixerA_LO_CLOCK_FREQ;
    
    /* Configure SC Block based on selected Mixer type */
    /* Continuous Time (up) mixer */
    #if (MixerA_MIXER_TYPE == MixerA_CTMIXER) 
        /* SC Block mode -  - SCxx_CR0[3:1] */
        MixerA_CR0_REG = MixerA_MODE_CTMIXER;   

        /* SC Block CR1 */ 
        MixerA_CR1_REG = (MixerA_COMP_4P35PF  |
                                MixerA_DIV2_DISABLE |
                                MixerA_GAIN_0DB);                                 

        /* 
            Set SC Block resistor values based on Local Oscillator being above 
            or below 100kHz - controled by r20_40 (Rmix) bit for CT mode mixer
            and SC Block
        */

        if (LOf < MixerA_LO_CLOCK_FREQ_100_KHz)
        {
            MixerA_CR2_REG = (MixerA_BIAS_LOW |
										MixerA_REDC_01 |
										MixerA_GNDVREF_DI |
										MixerA_R20_40B_40K);
        }
        else
        {
            MixerA_CR2_REG = (MixerA_BIAS_LOW |
										MixerA_REDC_01 |
										MixerA_GNDVREF_DI |
										MixerA_R20_40B_20K);
        }
    #else
        /* Discrete Time (down) mixer */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        MixerA_CR0_REG = MixerA_MODE_DTMIXER;       

        /* SC Block CR1 */ 
        MixerA_CR1_REG = (MixerA_COMP_4P35PF  |
                                MixerA_DIV2_ENABLE |
                                MixerA_GAIN_0DB);

        /* 
            Set SC Block resistor values based on Local Oscillator beign above 
            or below 100kHz - set r20_40 (input resitance) and rval (feedback) 
            resistor values seperately for DT mode and SC Block
        */
        if (LOf < MixerA_LO_CLOCK_FREQ_100_KHz)
        {
            MixerA_CR2_REG = (MixerA_BIAS_LOW |
										MixerA_GNDVREF_DI |
										MixerA_R20_40B_40K |
										MixerA_RVAL_40K); 
        }
        else
        {
            MixerA_CR2_REG = (MixerA_BIAS_LOW |
										MixerA_GNDVREF_DI |
										MixerA_R20_40B_20K |
										MixerA_RVAL_20K);
        }
    #endif /* end if - Mixer Type */

    /* Enable SC Block clocking */
    MixerA_CLK_REG |= MixerA_CLK_EN;

    /* Set default power */
    MixerA_SetPower(MixerA_INIT_POWER);
    
    /* Set 50 % Duty cycle for LO clock if LO source is internal */
    #if(MixerA_LO_SOURCE == MixerA_LO_SOURCE_INTERNAL)
        MixerA_aclk_SetMode(CYCLK_DUTY);
    #endif /* MixerA_LO_SOURCE == MixerA_LO_SOURCE_INTERNAL */

}


/*******************************************************************************
* Function Name: MixerA_Enable
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
void MixerA_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(MixerA_P5backup.enableState == 1u)
        {
            MixerA_CR1_REG = MixerA_P5backup.scCR1Reg;
            MixerA_CR2_REG = MixerA_P5backup.scCR2Reg;
            MixerA_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */
    
    /* Enable power to SC block in active mode */
    MixerA_PM_ACT_CFG_REG |= MixerA_ACT_PWR_EN;

    /* Enable power to SC block in Alternative active mode */
    MixerA_PM_STBY_CFG_REG |= MixerA_STBY_PWR_EN;
    
    /* Enable LO_Internal clock if LO source is choosen as internal */
    #if(MixerA_LO_SOURCE == MixerA_LO_SOURCE_INTERNAL)
        /* Enable power to the LO clock */
        MixerA_PWRMGR_ACLK_REG |= MixerA_ACT_PWR_ACLK_EN;        
        MixerA_STBY_PWRMGR_ACLK_REG |= MixerA_STBY_PWR_ACLK_EN;
        /* Enable the clock */
        MixerA_aclk_Enable();        
    #endif /* MixerA_LO_SOURCE == MixerA_LO_SOURCE_INTERNAL */

    MixerA_PUMP_CR1_REG |= MixerA_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                MixerA_BSTCLK_REG &= (uint8)(~MixerA_BST_CLK_INDEX_MASK);
                MixerA_BSTCLK_REG |= MixerA_BST_CLK_EN | CyScBoostClk__INDEX;
                MixerA_SC_MISC_REG |= MixerA_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                MixerA_BSTCLK_REG &= (uint8)(~MixerA_BST_CLK_EN);
                MixerA_SC_MISC_REG &= (uint8)(~MixerA_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: MixerA_Start
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
*  MixerA_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Theory: 
*  Full initialization of the SC Block configuration registers is only perfomed 
*  the first time the routine executes - global variable 
*  MixerA_initVar is used indicate that the static configuration has 
*  been completed.
*
*******************************************************************************/
void MixerA_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(MixerA_initVar == 0u)
    {
        MixerA_Init();
        MixerA_initVar = 1u;
    }
    /* Enable the power to the block */
    MixerA_Enable();
    
}


/*******************************************************************************
* Function Name: MixerA_Stop
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
void MixerA_Stop(void) 
{       
    /* Disble power to the Amp in Active mode template */
    MixerA_PM_ACT_CFG_REG &= (uint8)(~MixerA_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    MixerA_PM_STBY_CFG_REG &= (uint8)(~MixerA_STBY_PWR_EN);
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            MixerA_BSTCLK_REG &= (uint8)(~MixerA_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((MixerA_PM_ACT_CFG_REG & MixerA_PM_ACT_CFG_MASK) == 0u)
            {
                MixerA_SC_MISC_REG &= (uint8)(~MixerA_PUMP_FORCE);
                MixerA_PUMP_CR1_REG &= (uint8)(~MixerA_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* This sets Sample and hold in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        MixerA_P5backup.scCR1Reg = MixerA_CR1_REG;
        MixerA_P5backup.scCR2Reg = MixerA_CR2_REG;
        MixerA_CR1_REG = 0x00u;
        MixerA_CR2_REG = 0x00u;
        MixerA_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */  
    
    /* Disable aclk */
    #if(MixerA_LO_SOURCE == MixerA_LO_SOURCE_INTERNAL)
        /* Disable power to clock */
        MixerA_PWRMGR_ACLK_REG &= (uint8)(~MixerA_ACT_PWR_ACLK_EN);
        MixerA_STBY_PWRMGR_ACLK_REG &= (uint8)(~MixerA_STBY_PWR_ACLK_EN);
        /* Disable the clock */
        MixerA_aclk_Disable();
    #endif /* MixerA_LO_SOURCE == MixerA_LO_SOURCE_INTERNAL */
}


/*******************************************************************************
* Function Name: MixerA_SetPower
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
void MixerA_SetPower(uint8 power) 
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */    
    tmpCR = MixerA_CR1_REG & (uint8)(~MixerA_DRIVE_MASK);
    tmpCR |= (power & MixerA_DRIVE_MASK);
    MixerA_CR1_REG = tmpCR;  
}


/* [] END OF FILE */
