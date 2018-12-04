/*******************************************************************************
* File Name: N1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_N1_H) /* Pins N1_H */
#define CY_PINS_N1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "N1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 N1__PORT == 15 && ((N1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    N1_Write(uint8 value);
void    N1_SetDriveMode(uint8 mode);
uint8   N1_ReadDataReg(void);
uint8   N1_Read(void);
void    N1_SetInterruptMode(uint16 position, uint16 mode);
uint8   N1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the N1_SetDriveMode() function.
     *  @{
     */
        #define N1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define N1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define N1_DM_RES_UP          PIN_DM_RES_UP
        #define N1_DM_RES_DWN         PIN_DM_RES_DWN
        #define N1_DM_OD_LO           PIN_DM_OD_LO
        #define N1_DM_OD_HI           PIN_DM_OD_HI
        #define N1_DM_STRONG          PIN_DM_STRONG
        #define N1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define N1_MASK               N1__MASK
#define N1_SHIFT              N1__SHIFT
#define N1_WIDTH              1u

/* Interrupt constants */
#if defined(N1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in N1_SetInterruptMode() function.
     *  @{
     */
        #define N1_INTR_NONE      (uint16)(0x0000u)
        #define N1_INTR_RISING    (uint16)(0x0001u)
        #define N1_INTR_FALLING   (uint16)(0x0002u)
        #define N1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define N1_INTR_MASK      (0x01u) 
#endif /* (N1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define N1_PS                     (* (reg8 *) N1__PS)
/* Data Register */
#define N1_DR                     (* (reg8 *) N1__DR)
/* Port Number */
#define N1_PRT_NUM                (* (reg8 *) N1__PRT) 
/* Connect to Analog Globals */                                                  
#define N1_AG                     (* (reg8 *) N1__AG)                       
/* Analog MUX bux enable */
#define N1_AMUX                   (* (reg8 *) N1__AMUX) 
/* Bidirectional Enable */                                                        
#define N1_BIE                    (* (reg8 *) N1__BIE)
/* Bit-mask for Aliased Register Access */
#define N1_BIT_MASK               (* (reg8 *) N1__BIT_MASK)
/* Bypass Enable */
#define N1_BYP                    (* (reg8 *) N1__BYP)
/* Port wide control signals */                                                   
#define N1_CTL                    (* (reg8 *) N1__CTL)
/* Drive Modes */
#define N1_DM0                    (* (reg8 *) N1__DM0) 
#define N1_DM1                    (* (reg8 *) N1__DM1)
#define N1_DM2                    (* (reg8 *) N1__DM2) 
/* Input Buffer Disable Override */
#define N1_INP_DIS                (* (reg8 *) N1__INP_DIS)
/* LCD Common or Segment Drive */
#define N1_LCD_COM_SEG            (* (reg8 *) N1__LCD_COM_SEG)
/* Enable Segment LCD */
#define N1_LCD_EN                 (* (reg8 *) N1__LCD_EN)
/* Slew Rate Control */
#define N1_SLW                    (* (reg8 *) N1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define N1_PRTDSI__CAPS_SEL       (* (reg8 *) N1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define N1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) N1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define N1_PRTDSI__OE_SEL0        (* (reg8 *) N1__PRTDSI__OE_SEL0) 
#define N1_PRTDSI__OE_SEL1        (* (reg8 *) N1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define N1_PRTDSI__OUT_SEL0       (* (reg8 *) N1__PRTDSI__OUT_SEL0) 
#define N1_PRTDSI__OUT_SEL1       (* (reg8 *) N1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define N1_PRTDSI__SYNC_OUT       (* (reg8 *) N1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(N1__SIO_CFG)
    #define N1_SIO_HYST_EN        (* (reg8 *) N1__SIO_HYST_EN)
    #define N1_SIO_REG_HIFREQ     (* (reg8 *) N1__SIO_REG_HIFREQ)
    #define N1_SIO_CFG            (* (reg8 *) N1__SIO_CFG)
    #define N1_SIO_DIFF           (* (reg8 *) N1__SIO_DIFF)
#endif /* (N1__SIO_CFG) */

/* Interrupt Registers */
#if defined(N1__INTSTAT)
    #define N1_INTSTAT            (* (reg8 *) N1__INTSTAT)
    #define N1_SNAP               (* (reg8 *) N1__SNAP)
    
	#define N1_0_INTTYPE_REG 		(* (reg8 *) N1__0__INTTYPE)
#endif /* (N1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_N1_H */


/* [] END OF FILE */
