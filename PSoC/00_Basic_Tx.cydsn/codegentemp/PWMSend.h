/*******************************************************************************
* File Name: PWMSend.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_PWMSend_H)
#define CY_PWM_PWMSend_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PWMSend_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PWMSend_Resolution                     (16u)
#define PWMSend_UsingFixedFunction             (0u)
#define PWMSend_DeadBandMode                   (0u)
#define PWMSend_KillModeMinTime                (0u)
#define PWMSend_KillMode                       (0u)
#define PWMSend_PWMMode                        (0u)
#define PWMSend_PWMModeIsCenterAligned         (0u)
#define PWMSend_DeadBandUsed                   (0u)
#define PWMSend_DeadBand2_4                    (0u)

#if !defined(PWMSend_PWMUDB_genblk8_stsreg__REMOVED)
    #define PWMSend_UseStatus                  (1u)
#else
    #define PWMSend_UseStatus                  (0u)
#endif /* !defined(PWMSend_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(PWMSend_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define PWMSend_UseControl                 (1u)
#else
    #define PWMSend_UseControl                 (0u)
#endif /* !defined(PWMSend_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define PWMSend_UseOneCompareMode              (1u)
#define PWMSend_MinimumKillTime                (1u)
#define PWMSend_EnableMode                     (0u)

#define PWMSend_CompareMode1SW                 (0u)
#define PWMSend_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define PWMSend__B_PWM__DISABLED 0
#define PWMSend__B_PWM__ASYNCHRONOUS 1
#define PWMSend__B_PWM__SINGLECYCLE 2
#define PWMSend__B_PWM__LATCHED 3
#define PWMSend__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PWMSend__B_PWM__DBMDISABLED 0
#define PWMSend__B_PWM__DBM_2_4_CLOCKS 1
#define PWMSend__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PWMSend__B_PWM__ONE_OUTPUT 0
#define PWMSend__B_PWM__TWO_OUTPUTS 1
#define PWMSend__B_PWM__DUAL_EDGE 2
#define PWMSend__B_PWM__CENTER_ALIGN 3
#define PWMSend__B_PWM__DITHER 5
#define PWMSend__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PWMSend__B_PWM__LESS_THAN 1
#define PWMSend__B_PWM__LESS_THAN_OR_EQUAL 2
#define PWMSend__B_PWM__GREATER_THAN 3
#define PWMSend__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PWMSend__B_PWM__EQUAL 0
#define PWMSend__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!PWMSend_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!PWMSend_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!PWMSend_PWMModeIsCenterAligned) */
        #if (PWMSend_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (PWMSend_UseStatus) */

        /* Backup for Deadband parameters */
        #if(PWMSend_DeadBandMode == PWMSend__B_PWM__DBM_256_CLOCKS || \
            PWMSend_DeadBandMode == PWMSend__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(PWMSend_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (PWMSend_KillModeMinTime) */

        /* Backup control register */
        #if(PWMSend_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (PWMSend_UseControl) */

    #endif /* (!PWMSend_UsingFixedFunction) */

}PWMSend_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    PWMSend_Start(void) ;
void    PWMSend_Stop(void) ;

#if (PWMSend_UseStatus || PWMSend_UsingFixedFunction)
    void  PWMSend_SetInterruptMode(uint8 interruptMode) ;
    uint8 PWMSend_ReadStatusRegister(void) ;
#endif /* (PWMSend_UseStatus || PWMSend_UsingFixedFunction) */

#define PWMSend_GetInterruptSource() PWMSend_ReadStatusRegister()

#if (PWMSend_UseControl)
    uint8 PWMSend_ReadControlRegister(void) ;
    void  PWMSend_WriteControlRegister(uint8 control)
          ;
#endif /* (PWMSend_UseControl) */

#if (PWMSend_UseOneCompareMode)
   #if (PWMSend_CompareMode1SW)
       void    PWMSend_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (PWMSend_CompareMode1SW) */
#else
    #if (PWMSend_CompareMode1SW)
        void    PWMSend_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (PWMSend_CompareMode1SW) */
    #if (PWMSend_CompareMode2SW)
        void    PWMSend_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (PWMSend_CompareMode2SW) */
