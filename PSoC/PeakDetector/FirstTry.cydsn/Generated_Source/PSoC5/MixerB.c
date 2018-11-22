/*******************************************************************************
* File Name: MixerB.c  
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

#include "MixerB.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (MixerB_LO_SOURCE == MixerB_LO_SOURCE_INTERNAL)
    #include "MixerB_aclk.h"
#endif /* MixerB_LO_SOURCE */

/* Fixed configuration of SC Block only performed once */
uint8 MixerB_initVar = 0u;

/* Only for PSoC5A */
#if (CY_PSOC5A)
    static MixerB_backupStruct MixerB_P5backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: MixerB_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  MixerB_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void MixerB_Init(void) 
{
    float LOf = MixerB_LO_CLOCK_FREQ;
    
    /* Configure SC Block based on selected Mixer type */
    /* Continuous Time (up) mixer */
    #if (MixerB_MIXER_TYPE == MixerB_CTMIXER) 
        /* SC Block mode -  - SCxx_CR0[3:1] */
        MixerB_CR0_REG = MixerB_MODE_CTMIXER;   

        /* SC Block CR1 */ 
        MixerB_CR1_REG = (MixerB_COMP_4P35PF  |
                                MixerB_DIV2_DISABLE |
                                MixerB_GAIN_0DB);                                 

        /* 
            Set SC Block resistor values based on Local Oscillator being above 
            or below 100kHz - controled by r20_40 (Rmix) bit for CT mode mixer
            and SC Block
        */

        if (LOf < MixerB_LO_CLOCK_FREQ_100_KHz)
        {
            MixerB_CR2_REG = (MixerB_BIAS_LOW |
										MixerB_REDC_01 |
										MixerB_GNDVREF_DI |
										MixerB_R20_40B_40K);
        }
        else
        {
            MixerB_CR2_REG = (MixerB_BIAS_LOW |
										MixerB_REDC_01 |
										MixerB_GNDVREF_DI |
										MixerB_R20_40B_20K);
        }
    #else
        /* Discrete Time (down) mixer */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        MixerB_CR0_REG = MixerB_MODE_DTMIXER;       

        /* SC Block CR1 */ 
        MixerB_CR1_REG = (MixerB_COMP_4P35PF  |
                                MixerB_DIV2_ENABLE |
                                MixerB_GAIN_0DB);

        /* 
            Set SC Block resistor values based on Local Oscillator beign above 
            or below 100kHz - set r20_40 (input resitance) and rval (feedback) 
            resistor values seperately for DT mode and SC Block
        */
        if (LOf < MixerB_LO_CLOCK_FREQ_100_KHz)
        {
            MixerB_CR2_REG = (MixerB_BIAS_LOW |
										MixerB_GNDVREF_DI |
										MixerB_R20_40B_40K |
										MixerB_RVAL_40K); 
        }
        else
        {
            MixerB_CR2_REG = (MixerB_BIAS_LOW |
										MixerB_GNDVREF_DI |
										MixerB_R20_40B_20K |
										MixerB_RVAL_20K);
        }
    #endif /* end if - Mixer Type */

    /* Enable SC Block clocking */
    MixerB_CLK_REG |= MixerB_CLK_EN;

    /* Set default power */
    MixerB_SetPower(MixerB_INIT_POWER);
    
    /* Set 50 % Duty cycle for LO clock if LO source is internal */
    #if(MixerB_LO_SOURCE == MixerB_LO_SOURCE_INTERNAL)
        MixerB_aclk_SetMode(CYCLK_DUTY);
    #endif /* MixerB_LO_SOURCE == MixerB_LO_SOURCE_INTERNAL */

}


