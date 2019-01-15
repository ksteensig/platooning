/*******************************************************************************
* File Name: PWMHBro.h
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

#if !defined(CY_PWM_PWMHBro_H)
#define CY_PWM_PWMHBro_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PWMHBro_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PWMHBro_Resolution                     (8u)
#define PWMHBro_UsingFixedFunction             (0u)
#define PWMHBro_DeadBandMode                   (0u)
#define PWMHBro_KillModeMinTime                (0u)
#define PWMHBro_KillMode                       (0u)
#define PWMHBro_PWMMode                        (1u)
#define PWMHBro_PWMModeIsCenterAligned         (0u)
#define PWMHBro_DeadBandUsed                   (0u)
#define PWMHBro_DeadBand2_4                    (0u)

#if !defined(PWMHBro_PWMUDB_genblk8_stsreg__REMOVED)
    #define PWMHBro_UseStatus                  (1u)
#else
    #define PWMHBro_UseStatus                  (0u)
#endif /* !defined(PWMHBro_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(PWMHBro_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define PWMHBro_UseControl                 (1u)
#else
    #define PWMHBro_UseControl                 (0u)
#endif /* !defined(PWMHBro_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define PWMHBro_UseOneCompareMode              (0u)
#define PWMHBro_MinimumKillTime                (1u)
#define PWMHBro_EnableMode                     (0u)

#define PWMHBro_CompareMode1SW                 (0u)
#define PWMHBro_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define PWMHBro__B_PWM__DISABLED 0
#define PWMHBro__B_PWM__ASYNCHRONOUS 1
#define PWMHBro__B_PWM__SINGLECYCLE 2
#define PWMHBro__B_PWM__LATCHED 3
#define PWMHBro__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PWMHBro__B_PWM__DBMDISABLED 0
#define PWMHBro__B_PWM__DBM_2_4_CLOCKS 1
#define PWMHBro__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PWMHBro__B_PWM__ONE_OUTPUT 0
#define PWMHBro__B_PWM__TWO_OUTPUTS 1
#define PWMHBro__B_PWM__DUAL_EDGE 2
#define PWMHBro__B_PWM__CENTER_ALIGN 3
#define PWMHBro__B_PWM__DITHER 5
#define PWMHBro__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PWMHBro__B_PWM__LESS_THAN 1
#define PWMHBro__B_PWM__LESS_THAN_OR_EQUAL 2
#define PWMHBro__B_PWM__GREATER_THAN 3
#define PWMHBro__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PWMHBro__B_PWM__EQUAL 0
#define PWMHBro__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!PWMHBro_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!PWMHBro_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!PWMHBro_PWMModeIsCenterAligned) */
        #if (PWMHBro_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (PWMHBro_UseStatus) */

        /* Backup for Deadband parameters */
        #if(PWMHBro_DeadBandMode == PWMHBro__B_PWM__DBM_256_CLOCKS || \
            PWMHBro_DeadBandMode == PWMHBro__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(PWMHBro_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (PWMHBro_KillModeMinTime) */

        /* Backup control register */
        #if(PWMHBro_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (PWMHBro_UseControl) */

    #endif /* (!PWMHBro_UsingFixedFunction) */

}PWMHBro_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    PWMHBro_Start(void) ;
void    PWMHBro_Stop(void) ;

#if (PWMHBro_UseStatus || PWMHBro_UsingFixedFunction)
    void  PWMHBro_SetInterruptMode(uint8 interruptMode) ;
    uint8 PWMHBro_ReadStatusRegister(void) ;
#endif /* (PWMHBro_UseStatus || PWMHBro_UsingFixedFunction) */

#define PWMHBro_GetInterruptSource() PWMHBro_ReadStatusRegister()

#if (PWMHBro_UseControl)
    uint8 PWMHBro_ReadControlRegister(void) ;
    void  PWMHBro_WriteControlRegister(uint8 control)
          ;
#endif /* (PWMHBro_UseControl) */

#if (PWMHBro_UseOneCompareMode)
   #if (PWMHBro_CompareMode1SW)
       void    PWMHBro_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (PWMHBro_CompareMode1SW) */
#else
    #if (PWMHBro_CompareMode1SW)
        void    PWMHBro_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (PWMHBro_CompareMode1SW) */
    #if (PWMHBro_CompareMode2SW)
        void    PWMHBro_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (PWMHBro_CompareMode2SW) */
