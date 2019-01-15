/*******************************************************************************
* File Name: ServoClock.h
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

#if !defined(CY_CLOCK_ServoClock_H)
#define CY_CLOCK_ServoClock_H

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

void ServoClock_Start(void) ;
void ServoClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void ServoClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void ServoClock_StandbyPower(uint8 state) ;
void ServoClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 ServoClock_GetDividerRegister(void) ;
void ServoClock_SetModeRegister(uint8 modeBitMask) ;
void ServoClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 ServoClock_GetModeRegister(void) ;
void ServoClock_SetSourceRegister(uint8 clkSource) ;
uint8 ServoClock_GetSourceRegister(void) ;
#if defined(ServoClock__CFG3)
void ServoClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 ServoClock_GetPhaseRegister(void) ;
#endif /* defined(ServoClock__CFG3) */

#define ServoClock_Enable()                       ServoClock_Start()
#define ServoClock_Disable()                      ServoClock_Stop()
#define ServoClock_SetDivider(clkDivider)         ServoClock_SetDividerRegister(clkDivider, 1u)
#define ServoClock_SetDividerValue(clkDivider)    ServoClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define ServoClock_SetMode(clkMode)               ServoClock_SetModeRegister(clkMode)
#define ServoClock_SetSource(clkSource)           ServoClock_SetSourceRegister(clkSource)
#if defined(ServoClock__CFG3)
#define ServoClock_SetPhase(clkPhase)             ServoClock_SetPhaseRegister(clkPhase)
#define ServoClock_SetPhaseValue(clkPhase)        ServoClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(ServoClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define ServoClock_CLKEN              (* (reg8 *) ServoClock__PM_ACT_CFG)
#define ServoClock_CLKEN_PTR          ((reg8 *) ServoClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define ServoClock_CLKSTBY            (* (reg8 *) ServoClock__PM_STBY_CFG)
#define ServoClock_CLKSTBY_PTR        ((reg8 *) ServoClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define ServoClock_DIV_LSB            (* (reg8 *) ServoClock__CFG0)
#define ServoClock_DIV_LSB_PTR        ((reg8 *) ServoClock__CFG0)
#define ServoClock_DIV_PTR            ((reg16 *) ServoClock__CFG0)

/* Clock MSB divider configuration register. */
#define ServoClock_DIV_MSB            (* (reg8 *) ServoClock__CFG1)
#define ServoClock_DIV_MSB_PTR        ((reg8 *) ServoClock__CFG1)

/* Mode and source configuration register */
#define ServoClock_MOD_SRC            (* (reg8 *) ServoClock__CFG2)
#define ServoClock_MOD_SRC_PTR        ((reg8 *) ServoClock__CFG2)

#if defined(ServoClock__CFG3)
/* Analog clock phase configuration register */
#define ServoClock_PHASE              (* (reg8 *) ServoClock__CFG3)
#define ServoClock_PHASE_PTR          ((reg8 *) ServoClock__CFG3)
#endif /* defined(ServoClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define ServoClock_CLKEN_MASK         ServoClock__PM_ACT_MSK
#define ServoClock_CLKSTBY_MASK       ServoClock__PM_STBY_MSK

/* CFG2 field masks */
#define ServoClock_SRC_SEL_MSK        ServoClock__CFG2_SRC_SEL_MASK
#define ServoClock_MODE_MASK          (~(ServoClock_SRC_SEL_MSK))

#if defined(ServoClock__CFG3)
/* CFG3 phase mask */
#define ServoClock_PHASE_MASK         ServoClock__CFG3_PHASE_DLY_MASK
#endif /* defined(ServoClock__CFG3) */

#endif /* CY_CLOCK_ServoClock_H */


/* [] END OF FILE */
