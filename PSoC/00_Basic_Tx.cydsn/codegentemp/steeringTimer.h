/*******************************************************************************
* File Name: steeringTimer.h
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

#if !defined(CY_TIMER_steeringTimer_H)
#define CY_TIMER_steeringTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 steeringTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define steeringTimer_Resolution                 16u
#define steeringTimer_UsingFixedFunction         0u
#define steeringTimer_UsingHWCaptureCounter      0u
#define steeringTimer_SoftwareCaptureMode        0u
#define steeringTimer_SoftwareTriggerMode        0u
#define steeringTimer_UsingHWEnable              0u
#define steeringTimer_EnableTriggerMode          1u
#define steeringTimer_InterruptOnCaptureCount    0u
#define steeringTimer_RunModeUsed                0u
#define steeringTimer_ControlRegRemoved          0u

#if defined(steeringTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define steeringTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (steeringTimer_UsingFixedFunction)
    #define steeringTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define steeringTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End steeringTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!steeringTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (steeringTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!steeringTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}steeringTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    steeringTimer_Start(void) ;
void    steeringTimer_Stop(void) ;

void    steeringTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   steeringTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define steeringTimer_GetInterruptSource() steeringTimer_ReadStatusRegister()

#if(!steeringTimer_UDB_CONTROL_REG_REMOVED)
    uint8   steeringTimer_ReadControlRegister(void) ;
    void    steeringTimer_WriteControlRegister(uint8 control) ;
#endif /* (!steeringTimer_UDB_CONTROL_REG_REMOVED) */

uint16  steeringTimer_ReadPeriod(void) ;
void    steeringTimer_WritePeriod(uint16 period) ;
uint16  steeringTimer_ReadCounter(void) ;
void    steeringTimer_WriteCounter(uint16 counter) ;
uint16  steeringTimer_ReadCapture(void) ;
void    steeringTimer_SoftwareCapture(void) ;

#if(!steeringTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (steeringTimer_SoftwareCaptureMode)
        void    steeringTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!steeringTimer_UsingFixedFunction) */

    #if (steeringTimer_SoftwareTriggerMode)
        void    steeringTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (steeringTimer_SoftwareTriggerMode) */

    #if (steeringTimer_EnableTriggerMode)
        void    steeringTimer_EnableTrigger(void) ;
        void    steeringTimer_DisableTrigger(void) ;
    #endif /* (steeringTimer_EnableTriggerMode) */


    #if(steeringTimer_InterruptOnCaptureCount)
        void    steeringTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (steeringTimer_InterruptOnCaptureCount) */

    #if (steeringTimer_UsingHWCaptureCounter)
        void    steeringTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   steeringTimer_ReadCaptureCount(void) ;
    #endif /* (steeringTimer_UsingHWCaptureCounter) */

    void steeringTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void steeringTimer_Init(void)          ;
void steeringTimer_Enable(void)        ;
void steeringTimer_SaveConfig(void)    ;
void steeringTimer_RestoreConfig(void) ;
void steeringTimer_Sleep(void)         ;
void steeringTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define steeringTimer__B_TIMER__CM_NONE 0
#define steeringTimer__B_TIMER__CM_RISINGEDGE 1
#define steeringTimer__B_TIMER__CM_FALLINGEDGE 2
#define steeringTimer__B_TIMER__CM_EITHEREDGE 3
#define steeringTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define steeringTimer__B_TIMER__TM_NONE 0x00u
#define steeringTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define steeringTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define steeringTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define steeringTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define steeringTimer_INIT_PERIOD             9999u
#define steeringTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)2u << steeringTimer_CTRL_CAP_MODE_SHIFT))
#define steeringTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)1u << steeringTimer_CTRL_TRIG_MODE_SHIFT))
#if (steeringTimer_UsingFixedFunction)
    #define steeringTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << steeringTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << steeringTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define steeringTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << steeringTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << steeringTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << steeringTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (steeringTimer_UsingFixedFunction) */
