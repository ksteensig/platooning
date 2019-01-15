/*******************************************************************************
* File Name: throttleTimer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_throttleTimer_H)
#define CY_TIMER_throttleTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 throttleTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define throttleTimer_Resolution                 16u
#define throttleTimer_UsingFixedFunction         0u
#define throttleTimer_UsingHWCaptureCounter      0u
#define throttleTimer_SoftwareCaptureMode        0u
#define throttleTimer_SoftwareTriggerMode        0u
#define throttleTimer_UsingHWEnable              0u
#define throttleTimer_EnableTriggerMode          1u
#define throttleTimer_InterruptOnCaptureCount    0u
#define throttleTimer_RunModeUsed                0u
#define throttleTimer_ControlRegRemoved          0u

#if defined(throttleTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define throttleTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (throttleTimer_UsingFixedFunction)
    #define throttleTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define throttleTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End throttleTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!throttleTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (throttleTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!throttleTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}throttleTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    throttleTimer_Start(void) ;
void    throttleTimer_Stop(void) ;

void    throttleTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   throttleTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define throttleTimer_GetInterruptSource() throttleTimer_ReadStatusRegister()

#if(!throttleTimer_UDB_CONTROL_REG_REMOVED)
    uint8   throttleTimer_ReadControlRegister(void) ;
    void    throttleTimer_WriteControlRegister(uint8 control) ;
#endif /* (!throttleTimer_UDB_CONTROL_REG_REMOVED) */

uint16  throttleTimer_ReadPeriod(void) ;
void    throttleTimer_WritePeriod(uint16 period) ;
uint16  throttleTimer_ReadCounter(void) ;
void    throttleTimer_WriteCounter(uint16 counter) ;
uint16  throttleTimer_ReadCapture(void) ;
void    throttleTimer_SoftwareCapture(void) ;

#if(!throttleTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (throttleTimer_SoftwareCaptureMode)
        void    throttleTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!throttleTimer_UsingFixedFunction) */

    #if (throttleTimer_SoftwareTriggerMode)
        void    throttleTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (throttleTimer_SoftwareTriggerMode) */

    #if (throttleTimer_EnableTriggerMode)
        void    throttleTimer_EnableTrigger(void) ;
        void    throttleTimer_DisableTrigger(void) ;
    #endif /* (throttleTimer_EnableTriggerMode) */


    #if(throttleTimer_InterruptOnCaptureCount)
        void    throttleTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (throttleTimer_InterruptOnCaptureCount) */

    #if (throttleTimer_UsingHWCaptureCounter)
        void    throttleTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   throttleTimer_ReadCaptureCount(void) ;
    #endif /* (throttleTimer_UsingHWCaptureCounter) */

    void throttleTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void throttleTimer_Init(void)          ;
void throttleTimer_Enable(void)        ;
void throttleTimer_SaveConfig(void)    ;
void throttleTimer_RestoreConfig(void) ;
void throttleTimer_Sleep(void)         ;
void throttleTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define throttleTimer__B_TIMER__CM_NONE 0
#define throttleTimer__B_TIMER__CM_RISINGEDGE 1
#define throttleTimer__B_TIMER__CM_FALLINGEDGE 2
#define throttleTimer__B_TIMER__CM_EITHEREDGE 3
#define throttleTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define throttleTimer__B_TIMER__TM_NONE 0x00u
#define throttleTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define throttleTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define throttleTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define throttleTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define throttleTimer_INIT_PERIOD             9999u
#define throttleTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)2u << throttleTimer_CTRL_CAP_MODE_SHIFT))
#define throttleTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)1u << throttleTimer_CTRL_TRIG_MODE_SHIFT))
#if (throttleTimer_UsingFixedFunction)
    #define throttleTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << throttleTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << throttleTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define throttleTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << throttleTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << throttleTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << throttleTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (throttleTimer_UsingFixedFunction) */
