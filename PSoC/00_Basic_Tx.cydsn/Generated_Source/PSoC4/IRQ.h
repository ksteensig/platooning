/*******************************************************************************
* File Name: IRQ.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_IRQ_H) /* Pins IRQ_H */
#define CY_PINS_IRQ_H

#include "cytypes.h"
#include "cyfitter.h"
#include "IRQ_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} IRQ_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   IRQ_Read(void);
void    IRQ_Write(uint8 value);
uint8   IRQ_ReadDataReg(void);
#if defined(IRQ__PC) || (CY_PSOC4_4200L) 
    void    IRQ_SetDriveMode(uint8 mode);
#endif
void    IRQ_SetInterruptMode(uint16 position, uint16 mode);
uint8   IRQ_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void IRQ_Sleep(void); 
void IRQ_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(IRQ__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define IRQ_DRIVE_MODE_BITS        (3)
    #define IRQ_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - IRQ_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the IRQ_SetDriveMode() function.
         *  @{
         */
        #define IRQ_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define IRQ_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define IRQ_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define IRQ_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define IRQ_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define IRQ_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define IRQ_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define IRQ_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define IRQ_MASK               IRQ__MASK
#define IRQ_SHIFT              IRQ__SHIFT
#define IRQ_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IRQ_SetInterruptMode() function.
     *  @{
     */
        #define IRQ_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define IRQ_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define IRQ_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define IRQ_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(IRQ__SIO)
    #define IRQ_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(IRQ__PC) && (CY_PSOC4_4200L)
    #define IRQ_USBIO_ENABLE               ((uint32)0x80000000u)
    #define IRQ_USBIO_DISABLE              ((uint32)(~IRQ_USBIO_ENABLE))
    #define IRQ_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define IRQ_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define IRQ_USBIO_ENTER_SLEEP          ((uint32)((1u << IRQ_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << IRQ_USBIO_SUSPEND_DEL_SHIFT)))
    #define IRQ_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << IRQ_USBIO_SUSPEND_SHIFT)))
    #define IRQ_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << IRQ_USBIO_SUSPEND_DEL_SHIFT)))
    #define IRQ_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(IRQ__PC)
    /* Port Configuration */
    #define IRQ_PC                 (* (reg32 *) IRQ__PC)
#endif
/* Pin State */
#define IRQ_PS                     (* (reg32 *) IRQ__PS)
/* Data Register */
#define IRQ_DR                     (* (reg32 *) IRQ__DR)
/* Input Buffer Disable Override */
#define IRQ_INP_DIS                (* (reg32 *) IRQ__PC2)

/* Interrupt configuration Registers */
#define IRQ_INTCFG                 (* (reg32 *) IRQ__INTCFG)
#define IRQ_INTSTAT                (* (reg32 *) IRQ__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define IRQ_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(IRQ__SIO)
    #define IRQ_SIO_REG            (* (reg32 *) IRQ__SIO)
#endif /* (IRQ__SIO_CFG) */

/* USBIO registers */
#if !defined(IRQ__PC) && (CY_PSOC4_4200L)
    #define IRQ_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define IRQ_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define IRQ_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define IRQ_DRIVE_MODE_SHIFT       (0x00u)
#define IRQ_DRIVE_MODE_MASK        (0x07u << IRQ_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins IRQ_H */


/* [] END OF FILE */
