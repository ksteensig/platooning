/*******************************************************************************
* File Name: Mixer_A.c  
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

#include "Mixer_A.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (Mixer_A_LO_SOURCE == Mixer_A_LO_SOURCE_INTERNAL)
    #include "Mixer_A_aclk.h"
#endif /* Mixer_A_LO_SOURCE */

/* Fixed configuration of SC Block only performed once */
uint8 Mixer_A_initVar = 0u;

/* Only for PSoC5A */
#if (CY_PSOC5A)
    static Mixer_A_backupStruct Mixer_A_P5backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Mixer_A_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  Mixer_A_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Mixer_A_Init(void) 
{
    float LOf = Mixer_A_LO_CLOCK_FREQ;
    
    /* Configure SC Block based on selected Mixer type */
    /* Continuous Time (up) mixer */
    #if (Mixer_A_MIXER_TYPE == Mixer_A_CTMIXER) 
        /* SC Block mode -  - SCxx_CR0[3:1] */
        Mixer_A_CR0_REG = Mixer_A_MODE_CTMIXER;   

        /* SC Block CR1 */ 
        Mixer_A_CR1_REG = (Mixer_A_COMP_4P35PF  |
                                Mixer_A_DIV2_DISABLE |
                                Mixer_A_GAIN_0DB);                                 

        /* 
            Set SC Block resistor values based on Local Oscillator being above 
            or below 100kHz - controled by r20_40 (Rmix) bit for CT mode mixer
            and SC Block
        */

        if (LOf < Mixer_A_LO_CLOCK_FREQ_100_KHz)
        {
            Mixer_A_CR2_REG = (Mixer_A_BIAS_LOW |
										Mixer_A_REDC_01 |
										Mixer_A_GNDVREF_DI |
										Mixer_A_R20_40B_40K);
        }
        else
        {
            Mixer_A_CR2_REG = (Mixer_A_BIAS_LOW |
										Mixer_A_REDC_01 |
										Mixer_A_GNDVREF_DI |
										Mixer_A_R20_40B_20K);
        }
    #else
        /* Discrete Time (down) mixer */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        Mixer_A_CR0_REG = Mixer_A_MODE_DTMIXER;       

        /* SC Block CR1 */ 
        Mixer_A_CR1_REG = (Mixer_A_COMP_4P35PF  |
                                Mixer_A_DIV2_ENABLE |
                                Mixer_A_GAIN_0DB);

        /* 
            Set SC Block resistor values based on Local Oscillator beign above 
            or below 100kHz - set r20_40 (input resitance) and rval (feedback) 
            resistor values seperately for DT mode and SC Block
        */
        if (LOf < Mixer_A_LO_CLOCK_FREQ_100_KHz)
        {
            Mixer_A_CR2_REG = (Mixer_A_BIAS_LOW |
										Mixer_A_GNDVREF_DI |
										Mixer_A_R20_40B_40K |
										Mixer_A_RVAL_40K); 
        }
        else
        {
            Mixer_A_CR2_REG = (Mixer_A_BIAS_LOW |
										Mixer_A_GNDVREF_DI |
										Mixer_A_R20_40B_20K |
										Mixer_A_RVAL_20K);
        }
    #endif /* end if - Mixer Type */

    /* Enable SC Block clocking */
    Mixer_A_CLK_REG |= Mixer_A_CLK_EN;

    /* Set default power */
    Mixer_A_SetPower(Mixer_A_INIT_POWER);
    
    /* Set 50 % Duty cycle for LO clock if LO source is internal */
    #if(Mixer_A_LO_SOURCE == Mixer_A_LO_SOURCE_INTERNAL)
        Mixer_A_aclk_SetMode(CYCLK_DUTY);
    #endif /* Mixer_A_LO_SOURCE == Mixer_A_LO_SOURCE_INTERNAL */

}


