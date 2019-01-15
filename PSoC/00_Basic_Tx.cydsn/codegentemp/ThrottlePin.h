/*******************************************************************************
* File Name: ThrottlePin.h  
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

#if !defined(CY_PINS_ThrottlePin_H) /* Pins ThrottlePin_H */
#define CY_PINS_ThrottlePin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ThrottlePin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ThrottlePin__PORT == 15 && ((ThrottlePin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ThrottlePin_Write(uint8 value);
void    ThrottlePin_SetDriveMode(uint8 mode);
uint8   ThrottlePin_ReadDataReg(void);
uint8   ThrottlePin_Read(void);
void    ThrottlePin_SetInterruptMode(uint16 position, uint16 mode);
uint8   ThrottlePin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ThrottlePin_SetDriveMode() function.
     *  @{
     */
        #define ThrottlePin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ThrottlePin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ThrottlePin_DM_RES_UP          PIN_DM_RES_UP
        #define ThrottlePin_DM_RES_DWN         PIN_DM_RES_DWN
        #define ThrottlePin_DM_OD_LO           PIN_DM_OD_LO
        #define ThrottlePin_DM_OD_HI           PIN_DM_OD_HI
        #define ThrottlePin_DM_STRONG          PIN_DM_STRONG
        #define ThrottlePin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ThrottlePin_MASK               ThrottlePin__MASK
#define ThrottlePin_SHIFT              ThrottlePin__SHIFT
#define ThrottlePin_WIDTH              1u

/* Interrupt constants */
#if defined(ThrottlePin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ThrottlePin_SetInterruptMode() function.
     *  @{
     */
        #define ThrottlePin_INTR_NONE      (uint16)(0x0000u)
        #define ThrottlePin_INTR_RISING    (uint16)(0x0001u)
        #define ThrottlePin_INTR_FALLING   (uint16)(0x0002u)
        #define ThrottlePin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ThrottlePin_INTR_MASK      (0x01u) 
#endif /* (ThrottlePin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ThrottlePin_PS                     (* (reg8 *) ThrottlePin__PS)
/* Data Register */
#define ThrottlePin_DR                     (* (reg8 *) ThrottlePin__DR)
/* Port Number */
#define ThrottlePin_PRT_NUM                (* (reg8 *) ThrottlePin__PRT) 
/* Connect to Analog Globals */                                                  
#define ThrottlePin_AG                     (* (reg8 *) ThrottlePin__AG)                       
/* Analog MUX bux enable */
#define ThrottlePin_AMUX                   (* (reg8 *) ThrottlePin__AMUX) 
/* Bidirectional Enable */                                                        
#define ThrottlePin_BIE                    (* (reg8 *) ThrottlePin__BIE)
/* Bit-mask for Aliased Register Access */
#define ThrottlePin_BIT_MASK               (* (reg8 *) ThrottlePin__BIT_MASK)
/* Bypass Enable */
#define ThrottlePin_BYP                    (* (reg8 *) ThrottlePin__BYP)
/* Port wide control signals */                                                   
#define ThrottlePin_CTL                    (* (reg8 *) ThrottlePin__CTL)
/* Drive Modes */
#define ThrottlePin_DM0                    (* (reg8 *) ThrottlePin__DM0) 
#define ThrottlePin_DM1                    (* (reg8 *) ThrottlePin__DM1)
#define ThrottlePin_DM2                    (* (reg8 *) ThrottlePin__DM2) 
/* Input Buffer Disable Override */
#define ThrottlePin_INP_DIS                (* (reg8 *) ThrottlePin__INP_DIS)
/* LCD Common or Segment Drive */
#define ThrottlePin_LCD_COM_SEG            (* (reg8 *) ThrottlePin__LCD_COM_SEG)
/* Enable Segment LCD */
#define ThrottlePin_LCD_EN                 (* (reg8 *) ThrottlePin__LCD_EN)
/* Slew Rate Control */
#define ThrottlePin_SLW                    (* (reg8 *) ThrottlePin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ThrottlePin_PRTDSI__CAPS_SEL       (* (reg8 *) ThrottlePin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ThrottlePin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ThrottlePin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ThrottlePin_PRTDSI__OE_SEL0        (* (reg8 *) ThrottlePin__PRTDSI__OE_SEL0) 
#define ThrottlePin_PRTDSI__OE_SEL1        (* (reg8 *) ThrottlePin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ThrottlePin_PRTDSI__OUT_SEL0       (* (reg8 *) ThrottlePin__PRTDSI__OUT_SEL0) 
#define ThrottlePin_PRTDSI__OUT_SEL1       (* (reg8 *) ThrottlePin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ThrottlePin_PRTDSI__SYNC_OUT       (* (reg8 *) ThrottlePin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ThrottlePin__SIO_CFG)
    #define ThrottlePin_SIO_HYST_EN        (* (reg8 *) ThrottlePin__SIO_HYST_EN)
    #define ThrottlePin_SIO_REG_HIFREQ     (* (reg8 *) ThrottlePin__SIO_REG_HIFREQ)
    #define ThrottlePin_SIO_CFG            (* (reg8 *) ThrottlePin__SIO_CFG)
    #define ThrottlePin_SIO_DIFF           (* (reg8 *) ThrottlePin__SIO_DIFF)
#endif /* (ThrottlePin__SIO_CFG) */

/* Interrupt Registers */
#if defined(ThrottlePin__INTSTAT)
    #define ThrottlePin_INTSTAT            (* (reg8 *) ThrottlePin__INTSTAT)
    #define ThrottlePin_SNAP               (* (reg8 *) ThrottlePin__SNAP)
    
	#define ThrottlePin_0_INTTYPE_REG 		(* (reg8 *) ThrottlePin__0__INTTYPE)
#endif /* (ThrottlePin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ThrottlePin_H */


/* [] END OF FILE */