#endif /* (PWMHBro_UseOneCompareMode) */

#if (!PWMHBro_UsingFixedFunction)
    uint8   PWMHBro_ReadCounter(void) ;
    uint8 PWMHBro_ReadCapture(void) ;

    #if (PWMHBro_UseStatus)
            void PWMHBro_ClearFIFO(void) ;
    #endif /* (PWMHBro_UseStatus) */

    void    PWMHBro_WriteCounter(uint8 counter)
            ;
#endif /* (!PWMHBro_UsingFixedFunction) */

void    PWMHBro_WritePeriod(uint8 period)
        ;
uint8 PWMHBro_ReadPeriod(void) ;

#if (PWMHBro_UseOneCompareMode)
    void    PWMHBro_WriteCompare(uint8 compare)
            ;
    uint8 PWMHBro_ReadCompare(void) ;
#else
    void    PWMHBro_WriteCompare1(uint8 compare)
            ;
    uint8 PWMHBro_ReadCompare1(void) ;
    void    PWMHBro_WriteCompare2(uint8 compare)
            ;
    uint8 PWMHBro_ReadCompare2(void) ;
#endif /* (PWMHBro_UseOneCompareMode) */


#if (PWMHBro_DeadBandUsed)
    void    PWMHBro_WriteDeadTime(uint8 deadtime) ;
    uint8   PWMHBro_ReadDeadTime(void) ;
#endif /* (PWMHBro_DeadBandUsed) */

#if ( PWMHBro_KillModeMinTime)
    void PWMHBro_WriteKillTime(uint8 killtime) ;
    uint8 PWMHBro_ReadKillTime(void) ;
#endif /* ( PWMHBro_KillModeMinTime) */

void PWMHBro_Init(void) ;
void PWMHBro_Enable(void) ;
void PWMHBro_Sleep(void) ;
void PWMHBro_Wakeup(void) ;
void PWMHBro_SaveConfig(void) ;
void PWMHBro_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PWMHBro_INIT_PERIOD_VALUE          (255u)
#define PWMHBro_INIT_COMPARE_VALUE1        (0u)
#define PWMHBro_INIT_COMPARE_VALUE2        (0u)
#define PWMHBro_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    PWMHBro_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMHBro_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMHBro_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMHBro_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define PWMHBro_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  PWMHBro_CTRL_CMPMODE2_SHIFT)
#define PWMHBro_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  PWMHBro_CTRL_CMPMODE1_SHIFT)
#define PWMHBro_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (PWMHBro_UsingFixedFunction)
   #define PWMHBro_PERIOD_LSB              (*(reg16 *) PWMHBro_PWMHW__PER0)
   #define PWMHBro_PERIOD_LSB_PTR          ( (reg16 *) PWMHBro_PWMHW__PER0)
   #define PWMHBro_COMPARE1_LSB            (*(reg16 *) PWMHBro_PWMHW__CNT_CMP0)
   #define PWMHBro_COMPARE1_LSB_PTR        ( (reg16 *) PWMHBro_PWMHW__CNT_CMP0)
   #define PWMHBro_COMPARE2_LSB            (0x00u)
   #define PWMHBro_COMPARE2_LSB_PTR        (0x00u)
   #define PWMHBro_COUNTER_LSB             (*(reg16 *) PWMHBro_PWMHW__CNT_CMP0)
   #define PWMHBro_COUNTER_LSB_PTR         ( (reg16 *) PWMHBro_PWMHW__CNT_CMP0)
   #define PWMHBro_CAPTURE_LSB             (*(reg16 *) PWMHBro_PWMHW__CAP0)
   #define PWMHBro_CAPTURE_LSB_PTR         ( (reg16 *) PWMHBro_PWMHW__CAP0)
   #define PWMHBro_RT1                     (*(reg8 *)  PWMHBro_PWMHW__RT1)
   #define PWMHBro_RT1_PTR                 ( (reg8 *)  PWMHBro_PWMHW__RT1)