/*******************************************************************************
* Function Name: Mixer_A_Enable
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
void Mixer_A_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(Mixer_A_P5backup.enableState == 1u)
        {
            Mixer_A_CR1_REG = Mixer_A_P5backup.scCR1Reg;
            Mixer_A_CR2_REG = Mixer_A_P5backup.scCR2Reg;
            Mixer_A_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */
    
    /* Enable power to SC block in active mode */
    Mixer_A_PM_ACT_CFG_REG |= Mixer_A_ACT_PWR_EN;

    /* Enable power to SC block in Alternative active mode */
    Mixer_A_PM_STBY_CFG_REG |= Mixer_A_STBY_PWR_EN;
    
    /* Enable LO_Internal clock if LO source is choosen as internal */
    #if(Mixer_A_LO_SOURCE == Mixer_A_LO_SOURCE_INTERNAL)
        /* Enable power to the LO clock */
        Mixer_A_PWRMGR_ACLK_REG |= Mixer_A_ACT_PWR_ACLK_EN;        
        Mixer_A_STBY_PWRMGR_ACLK_REG |= Mixer_A_STBY_PWR_ACLK_EN;
        /* Enable the clock */
        Mixer_A_aclk_Enable();        
    #endif /* Mixer_A_LO_SOURCE == Mixer_A_LO_SOURCE_INTERNAL */

    Mixer_A_PUMP_CR1_REG |= Mixer_A_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                Mixer_A_BSTCLK_REG &= (uint8)(~Mixer_A_BST_CLK_INDEX_MASK);
                Mixer_A_BSTCLK_REG |= Mixer_A_BST_CLK_EN | CyScBoostClk__INDEX;
                Mixer_A_SC_MISC_REG |= Mixer_A_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                Mixer_A_BSTCLK_REG &= (uint8)(~Mixer_A_BST_CLK_EN);
                Mixer_A_SC_MISC_REG &= (uint8)(~Mixer_A_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: Mixer_A_Start
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
*  Mixer_A_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Theory: 
*  Full initialization of the SC Block configuration registers is only perfomed 
*  the first time the routine executes - global variable 
*  Mixer_A_initVar is used indicate that the static configuration has 
*  been completed.
*
*******************************************************************************/
void Mixer_A_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Mixer_A_initVar == 0u)
    {
        Mixer_A_Init();
        Mixer_A_initVar = 1u;
    }
    /* Enable the power to the block */
    Mixer_A_Enable();
    
}


/*******************************************************************************
* Function Name: Mixer_A_Stop
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
void Mixer_A_Stop(void) 
{       
    /* Disble power to the Amp in Active mode template */
    Mixer_A_PM_ACT_CFG_REG &= (uint8)(~Mixer_A_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    Mixer_A_PM_STBY_CFG_REG &= (uint8)(~Mixer_A_STBY_PWR_EN);
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            Mixer_A_BSTCLK_REG &= (uint8)(~Mixer_A_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((Mixer_A_PM_ACT_CFG_REG & Mixer_A_PM_ACT_CFG_MASK) == 0u)
            {
                Mixer_A_SC_MISC_REG &= (uint8)(~Mixer_A_PUMP_FORCE);
                Mixer_A_PUMP_CR1_REG &= (uint8)(~Mixer_A_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* This sets Sample and hold in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        Mixer_A_P5backup.scCR1Reg = Mixer_A_CR1_REG;
        Mixer_A_P5backup.scCR2Reg = Mixer_A_CR2_REG;
        Mixer_A_CR1_REG = 0x00u;
        Mixer_A_CR2_REG = 0x00u;
        Mixer_A_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */  
    
    /* Disable aclk */
    #if(Mixer_A_LO_SOURCE == Mixer_A_LO_SOURCE_INTERNAL)
        /* Disable power to clock */
        Mixer_A_PWRMGR_ACLK_REG &= (uint8)(~Mixer_A_ACT_PWR_ACLK_EN);
        Mixer_A_STBY_PWRMGR_ACLK_REG &= (uint8)(~Mixer_A_STBY_PWR_ACLK_EN);
        /* Disable the clock */
        Mixer_A_aclk_Disable();
    #endif /* Mixer_A_LO_SOURCE == Mixer_A_LO_SOURCE_INTERNAL */
}


/*******************************************************************************
* Function Name: Mixer_A_SetPower
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
void Mixer_A_SetPower(uint8 power) 
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */    
    tmpCR = Mixer_A_CR1_REG & (uint8)(~Mixer_A_DRIVE_MASK);
    tmpCR |= (power & Mixer_A_DRIVE_MASK);
    Mixer_A_CR1_REG = tmpCR;  
}


/* [] END OF FILE */