#define throttleTimer_INIT_CAPTURE_COUNT      (2u)
#define throttleTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << throttleTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (throttleTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define throttleTimer_STATUS         (*(reg8 *) throttleTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define throttleTimer_STATUS_MASK    (*(reg8 *) throttleTimer_TimerHW__SR0 )
    #define throttleTimer_CONTROL        (*(reg8 *) throttleTimer_TimerHW__CFG0)
    #define throttleTimer_CONTROL2       (*(reg8 *) throttleTimer_TimerHW__CFG1)
    #define throttleTimer_CONTROL2_PTR   ( (reg8 *) throttleTimer_TimerHW__CFG1)
    #define throttleTimer_RT1            (*(reg8 *) throttleTimer_TimerHW__RT1)
    #define throttleTimer_RT1_PTR        ( (reg8 *) throttleTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define throttleTimer_CONTROL3       (*(reg8 *) throttleTimer_TimerHW__CFG2)
        #define throttleTimer_CONTROL3_PTR   ( (reg8 *) throttleTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define throttleTimer_GLOBAL_ENABLE  (*(reg8 *) throttleTimer_TimerHW__PM_ACT_CFG)
    #define throttleTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) throttleTimer_TimerHW__PM_STBY_CFG)

    #define throttleTimer_CAPTURE_LSB         (* (reg16 *) throttleTimer_TimerHW__CAP0 )
    #define throttleTimer_CAPTURE_LSB_PTR       ((reg16 *) throttleTimer_TimerHW__CAP0 )
    #define throttleTimer_PERIOD_LSB          (* (reg16 *) throttleTimer_TimerHW__PER0 )
    #define throttleTimer_PERIOD_LSB_PTR        ((reg16 *) throttleTimer_TimerHW__PER0 )
    #define throttleTimer_COUNTER_LSB         (* (reg16 *) throttleTimer_TimerHW__CNT_CMP0 )
    #define throttleTimer_COUNTER_LSB_PTR       ((reg16 *) throttleTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define throttleTimer_BLOCK_EN_MASK                     throttleTimer_TimerHW__PM_ACT_MSK
    #define throttleTimer_BLOCK_STBY_EN_MASK                throttleTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define throttleTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define throttleTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define throttleTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define throttleTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define throttleTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define throttleTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << throttleTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define throttleTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define throttleTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << throttleTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define throttleTimer_CTRL_MODE_SHIFT                 0x01u
        #define throttleTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << throttleTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define throttleTimer_CTRL_RCOD_SHIFT        0x02u
        #define throttleTimer_CTRL_ENBL_SHIFT        0x00u
        #define throttleTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define throttleTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << throttleTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define throttleTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << throttleTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define throttleTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << throttleTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define throttleTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << throttleTimer_CTRL_RCOD_SHIFT))
        #define throttleTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << throttleTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define throttleTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define throttleTimer_RT1_MASK                        ((uint8)((uint8)0x03u << throttleTimer_RT1_SHIFT))
    #define throttleTimer_SYNC                            ((uint8)((uint8)0x03u << throttleTimer_RT1_SHIFT))
    #define throttleTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define throttleTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << throttleTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define throttleTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << throttleTimer_SYNCDSI_SHIFT))

    #define throttleTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << throttleTimer_CTRL_MODE_SHIFT))
    #define throttleTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << throttleTimer_CTRL_MODE_SHIFT))
    #define throttleTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << throttleTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define throttleTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define throttleTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define throttleTimer_STATUS_TC_INT_MASK_SHIFT        (throttleTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define throttleTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (throttleTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define throttleTimer_STATUS_TC                       ((uint8)((uint8)0x01u << throttleTimer_STATUS_TC_SHIFT))
    #define throttleTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << throttleTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define throttleTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << throttleTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define throttleTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << throttleTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define throttleTimer_STATUS              (* (reg8 *) throttleTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define throttleTimer_STATUS_MASK         (* (reg8 *) throttleTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define throttleTimer_STATUS_AUX_CTRL     (* (reg8 *) throttleTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define throttleTimer_CONTROL             (* (reg8 *) throttleTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(throttleTimer_Resolution <= 8u) /* 8-bit Timer */
        #define throttleTimer_CAPTURE_LSB         (* (reg8 *) throttleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define throttleTimer_CAPTURE_LSB_PTR       ((reg8 *) throttleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define throttleTimer_PERIOD_LSB          (* (reg8 *) throttleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define throttleTimer_PERIOD_LSB_PTR        ((reg8 *) throttleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define throttleTimer_COUNTER_LSB         (* (reg8 *) throttleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define throttleTimer_COUNTER_LSB_PTR       ((reg8 *) throttleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(throttleTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define throttleTimer_CAPTURE_LSB         (* (reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define throttleTimer_CAPTURE_LSB_PTR       ((reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define throttleTimer_PERIOD_LSB          (* (reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define throttleTimer_PERIOD_LSB_PTR        ((reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define throttleTimer_COUNTER_LSB         (* (reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define throttleTimer_COUNTER_LSB_PTR       ((reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define throttleTimer_CAPTURE_LSB         (* (reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define throttleTimer_CAPTURE_LSB_PTR       ((reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define throttleTimer_PERIOD_LSB          (* (reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define throttleTimer_PERIOD_LSB_PTR        ((reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define throttleTimer_COUNTER_LSB         (* (reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define throttleTimer_COUNTER_LSB_PTR       ((reg16 *) throttleTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(throttleTimer_Resolution <= 24u)/* 24-bit Timer */
        #define throttleTimer_CAPTURE_LSB         (* (reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define throttleTimer_CAPTURE_LSB_PTR       ((reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define throttleTimer_PERIOD_LSB          (* (reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define throttleTimer_PERIOD_LSB_PTR        ((reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define throttleTimer_COUNTER_LSB         (* (reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define throttleTimer_COUNTER_LSB_PTR       ((reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define throttleTimer_CAPTURE_LSB         (* (reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define throttleTimer_CAPTURE_LSB_PTR       ((reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define throttleTimer_PERIOD_LSB          (* (reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define throttleTimer_PERIOD_LSB_PTR        ((reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define throttleTimer_COUNTER_LSB         (* (reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define throttleTimer_COUNTER_LSB_PTR       ((reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define throttleTimer_CAPTURE_LSB         (* (reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define throttleTimer_CAPTURE_LSB_PTR       ((reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define throttleTimer_PERIOD_LSB          (* (reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define throttleTimer_PERIOD_LSB_PTR        ((reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define throttleTimer_COUNTER_LSB         (* (reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define throttleTimer_COUNTER_LSB_PTR       ((reg32 *) throttleTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define throttleTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) throttleTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (throttleTimer_UsingHWCaptureCounter)
        #define throttleTimer_CAP_COUNT              (*(reg8 *) throttleTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define throttleTimer_CAP_COUNT_PTR          ( (reg8 *) throttleTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define throttleTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) throttleTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define throttleTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) throttleTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (throttleTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define throttleTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define throttleTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define throttleTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define throttleTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define throttleTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define throttleTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << throttleTimer_CTRL_INTCNT_SHIFT))
    #define throttleTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << throttleTimer_CTRL_TRIG_MODE_SHIFT))
    #define throttleTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << throttleTimer_CTRL_TRIG_EN_SHIFT))
    #define throttleTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << throttleTimer_CTRL_CAP_MODE_SHIFT))
    #define throttleTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << throttleTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define throttleTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define throttleTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define throttleTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define throttleTimer_STATUS_TC_INT_MASK_SHIFT       throttleTimer_STATUS_TC_SHIFT
    #define throttleTimer_STATUS_CAPTURE_INT_MASK_SHIFT  throttleTimer_STATUS_CAPTURE_SHIFT
    #define throttleTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define throttleTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define throttleTimer_STATUS_FIFOFULL_INT_MASK_SHIFT throttleTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define throttleTimer_STATUS_TC                      ((uint8)((uint8)0x01u << throttleTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define throttleTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << throttleTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define throttleTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << throttleTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define throttleTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << throttleTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define throttleTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << throttleTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define throttleTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << throttleTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define throttleTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << throttleTimer_STATUS_FIFOFULL_SHIFT))

    #define throttleTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define throttleTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define throttleTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define throttleTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define throttleTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define throttleTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_throttleTimer_H */


/* [] END OF FILE */
