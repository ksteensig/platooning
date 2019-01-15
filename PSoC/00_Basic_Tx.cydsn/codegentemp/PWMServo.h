/*******************************************************************************
* File Name: PWMServo.h
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

#if !defined(CY_PWM_PWMServo_H)
#define CY_PWM_PWMServo_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PWMServo_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PWMServo_Resolution                     (16u)
#define PWMServo_UsingFixedFunction             (0u)
#define PWMServo_DeadBandMode                   (0u)
#define PWMServo_KillModeMinTime                (0u)
#define PWMServo_KillMode                       (0u)
#define PWMServo_PWMMode                        (0u)
#define PWMServo_PWMModeIsCenterAligned         (0u)
#define PWMServo_DeadBandUsed                   (0u)
#define PWMServo_DeadBand2_4                    (0u)

#if !defined(PWMServo_PWMUDB_genblk8_stsreg__REMOVED)
    #define PWMServo_UseStatus                  (1u)
#else
    #define PWMServo_UseStatus                  (0u)
#endif /* !defined(PWMServo_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(PWMServo_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define PWMServo_UseControl                 (1u)
#else
    #define PWMServo_UseControl                 (0u)
#endif /* !defined(PWMServo_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define PWMServo_UseOneCompareMode              (1u)
#define PWMServo_MinimumKillTime                (1u)
#define PWMServo_EnableMode                     (0u)

#define PWMServo_CompareMode1SW                 (0u)
#define PWMServo_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define PWMServo__B_PWM__DISABLED 0
#define PWMServo__B_PWM__ASYNCHRONOUS 1
#define PWMServo__B_PWM__SINGLECYCLE 2
#define PWMServo__B_PWM__LATCHED 3
#define PWMServo__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PWMServo__B_PWM__DBMDISABLED 0
#define PWMServo__B_PWM__DBM_2_4_CLOCKS 1
#define PWMServo__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PWMServo__B_PWM__ONE_OUTPUT 0
#define PWMServo__B_PWM__TWO_OUTPUTS 1
#define PWMServo__B_PWM__DUAL_EDGE 2
#define PWMServo__B_PWM__CENTER_ALIGN 3
#define PWMServo__B_PWM__DITHER 5
#define PWMServo__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PWMServo__B_PWM__LESS_THAN 1
#define PWMServo__B_PWM__LESS_THAN_OR_EQUAL 2
#define PWMServo__B_PWM__GREATER_THAN 3
#define PWMServo__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PWMServo__B_PWM__EQUAL 0
#define PWMServo__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!PWMServo_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!PWMServo_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!PWMServo_PWMModeIsCenterAligned) */
        #if (PWMServo_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (PWMServo_UseStatus) */

        /* Backup for Deadband parameters */
        #if(PWMServo_DeadBandMode == PWMServo__B_PWM__DBM_256_CLOCKS || \
            PWMServo_DeadBandMode == PWMServo__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(PWMServo_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (PWMServo_KillModeMinTime) */

        /* Backup control register */
        #if(PWMServo_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (PWMServo_UseControl) */

    #endif /* (!PWMServo_UsingFixedFunction) */

}PWMServo_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    PWMServo_Start(void) ;
void    PWMServo_Stop(void) ;

#if (PWMServo_UseStatus || PWMServo_UsingFixedFunction)
    void  PWMServo_SetInterruptMode(uint8 interruptMode) ;
    uint8 PWMServo_ReadStatusRegister(void) ;
#endif /* (PWMServo_UseStatus || PWMServo_UsingFixedFunction) */

#define PWMServo_GetInterruptSource() PWMServo_ReadStatusRegister()

#if (PWMServo_UseControl)
    uint8 PWMServo_ReadControlRegister(void) ;
    void  PWMServo_WriteControlRegister(uint8 control)
          ;
#endif /* (PWMServo_UseControl) */

#if (PWMServo_UseOneCompareMode)
   #if (PWMServo_CompareMode1SW)
       void    PWMServo_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (PWMServo_CompareMode1SW) */