#else
   #if (PWMHBro_Resolution == 8u) /* 8bit - PWM */

       #if(PWMHBro_PWMModeIsCenterAligned)
           #define PWMHBro_PERIOD_LSB      (*(reg8 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define PWMHBro_PERIOD_LSB_PTR  ((reg8 *)   PWMHBro_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define PWMHBro_PERIOD_LSB      (*(reg8 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define PWMHBro_PERIOD_LSB_PTR  ((reg8 *)   PWMHBro_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (PWMHBro_PWMModeIsCenterAligned) */

       #define PWMHBro_COMPARE1_LSB        (*(reg8 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define PWMHBro_COMPARE1_LSB_PTR    ((reg8 *)   PWMHBro_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define PWMHBro_COMPARE2_LSB        (*(reg8 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define PWMHBro_COMPARE2_LSB_PTR    ((reg8 *)   PWMHBro_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define PWMHBro_COUNTERCAP_LSB      (*(reg8 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define PWMHBro_COUNTERCAP_LSB_PTR  ((reg8 *)   PWMHBro_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define PWMHBro_COUNTER_LSB         (*(reg8 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define PWMHBro_COUNTER_LSB_PTR     ((reg8 *)   PWMHBro_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define PWMHBro_CAPTURE_LSB         (*(reg8 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define PWMHBro_CAPTURE_LSB_PTR     ((reg8 *)   PWMHBro_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(PWMHBro_PWMModeIsCenterAligned)
               #define PWMHBro_PERIOD_LSB      (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define PWMHBro_PERIOD_LSB_PTR  ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define PWMHBro_PERIOD_LSB      (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define PWMHBro_PERIOD_LSB_PTR  ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (PWMHBro_PWMModeIsCenterAligned) */

            #define PWMHBro_COMPARE1_LSB       (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define PWMHBro_COMPARE1_LSB_PTR   ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define PWMHBro_COMPARE2_LSB       (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define PWMHBro_COMPARE2_LSB_PTR   ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define PWMHBro_COUNTERCAP_LSB     (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define PWMHBro_COUNTERCAP_LSB_PTR ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define PWMHBro_COUNTER_LSB        (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define PWMHBro_COUNTER_LSB_PTR    ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define PWMHBro_CAPTURE_LSB        (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define PWMHBro_CAPTURE_LSB_PTR    ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(PWMHBro_PWMModeIsCenterAligned)
               #define PWMHBro_PERIOD_LSB      (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define PWMHBro_PERIOD_LSB_PTR  ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define PWMHBro_PERIOD_LSB      (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define PWMHBro_PERIOD_LSB_PTR  ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (PWMHBro_PWMModeIsCenterAligned) */

            #define PWMHBro_COMPARE1_LSB       (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define PWMHBro_COMPARE1_LSB_PTR   ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define PWMHBro_COMPARE2_LSB       (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define PWMHBro_COMPARE2_LSB_PTR   ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define PWMHBro_COUNTERCAP_LSB     (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define PWMHBro_COUNTERCAP_LSB_PTR ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define PWMHBro_COUNTER_LSB        (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define PWMHBro_COUNTER_LSB_PTR    ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define PWMHBro_CAPTURE_LSB        (*(reg16 *) PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define PWMHBro_CAPTURE_LSB_PTR    ((reg16 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define PWMHBro_AUX_CONTROLDP1          (*(reg8 *)  PWMHBro_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define PWMHBro_AUX_CONTROLDP1_PTR      ((reg8 *)   PWMHBro_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (PWMHBro_Resolution == 8) */

   #define PWMHBro_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define PWMHBro_AUX_CONTROLDP0          (*(reg8 *)  PWMHBro_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define PWMHBro_AUX_CONTROLDP0_PTR      ((reg8 *)   PWMHBro_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (PWMHBro_UsingFixedFunction) */

#if(PWMHBro_KillModeMinTime )
    #define PWMHBro_KILLMODEMINTIME        (*(reg8 *)  PWMHBro_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PWMHBro_KILLMODEMINTIME_PTR    ((reg8 *)   PWMHBro_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (PWMHBro_KillModeMinTime ) */

