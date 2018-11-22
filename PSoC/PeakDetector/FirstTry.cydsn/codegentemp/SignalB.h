/*******************************************************************************
* File Name: SignalB.h  
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

#if !defined(CY_PINS_SignalB_H) /* Pins SignalB_H */
#define CY_PINS_SignalB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SignalB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SignalB__PORT == 15 && ((SignalB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SignalB_Write(uint8 value);
void    SignalB_SetDriveMode(uint8 mode);
uint8   SignalB_ReadDataReg(void);
uint8   SignalB_Read(void);
void    SignalB_SetInterruptMode(uint16 position, uint16 mode);
uint8   SignalB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SignalB_SetDriveMode() function.
     *  @{
     */
        #define SignalB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SignalB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SignalB_DM_RES_UP          PIN_DM_RES_UP
        #define SignalB_DM_RES_DWN         PIN_DM_RES_DWN
        #define SignalB_DM_OD_LO           PIN_DM_OD_LO
        #define SignalB_DM_OD_HI           PIN_DM_OD_HI
        #define SignalB_DM_STRONG          PIN_DM_STRONG
        #define SignalB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SignalB_MASK               SignalB__MASK
#define SignalB_SHIFT              SignalB__SHIFT
#define SignalB_WIDTH              1u

/* Interrupt constants */
#if defined(SignalB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SignalB_SetInterruptMode() function.
     *  @{
     */
        #define SignalB_INTR_NONE      (uint16)(0x0000u)
        #define SignalB_INTR_RISING    (uint16)(0x0001u)
        #define SignalB_INTR_FALLING   (uint16)(0x0002u)
        #define SignalB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SignalB_INTR_MASK      (0x01u) 
#endif /* (SignalB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SignalB_PS                     (* (reg8 *) SignalB__PS)
/* Data Register */
#define SignalB_DR                     (* (reg8 *) SignalB__DR)
/* Port Number */
#define SignalB_PRT_NUM                (* (reg8 *) SignalB__PRT) 
/* Connect to Analog Globals */                                                  
#define SignalB_AG                     (* (reg8 *) SignalB__AG)                       
/* Analog MUX bux enable */
#define SignalB_AMUX                   (* (reg8 *) SignalB__AMUX) 
/* Bidirectional Enable */                                                        
#define SignalB_BIE                    (* (reg8 *) SignalB__BIE)
/* Bit-mask for Aliased Register Access */
#define SignalB_BIT_MASK               (* (reg8 *) SignalB__BIT_MASK)
/* Bypass Enable */
#define SignalB_BYP                    (* (reg8 *) SignalB__BYP)
/* Port wide control signals */                                                   
#define SignalB_CTL                    (* (reg8 *) SignalB__CTL)
/* Drive Modes */
#define SignalB_DM0                    (* (reg8 *) SignalB__DM0) 
#define SignalB_DM1                    (* (reg8 *) SignalB__DM1)
#define SignalB_DM2                    (* (reg8 *) SignalB__DM2) 
/* Input Buffer Disable Override */
#define SignalB_INP_DIS                (* (reg8 *) SignalB__INP_DIS)
/* LCD Common or Segment Drive */
#define SignalB_LCD_COM_SEG            (* (reg8 *) SignalB__LCD_COM_SEG)
/* Enable Segment LCD */
#define SignalB_LCD_EN                 (* (reg8 *) SignalB__LCD_EN)
/* Slew Rate Control */
#define SignalB_SLW                    (* (reg8 *) SignalB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SignalB_PRTDSI__CAPS_SEL       (* (reg8 *) SignalB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SignalB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SignalB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SignalB_PRTDSI__OE_SEL0        (* (reg8 *) SignalB__PRTDSI__OE_SEL0) 
#define SignalB_PRTDSI__OE_SEL1        (* (reg8 *) SignalB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SignalB_PRTDSI__OUT_SEL0       (* (reg8 *) SignalB__PRTDSI__OUT_SEL0) 
#define SignalB_PRTDSI__OUT_SEL1       (* (reg8 *) SignalB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SignalB_PRTDSI__SYNC_OUT       (* (reg8 *) SignalB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SignalB__SIO_CFG)
    #define SignalB_SIO_HYST_EN        (* (reg8 *) SignalB__SIO_HYST_EN)
    #define SignalB_SIO_REG_HIFREQ     (* (reg8 *) SignalB__SIO_REG_HIFREQ)
    #define SignalB_SIO_CFG            (* (reg8 *) SignalB__SIO_CFG)
    #define SignalB_SIO_DIFF           (* (reg8 *) SignalB__SIO_DIFF)
#endif /* (SignalB__SIO_CFG) */

/* Interrupt Registers */
#if defined(SignalB__INTSTAT)
    #define SignalB_INTSTAT            (* (reg8 *) SignalB__INTSTAT)
    #define SignalB_SNAP               (* (reg8 *) SignalB__SNAP)
    
	#define SignalB_0_INTTYPE_REG 		(* (reg8 *) SignalB__0__INTTYPE)
#endif /* (SignalB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SignalB_H */


/* [] END OF FILE */
