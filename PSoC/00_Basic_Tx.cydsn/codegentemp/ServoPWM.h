/*******************************************************************************
* File Name: ServoPWM.h  
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

#if !defined(CY_PINS_ServoPWM_H) /* Pins ServoPWM_H */
#define CY_PINS_ServoPWM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ServoPWM_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ServoPWM__PORT == 15 && ((ServoPWM__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ServoPWM_Write(uint8 value);
void    ServoPWM_SetDriveMode(uint8 mode);
uint8   ServoPWM_ReadDataReg(void);
uint8   ServoPWM_Read(void);
void    ServoPWM_SetInterruptMode(uint16 position, uint16 mode);
uint8   ServoPWM_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ServoPWM_SetDriveMode() function.
     *  @{
     */
        #define ServoPWM_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ServoPWM_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ServoPWM_DM_RES_UP          PIN_DM_RES_UP
        #define ServoPWM_DM_RES_DWN         PIN_DM_RES_DWN
        #define ServoPWM_DM_OD_LO           PIN_DM_OD_LO
        #define ServoPWM_DM_OD_HI           PIN_DM_OD_HI
        #define ServoPWM_DM_STRONG          PIN_DM_STRONG
        #define ServoPWM_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ServoPWM_MASK               ServoPWM__MASK
#define ServoPWM_SHIFT              ServoPWM__SHIFT
#define ServoPWM_WIDTH              1u

/* Interrupt constants */
#if defined(ServoPWM__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ServoPWM_SetInterruptMode() function.
     *  @{
     */
        #define ServoPWM_INTR_NONE      (uint16)(0x0000u)
        #define ServoPWM_INTR_RISING    (uint16)(0x0001u)
        #define ServoPWM_INTR_FALLING   (uint16)(0x0002u)
        #define ServoPWM_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ServoPWM_INTR_MASK      (0x01u) 
#endif /* (ServoPWM__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ServoPWM_PS                     (* (reg8 *) ServoPWM__PS)
/* Data Register */
#define ServoPWM_DR                     (* (reg8 *) ServoPWM__DR)
/* Port Number */
#define ServoPWM_PRT_NUM                (* (reg8 *) ServoPWM__PRT) 
/* Connect to Analog Globals */                                                  
#define ServoPWM_AG                     (* (reg8 *) ServoPWM__AG)                       
/* Analog MUX bux enable */
#define ServoPWM_AMUX                   (* (reg8 *) ServoPWM__AMUX) 
/* Bidirectional Enable */                                                        
#define ServoPWM_BIE                    (* (reg8 *) ServoPWM__BIE)
/* Bit-mask for Aliased Register Access */
#define ServoPWM_BIT_MASK               (* (reg8 *) ServoPWM__BIT_MASK)
/* Bypass Enable */
#define ServoPWM_BYP                    (* (reg8 *) ServoPWM__BYP)
/* Port wide control signals */                                                   
#define ServoPWM_CTL                    (* (reg8 *) ServoPWM__CTL)
/* Drive Modes */
#define ServoPWM_DM0                    (* (reg8 *) ServoPWM__DM0) 
#define ServoPWM_DM1                    (* (reg8 *) ServoPWM__DM1)
#define ServoPWM_DM2                    (* (reg8 *) ServoPWM__DM2) 
/* Input Buffer Disable Override */
#define ServoPWM_INP_DIS                (* (reg8 *) ServoPWM__INP_DIS)
/* LCD Common or Segment Drive */
#define ServoPWM_LCD_COM_SEG            (* (reg8 *) ServoPWM__LCD_COM_SEG)
/* Enable Segment LCD */
#define ServoPWM_LCD_EN                 (* (reg8 *) ServoPWM__LCD_EN)
/* Slew Rate Control */
#define ServoPWM_SLW                    (* (reg8 *) ServoPWM__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ServoPWM_PRTDSI__CAPS_SEL       (* (reg8 *) ServoPWM__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ServoPWM_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ServoPWM__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ServoPWM_PRTDSI__OE_SEL0        (* (reg8 *) ServoPWM__PRTDSI__OE_SEL0) 
#define ServoPWM_PRTDSI__OE_SEL1        (* (reg8 *) ServoPWM__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ServoPWM_PRTDSI__OUT_SEL0       (* (reg8 *) ServoPWM__PRTDSI__OUT_SEL0) 
#define ServoPWM_PRTDSI__OUT_SEL1       (* (reg8 *) ServoPWM__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ServoPWM_PRTDSI__SYNC_OUT       (* (reg8 *) ServoPWM__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ServoPWM__SIO_CFG)
    #define ServoPWM_SIO_HYST_EN        (* (reg8 *) ServoPWM__SIO_HYST_EN)
    #define ServoPWM_SIO_REG_HIFREQ     (* (reg8 *) ServoPWM__SIO_REG_HIFREQ)
    #define ServoPWM_SIO_CFG            (* (reg8 *) ServoPWM__SIO_CFG)
    #define ServoPWM_SIO_DIFF           (* (reg8 *) ServoPWM__SIO_DIFF)
#endif /* (ServoPWM__SIO_CFG) */

/* Interrupt Registers */
#if defined(ServoPWM__INTSTAT)
    #define ServoPWM_INTSTAT            (* (reg8 *) ServoPWM__INTSTAT)
    #define ServoPWM_SNAP               (* (reg8 *) ServoPWM__SNAP)
    
	#define ServoPWM_0_INTTYPE_REG 		(* (reg8 *) ServoPWM__0__INTTYPE)
#endif /* (ServoPWM__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ServoPWM_H */


/* [] END OF FILE */