#else
    #if (PWMServo_CompareMode1SW)
        void    PWMServo_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (PWMServo_CompareMode1SW) */
    #if (PWMServo_CompareMode2SW)
        void    PWMServo_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (PWMServo_CompareMode2SW) */
#endif /* (PWMServo_UseOneCompareMode) */

#if (!PWMServo_UsingFixedFunction)
    uint16   PWMServo_ReadCounter(void) ;
    uint16 PWMServo_ReadCapture(void) ;

    #if (PWMServo_UseStatus)
            void PWMServo_ClearFIFO(void) ;
    #endif /* (PWMServo_UseStatus) */

    void    PWMServo_WriteCounter(uint16 counter)
            ;
#endif /* (!PWMServo_UsingFixedFunction) */

void    PWMServo_WritePeriod(uint16 period)
        ;
uint16 PWMServo_ReadPeriod(void) ;

#if (PWMServo_UseOneCompareMode)
    void    PWMServo_WriteCompare(uint16 compare)
            ;
    uint16 PWMServo_ReadCompare(void) ;
#else
    void    PWMServo_WriteCompare1(uint16 compare)
            ;
    uint16 PWMServo_ReadCompare1(void) ;
    void    PWMServo_WriteCompare2(uint16 compare)
            ;
    uint16 PWMServo_ReadCompare2(void) ;
#endif /* (PWMServo_UseOneCompareMode) */


#if (PWMServo_DeadBandUsed)
    void    PWMServo_WriteDeadTime(uint8 deadtime) ;
    uint8   PWMServo_ReadDeadTime(void) ;
#endif /* (PWMServo_DeadBandUsed) */

#if ( PWMServo_KillModeMinTime)
    void PWMServo_WriteKillTime(uint8 killtime) ;
    uint8 PWMServo_ReadKillTime(void) ;
#endif /* ( PWMServo_KillModeMinTime) */

void PWMServo_Init(void) ;
void PWMServo_Enable(void) ;
void PWMServo_Sleep(void) ;
void PWMServo_Wakeup(void) ;
void PWMServo_SaveConfig(void) ;
void PWMServo_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PWMServo_INIT_PERIOD_VALUE          (19999u)
#define PWMServo_INIT_COMPARE_VALUE1        (1500u)
#define PWMServo_INIT_COMPARE_VALUE2        (0u)
#define PWMServo_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    PWMServo_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMServo_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMServo_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    PWMServo_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define PWMServo_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  PWMServo_CTRL_CMPMODE2_SHIFT)
#define PWMServo_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  PWMServo_CTRL_CMPMODE1_SHIFT)
#define PWMServo_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (PWMServo_UsingFixedFunction)
   #define PWMServo_PERIOD_LSB              (*(reg16 *) PWMServo_PWMHW__PER0)
   #define PWMServo_PERIOD_LSB_PTR          ( (reg16 *) PWMServo_PWMHW__PER0)
   #define PWMServo_COMPARE1_LSB            (*(reg16 *) PWMServo_PWMHW__CNT_CMP0)
   #define PWMServo_COMPARE1_LSB_PTR        ( (reg16 *) PWMServo_PWMHW__CNT_CMP0)
   #define PWMServo_COMPARE2_LSB            (0x00u)
   #define PWMServo_COMPARE2_LSB_PTR        (0x00u)
   #define PWMServo_COUNTER_LSB             (*(reg16 *) PWMServo_PWMHW__CNT_CMP0)
   #define PWMServo_COUNTER_LSB_PTR         ( (reg16 *) PWMServo_PWMHW__CNT_CMP0)
   #define PWMServo_CAPTURE_LSB             (*(reg16 *) PWMServo_PWMHW__CAP0)
   #define PWMServo_CAPTURE_LSB_PTR         ( (reg16 *) PWMServo_PWMHW__CAP0)
   #define PWMServo_RT1                     (*(reg8 *)  PWMServo_PWMHW__RT1)
   #define PWMServo_RT1_PTR                 ( (reg8 *)  PWMServo_PWMHW__RT1)