#endif /* (PWMSend_UseOneCompareMode) */

#if (!PWMSend_UsingFixedFunction)
    uint16   PWMSend_ReadCounter(void) ;
    uint16 PWMSend_ReadCapture(void) ;

    #if (PWMSend_UseStatus)
            void PWMSend_ClearFIFO(void) ;
    #endif /* (PWMSend_UseStatus) */

    void    PWMSend_WriteCounter(uint16 counter)
            ;
#endif /* (!PWMSend_UsingFixedFunction) */

void    PWMSend_WritePeriod(uint16 period)
        ;
uint16 PWMSend_ReadPeriod(void) ;

#if (PWMSend_UseOneCompareMode)
    void    PWMSend_WriteCompare(uint16 compare)
            ;
    uint16 PWMSend_ReadCompare(void) ;
#else
    void    PWMSend_WriteCompare1(uint16 compare)
            ;
    uint16 PWMSend_ReadCompare1(void) ;
    void    PWMSend_WriteCompare2(uint16 compare)
            ;
    uint16 PWMSend_ReadCompare2(void) ;
#endif /* (PWMSend_UseOneCompareMode) */


#if (PWMSend_DeadBandUsed)
    void    PWMSend_WriteDeadTime(uint8 deadtime) ;
    uint8   PWMSend_ReadDeadTime(void) ;
#endif /* (PWMSend_DeadBandUsed) */

#if ( PWMSend_KillModeMinTime)
    void PWMSend_WriteKillTime(uint8 killtime) ;
    uint8 PWMSend_ReadKillTime(void) ;
#endif /* ( PWMSend_KillModeMinTime) */

void PWMSend_Init(void) ;
void PWMSend_Enable(void) ;
void PWMSend_Sleep(void) ;
void PWMSend_Wakeup(void) ;
void PWMSend_SaveConfig(void) ;
void PWMSend_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PWMSend_INIT_PERIOD_VALUE          (9999u)
#define PWMSend_INIT_COMPARE_VALUE1        (1u)
#define PWMSend_INIT_COMPARE_VALUE2        (0u)
#define PWMSend_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    PWMSend_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMSend_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMSend_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMSend_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define PWMSend_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  PWMSend_CTRL_CMPMODE2_SHIFT)
#define PWMSend_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  PWMSend_CTRL_CMPMODE1_SHIFT)
#define PWMSend_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (PWMSend_UsingFixedFunction)
   #define PWMSend_PERIOD_LSB              (*(reg16 *) PWMSend_PWMHW__PER0)
   #define PWMSend_PERIOD_LSB_PTR          ( (reg16 *) PWMSend_PWMHW__PER0)
   #define PWMSend_COMPARE1_LSB            (*(reg16 *) PWMSend_PWMHW__CNT_CMP0)
   #define PWMSend_COMPARE1_LSB_PTR        ( (reg16 *) PWMSend_PWMHW__CNT_CMP0)
   #define PWMSend_COMPARE2_LSB            (0x00u)
   #define PWMSend_COMPARE2_LSB_PTR        (0x00u)
   #define PWMSend_COUNTER_LSB             (*(reg16 *) PWMSend_PWMHW__CNT_CMP0)
   #define PWMSend_COUNTER_LSB_PTR         ( (reg16 *) PWMSend_PWMHW__CNT_CMP0)
   #define PWMSend_CAPTURE_LSB             (*(reg16 *) PWMSend_PWMHW__CAP0)
   #define PWMSend_CAPTURE_LSB_PTR         ( (reg16 *) PWMSend_PWMHW__CAP0)
   #define PWMSend_RT1                     (*(reg8 *)  PWMSend_PWMHW__RT1)
   #define PWMSend_RT1_PTR                 ( (reg8 *)  PWMSend_PWMHW__RT1)

