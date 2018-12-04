/*******************************************************************************
* File Name: killswitchP.h  
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

#if !defined(CY_PINS_killswitchP_H) /* Pins killswitchP_H */
#define CY_PINS_killswitchP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "killswitchP_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 killswitchP__PORT == 15 && ((killswitchP__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    killswitchP_Write(uint8 value);
void    killswitchP_SetDriveMode(uint8 mode);
uint8   killswitchP_ReadDataReg(void);
uint8   killswitchP_Read(void);
void    killswitchP_SetInterruptMode(uint16 position, uint16 mode);
uint8   killswitchP_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the killswitchP_SetDriveMode() function.
     *  @{
     */
        #define killswitchP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define killswitchP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define killswitchP_DM_RES_UP          PIN_DM_RES_UP
        #define killswitchP_DM_RES_DWN         PIN_DM_RES_DWN
        #define killswitchP_DM_OD_LO           PIN_DM_OD_LO
        #define killswitchP_DM_OD_HI           PIN_DM_OD_HI
        #define killswitchP_DM_STRONG          PIN_DM_STRONG
        #define killswitchP_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define killswitchP_MASK               killswitchP__MASK
#define killswitchP_SHIFT              killswitchP__SHIFT
#define killswitchP_WIDTH              1u

/* Interrupt constants */
#if defined(killswitchP__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in killswitchP_SetInterruptMode() function.
     *  @{
     */
        #define killswitchP_INTR_NONE      (uint16)(0x0000u)
        #define killswitchP_INTR_RISING    (uint16)(0x0001u)
        #define killswitchP_INTR_FALLING   (uint16)(0x0002u)
        #define killswitchP_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define killswitchP_INTR_MASK      (0x01u) 
#endif /* (killswitchP__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define killswitchP_PS                     (* (reg8 *) killswitchP__PS)
/* Data Register */
#define killswitchP_DR                     (* (reg8 *) killswitchP__DR)
/* Port Number */
#define killswitchP_PRT_NUM                (* (reg8 *) killswitchP__PRT) 
/* Connect to Analog Globals */                                                  
#define killswitchP_AG                     (* (reg8 *) killswitchP__AG)                       
/* Analog MUX bux enable */
#define killswitchP_AMUX                   (* (reg8 *) killswitchP__AMUX) 
/* Bidirectional Enable */                                                        
#define killswitchP_BIE                    (* (reg8 *) killswitchP__BIE)
/* Bit-mask for Aliased Register Access */
#define killswitchP_BIT_MASK               (* (reg8 *) killswitchP__BIT_MASK)
/* Bypass Enable */
#define killswitchP_BYP                    (* (reg8 *) killswitchP__BYP)
/* Port wide control signals */                                                   
#define killswitchP_CTL                    (* (reg8 *) killswitchP__CTL)
/* Drive Modes */
#define killswitchP_DM0                    (* (reg8 *) killswitchP__DM0) 
#define killswitchP_DM1                    (* (reg8 *) killswitchP__DM1)
#define killswitchP_DM2                    (* (reg8 *) killswitchP__DM2) 
/* Input Buffer Disable Override */
#define killswitchP_INP_DIS                (* (reg8 *) killswitchP__INP_DIS)
/* LCD Common or Segment Drive */
#define killswitchP_LCD_COM_SEG            (* (reg8 *) killswitchP__LCD_COM_SEG)
/* Enable Segment LCD */
#define killswitchP_LCD_EN                 (* (reg8 *) killswitchP__LCD_EN)
/* Slew Rate Control */
#define killswitchP_SLW                    (* (reg8 *) killswitchP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define killswitchP_PRTDSI__CAPS_SEL       (* (reg8 *) killswitchP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define killswitchP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) killswitchP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define killswitchP_PRTDSI__OE_SEL0        (* (reg8 *) killswitchP__PRTDSI__OE_SEL0) 
#define killswitchP_PRTDSI__OE_SEL1        (* (reg8 *) killswitchP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define killswitchP_PRTDSI__OUT_SEL0       (* (reg8 *) killswitchP__PRTDSI__OUT_SEL0) 
#define killswitchP_PRTDSI__OUT_SEL1       (* (reg8 *) killswitchP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define killswitchP_PRTDSI__SYNC_OUT       (* (reg8 *) killswitchP__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(killswitchP__SIO_CFG)
    #define killswitchP_SIO_HYST_EN        (* (reg8 *) killswitchP__SIO_HYST_EN)
    #define killswitchP_SIO_REG_HIFREQ     (* (reg8 *) killswitchP__SIO_REG_HIFREQ)
    #define killswitchP_SIO_CFG            (* (reg8 *) killswitchP__SIO_CFG)
    #define killswitchP_SIO_DIFF           (* (reg8 *) killswitchP__SIO_DIFF)
#endif /* (killswitchP__SIO_CFG) */

/* Interrupt Registers */
#if defined(killswitchP__INTSTAT)
    #define killswitchP_INTSTAT            (* (reg8 *) killswitchP__INTSTAT)
    #define killswitchP_SNAP               (* (reg8 *) killswitchP__SNAP)
    
	#define killswitchP_0_INTTYPE_REG 		(* (reg8 *) killswitchP__0__INTTYPE)
#endif /* (killswitchP__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_killswitchP_H */


/* [] END OF FILE */
