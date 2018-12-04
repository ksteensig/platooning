/*******************************************************************************
* File Name: IRQ.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "IRQ.h"

static IRQ_BACKUP_STRUCT  IRQ_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: IRQ_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet IRQ_SUT.c usage_IRQ_Sleep_Wakeup
*******************************************************************************/
void IRQ_Sleep(void)
{
    #if defined(IRQ__PC)
        IRQ_backup.pcState = IRQ_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            IRQ_backup.usbState = IRQ_CR1_REG;
            IRQ_USB_POWER_REG |= IRQ_USBIO_ENTER_SLEEP;
            IRQ_CR1_REG &= IRQ_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(IRQ__SIO)
        IRQ_backup.sioState = IRQ_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        IRQ_SIO_REG &= (uint32)(~IRQ_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: IRQ_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to IRQ_Sleep() for an example usage.
*******************************************************************************/
void IRQ_Wakeup(void)
{
    #if defined(IRQ__PC)
        IRQ_PC = IRQ_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            IRQ_USB_POWER_REG &= IRQ_USBIO_EXIT_SLEEP_PH1;
            IRQ_CR1_REG = IRQ_backup.usbState;
            IRQ_USB_POWER_REG &= IRQ_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(IRQ__SIO)
        IRQ_SIO_REG = IRQ_backup.sioState;
    #endif
}


/* [] END OF FILE */