#else
   #if (PWMSend_Resolution == 8u) /* 8bit - PWM */

       #if(PWMSend_PWMModeIsCenterAligned)
           #define PWMSend_PERIOD_LSB      (*(reg8 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define PWMSend_PERIOD_LSB_PTR  ((reg8 *)   PWMSend_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define PWMSend_PERIOD_LSB      (*(reg8 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define PWMSend_PERIOD_LSB_PTR  ((reg8 *)   PWMSend_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (PWMSend_PWMModeIsCenterAligned) */

       #define PWMSend_COMPARE1_LSB        (*(reg8 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define PWMSend_COMPARE1_LSB_PTR    ((reg8 *)   PWMSend_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define PWMSend_COMPARE2_LSB        (*(reg8 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define PWMSend_COMPARE2_LSB_PTR    ((reg8 *)   PWMSend_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define PWMSend_COUNTERCAP_LSB      (*(reg8 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define PWMSend_COUNTERCAP_LSB_PTR  ((reg8 *)   PWMSend_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define PWMSend_COUNTER_LSB         (*(reg8 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define PWMSend_COUNTER_LSB_PTR     ((reg8 *)   PWMSend_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define PWMSend_CAPTURE_LSB         (*(reg8 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define PWMSend_CAPTURE_LSB_PTR     ((reg8 *)   PWMSend_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(PWMSend_PWMModeIsCenterAligned)
               #define PWMSend_PERIOD_LSB      (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define PWMSend_PERIOD_LSB_PTR  ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define PWMSend_PERIOD_LSB      (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define PWMSend_PERIOD_LSB_PTR  ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (PWMSend_PWMModeIsCenterAligned) */

            #define PWMSend_COMPARE1_LSB       (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define PWMSend_COMPARE1_LSB_PTR   ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define PWMSend_COMPARE2_LSB       (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define PWMSend_COMPARE2_LSB_PTR   ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define PWMSend_COUNTERCAP_LSB     (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define PWMSend_COUNTERCAP_LSB_PTR ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define PWMSend_COUNTER_LSB        (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define PWMSend_COUNTER_LSB_PTR    ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define PWMSend_CAPTURE_LSB        (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define PWMSend_CAPTURE_LSB_PTR    ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(PWMSend_PWMModeIsCenterAligned)
               #define PWMSend_PERIOD_LSB      (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define PWMSend_PERIOD_LSB_PTR  ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define PWMSend_PERIOD_LSB      (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define PWMSend_PERIOD_LSB_PTR  ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (PWMSend_PWMModeIsCenterAligned) */

            #define PWMSend_COMPARE1_LSB       (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define PWMSend_COMPARE1_LSB_PTR   ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define PWMSend_COMPARE2_LSB       (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define PWMSend_COMPARE2_LSB_PTR   ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define PWMSend_COUNTERCAP_LSB     (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define PWMSend_COUNTERCAP_LSB_PTR ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define PWMSend_COUNTER_LSB        (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define PWMSend_COUNTER_LSB_PTR    ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define PWMSend_CAPTURE_LSB        (*(reg16 *) PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define PWMSend_CAPTURE_LSB_PTR    ((reg16 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define PWMSend_AUX_CONTROLDP1          (*(reg8 *)  PWMSend_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define PWMSend_AUX_CONTROLDP1_PTR      ((reg8 *)   PWMSend_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (PWMSend_Resolution == 8) */

   #define PWMSend_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define PWMSend_AUX_CONTROLDP0          (*(reg8 *)  PWMSend_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define PWMSend_AUX_CONTROLDP0_PTR      ((reg8 *)   PWMSend_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (PWMSend_UsingFixedFunction) */

#if(PWMSend_KillModeMinTime )
    #define PWMSend_KILLMODEMINTIME        (*(reg8 *)  PWMSend_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PWMSend_KILLMODEMINTIME_PTR    ((reg8 *)   PWMSend_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (PWMSend_KillModeMinTime ) */