#else
   #if (PWMServo_Resolution == 8u) /* 8bit - PWM */

       #if(PWMServo_PWMModeIsCenterAligned)
           #define PWMServo_PERIOD_LSB      (*(reg8 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define PWMServo_PERIOD_LSB_PTR  ((reg8 *)   PWMServo_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define PWMServo_PERIOD_LSB      (*(reg8 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define PWMServo_PERIOD_LSB_PTR  ((reg8 *)   PWMServo_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (PWMServo_PWMModeIsCenterAligned) */

       #define PWMServo_COMPARE1_LSB        (*(reg8 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define PWMServo_COMPARE1_LSB_PTR    ((reg8 *)   PWMServo_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define PWMServo_COMPARE2_LSB        (*(reg8 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define PWMServo_COMPARE2_LSB_PTR    ((reg8 *)   PWMServo_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define PWMServo_COUNTERCAP_LSB      (*(reg8 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define PWMServo_COUNTERCAP_LSB_PTR  ((reg8 *)   PWMServo_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define PWMServo_COUNTER_LSB         (*(reg8 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define PWMServo_COUNTER_LSB_PTR     ((reg8 *)   PWMServo_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define PWMServo_CAPTURE_LSB         (*(reg8 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define PWMServo_CAPTURE_LSB_PTR     ((reg8 *)   PWMServo_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(PWMServo_PWMModeIsCenterAligned)
               #define PWMServo_PERIOD_LSB      (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define PWMServo_PERIOD_LSB_PTR  ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define PWMServo_PERIOD_LSB      (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define PWMServo_PERIOD_LSB_PTR  ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (PWMServo_PWMModeIsCenterAligned) */

            #define PWMServo_COMPARE1_LSB       (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define PWMServo_COMPARE1_LSB_PTR   ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define PWMServo_COMPARE2_LSB       (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define PWMServo_COMPARE2_LSB_PTR   ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define PWMServo_COUNTERCAP_LSB     (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define PWMServo_COUNTERCAP_LSB_PTR ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define PWMServo_COUNTER_LSB        (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define PWMServo_COUNTER_LSB_PTR    ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define PWMServo_CAPTURE_LSB        (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define PWMServo_CAPTURE_LSB_PTR    ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(PWMServo_PWMModeIsCenterAligned)
               #define PWMServo_PERIOD_LSB      (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define PWMServo_PERIOD_LSB_PTR  ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define PWMServo_PERIOD_LSB      (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define PWMServo_PERIOD_LSB_PTR  ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (PWMServo_PWMModeIsCenterAligned) */

            #define PWMServo_COMPARE1_LSB       (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define PWMServo_COMPARE1_LSB_PTR   ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define PWMServo_COMPARE2_LSB       (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define PWMServo_COMPARE2_LSB_PTR   ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define PWMServo_COUNTERCAP_LSB     (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define PWMServo_COUNTERCAP_LSB_PTR ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define PWMServo_COUNTER_LSB        (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define PWMServo_COUNTER_LSB_PTR    ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define PWMServo_CAPTURE_LSB        (*(reg16 *) PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define PWMServo_CAPTURE_LSB_PTR    ((reg16 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define PWMServo_AUX_CONTROLDP1          (*(reg8 *)  PWMServo_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define PWMServo_AUX_CONTROLDP1_PTR      ((reg8 *)   PWMServo_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (PWMServo_Resolution == 8) */

   #define PWMServo_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define PWMServo_AUX_CONTROLDP0          (*(reg8 *)  PWMServo_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define PWMServo_AUX_CONTROLDP0_PTR      ((reg8 *)   PWMServo_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (PWMServo_UsingFixedFunction) */

#if(PWMServo_KillModeMinTime )
    #define PWMServo_KILLMODEMINTIME        (*(reg8 *)  PWMServo_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PWMServo_KILLMODEMINTIME_PTR    ((reg8 *)   PWMServo_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (PWMServo_KillModeMinTime ) */

