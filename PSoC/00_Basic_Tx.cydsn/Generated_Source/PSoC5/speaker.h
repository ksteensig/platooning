/*******************************************************************************
* File Name: speaker.h  
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

#if !defined(CY_PINS_speaker_H) /* Pins speaker_H */
#define CY_PINS_speaker_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "speaker_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 speaker__PORT == 15 && ((speaker__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    speaker_Write(uint8 value);
void    speaker_SetDriveMode(uint8 mode);
uint8   speaker_ReadDataReg(void);
uint8   speaker_Read(void);
void    speaker_SetInterruptMode(uint16 position, uint16 mode);
uint8   speaker_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the speaker_SetDriveMode() function.
     *  @{
     */
        #define speaker_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define speaker_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define speaker_DM_RES_UP          PIN_DM_RES_UP
        #define speaker_DM_RES_DWN         PIN_DM_RES_DWN
        #define speaker_DM_OD_LO           PIN_DM_OD_LO
        #define speaker_DM_OD_HI           PIN_DM_OD_HI
        #define speaker_DM_STRONG          PIN_DM_STRONG
        #define speaker_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define speaker_MASK               speaker__MASK
#define speaker_SHIFT              speaker__SHIFT
#define speaker_WIDTH              1u

/* Interrupt constants */
#if defined(speaker__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in speaker_SetInterruptMode() function.
     *  @{
     */
        #define speaker_INTR_NONE      (uint16)(0x0000u)
        #define speaker_INTR_RISING    (uint16)(0x0001u)
        #define speaker_INTR_FALLING   (uint16)(0x0002u)
        #define speaker_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define speaker_INTR_MASK      (0x01u) 
#endif /* (speaker__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define speaker_PS                     (* (reg8 *) speaker__PS)
/* Data Register */
#define speaker_DR                     (* (reg8 *) speaker__DR)
/* Port Number */
#define speaker_PRT_NUM                (* (reg8 *) speaker__PRT) 
/* Connect to Analog Globals */                                                  
#define speaker_AG                     (* (reg8 *) speaker__AG)                       
/* Analog MUX bux enable */
#define speaker_AMUX                   (* (reg8 *) speaker__AMUX) 
/* Bidirectional Enable */                                                        
#define speaker_BIE                    (* (reg8 *) speaker__BIE)
/* Bit-mask for Aliased Register Access */
#define speaker_BIT_MASK               (* (reg8 *) speaker__BIT_MASK)
/* Bypass Enable */
#define speaker_BYP                    (* (reg8 *) speaker__BYP)
/* Port wide control signals */                                                   
#define speaker_CTL                    (* (reg8 *) speaker__CTL)
/* Drive Modes */
#define speaker_DM0                    (* (reg8 *) speaker__DM0) 
#define speaker_DM1                    (* (reg8 *) speaker__DM1)
#define speaker_DM2                    (* (reg8 *) speaker__DM2) 
/* Input Buffer Disable Override */
#define speaker_INP_DIS                (* (reg8 *) speaker__INP_DIS)
/* LCD Common or Segment Drive */
#define speaker_LCD_COM_SEG            (* (reg8 *) speaker__LCD_COM_SEG)
/* Enable Segment LCD */
#define speaker_LCD_EN                 (* (reg8 *) speaker__LCD_EN)
/* Slew Rate Control */
#define speaker_SLW                    (* (reg8 *) speaker__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define speaker_PRTDSI__CAPS_SEL       (* (reg8 *) speaker__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define speaker_PRTDSI__DBL_SYNC_IN    (* (reg8 *) speaker__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define speaker_PRTDSI__OE_SEL0        (* (reg8 *) speaker__PRTDSI__OE_SEL0) 
#define speaker_PRTDSI__OE_SEL1        (* (reg8 *) speaker__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define speaker_PRTDSI__OUT_SEL0       (* (reg8 *) speaker__PRTDSI__OUT_SEL0) 
#define speaker_PRTDSI__OUT_SEL1       (* (reg8 *) speaker__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define speaker_PRTDSI__SYNC_OUT       (* (reg8 *) speaker__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(speaker__SIO_CFG)
    #define speaker_SIO_HYST_EN        (* (reg8 *) speaker__SIO_HYST_EN)
    #define speaker_SIO_REG_HIFREQ     (* (reg8 *) speaker__SIO_REG_HIFREQ)
    #define speaker_SIO_CFG            (* (reg8 *) speaker__SIO_CFG)
    #define speaker_SIO_DIFF           (* (reg8 *) speaker__SIO_DIFF)
#endif /* (speaker__SIO_CFG) */

/* Interrupt Registers */
#if defined(speaker__INTSTAT)
    #define speaker_INTSTAT            (* (reg8 *) speaker__INTSTAT)
    #define speaker_SNAP               (* (reg8 *) speaker__SNAP)
    
	#define speaker_0_INTTYPE_REG 		(* (reg8 *) speaker__0__INTTYPE)
#endif /* (speaker__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_speaker_H */


/* [] END OF FILE */
