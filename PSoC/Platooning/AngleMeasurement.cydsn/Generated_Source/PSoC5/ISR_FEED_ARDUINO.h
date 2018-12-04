/*******************************************************************************
* File Name: ISR_FEED_ARDUINO.h
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
#if !defined(CY_ISR_ISR_FEED_ARDUINO_H)
#define CY_ISR_ISR_FEED_ARDUINO_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISR_FEED_ARDUINO_Start(void);
void ISR_FEED_ARDUINO_StartEx(cyisraddress address);
void ISR_FEED_ARDUINO_Stop(void);

CY_ISR_PROTO(ISR_FEED_ARDUINO_Interrupt);

void ISR_FEED_ARDUINO_SetVector(cyisraddress address);
cyisraddress ISR_FEED_ARDUINO_GetVector(void);

void ISR_FEED_ARDUINO_SetPriority(uint8 priority);
uint8 ISR_FEED_ARDUINO_GetPriority(void);

void ISR_FEED_ARDUINO_Enable(void);
uint8 ISR_FEED_ARDUINO_GetState(void);
void ISR_FEED_ARDUINO_Disable(void);

void ISR_FEED_ARDUINO_SetPending(void);
void ISR_FEED_ARDUINO_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISR_FEED_ARDUINO ISR. */
#define ISR_FEED_ARDUINO_INTC_VECTOR            ((reg32 *) ISR_FEED_ARDUINO__INTC_VECT)

/* Address of the ISR_FEED_ARDUINO ISR priority. */
#define ISR_FEED_ARDUINO_INTC_PRIOR             ((reg8 *) ISR_FEED_ARDUINO__INTC_PRIOR_REG)

/* Priority of the ISR_FEED_ARDUINO interrupt. */
#define ISR_FEED_ARDUINO_INTC_PRIOR_NUMBER      ISR_FEED_ARDUINO__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISR_FEED_ARDUINO interrupt. */
#define ISR_FEED_ARDUINO_INTC_SET_EN            ((reg32 *) ISR_FEED_ARDUINO__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISR_FEED_ARDUINO interrupt. */
#define ISR_FEED_ARDUINO_INTC_CLR_EN            ((reg32 *) ISR_FEED_ARDUINO__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISR_FEED_ARDUINO interrupt state to pending. */
#define ISR_FEED_ARDUINO_INTC_SET_PD            ((reg32 *) ISR_FEED_ARDUINO__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISR_FEED_ARDUINO interrupt. */
#define ISR_FEED_ARDUINO_INTC_CLR_PD            ((reg32 *) ISR_FEED_ARDUINO__INTC_CLR_PD_REG)


#endif /* CY_ISR_ISR_FEED_ARDUINO_H */


/* [] END OF FILE */
