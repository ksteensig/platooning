/*******************************************************************************
* File Name: NETWORK_PIN.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_NETWORK_PIN_H)
#define CY_ISR_NETWORK_PIN_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void NETWORK_PIN_Start(void);
void NETWORK_PIN_StartEx(cyisraddress address);
void NETWORK_PIN_Stop(void);

CY_ISR_PROTO(NETWORK_PIN_Interrupt);

void NETWORK_PIN_SetVector(cyisraddress address);
cyisraddress NETWORK_PIN_GetVector(void);

void NETWORK_PIN_SetPriority(uint8 priority);
uint8 NETWORK_PIN_GetPriority(void);

void NETWORK_PIN_Enable(void);
uint8 NETWORK_PIN_GetState(void);
void NETWORK_PIN_Disable(void);

void NETWORK_PIN_SetPending(void);
void NETWORK_PIN_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the NETWORK_PIN ISR. */
#define NETWORK_PIN_INTC_VECTOR            ((reg32 *) NETWORK_PIN__INTC_VECT)

/* Address of the NETWORK_PIN ISR priority. */
#define NETWORK_PIN_INTC_PRIOR             ((reg8 *) NETWORK_PIN__INTC_PRIOR_REG)

/* Priority of the NETWORK_PIN interrupt. */
#define NETWORK_PIN_INTC_PRIOR_NUMBER      NETWORK_PIN__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable NETWORK_PIN interrupt. */
#define NETWORK_PIN_INTC_SET_EN            ((reg32 *) NETWORK_PIN__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the NETWORK_PIN interrupt. */
#define NETWORK_PIN_INTC_CLR_EN            ((reg32 *) NETWORK_PIN__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the NETWORK_PIN interrupt state to pending. */
#define NETWORK_PIN_INTC_SET_PD            ((reg32 *) NETWORK_PIN__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the NETWORK_PIN interrupt. */
#define NETWORK_PIN_INTC_CLR_PD            ((reg32 *) NETWORK_PIN__INTC_CLR_PD_REG)


#endif /* CY_ISR_NETWORK_PIN_H */


/* [] END OF FILE */