#if(PWMServo_DeadBandMode == PWMServo__B_PWM__DBM_256_CLOCKS)
    #define PWMServo_DEADBAND_COUNT         (*(reg8 *)  PWMServo_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWMServo_DEADBAND_COUNT_PTR     ((reg8 *)   PWMServo_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWMServo_DEADBAND_LSB_PTR       ((reg8 *)   PWMServo_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PWMServo_DEADBAND_LSB           (*(reg8 *)  PWMServo_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PWMServo_DeadBandMode == PWMServo__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PWMServo_UsingFixedFunction)
        #define PWMServo_DEADBAND_COUNT         (*(reg8 *)  PWMServo_PWMHW__CFG0)
        #define PWMServo_DEADBAND_COUNT_PTR     ((reg8 *)   PWMServo_PWMHW__CFG0)
        #define PWMServo_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWMServo_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define PWMServo_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PWMServo_DEADBAND_COUNT         (*(reg8 *)  PWMServo_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWMServo_DEADBAND_COUNT_PTR     ((reg8 *)   PWMServo_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define PWMServo_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWMServo_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define PWMServo_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (PWMServo_UsingFixedFunction) */
#endif /* (PWMServo_DeadBandMode == PWMServo__B_PWM__DBM_256_CLOCKS) */



#if (PWMServo_UsingFixedFunction)
    #define PWMServo_STATUS                 (*(reg8 *) PWMServo_PWMHW__SR0)
    #define PWMServo_STATUS_PTR             ((reg8 *) PWMServo_PWMHW__SR0)
    #define PWMServo_STATUS_MASK            (*(reg8 *) PWMServo_PWMHW__SR0)
    #define PWMServo_STATUS_MASK_PTR        ((reg8 *) PWMServo_PWMHW__SR0)
    #define PWMServo_CONTROL                (*(reg8 *) PWMServo_PWMHW__CFG0)
    #define PWMServo_CONTROL_PTR            ((reg8 *) PWMServo_PWMHW__CFG0)
    #define PWMServo_CONTROL2               (*(reg8 *) PWMServo_PWMHW__CFG1)
    #define PWMServo_CONTROL3               (*(reg8 *) PWMServo_PWMHW__CFG2)
    #define PWMServo_GLOBAL_ENABLE          (*(reg8 *) PWMServo_PWMHW__PM_ACT_CFG)
    #define PWMServo_GLOBAL_ENABLE_PTR      ( (reg8 *) PWMServo_PWMHW__PM_ACT_CFG)
    #define PWMServo_GLOBAL_STBY_ENABLE     (*(reg8 *) PWMServo_PWMHW__PM_STBY_CFG)
    #define PWMServo_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) PWMServo_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define PWMServo_BLOCK_EN_MASK          (PWMServo_PWMHW__PM_ACT_MSK)
    #define PWMServo_BLOCK_STBY_EN_MASK     (PWMServo_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define PWMServo_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define PWMServo_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define PWMServo_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define PWMServo_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define PWMServo_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define PWMServo_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define PWMServo_CTRL_ENABLE            (uint8)((uint8)0x01u << PWMServo_CTRL_ENABLE_SHIFT)
    #define PWMServo_CTRL_RESET             (uint8)((uint8)0x01u << PWMServo_CTRL_RESET_SHIFT)
    #define PWMServo_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWMServo_CTRL_CMPMODE2_SHIFT)
    #define PWMServo_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWMServo_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PWMServo_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define PWMServo_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << PWMServo_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define PWMServo_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define PWMServo_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define PWMServo_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define PWMServo_STATUS_TC_INT_EN_MASK_SHIFT            (PWMServo_STATUS_TC_SHIFT - 4u)
    #define PWMServo_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define PWMServo_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWMServo_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define PWMServo_STATUS_TC              (uint8)((uint8)0x01u << PWMServo_STATUS_TC_SHIFT)
    #define PWMServo_STATUS_CMP1            (uint8)((uint8)0x01u << PWMServo_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define PWMServo_STATUS_TC_INT_EN_MASK              (uint8)((uint8)PWMServo_STATUS_TC >> 4u)
    #define PWMServo_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)PWMServo_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define PWMServo_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define PWMServo_RT1_MASK              (uint8)((uint8)0x03u << PWMServo_RT1_SHIFT)
    #define PWMServo_SYNC                  (uint8)((uint8)0x03u << PWMServo_RT1_SHIFT)
    #define PWMServo_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define PWMServo_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << PWMServo_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define PWMServo_SYNCDSI_EN            (uint8)((uint8)0x0Fu << PWMServo_SYNCDSI_SHIFT)


