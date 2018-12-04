/*******************************************************************************
* File Name: Signal_B.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Signal_B_H) /* Pins Signal_B_H */
#define CY_PINS_Signal_B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Signal_B_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Signal_B__PORT == 15 && ((Signal_B__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Signal_B_Write(uint8 value) ;
void    Signal_B_SetDriveMode(uint8 mode) ;
uint8   Signal_B_ReadDataReg(void) ;
uint8   Signal_B_Read(void) ;
uint8   Signal_B_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Signal_B_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Signal_B_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Signal_B_DM_RES_UP          PIN_DM_RES_UP
#define Signal_B_DM_RES_DWN         PIN_DM_RES_DWN
#define Signal_B_DM_OD_LO           PIN_DM_OD_LO
#define Signal_B_DM_OD_HI           PIN_DM_OD_HI
#define Signal_B_DM_STRONG          PIN_DM_STRONG
#define Signal_B_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Signal_B_MASK               Signal_B__MASK
#define Signal_B_SHIFT              Signal_B__SHIFT
#define Signal_B_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Signal_B_PS                     (* (reg8 *) Signal_B__PS)
/* Data Register */
#define Signal_B_DR                     (* (reg8 *) Signal_B__DR)
/* Port Number */
#define Signal_B_PRT_NUM                (* (reg8 *) Signal_B__PRT) 
/* Connect to Analog Globals */                                                  
#define Signal_B_AG                     (* (reg8 *) Signal_B__AG)                       
/* Analog MUX bux enable */
#define Signal_B_AMUX                   (* (reg8 *) Signal_B__AMUX) 
/* Bidirectional Enable */                                                        
#define Signal_B_BIE                    (* (reg8 *) Signal_B__BIE)
/* Bit-mask for Aliased Register Access */
#define Signal_B_BIT_MASK               (* (reg8 *) Signal_B__BIT_MASK)
/* Bypass Enable */
#define Signal_B_BYP                    (* (reg8 *) Signal_B__BYP)
/* Port wide control signals */                                                   
#define Signal_B_CTL                    (* (reg8 *) Signal_B__CTL)
/* Drive Modes */
#define Signal_B_DM0                    (* (reg8 *) Signal_B__DM0) 
#define Signal_B_DM1                    (* (reg8 *) Signal_B__DM1)
#define Signal_B_DM2                    (* (reg8 *) Signal_B__DM2) 
/* Input Buffer Disable Override */
#define Signal_B_INP_DIS                (* (reg8 *) Signal_B__INP_DIS)
/* LCD Common or Segment Drive */
#define Signal_B_LCD_COM_SEG            (* (reg8 *) Signal_B__LCD_COM_SEG)
/* Enable Segment LCD */
#define Signal_B_LCD_EN                 (* (reg8 *) Signal_B__LCD_EN)
/* Slew Rate Control */
#define Signal_B_SLW                    (* (reg8 *) Signal_B__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Signal_B_PRTDSI__CAPS_SEL       (* (reg8 *) Signal_B__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Signal_B_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Signal_B__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Signal_B_PRTDSI__OE_SEL0        (* (reg8 *) Signal_B__PRTDSI__OE_SEL0) 
#define Signal_B_PRTDSI__OE_SEL1        (* (reg8 *) Signal_B__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Signal_B_PRTDSI__OUT_SEL0       (* (reg8 *) Signal_B__PRTDSI__OUT_SEL0) 
#define Signal_B_PRTDSI__OUT_SEL1       (* (reg8 *) Signal_B__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Signal_B_PRTDSI__SYNC_OUT       (* (reg8 *) Signal_B__PRTDSI__SYNC_OUT) 


#if defined(Signal_B__INTSTAT)  /* Interrupt Registers */

    #define Signal_B_INTSTAT                (* (reg8 *) Signal_B__INTSTAT)
    #define Signal_B_SNAP                   (* (reg8 *) Signal_B__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Signal_B_H */


/* [] END OF FILE */