#define steeringTimer_INIT_CAPTURE_COUNT      (2u)
#define steeringTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << steeringTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (steeringTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define steeringTimer_STATUS         (*(reg8 *) steeringTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define steeringTimer_STATUS_MASK    (*(reg8 *) steeringTimer_TimerHW__SR0 )
    #define steeringTimer_CONTROL        (*(reg8 *) steeringTimer_TimerHW__CFG0)
    #define steeringTimer_CONTROL2       (*(reg8 *) steeringTimer_TimerHW__CFG1)
    #define steeringTimer_CONTROL2_PTR   ( (reg8 *) steeringTimer_TimerHW__CFG1)
    #define steeringTimer_RT1            (*(reg8 *) steeringTimer_TimerHW__RT1)
    #define steeringTimer_RT1_PTR        ( (reg8 *) steeringTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define steeringTimer_CONTROL3       (*(reg8 *) steeringTimer_TimerHW__CFG2)
        #define steeringTimer_CONTROL3_PTR   ( (reg8 *) steeringTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define steeringTimer_GLOBAL_ENABLE  (*(reg8 *) steeringTimer_TimerHW__PM_ACT_CFG)
    #define steeringTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) steeringTimer_TimerHW__PM_STBY_CFG)

    #define steeringTimer_CAPTURE_LSB         (* (reg16 *) steeringTimer_TimerHW__CAP0 )
    #define steeringTimer_CAPTURE_LSB_PTR       ((reg16 *) steeringTimer_TimerHW__CAP0 )
    #define steeringTimer_PERIOD_LSB          (* (reg16 *) steeringTimer_TimerHW__PER0 )
    #define steeringTimer_PERIOD_LSB_PTR        ((reg16 *) steeringTimer_TimerHW__PER0 )
    #define steeringTimer_COUNTER_LSB         (* (reg16 *) steeringTimer_TimerHW__CNT_CMP0 )
    #define steeringTimer_COUNTER_LSB_PTR       ((reg16 *) steeringTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define steeringTimer_BLOCK_EN_MASK                     steeringTimer_TimerHW__PM_ACT_MSK
    #define steeringTimer_BLOCK_STBY_EN_MASK                steeringTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define steeringTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define steeringTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define steeringTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define steeringTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define steeringTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define steeringTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << steeringTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define steeringTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define steeringTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << steeringTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define steeringTimer_CTRL_MODE_SHIFT                 0x01u
        #define steeringTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << steeringTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define steeringTimer_CTRL_RCOD_SHIFT        0x02u
        #define steeringTimer_CTRL_ENBL_SHIFT        0x00u
        #define steeringTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define steeringTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << steeringTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define steeringTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << steeringTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define steeringTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << steeringTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define steeringTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << steeringTimer_CTRL_RCOD_SHIFT))
        #define steeringTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << steeringTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define steeringTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define steeringTimer_RT1_MASK                        ((uint8)((uint8)0x03u << steeringTimer_RT1_SHIFT))
    #define steeringTimer_SYNC                            ((uint8)((uint8)0x03u << steeringTimer_RT1_SHIFT))
    #define steeringTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define steeringTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << steeringTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define steeringTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << steeringTimer_SYNCDSI_SHIFT))

    #define steeringTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << steeringTimer_CTRL_MODE_SHIFT))
    #define steeringTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << steeringTimer_CTRL_MODE_SHIFT))
    #define steeringTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << steeringTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define steeringTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define steeringTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define steeringTimer_STATUS_TC_INT_MASK_SHIFT        (steeringTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define steeringTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (steeringTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define steeringTimer_STATUS_TC                       ((uint8)((uint8)0x01u << steeringTimer_STATUS_TC_SHIFT))
    #define steeringTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << steeringTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define steeringTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << steeringTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define steeringTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << steeringTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define steeringTimer_STATUS              (* (reg8 *) steeringTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define steeringTimer_STATUS_MASK         (* (reg8 *) steeringTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define steeringTimer_STATUS_AUX_CTRL     (* (reg8 *) steeringTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define steeringTimer_CONTROL             (* (reg8 *) steeringTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(steeringTimer_Resolution <= 8u) /* 8-bit Timer */
        #define steeringTimer_CAPTURE_LSB         (* (reg8 *) steeringTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define steeringTimer_CAPTURE_LSB_PTR       ((reg8 *) steeringTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define steeringTimer_PERIOD_LSB          (* (reg8 *) steeringTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define steeringTimer_PERIOD_LSB_PTR        ((reg8 *) steeringTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define steeringTimer_COUNTER_LSB         (* (reg8 *) steeringTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define steeringTimer_COUNTER_LSB_PTR       ((reg8 *) steeringTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(steeringTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define steeringTimer_CAPTURE_LSB         (* (reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define steeringTimer_CAPTURE_LSB_PTR       ((reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define steeringTimer_PERIOD_LSB          (* (reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define steeringTimer_PERIOD_LSB_PTR        ((reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define steeringTimer_COUNTER_LSB         (* (reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define steeringTimer_COUNTER_LSB_PTR       ((reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define steeringTimer_CAPTURE_LSB         (* (reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define steeringTimer_CAPTURE_LSB_PTR       ((reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define steeringTimer_PERIOD_LSB          (* (reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define steeringTimer_PERIOD_LSB_PTR        ((reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define steeringTimer_COUNTER_LSB         (* (reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define steeringTimer_COUNTER_LSB_PTR       ((reg16 *) steeringTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(steeringTimer_Resolution <= 24u)/* 24-bit Timer */
        #define steeringTimer_CAPTURE_LSB         (* (reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define steeringTimer_CAPTURE_LSB_PTR       ((reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define steeringTimer_PERIOD_LSB          (* (reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define steeringTimer_PERIOD_LSB_PTR        ((reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define steeringTimer_COUNTER_LSB         (* (reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define steeringTimer_COUNTER_LSB_PTR       ((reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define steeringTimer_CAPTURE_LSB         (* (reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define steeringTimer_CAPTURE_LSB_PTR       ((reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define steeringTimer_PERIOD_LSB          (* (reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define steeringTimer_PERIOD_LSB_PTR        ((reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define steeringTimer_COUNTER_LSB         (* (reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define steeringTimer_COUNTER_LSB_PTR       ((reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define steeringTimer_CAPTURE_LSB         (* (reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define steeringTimer_CAPTURE_LSB_PTR       ((reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define steeringTimer_PERIOD_LSB          (* (reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define steeringTimer_PERIOD_LSB_PTR        ((reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define steeringTimer_COUNTER_LSB         (* (reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define steeringTimer_COUNTER_LSB_PTR       ((reg32 *) steeringTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define steeringTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) steeringTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (steeringTimer_UsingHWCaptureCounter)
        #define steeringTimer_CAP_COUNT              (*(reg8 *) steeringTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define steeringTimer_CAP_COUNT_PTR          ( (reg8 *) steeringTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define steeringTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) steeringTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define steeringTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) steeringTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (steeringTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define steeringTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define steeringTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define steeringTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define steeringTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define steeringTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define steeringTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << steeringTimer_CTRL_INTCNT_SHIFT))
    #define steeringTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << steeringTimer_CTRL_TRIG_MODE_SHIFT))
    #define steeringTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << steeringTimer_CTRL_TRIG_EN_SHIFT))
    #define steeringTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << steeringTimer_CTRL_CAP_MODE_SHIFT))
    #define steeringTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << steeringTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define steeringTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define steeringTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define steeringTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define steeringTimer_STATUS_TC_INT_MASK_SHIFT       steeringTimer_STATUS_TC_SHIFT
    #define steeringTimer_STATUS_CAPTURE_INT_MASK_SHIFT  steeringTimer_STATUS_CAPTURE_SHIFT
    #define steeringTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define steeringTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define steeringTimer_STATUS_FIFOFULL_INT_MASK_SHIFT steeringTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define steeringTimer_STATUS_TC                      ((uint8)((uint8)0x01u << steeringTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define steeringTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << steeringTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define steeringTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << steeringTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define steeringTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << steeringTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define steeringTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << steeringTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define steeringTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << steeringTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define steeringTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << steeringTimer_STATUS_FIFOFULL_SHIFT))

    #define steeringTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define steeringTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define steeringTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define steeringTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define steeringTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define steeringTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_steeringTimer_H */


/* [] END OF FILE */
