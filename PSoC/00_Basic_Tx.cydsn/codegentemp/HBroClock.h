/*******************************************************************************
* File Name: HBroClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_HBroClock_H)
#define CY_CLOCK_HBroClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void HBroClock_Start(void) ;
void HBroClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void HBroClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void HBroClock_StandbyPower(uint8 state) ;
void HBroClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 HBroClock_GetDividerRegister(void) ;
void HBroClock_SetModeRegister(uint8 modeBitMask) ;
void HBroClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 HBroClock_GetModeRegister(void) ;
void HBroClock_SetSourceRegister(uint8 clkSource) ;
uint8 HBroClock_GetSourceRegister(void) ;
#if defined(HBroClock__CFG3)
void HBroClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 HBroClock_GetPhaseRegister(void) ;
#endif /* defined(HBroClock__CFG3) */

#define HBroClock_Enable()                       HBroClock_Start()
#define HBroClock_Disable()                      HBroClock_Stop()
#define HBroClock_SetDivider(clkDivider)         HBroClock_SetDividerRegister(clkDivider, 1u)
#define HBroClock_SetDividerValue(clkDivider)    HBroClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define HBroClock_SetMode(clkMode)               HBroClock_SetModeRegister(clkMode)
#define HBroClock_SetSource(clkSource)           HBroClock_SetSourceRegister(clkSource)
#if defined(HBroClock__CFG3)
#define HBroClock_SetPhase(clkPhase)             HBroClock_SetPhaseRegister(clkPhase)
#define HBroClock_SetPhaseValue(clkPhase)        HBroClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(HBroClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define HBroClock_CLKEN              (* (reg8 *) HBroClock__PM_ACT_CFG)
#define HBroClock_CLKEN_PTR          ((reg8 *) HBroClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define HBroClock_CLKSTBY            (* (reg8 *) HBroClock__PM_STBY_CFG)
#define HBroClock_CLKSTBY_PTR        ((reg8 *) HBroClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define HBroClock_DIV_LSB            (* (reg8 *) HBroClock__CFG0)
#define HBroClock_DIV_LSB_PTR        ((reg8 *) HBroClock__CFG0)
#define HBroClock_DIV_PTR            ((reg16 *) HBroClock__CFG0)

/* Clock MSB divider configuration register. */
#define HBroClock_DIV_MSB            (* (reg8 *) HBroClock__CFG1)
#define HBroClock_DIV_MSB_PTR        ((reg8 *) HBroClock__CFG1)

/* Mode and source configuration register */
#define HBroClock_MOD_SRC            (* (reg8 *) HBroClock__CFG2)
#define HBroClock_MOD_SRC_PTR        ((reg8 *) HBroClock__CFG2)

#if defined(HBroClock__CFG3)
/* Analog clock phase configuration register */
#define HBroClock_PHASE              (* (reg8 *) HBroClock__CFG3)
#define HBroClock_PHASE_PTR          ((reg8 *) HBroClock__CFG3)
#endif /* defined(HBroClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define HBroClock_CLKEN_MASK         HBroClock__PM_ACT_MSK
#define HBroClock_CLKSTBY_MASK       HBroClock__PM_STBY_MSK

/* CFG2 field masks */
#define HBroClock_SRC_SEL_MSK        HBroClock__CFG2_SRC_SEL_MASK
#define HBroClock_MODE_MASK          (~(HBroClock_SRC_SEL_MSK))

#if defined(HBroClock__CFG3)
/* CFG3 phase mask */
#define HBroClock_PHASE_MASK         HBroClock__CFG3_PHASE_DLY_MASK
#endif /* defined(HBroClock__CFG3) */

#endif /* CY_CLOCK_HBroClock_H */


/* [] END OF FILE */
