/*******************************************************************************
* File Name: Filter.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the FILT component.
*
* Note:
* 
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(Filter_H) /* FILT Header File */
#define Filter_H

#include "cyfitter.h"
#include "CyLib.h"

extern uint8 Filter_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/
#define Filter_DA_RAM_SIZE_CUR        (0x200u)
#define Filter_DB_RAM_SIZE_CUR        (0x200u)
#define Filter_CSA_RAM_SIZE_CUR       (0x100u)
#define Filter_CSB_RAM_SIZE_CUR       (0x100u)
#define Filter_CFSM_RAM_SIZE_CUR      (0x100u)
#define Filter_ACU_RAM_SIZE_CUR       (0x40u)

#define Filter_FIR_A_SIZE       (128u)
#define Filter_FIR_B_SIZE       (128u)
	
extern const uint8 CYCODE Filter_ChannelAFirCoefficients[Filter_FIR_A_SIZE];
extern const uint8 CYCODE Filter_ChannelBFirCoefficients[Filter_FIR_B_SIZE];


/***************************************
*     Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct 
{
    uint8 enableState;
    uint8 cr;
    uint8 sr;
    uint8 sema;
    uint8 saveAcu[Filter_ACU_RAM_SIZE_CUR];
}   Filter_backupStruct;


/***************************************
* FILT component function prototypes.
****************************************/

void   Filter_Start(void) ;
void   Filter_Stop(void) ;
uint8 Filter_Read8(uint8 channel) ;
uint16 Filter_Read16(uint8 channel) ;
uint32 Filter_Read24(uint8 channel) ;
void Filter_Write8(uint8 channel, uint8 sample) ;
void Filter_Write16(uint8 channel, uint16 sample) ;
void Filter_Write24(uint8 channel, uint32 sample) ;
void Filter_Sleep(void) ;
void Filter_Wakeup(void) ;
void Filter_SaveConfig(void) ;
void Filter_RestoreConfig(void) ;
void Filter_Init(void) ;
void Filter_Enable(void) ;
void Filter_SetCoherency(uint8 channel, uint8 byteSelect) ;
void Filter_SetCoherencyEx(uint8 regSelect, uint8 key) ;
void Filter_SetDalign(uint8 regSelect, uint8 state) ;

/*****************************************
* FILT component API Constants.
******************************************/

/* Channel Definitions */
#define Filter_CHANNEL_A             (0u)
#define Filter_CHANNEL_B             (1u)

#define Filter_CHANNEL_A_INTR        (0x08u)
#define Filter_CHANNEL_B_INTR        (0x10u)

#define Filter_ALL_INTR              (0xf8u)

#define Filter_SIGN_BIT              ((uint32)0x00800000u)
#define Filter_SIGN_BYTE             ((uint32)0xFF000000u)

/* Component's enable/disable state */
#define Filter_ENABLED               (0x01u)
#define Filter_DISABLED              (0x00u)

/* SetCoherency API constants */
#define Filter_KEY_LOW               (0x00u)
#define Filter_KEY_MID               (0x01u)
#define Filter_KEY_HIGH              (0x02u)


/*******************************************************************************
* FILT component macros.
*******************************************************************************/

#define Filter_ClearInterruptSource() \
   (Filter_SR_REG = Filter_ALL_INTR )

#define Filter_IsInterruptChannelA() \
    (Filter_SR_REG & Filter_CHANNEL_A_INTR)

#define Filter_IsInterruptChannelB() \
    (Filter_SR_REG & Filter_CHANNEL_B_INTR)


/*******************************************************************************
* FILT component DFB registers.
*******************************************************************************/

/* DFB Status register */
#define Filter_SR_REG             (* (reg8 *) Filter_DFB__SR)
#define Filter_SR_PTR             (  (reg8 *) Filter_DFB__SR)

/* DFB Control register */
#define Filter_CR_REG             (* (reg8 *) Filter_DFB__CR)
#define Filter_CR_PTR             (  (reg8 *) Filter_DFB__CR)


/*******************************************************************************
* DFB.COHER bit field defines.
*******************************************************************************/

/* STAGEA key coherency mask */
#define Filter_STAGEA_COHER_MASK    (0x03u)
#define Filter_STAGEA_COHER         Filter_STAGEA_COHER_MASK

/* HOLDA key coherency mask */
#define Filter_HOLDA_COHER_MASK     ((uint8)((uint8)0x03u << 4u))
#define Filter_HOLDA_COHER          Filter_HOLDA_COHER_MASK

/* STAGEB key coherency mask */
#define Filter_STAGEB_COHER_MASK    (0x0Cu)
#define Filter_STAGEB_COHER         Filter_STAGEB_COHER_MASK

/* HOLDB key coherency mask */
#define Filter_HOLDB_COHER_MASK     ((uint8)((uint8)0x0Cu << 4u))
#define Filter_HOLDB_COHER          Filter_HOLDB_COHER_MASK


/*******************************************************************************
* DFB.DALIGN bit field defines.
*******************************************************************************/

/* STAGEA dalign mask */
#define Filter_STAGEA_DALIGN    (0x01u)

/* HOLDA dalign mask */
#define Filter_HOLDA_DALIGN     (0x04u)

/* STAGEB dalign mask */
#define Filter_STAGEB_DALIGN    (0x02u)

/* HOLDB dalign mask */
#define Filter_HOLDB_DALIGN     (0x08u)


#endif /* End FILT Header File */


/* [] END OF FILE */
