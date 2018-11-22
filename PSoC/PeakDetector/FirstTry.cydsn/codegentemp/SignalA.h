/*******************************************************************************
* File Name: SignalA.h  
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

#if !defined(CY_PINS_SignalA_H) /* Pins SignalA_H */
#define CY_PINS_SignalA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SignalA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SignalA__PORT == 15 && ((SignalA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SignalA_Write(uint8 value);
void    SignalA_SetDriveMode(uint8 mode);
uint8   SignalA_ReadDataReg(void);
uint8   SignalA_Read(void);
void    SignalA_SetInterruptMode(uint16 position, uint16 mode);
uint8   SignalA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SignalA_SetDriveMode() function.
     *  @{
     */
        #define SignalA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SignalA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SignalA_DM_RES_UP          PIN_DM_RES_UP
        #define SignalA_DM_RES_DWN         PIN_DM_RES_DWN
        #define SignalA_DM_OD_LO           PIN_DM_OD_LO
        #define SignalA_DM_OD_HI           PIN_DM_OD_HI
        #define SignalA_DM_STRONG          PIN_DM_STRONG
        #define SignalA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SignalA_MASK               SignalA__MASK
#define SignalA_SHIFT              SignalA__SHIFT
#define SignalA_WIDTH              1u

/* Interrupt constants */
#if defined(SignalA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SignalA_SetInterruptMode() function.
     *  @{
     */
        #define SignalA_INTR_NONE      (uint16)(0x0000u)
        #define SignalA_INTR_RISING    (uint16)(0x0001u)
        #define SignalA_INTR_FALLING   (uint16)(0x0002u)
        #define SignalA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SignalA_INTR_MASK      (0x01u) 
#endif /* (SignalA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SignalA_PS                     (* (reg8 *) SignalA__PS)
/* Data Register */
#define SignalA_DR                     (* (reg8 *) SignalA__DR)
/* Port Number */
#define SignalA_PRT_NUM                (* (reg8 *) SignalA__PRT) 
/* Connect to Analog Globals */                                                  
#define SignalA_AG                     (* (reg8 *) SignalA__AG)                       
/* Analog MUX bux enable */
#define SignalA_AMUX                   (* (reg8 *) SignalA__AMUX) 
/* Bidirectional Enable */                                                        
#define SignalA_BIE                    (* (reg8 *) SignalA__BIE)
/* Bit-mask for Aliased Register Access */
#define SignalA_BIT_MASK               (* (reg8 *) SignalA__BIT_MASK)
/* Bypass Enable */
#define SignalA_BYP                    (* (reg8 *) SignalA__BYP)
/* Port wide control signals */                                                   
#define SignalA_CTL                    (* (reg8 *) SignalA__CTL)
/* Drive Modes */
#define SignalA_DM0                    (* (reg8 *) SignalA__DM0) 
#define SignalA_DM1                    (* (reg8 *) SignalA__DM1)
#define SignalA_DM2                    (* (reg8 *) SignalA__DM2) 
/* Input Buffer Disable Override */
#define SignalA_INP_DIS                (* (reg8 *) SignalA__INP_DIS)
/* LCD Common or Segment Drive */
#define SignalA_LCD_COM_SEG            (* (reg8 *) SignalA__LCD_COM_SEG)
/* Enable Segment LCD */
#define SignalA_LCD_EN                 (* (reg8 *) SignalA__LCD_EN)
/* Slew Rate Control */
#define SignalA_SLW                    (* (reg8 *) SignalA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SignalA_PRTDSI__CAPS_SEL       (* (reg8 *) SignalA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SignalA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SignalA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SignalA_PRTDSI__OE_SEL0        (* (reg8 *) SignalA__PRTDSI__OE_SEL0) 
#define SignalA_PRTDSI__OE_SEL1        (* (reg8 *) SignalA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SignalA_PRTDSI__OUT_SEL0       (* (reg8 *) SignalA__PRTDSI__OUT_SEL0) 
#define SignalA_PRTDSI__OUT_SEL1       (* (reg8 *) SignalA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SignalA_PRTDSI__SYNC_OUT       (* (reg8 *) SignalA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SignalA__SIO_CFG)
    #define SignalA_SIO_HYST_EN        (* (reg8 *) SignalA__SIO_HYST_EN)
    #define SignalA_SIO_REG_HIFREQ     (* (reg8 *) SignalA__SIO_REG_HIFREQ)
    #define SignalA_SIO_CFG            (* (reg8 *) SignalA__SIO_CFG)
    #define SignalA_SIO_DIFF           (* (reg8 *) SignalA__SIO_DIFF)
#endif /* (SignalA__SIO_CFG) */

/* Interrupt Registers */
#if defined(SignalA__INTSTAT)
    #define SignalA_INTSTAT            (* (reg8 *) SignalA__INTSTAT)
    #define SignalA_SNAP               (* (reg8 *) SignalA__SNAP)
    
	#define SignalA_0_INTTYPE_REG 		(* (reg8 *) SignalA__0__INTTYPE)
#endif /* (SignalA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SignalA_H */


/* [] END OF FILE */