#if(PWMSend_DeadBandMode == PWMSend__B_PWM__DBM_256_CLOCKS)
    #define PWMSend_DEADBAND_COUNT         (*(reg8 *)  PWMSend_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWMSend_DEADBAND_COUNT_PTR     ((reg8 *)   PWMSend_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWMSend_DEADBAND_LSB_PTR       ((reg8 *)   PWMSend_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PWMSend_DEADBAND_LSB           (*(reg8 *)  PWMSend_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PWMSend_DeadBandMode == PWMSend__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PWMSend_UsingFixedFunction)
        #define PWMSend_DEADBAND_COUNT         (*(reg8 *)  PWMSend_PWMHW__CFG0)
        #define PWMSend_DEADBAND_COUNT_PTR     ((reg8 *)   PWMSend_PWMHW__CFG0)
        #define PWMSend_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWMSend_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define PWMSend_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PWMSend_DEADBAND_COUNT         (*(reg8 *)  PWMSend_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWMSend_DEADBAND_COUNT_PTR     ((reg8 *)   PWMSend_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWMSend_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWMSend_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define PWMSend_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (PWMSend_UsingFixedFunction) */
#endif /* (PWMSend_DeadBandMode == PWMSend__B_PWM__DBM_256_CLOCKS) */



#if (PWMSend_UsingFixedFunction)
    #define PWMSend_STATUS                 (*(reg8 *) PWMSend_PWMHW__SR0)
    #define PWMSend_STATUS_PTR             ((reg8 *) PWMSend_PWMHW__SR0)
    #define PWMSend_STATUS_MASK            (*(reg8 *) PWMSend_PWMHW__SR0)
    #define PWMSend_STATUS_MASK_PTR        ((reg8 *) PWMSend_PWMHW__SR0)
    #define PWMSend_CONTROL                (*(reg8 *) PWMSend_PWMHW__CFG0)
    #define PWMSend_CONTROL_PTR            ((reg8 *) PWMSend_PWMHW__CFG0)
    #define PWMSend_CONTROL2               (*(reg8 *) PWMSend_PWMHW__CFG1)
    #define PWMSend_CONTROL3               (*(reg8 *) PWMSend_PWMHW__CFG2)
    #define PWMSend_GLOBAL_ENABLE          (*(reg8 *) PWMSend_PWMHW__PM_ACT_CFG)
    #define PWMSend_GLOBAL_ENABLE_PTR      ( (reg8 *) PWMSend_PWMHW__PM_ACT_CFG)
    #define PWMSend_GLOBAL_STBY_ENABLE     (*(reg8 *) PWMSend_PWMHW__PM_STBY_CFG)
    #define PWMSend_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) PWMSend_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define PWMSend_BLOCK_EN_MASK          (PWMSend_PWMHW__PM_ACT_MSK)
    #define PWMSend_BLOCK_STBY_EN_MASK     (PWMSend_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define PWMSend_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define PWMSend_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define PWMSend_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define PWMSend_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define PWMSend_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define PWMSend_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define PWMSend_CTRL_ENABLE            (uint8)((uint8)0x01u << PWMSend_CTRL_ENABLE_SHIFT)
    #define PWMSend_CTRL_RESET             (uint8)((uint8)0x01u << PWMSend_CTRL_RESET_SHIFT)
    #define PWMSend_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWMSend_CTRL_CMPMODE2_SHIFT)
    #define PWMSend_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWMSend_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PWMSend_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define PWMSend_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << PWMSend_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define PWMSend_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define PWMSend_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define PWMSend_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define PWMSend_STATUS_TC_INT_EN_MASK_SHIFT            (PWMSend_STATUS_TC_SHIFT - 4u)
    #define PWMSend_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define PWMSend_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWMSend_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define PWMSend_STATUS_TC              (uint8)((uint8)0x01u << PWMSend_STATUS_TC_SHIFT)
    #define PWMSend_STATUS_CMP1            (uint8)((uint8)0x01u << PWMSend_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define PWMSend_STATUS_TC_INT_EN_MASK              (uint8)((uint8)PWMSend_STATUS_TC >> 4u)
    #define PWMSend_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)PWMSend_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define PWMSend_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define PWMSend_RT1_MASK              (uint8)((uint8)0x03u << PWMSend_RT1_SHIFT)
    #define PWMSend_SYNC                  (uint8)((uint8)0x03u << PWMSend_RT1_SHIFT)
    #define PWMSend_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define PWMSend_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << PWMSend_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define PWMSend_SYNCDSI_EN            (uint8)((uint8)0x0Fu << PWMSend_SYNCDSI_SHIFT)


