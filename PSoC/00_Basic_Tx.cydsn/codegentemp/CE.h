/*******************************************************************************
* File Name: CE.h  
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

#if !defined(CY_PINS_CE_H) /* Pins CE_H */
#define CY_PINS_CE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CE_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CE__PORT == 15 && ((CE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CE_Write(uint8 value);
void    CE_SetDriveMode(uint8 mode);
uint8   CE_ReadDataReg(void);
uint8   CE_Read(void);
void    CE_SetInterruptMode(uint16 position, uint16 mode);
uint8   CE_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CE_SetDriveMode() function.
     *  @{
     */
        #define CE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CE_DM_RES_UP          PIN_DM_RES_UP
        #define CE_DM_RES_DWN         PIN_DM_RES_DWN
        #define CE_DM_OD_LO           PIN_DM_OD_LO
        #define CE_DM_OD_HI           PIN_DM_OD_HI
        #define CE_DM_STRONG          PIN_DM_STRONG
        #define CE_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CE_MASK               CE__MASK
#define CE_SHIFT              CE__SHIFT
#define CE_WIDTH              1u

/* Interrupt constants */
#if defined(CE__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CE_SetInterruptMode() function.
     *  @{
     */
        #define CE_INTR_NONE      (uint16)(0x0000u)
        #define CE_INTR_RISING    (uint16)(0x0001u)
        #define CE_INTR_FALLING   (uint16)(0x0002u)
        #define CE_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CE_INTR_MASK      (0x01u) 
#endif /* (CE__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CE_PS                     (* (reg8 *) CE__PS)
/* Data Register */
#define CE_DR                     (* (reg8 *) CE__DR)
/* Port Number */
#define CE_PRT_NUM                (* (reg8 *) CE__PRT) 
/* Connect to Analog Globals */                                                  
#define CE_AG                     (* (reg8 *) CE__AG)                       
/* Analog MUX bux enable */
#define CE_AMUX                   (* (reg8 *) CE__AMUX) 
/* Bidirectional Enable */                                                        
#define CE_BIE                    (* (reg8 *) CE__BIE)
/* Bit-mask for Aliased Register Access */
#define CE_BIT_MASK               (* (reg8 *) CE__BIT_MASK)
/* Bypass Enable */
#define CE_BYP                    (* (reg8 *) CE__BYP)
/* Port wide control signals */                                                   
#define CE_CTL                    (* (reg8 *) CE__CTL)
/* Drive Modes */
#define CE_DM0                    (* (reg8 *) CE__DM0) 
#define CE_DM1                    (* (reg8 *) CE__DM1)
#define CE_DM2                    (* (reg8 *) CE__DM2) 
/* Input Buffer Disable Override */
#define CE_INP_DIS                (* (reg8 *) CE__INP_DIS)
/* LCD Common or Segment Drive */
#define CE_LCD_COM_SEG            (* (reg8 *) CE__LCD_COM_SEG)
/* Enable Segment LCD */
#define CE_LCD_EN                 (* (reg8 *) CE__LCD_EN)
/* Slew Rate Control */
#define CE_SLW                    (* (reg8 *) CE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CE_PRTDSI__CAPS_SEL       (* (reg8 *) CE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CE_PRTDSI__OE_SEL0        (* (reg8 *) CE__PRTDSI__OE_SEL0) 
#define CE_PRTDSI__OE_SEL1        (* (reg8 *) CE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CE_PRTDSI__OUT_SEL0       (* (reg8 *) CE__PRTDSI__OUT_SEL0) 
#define CE_PRTDSI__OUT_SEL1       (* (reg8 *) CE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CE_PRTDSI__SYNC_OUT       (* (reg8 *) CE__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CE__SIO_CFG)
    #define CE_SIO_HYST_EN        (* (reg8 *) CE__SIO_HYST_EN)
    #define CE_SIO_REG_HIFREQ     (* (reg8 *) CE__SIO_REG_HIFREQ)
    #define CE_SIO_CFG            (* (reg8 *) CE__SIO_CFG)
    #define CE_SIO_DIFF           (* (reg8 *) CE__SIO_DIFF)
#endif /* (CE__SIO_CFG) */

/* Interrupt Registers */
#if defined(CE__INTSTAT)
    #define CE_INTSTAT            (* (reg8 *) CE__INTSTAT)
    #define CE_SNAP               (* (reg8 *) CE__SNAP)
    
	#define CE_0_INTTYPE_REG 		(* (reg8 *) CE__0__INTTYPE)
#endif /* (CE__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CE_H */


/* [] END OF FILE */