#if(PWMHBro_DeadBandMode == PWMHBro__B_PWM__DBM_256_CLOCKS)
    #define PWMHBro_DEADBAND_COUNT         (*(reg8 *)  PWMHBro_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWMHBro_DEADBAND_COUNT_PTR     ((reg8 *)   PWMHBro_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWMHBro_DEADBAND_LSB_PTR       ((reg8 *)   PWMHBro_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PWMHBro_DEADBAND_LSB           (*(reg8 *)  PWMHBro_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PWMHBro_DeadBandMode == PWMHBro__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PWMHBro_UsingFixedFunction)
        #define PWMHBro_DEADBAND_COUNT         (*(reg8 *)  PWMHBro_PWMHW__CFG0)
        #define PWMHBro_DEADBAND_COUNT_PTR     ((reg8 *)   PWMHBro_PWMHW__CFG0)
        #define PWMHBro_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWMHBro_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define PWMHBro_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PWMHBro_DEADBAND_COUNT         (*(reg8 *)  PWMHBro_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWMHBro_DEADBAND_COUNT_PTR     ((reg8 *)   PWMHBro_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWMHBro_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWMHBro_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define PWMHBro_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (PWMHBro_UsingFixedFunction) */
#endif /* (PWMHBro_DeadBandMode == PWMHBro__B_PWM__DBM_256_CLOCKS) */



#if (PWMHBro_UsingFixedFunction)
    #define PWMHBro_STATUS                 (*(reg8 *) PWMHBro_PWMHW__SR0)
    #define PWMHBro_STATUS_PTR             ((reg8 *) PWMHBro_PWMHW__SR0)
    #define PWMHBro_STATUS_MASK            (*(reg8 *) PWMHBro_PWMHW__SR0)
    #define PWMHBro_STATUS_MASK_PTR        ((reg8 *) PWMHBro_PWMHW__SR0)
    #define PWMHBro_CONTROL                (*(reg8 *) PWMHBro_PWMHW__CFG0)
    #define PWMHBro_CONTROL_PTR            ((reg8 *) PWMHBro_PWMHW__CFG0)
    #define PWMHBro_CONTROL2               (*(reg8 *) PWMHBro_PWMHW__CFG1)
    #define PWMHBro_CONTROL3               (*(reg8 *) PWMHBro_PWMHW__CFG2)
    #define PWMHBro_GLOBAL_ENABLE          (*(reg8 *) PWMHBro_PWMHW__PM_ACT_CFG)
    #define PWMHBro_GLOBAL_ENABLE_PTR      ( (reg8 *) PWMHBro_PWMHW__PM_ACT_CFG)
    #define PWMHBro_GLOBAL_STBY_ENABLE     (*(reg8 *) PWMHBro_PWMHW__PM_STBY_CFG)
    #define PWMHBro_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) PWMHBro_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define PWMHBro_BLOCK_EN_MASK          (PWMHBro_PWMHW__PM_ACT_MSK)
    #define PWMHBro_BLOCK_STBY_EN_MASK     (PWMHBro_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define PWMHBro_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define PWMHBro_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define PWMHBro_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define PWMHBro_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define PWMHBro_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define PWMHBro_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define PWMHBro_CTRL_ENABLE            (uint8)((uint8)0x01u << PWMHBro_CTRL_ENABLE_SHIFT)
    #define PWMHBro_CTRL_RESET             (uint8)((uint8)0x01u << PWMHBro_CTRL_RESET_SHIFT)
    #define PWMHBro_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWMHBro_CTRL_CMPMODE2_SHIFT)
    #define PWMHBro_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWMHBro_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PWMHBro_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define PWMHBro_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << PWMHBro_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define PWMHBro_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define PWMHBro_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define PWMHBro_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define PWMHBro_STATUS_TC_INT_EN_MASK_SHIFT            (PWMHBro_STATUS_TC_SHIFT - 4u)
    #define PWMHBro_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define PWMHBro_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWMHBro_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define PWMHBro_STATUS_TC              (uint8)((uint8)0x01u << PWMHBro_STATUS_TC_SHIFT)
    #define PWMHBro_STATUS_CMP1            (uint8)((uint8)0x01u << PWMHBro_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define PWMHBro_STATUS_TC_INT_EN_MASK              (uint8)((uint8)PWMHBro_STATUS_TC >> 4u)
    #define PWMHBro_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)PWMHBro_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define PWMHBro_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define PWMHBro_RT1_MASK              (uint8)((uint8)0x03u << PWMHBro_RT1_SHIFT)
    #define PWMHBro_SYNC                  (uint8)((uint8)0x03u << PWMHBro_RT1_SHIFT)
    #define PWMHBro_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define PWMHBro_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << PWMHBro_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define PWMHBro_SYNCDSI_EN            (uint8)((uint8)0x0Fu << PWMHBro_SYNCDSI_SHIFT)