#else
    #define PWMSend_STATUS                (*(reg8 *)   PWMSend_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWMSend_STATUS_PTR            ((reg8 *)    PWMSend_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWMSend_STATUS_MASK           (*(reg8 *)   PWMSend_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWMSend_STATUS_MASK_PTR       ((reg8 *)    PWMSend_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWMSend_STATUS_AUX_CTRL       (*(reg8 *)   PWMSend_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define PWMSend_CONTROL               (*(reg8 *)   PWMSend_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define PWMSend_CONTROL_PTR           ((reg8 *)    PWMSend_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define PWMSend_CTRL_ENABLE_SHIFT      (0x07u)
    #define PWMSend_CTRL_RESET_SHIFT       (0x06u)
    #define PWMSend_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define PWMSend_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define PWMSend_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define PWMSend_CTRL_ENABLE            (uint8)((uint8)0x01u << PWMSend_CTRL_ENABLE_SHIFT)
    #define PWMSend_CTRL_RESET             (uint8)((uint8)0x01u << PWMSend_CTRL_RESET_SHIFT)
    #define PWMSend_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWMSend_CTRL_CMPMODE2_SHIFT)
    #define PWMSend_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWMSend_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define PWMSend_STATUS_KILL_SHIFT          (0x05u)
    #define PWMSend_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define PWMSend_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define PWMSend_STATUS_TC_SHIFT            (0x02u)
    #define PWMSend_STATUS_CMP2_SHIFT          (0x01u)
    #define PWMSend_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PWMSend_STATUS_KILL_INT_EN_MASK_SHIFT          (PWMSend_STATUS_KILL_SHIFT)
    #define PWMSend_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (PWMSend_STATUS_FIFONEMPTY_SHIFT)
    #define PWMSend_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (PWMSend_STATUS_FIFOFULL_SHIFT)
    #define PWMSend_STATUS_TC_INT_EN_MASK_SHIFT            (PWMSend_STATUS_TC_SHIFT)
    #define PWMSend_STATUS_CMP2_INT_EN_MASK_SHIFT          (PWMSend_STATUS_CMP2_SHIFT)
    #define PWMSend_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWMSend_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define PWMSend_STATUS_KILL            (uint8)((uint8)0x00u << PWMSend_STATUS_KILL_SHIFT )
    #define PWMSend_STATUS_FIFOFULL        (uint8)((uint8)0x01u << PWMSend_STATUS_FIFOFULL_SHIFT)
    #define PWMSend_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << PWMSend_STATUS_FIFONEMPTY_SHIFT)
    #define PWMSend_STATUS_TC              (uint8)((uint8)0x01u << PWMSend_STATUS_TC_SHIFT)
    #define PWMSend_STATUS_CMP2            (uint8)((uint8)0x01u << PWMSend_STATUS_CMP2_SHIFT)
    #define PWMSend_STATUS_CMP1            (uint8)((uint8)0x01u << PWMSend_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PWMSend_STATUS_KILL_INT_EN_MASK            (PWMSend_STATUS_KILL)
    #define PWMSend_STATUS_FIFOFULL_INT_EN_MASK        (PWMSend_STATUS_FIFOFULL)
    #define PWMSend_STATUS_FIFONEMPTY_INT_EN_MASK      (PWMSend_STATUS_FIFONEMPTY)
    #define PWMSend_STATUS_TC_INT_EN_MASK              (PWMSend_STATUS_TC)
    #define PWMSend_STATUS_CMP2_INT_EN_MASK            (PWMSend_STATUS_CMP2)
    #define PWMSend_STATUS_CMP1_INT_EN_MASK            (PWMSend_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define PWMSend_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define PWMSend_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define PWMSend_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define PWMSend_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define PWMSend_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* PWMSend_UsingFixedFunction */

#endif  /* CY_PWM_PWMSend_H */


/* [] END OF FILE */