/*******************************************************************************
* Function Name: MixerB_Enable
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
void MixerB_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(MixerB_P5backup.enableState == 1u)
        {
            MixerB_CR1_REG = MixerB_P5backup.scCR1Reg;
            MixerB_CR2_REG = MixerB_P5backup.scCR2Reg;
            MixerB_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */
    
    /* Enable power to SC block in active mode */
    MixerB_PM_ACT_CFG_REG |= MixerB_ACT_PWR_EN;

    /* Enable power to SC block in Alternative active mode */
    MixerB_PM_STBY_CFG_REG |= MixerB_STBY_PWR_EN;
    
    /* Enable LO_Internal clock if LO source is choosen as internal */
    #if(MixerB_LO_SOURCE == MixerB_LO_SOURCE_INTERNAL)
        /* Enable power to the LO clock */
        MixerB_PWRMGR_ACLK_REG |= MixerB_ACT_PWR_ACLK_EN;        
        MixerB_STBY_PWRMGR_ACLK_REG |= MixerB_STBY_PWR_ACLK_EN;
        /* Enable the clock */
        MixerB_aclk_Enable();        
    #endif /* MixerB_LO_SOURCE == MixerB_LO_SOURCE_INTERNAL */

    MixerB_PUMP_CR1_REG |= MixerB_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                MixerB_BSTCLK_REG &= (uint8)(~MixerB_BST_CLK_INDEX_MASK);
                MixerB_BSTCLK_REG |= MixerB_BST_CLK_EN | CyScBoostClk__INDEX;
                MixerB_SC_MISC_REG |= MixerB_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                MixerB_BSTCLK_REG &= (uint8)(~MixerB_BST_CLK_EN);
                MixerB_SC_MISC_REG &= (uint8)(~MixerB_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: MixerB_Start
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
*  MixerB_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Theory: 
*  Full initialization of the SC Block configuration registers is only perfomed 
*  the first time the routine executes - global variable 
*  MixerB_initVar is used indicate that the static configuration has 
*  been completed.
*
*******************************************************************************/
void MixerB_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(MixerB_initVar == 0u)
    {
        MixerB_Init();
        MixerB_initVar = 1u;
    }
    /* Enable the power to the block */
    MixerB_Enable();
    
}


/*******************************************************************************
* Function Name: MixerB_Stop
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
void MixerB_Stop(void) 
{       
    /* Disble power to the Amp in Active mode template */
    MixerB_PM_ACT_CFG_REG &= (uint8)(~MixerB_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    MixerB_PM_STBY_CFG_REG &= (uint8)(~MixerB_STBY_PWR_EN);
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            MixerB_BSTCLK_REG &= (uint8)(~MixerB_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((MixerB_PM_ACT_CFG_REG & MixerB_PM_ACT_CFG_MASK) == 0u)
            {
                MixerB_SC_MISC_REG &= (uint8)(~MixerB_PUMP_FORCE);
                MixerB_PUMP_CR1_REG &= (uint8)(~MixerB_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* This sets Sample and hold in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        MixerB_P5backup.scCR1Reg = MixerB_CR1_REG;
        MixerB_P5backup.scCR2Reg = MixerB_CR2_REG;
        MixerB_CR1_REG = 0x00u;
        MixerB_CR2_REG = 0x00u;
        MixerB_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */  
    
    /* Disable aclk */
    #if(MixerB_LO_SOURCE == MixerB_LO_SOURCE_INTERNAL)
        /* Disable power to clock */
        MixerB_PWRMGR_ACLK_REG &= (uint8)(~MixerB_ACT_PWR_ACLK_EN);
        MixerB_STBY_PWRMGR_ACLK_REG &= (uint8)(~MixerB_STBY_PWR_ACLK_EN);
        /* Disable the clock */
        MixerB_aclk_Disable();
    #endif /* MixerB_LO_SOURCE == MixerB_LO_SOURCE_INTERNAL */
}


/*******************************************************************************
* Function Name: MixerB_SetPower
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
void MixerB_SetPower(uint8 power) 
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */    
    tmpCR = MixerB_CR1_REG & (uint8)(~MixerB_DRIVE_MASK);
    tmpCR |= (power & MixerB_DRIVE_MASK);
    MixerB_CR1_REG = tmpCR;  
}


/* [] END OF FILE */