#else
    #define PWMHBro_STATUS                (*(reg8 *)   PWMHBro_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWMHBro_STATUS_PTR            ((reg8 *)    PWMHBro_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWMHBro_STATUS_MASK           (*(reg8 *)   PWMHBro_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWMHBro_STATUS_MASK_PTR       ((reg8 *)    PWMHBro_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWMHBro_STATUS_AUX_CTRL       (*(reg8 *)   PWMHBro_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define PWMHBro_CONTROL               (*(reg8 *)   PWMHBro_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define PWMHBro_CONTROL_PTR           ((reg8 *)    PWMHBro_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define PWMHBro_CTRL_ENABLE_SHIFT      (0x07u)
    #define PWMHBro_CTRL_RESET_SHIFT       (0x06u)
    #define PWMHBro_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define PWMHBro_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define PWMHBro_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define PWMHBro_CTRL_ENABLE            (uint8)((uint8)0x01u << PWMHBro_CTRL_ENABLE_SHIFT)
    #define PWMHBro_CTRL_RESET             (uint8)((uint8)0x01u << PWMHBro_CTRL_RESET_SHIFT)
    #define PWMHBro_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWMHBro_CTRL_CMPMODE2_SHIFT)
    #define PWMHBro_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWMHBro_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define PWMHBro_STATUS_KILL_SHIFT          (0x05u)
    #define PWMHBro_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define PWMHBro_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define PWMHBro_STATUS_TC_SHIFT            (0x02u)
    #define PWMHBro_STATUS_CMP2_SHIFT          (0x01u)
    #define PWMHBro_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PWMHBro_STATUS_KILL_INT_EN_MASK_SHIFT          (PWMHBro_STATUS_KILL_SHIFT)
    #define PWMHBro_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (PWMHBro_STATUS_FIFONEMPTY_SHIFT)
    #define PWMHBro_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (PWMHBro_STATUS_FIFOFULL_SHIFT)
    #define PWMHBro_STATUS_TC_INT_EN_MASK_SHIFT            (PWMHBro_STATUS_TC_SHIFT)
    #define PWMHBro_STATUS_CMP2_INT_EN_MASK_SHIFT          (PWMHBro_STATUS_CMP2_SHIFT)
    #define PWMHBro_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWMHBro_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define PWMHBro_STATUS_KILL            (uint8)((uint8)0x00u << PWMHBro_STATUS_KILL_SHIFT )
    #define PWMHBro_STATUS_FIFOFULL        (uint8)((uint8)0x01u << PWMHBro_STATUS_FIFOFULL_SHIFT)
    #define PWMHBro_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << PWMHBro_STATUS_FIFONEMPTY_SHIFT)
    #define PWMHBro_STATUS_TC              (uint8)((uint8)0x01u << PWMHBro_STATUS_TC_SHIFT)
    #define PWMHBro_STATUS_CMP2            (uint8)((uint8)0x01u << PWMHBro_STATUS_CMP2_SHIFT)
    #define PWMHBro_STATUS_CMP1            (uint8)((uint8)0x01u << PWMHBro_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PWMHBro_STATUS_KILL_INT_EN_MASK            (PWMHBro_STATUS_KILL)
    #define PWMHBro_STATUS_FIFOFULL_INT_EN_MASK        (PWMHBro_STATUS_FIFOFULL)
    #define PWMHBro_STATUS_FIFONEMPTY_INT_EN_MASK      (PWMHBro_STATUS_FIFONEMPTY)
    #define PWMHBro_STATUS_TC_INT_EN_MASK              (PWMHBro_STATUS_TC)
    #define PWMHBro_STATUS_CMP2_INT_EN_MASK            (PWMHBro_STATUS_CMP2)
    #define PWMHBro_STATUS_CMP1_INT_EN_MASK            (PWMHBro_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define PWMHBro_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define PWMHBro_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define PWMHBro_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define PWMHBro_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define PWMHBro_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* PWMHBro_UsingFixedFunction */

#endif  /* CY_PWM_PWMHBro_H */


/* [] END OF FILE */
