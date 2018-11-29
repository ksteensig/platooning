/*******************************************************************************
* File Name: CE.h  
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

#if !defined(CY_PINS_CE_H) /* Pins CE_H */
#define CY_PINS_CE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CE_aliases.h"


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
} CE_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CE_Read(void);
void    CE_Write(uint8 value);
uint8   CE_ReadDataReg(void);
#if defined(CE__PC) || (CY_PSOC4_4200L) 
    void    CE_SetDriveMode(uint8 mode);
#endif
void    CE_SetInterruptMode(uint16 position, uint16 mode);
uint8   CE_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CE_Sleep(void); 
void CE_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CE__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CE_DRIVE_MODE_BITS        (3)
    #define CE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CE_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CE_SetDriveMode() function.
         *  @{
         */
        #define CE_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CE_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CE_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CE_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CE_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CE_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CE_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CE_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CE_MASK               CE__MASK
#define CE_SHIFT              CE__SHIFT
#define CE_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CE_SetInterruptMode() function.
     *  @{
     */
        #define CE_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CE_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CE_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CE_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CE__SIO)
    #define CE_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CE__PC) && (CY_PSOC4_4200L)
    #define CE_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CE_USBIO_DISABLE              ((uint32)(~CE_USBIO_ENABLE))
    #define CE_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CE_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CE_USBIO_ENTER_SLEEP          ((uint32)((1u << CE_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CE_USBIO_SUSPEND_DEL_SHIFT)))
    #define CE_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CE_USBIO_SUSPEND_SHIFT)))
    #define CE_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CE_USBIO_SUSPEND_DEL_SHIFT)))
    #define CE_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CE__PC)
    /* Port Configuration */
    #define CE_PC                 (* (reg32 *) CE__PC)
#endif
/* Pin State */
#define CE_PS                     (* (reg32 *) CE__PS)
/* Data Register */
#define CE_DR                     (* (reg32 *) CE__DR)
/* Input Buffer Disable Override */
#define CE_INP_DIS                (* (reg32 *) CE__PC2)

/* Interrupt configuration Registers */
#define CE_INTCFG                 (* (reg32 *) CE__INTCFG)
#define CE_INTSTAT                (* (reg32 *) CE__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CE_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CE__SIO)
    #define CE_SIO_REG            (* (reg32 *) CE__SIO)
#endif /* (CE__SIO_CFG) */

/* USBIO registers */
#if !defined(CE__PC) && (CY_PSOC4_4200L)
    #define CE_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CE_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CE_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CE_DRIVE_MODE_SHIFT       (0x00u)
#define CE_DRIVE_MODE_MASK        (0x07u << CE_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CE_H */


/* [] END OF FILE */
