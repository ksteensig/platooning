/*******************************************************************************
* File Name: Hbridge_Clock.h
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

#if !defined(CY_CLOCK_Hbridge_Clock_H)
#define CY_CLOCK_Hbridge_Clock_H

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

void Hbridge_Clock_Start(void) ;
void Hbridge_Clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Hbridge_Clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Hbridge_Clock_StandbyPower(uint8 state) ;
void Hbridge_Clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Hbridge_Clock_GetDividerRegister(void) ;
void Hbridge_Clock_SetModeRegister(uint8 modeBitMask) ;
void Hbridge_Clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 Hbridge_Clock_GetModeRegister(void) ;
void Hbridge_Clock_SetSourceRegister(uint8 clkSource) ;
uint8 Hbridge_Clock_GetSourceRegister(void) ;
#if defined(Hbridge_Clock__CFG3)
void Hbridge_Clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 Hbridge_Clock_GetPhaseRegister(void) ;
#endif /* defined(Hbridge_Clock__CFG3) */

#define Hbridge_Clock_Enable()                       Hbridge_Clock_Start()
#define Hbridge_Clock_Disable()                      Hbridge_Clock_Stop()
#define Hbridge_Clock_SetDivider(clkDivider)         Hbridge_Clock_SetDividerRegister(clkDivider, 1u)
#define Hbridge_Clock_SetDividerValue(clkDivider)    Hbridge_Clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define Hbridge_Clock_SetMode(clkMode)               Hbridge_Clock_SetModeRegister(clkMode)
#define Hbridge_Clock_SetSource(clkSource)           Hbridge_Clock_SetSourceRegister(clkSource)
#if defined(Hbridge_Clock__CFG3)
#define Hbridge_Clock_SetPhase(clkPhase)             Hbridge_Clock_SetPhaseRegister(clkPhase)
#define Hbridge_Clock_SetPhaseValue(clkPhase)        Hbridge_Clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Hbridge_Clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Hbridge_Clock_CLKEN              (* (reg8 *) Hbridge_Clock__PM_ACT_CFG)
#define Hbridge_Clock_CLKEN_PTR          ((reg8 *) Hbridge_Clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Hbridge_Clock_CLKSTBY            (* (reg8 *) Hbridge_Clock__PM_STBY_CFG)
#define Hbridge_Clock_CLKSTBY_PTR        ((reg8 *) Hbridge_Clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Hbridge_Clock_DIV_LSB            (* (reg8 *) Hbridge_Clock__CFG0)
#define Hbridge_Clock_DIV_LSB_PTR        ((reg8 *) Hbridge_Clock__CFG0)
#define Hbridge_Clock_DIV_PTR            ((reg16 *) Hbridge_Clock__CFG0)

/* Clock MSB divider configuration register. */
#define Hbridge_Clock_DIV_MSB            (* (reg8 *) Hbridge_Clock__CFG1)
#define Hbridge_Clock_DIV_MSB_PTR        ((reg8 *) Hbridge_Clock__CFG1)

/* Mode and source configuration register */
#define Hbridge_Clock_MOD_SRC            (* (reg8 *) Hbridge_Clock__CFG2)
#define Hbridge_Clock_MOD_SRC_PTR        ((reg8 *) Hbridge_Clock__CFG2)

#if defined(Hbridge_Clock__CFG3)
/* Analog clock phase configuration register */
#define Hbridge_Clock_PHASE              (* (reg8 *) Hbridge_Clock__CFG3)
#define Hbridge_Clock_PHASE_PTR          ((reg8 *) Hbridge_Clock__CFG3)
#endif /* defined(Hbridge_Clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Hbridge_Clock_CLKEN_MASK         Hbridge_Clock__PM_ACT_MSK
#define Hbridge_Clock_CLKSTBY_MASK       Hbridge_Clock__PM_STBY_MSK

/* CFG2 field masks */
#define Hbridge_Clock_SRC_SEL_MSK        Hbridge_Clock__CFG2_SRC_SEL_MASK
#define Hbridge_Clock_MODE_MASK          (~(Hbridge_Clock_SRC_SEL_MSK))

#if defined(Hbridge_Clock__CFG3)
/* CFG3 phase mask */
#define Hbridge_Clock_PHASE_MASK         Hbridge_Clock__CFG3_PHASE_DLY_MASK
#endif /* defined(Hbridge_Clock__CFG3) */

#endif /* CY_CLOCK_Hbridge_Clock_H */


/* [] END OF FILE */
