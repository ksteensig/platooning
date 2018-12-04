/*******************************************************************************
* File Name: Arduino.h  
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

#if !defined(CY_PINS_Arduino_H) /* Pins Arduino_H */
#define CY_PINS_Arduino_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Arduino_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Arduino__PORT == 15 && ((Arduino__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Arduino_Write(uint8 value);
void    Arduino_SetDriveMode(uint8 mode);
uint8   Arduino_ReadDataReg(void);
uint8   Arduino_Read(void);
void    Arduino_SetInterruptMode(uint16 position, uint16 mode);
uint8   Arduino_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Arduino_SetDriveMode() function.
     *  @{
     */
        #define Arduino_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Arduino_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Arduino_DM_RES_UP          PIN_DM_RES_UP
        #define Arduino_DM_RES_DWN         PIN_DM_RES_DWN
        #define Arduino_DM_OD_LO           PIN_DM_OD_LO
        #define Arduino_DM_OD_HI           PIN_DM_OD_HI
        #define Arduino_DM_STRONG          PIN_DM_STRONG
        #define Arduino_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Arduino_MASK               Arduino__MASK
#define Arduino_SHIFT              Arduino__SHIFT
#define Arduino_WIDTH              1u

/* Interrupt constants */
#if defined(Arduino__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Arduino_SetInterruptMode() function.
     *  @{
     */
        #define Arduino_INTR_NONE      (uint16)(0x0000u)
        #define Arduino_INTR_RISING    (uint16)(0x0001u)
        #define Arduino_INTR_FALLING   (uint16)(0x0002u)
        #define Arduino_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Arduino_INTR_MASK      (0x01u) 
#endif /* (Arduino__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Arduino_PS                     (* (reg8 *) Arduino__PS)
/* Data Register */
#define Arduino_DR                     (* (reg8 *) Arduino__DR)
/* Port Number */
#define Arduino_PRT_NUM                (* (reg8 *) Arduino__PRT) 
/* Connect to Analog Globals */                                                  
#define Arduino_AG                     (* (reg8 *) Arduino__AG)                       
/* Analog MUX bux enable */
#define Arduino_AMUX                   (* (reg8 *) Arduino__AMUX) 
/* Bidirectional Enable */                                                        
#define Arduino_BIE                    (* (reg8 *) Arduino__BIE)
/* Bit-mask for Aliased Register Access */
#define Arduino_BIT_MASK               (* (reg8 *) Arduino__BIT_MASK)
/* Bypass Enable */
#define Arduino_BYP                    (* (reg8 *) Arduino__BYP)
/* Port wide control signals */                                                   
#define Arduino_CTL                    (* (reg8 *) Arduino__CTL)
/* Drive Modes */
#define Arduino_DM0                    (* (reg8 *) Arduino__DM0) 
#define Arduino_DM1                    (* (reg8 *) Arduino__DM1)
#define Arduino_DM2                    (* (reg8 *) Arduino__DM2) 
/* Input Buffer Disable Override */
#define Arduino_INP_DIS                (* (reg8 *) Arduino__INP_DIS)
/* LCD Common or Segment Drive */
#define Arduino_LCD_COM_SEG            (* (reg8 *) Arduino__LCD_COM_SEG)
/* Enable Segment LCD */
#define Arduino_LCD_EN                 (* (reg8 *) Arduino__LCD_EN)
/* Slew Rate Control */
#define Arduino_SLW                    (* (reg8 *) Arduino__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Arduino_PRTDSI__CAPS_SEL       (* (reg8 *) Arduino__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Arduino_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Arduino__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Arduino_PRTDSI__OE_SEL0        (* (reg8 *) Arduino__PRTDSI__OE_SEL0) 
#define Arduino_PRTDSI__OE_SEL1        (* (reg8 *) Arduino__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Arduino_PRTDSI__OUT_SEL0       (* (reg8 *) Arduino__PRTDSI__OUT_SEL0) 
#define Arduino_PRTDSI__OUT_SEL1       (* (reg8 *) Arduino__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Arduino_PRTDSI__SYNC_OUT       (* (reg8 *) Arduino__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Arduino__SIO_CFG)
    #define Arduino_SIO_HYST_EN        (* (reg8 *) Arduino__SIO_HYST_EN)
    #define Arduino_SIO_REG_HIFREQ     (* (reg8 *) Arduino__SIO_REG_HIFREQ)
    #define Arduino_SIO_CFG            (* (reg8 *) Arduino__SIO_CFG)
    #define Arduino_SIO_DIFF           (* (reg8 *) Arduino__SIO_DIFF)
#endif /* (Arduino__SIO_CFG) */

/* Interrupt Registers */
#if defined(Arduino__INTSTAT)
    #define Arduino_INTSTAT            (* (reg8 *) Arduino__INTSTAT)
    #define Arduino_SNAP               (* (reg8 *) Arduino__SNAP)
    
	#define Arduino_0_INTTYPE_REG 		(* (reg8 *) Arduino__0__INTTYPE)
#endif /* (Arduino__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Arduino_H */


/* [] END OF FILE */
