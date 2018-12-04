/*******************************************************************************
* File Name: killswitchS.h  
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

#if !defined(CY_PINS_killswitchS_H) /* Pins killswitchS_H */
#define CY_PINS_killswitchS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "killswitchS_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 killswitchS__PORT == 15 && ((killswitchS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    killswitchS_Write(uint8 value);
void    killswitchS_SetDriveMode(uint8 mode);
uint8   killswitchS_ReadDataReg(void);
uint8   killswitchS_Read(void);
void    killswitchS_SetInterruptMode(uint16 position, uint16 mode);
uint8   killswitchS_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the killswitchS_SetDriveMode() function.
     *  @{
     */
        #define killswitchS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define killswitchS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define killswitchS_DM_RES_UP          PIN_DM_RES_UP
        #define killswitchS_DM_RES_DWN         PIN_DM_RES_DWN
        #define killswitchS_DM_OD_LO           PIN_DM_OD_LO
        #define killswitchS_DM_OD_HI           PIN_DM_OD_HI
        #define killswitchS_DM_STRONG          PIN_DM_STRONG
        #define killswitchS_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define killswitchS_MASK               killswitchS__MASK
#define killswitchS_SHIFT              killswitchS__SHIFT
#define killswitchS_WIDTH              1u

/* Interrupt constants */
#if defined(killswitchS__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in killswitchS_SetInterruptMode() function.
     *  @{
     */
        #define killswitchS_INTR_NONE      (uint16)(0x0000u)
        #define killswitchS_INTR_RISING    (uint16)(0x0001u)
        #define killswitchS_INTR_FALLING   (uint16)(0x0002u)
        #define killswitchS_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define killswitchS_INTR_MASK      (0x01u) 
#endif /* (killswitchS__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define killswitchS_PS                     (* (reg8 *) killswitchS__PS)
/* Data Register */
#define killswitchS_DR                     (* (reg8 *) killswitchS__DR)
/* Port Number */
#define killswitchS_PRT_NUM                (* (reg8 *) killswitchS__PRT) 
/* Connect to Analog Globals */                                                  
#define killswitchS_AG                     (* (reg8 *) killswitchS__AG)                       
/* Analog MUX bux enable */
#define killswitchS_AMUX                   (* (reg8 *) killswitchS__AMUX) 
/* Bidirectional Enable */                                                        
#define killswitchS_BIE                    (* (reg8 *) killswitchS__BIE)
/* Bit-mask for Aliased Register Access */
#define killswitchS_BIT_MASK               (* (reg8 *) killswitchS__BIT_MASK)
/* Bypass Enable */
#define killswitchS_BYP                    (* (reg8 *) killswitchS__BYP)
/* Port wide control signals */                                                   
#define killswitchS_CTL                    (* (reg8 *) killswitchS__CTL)
/* Drive Modes */
#define killswitchS_DM0                    (* (reg8 *) killswitchS__DM0) 
#define killswitchS_DM1                    (* (reg8 *) killswitchS__DM1)
#define killswitchS_DM2                    (* (reg8 *) killswitchS__DM2) 
/* Input Buffer Disable Override */
#define killswitchS_INP_DIS                (* (reg8 *) killswitchS__INP_DIS)
/* LCD Common or Segment Drive */
#define killswitchS_LCD_COM_SEG            (* (reg8 *) killswitchS__LCD_COM_SEG)
/* Enable Segment LCD */
#define killswitchS_LCD_EN                 (* (reg8 *) killswitchS__LCD_EN)
/* Slew Rate Control */
#define killswitchS_SLW                    (* (reg8 *) killswitchS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define killswitchS_PRTDSI__CAPS_SEL       (* (reg8 *) killswitchS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define killswitchS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) killswitchS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define killswitchS_PRTDSI__OE_SEL0        (* (reg8 *) killswitchS__PRTDSI__OE_SEL0) 
#define killswitchS_PRTDSI__OE_SEL1        (* (reg8 *) killswitchS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define killswitchS_PRTDSI__OUT_SEL0       (* (reg8 *) killswitchS__PRTDSI__OUT_SEL0) 
#define killswitchS_PRTDSI__OUT_SEL1       (* (reg8 *) killswitchS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define killswitchS_PRTDSI__SYNC_OUT       (* (reg8 *) killswitchS__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(killswitchS__SIO_CFG)
    #define killswitchS_SIO_HYST_EN        (* (reg8 *) killswitchS__SIO_HYST_EN)
    #define killswitchS_SIO_REG_HIFREQ     (* (reg8 *) killswitchS__SIO_REG_HIFREQ)
    #define killswitchS_SIO_CFG            (* (reg8 *) killswitchS__SIO_CFG)
    #define killswitchS_SIO_DIFF           (* (reg8 *) killswitchS__SIO_DIFF)
#endif /* (killswitchS__SIO_CFG) */

/* Interrupt Registers */
#if defined(killswitchS__INTSTAT)
    #define killswitchS_INTSTAT            (* (reg8 *) killswitchS__INTSTAT)
    #define killswitchS_SNAP               (* (reg8 *) killswitchS__SNAP)
    
	#define killswitchS_0_INTTYPE_REG 		(* (reg8 *) killswitchS__0__INTTYPE)
#endif /* (killswitchS__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_killswitchS_H */


/* [] END OF FILE */