#else
    #define PWMServo_STATUS                (*(reg8 *)   PWMServo_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWMServo_STATUS_PTR            ((reg8 *)    PWMServo_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define PWMServo_STATUS_MASK           (*(reg8 *)   PWMServo_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWMServo_STATUS_MASK_PTR       ((reg8 *)    PWMServo_PWMUDB_genblk8_stsreg__MASK_REG)
    #define PWMServo_STATUS_AUX_CTRL       (*(reg8 *)   PWMServo_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define PWMServo_CONTROL               (*(reg8 *)   PWMServo_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define PWMServo_CONTROL_PTR           ((reg8 *)    PWMServo_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define PWMServo_CTRL_ENABLE_SHIFT      (0x07u)
    #define PWMServo_CTRL_RESET_SHIFT       (0x06u)
    #define PWMServo_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define PWMServo_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define PWMServo_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define PWMServo_CTRL_ENABLE            (uint8)((uint8)0x01u << PWMServo_CTRL_ENABLE_SHIFT)
    #define PWMServo_CTRL_RESET             (uint8)((uint8)0x01u << PWMServo_CTRL_RESET_SHIFT)
    #define PWMServo_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWMServo_CTRL_CMPMODE2_SHIFT)
    #define PWMServo_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWMServo_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define PWMServo_STATUS_KILL_SHIFT          (0x05u)
    #define PWMServo_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define PWMServo_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define PWMServo_STATUS_TC_SHIFT            (0x02u)
    #define PWMServo_STATUS_CMP2_SHIFT          (0x01u)
    #define PWMServo_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PWMServo_STATUS_KILL_INT_EN_MASK_SHIFT          (PWMServo_STATUS_KILL_SHIFT)
    #define PWMServo_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (PWMServo_STATUS_FIFONEMPTY_SHIFT)
    #define PWMServo_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (PWMServo_STATUS_FIFOFULL_SHIFT)
    #define PWMServo_STATUS_TC_INT_EN_MASK_SHIFT            (PWMServo_STATUS_TC_SHIFT)
    #define PWMServo_STATUS_CMP2_INT_EN_MASK_SHIFT          (PWMServo_STATUS_CMP2_SHIFT)
    #define PWMServo_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWMServo_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define PWMServo_STATUS_KILL            (uint8)((uint8)0x00u << PWMServo_STATUS_KILL_SHIFT )
    #define PWMServo_STATUS_FIFOFULL        (uint8)((uint8)0x01u << PWMServo_STATUS_FIFOFULL_SHIFT)
    #define PWMServo_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << PWMServo_STATUS_FIFONEMPTY_SHIFT)
    #define PWMServo_STATUS_TC              (uint8)((uint8)0x01u << PWMServo_STATUS_TC_SHIFT)
    #define PWMServo_STATUS_CMP2            (uint8)((uint8)0x01u << PWMServo_STATUS_CMP2_SHIFT)
    #define PWMServo_STATUS_CMP1            (uint8)((uint8)0x01u << PWMServo_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PWMServo_STATUS_KILL_INT_EN_MASK            (PWMServo_STATUS_KILL)
    #define PWMServo_STATUS_FIFOFULL_INT_EN_MASK        (PWMServo_STATUS_FIFOFULL)
    #define PWMServo_STATUS_FIFONEMPTY_INT_EN_MASK      (PWMServo_STATUS_FIFONEMPTY)
    #define PWMServo_STATUS_TC_INT_EN_MASK              (PWMServo_STATUS_TC)
    #define PWMServo_STATUS_CMP2_INT_EN_MASK            (PWMServo_STATUS_CMP2)
    #define PWMServo_STATUS_CMP1_INT_EN_MASK            (PWMServo_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define PWMServo_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define PWMServo_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define PWMServo_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define PWMServo_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define PWMServo_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* PWMServo_UsingFixedFunction */

#endif  /* CY_PWM_PWMServo_H */


/* [] END OF FILE */
