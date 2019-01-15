/*******************************************************************************
* File Name: PWMHBro.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "PWMHBro.h"

/* Error message for removed <resource> through optimization */
#ifdef PWMHBro_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* PWMHBro_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 PWMHBro_initVar = 0u;


/*******************************************************************************
* Function Name: PWMHBro_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMHBro_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void PWMHBro_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(PWMHBro_initVar == 0u)
    {
        PWMHBro_Init();
        PWMHBro_initVar = 1u;
    }
    PWMHBro_Enable();

}


/*******************************************************************************
* Function Name: PWMHBro_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  PWMHBro_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMHBro_Init(void) 
{
    #if (PWMHBro_UsingFixedFunction || PWMHBro_UseControl)
        uint8 ctrl;
    #endif /* (PWMHBro_UsingFixedFunction || PWMHBro_UseControl) */

    #if(!PWMHBro_UsingFixedFunction)
        #if(PWMHBro_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 PWMHBro_interruptState;
        #endif /* (PWMHBro_UseStatus) */
    #endif /* (!PWMHBro_UsingFixedFunction) */

    #if (PWMHBro_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        PWMHBro_CONTROL |= PWMHBro_CFG0_MODE;
        #if (PWMHBro_DeadBand2_4)
            PWMHBro_CONTROL |= PWMHBro_CFG0_DB;
        #endif /* (PWMHBro_DeadBand2_4) */

        ctrl = PWMHBro_CONTROL3 & ((uint8 )(~PWMHBro_CTRL_CMPMODE1_MASK));
        PWMHBro_CONTROL3 = ctrl | PWMHBro_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        PWMHBro_RT1 &= ((uint8)(~PWMHBro_RT1_MASK));
        PWMHBro_RT1 |= PWMHBro_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        PWMHBro_RT1 &= ((uint8)(~PWMHBro_SYNCDSI_MASK));
        PWMHBro_RT1 |= PWMHBro_SYNCDSI_EN;

    #elif (PWMHBro_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = PWMHBro_CONTROL & ((uint8)(~PWMHBro_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~PWMHBro_CTRL_CMPMODE1_MASK));
        PWMHBro_CONTROL = ctrl | PWMHBro_DEFAULT_COMPARE2_MODE |
                                   PWMHBro_DEFAULT_COMPARE1_MODE;
    #endif /* (PWMHBro_UsingFixedFunction) */

    #if (!PWMHBro_UsingFixedFunction)
        #if (PWMHBro_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            PWMHBro_AUX_CONTROLDP0 |= (PWMHBro_AUX_CTRL_FIFO0_CLR);
        #else /* (PWMHBro_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            PWMHBro_AUX_CONTROLDP0 |= (PWMHBro_AUX_CTRL_FIFO0_CLR);
            PWMHBro_AUX_CONTROLDP1 |= (PWMHBro_AUX_CTRL_FIFO0_CLR);
        #endif /* (PWMHBro_Resolution == 8) */

        PWMHBro_WriteCounter(PWMHBro_INIT_PERIOD_VALUE);
    #endif /* (!PWMHBro_UsingFixedFunction) */

    PWMHBro_WritePeriod(PWMHBro_INIT_PERIOD_VALUE);

        #if (PWMHBro_UseOneCompareMode)
            PWMHBro_WriteCompare(PWMHBro_INIT_COMPARE_VALUE1);
        #else
            PWMHBro_WriteCompare1(PWMHBro_INIT_COMPARE_VALUE1);
            PWMHBro_WriteCompare2(PWMHBro_INIT_COMPARE_VALUE2);
        #endif /* (PWMHBro_UseOneCompareMode) */

        #if (PWMHBro_KillModeMinTime)
            PWMHBro_WriteKillTime(PWMHBro_MinimumKillTime);
        #endif /* (PWMHBro_KillModeMinTime) */

        #if (PWMHBro_DeadBandUsed)
            PWMHBro_WriteDeadTime(PWMHBro_INIT_DEAD_TIME);
        #endif /* (PWMHBro_DeadBandUsed) */

    #if (PWMHBro_UseStatus || PWMHBro_UsingFixedFunction)
        PWMHBro_SetInterruptMode(PWMHBro_INIT_INTERRUPTS_MODE);
    #endif /* (PWMHBro_UseStatus || PWMHBro_UsingFixedFunction) */

    #if (PWMHBro_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        PWMHBro_GLOBAL_ENABLE |= PWMHBro_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        PWMHBro_CONTROL2 |= PWMHBro_CTRL2_IRQ_SEL;
    #else
        #if(PWMHBro_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PWMHBro_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            PWMHBro_STATUS_AUX_CTRL |= PWMHBro_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(PWMHBro_interruptState);

            /* Clear the FIFO to enable the PWMHBro_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            PWMHBro_ClearFIFO();
        #endif /* (PWMHBro_UseStatus) */
    #endif /* (PWMHBro_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMHBro_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void PWMHBro_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PWMHBro_UsingFixedFunction)
        PWMHBro_GLOBAL_ENABLE |= PWMHBro_BLOCK_EN_MASK;
        PWMHBro_GLOBAL_STBY_ENABLE |= PWMHBro_BLOCK_STBY_EN_MASK;
    #endif /* (PWMHBro_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (PWMHBro_UseControl || PWMHBro_UsingFixedFunction)
        PWMHBro_CONTROL |= PWMHBro_CTRL_ENABLE;
    #endif /* (PWMHBro_UseControl || PWMHBro_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMHBro_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void PWMHBro_Stop(void) 
{
    #if (PWMHBro_UseControl || PWMHBro_UsingFixedFunction)
        PWMHBro_CONTROL &= ((uint8)(~PWMHBro_CTRL_ENABLE));
    #endif /* (PWMHBro_UseControl || PWMHBro_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (PWMHBro_UsingFixedFunction)
        PWMHBro_GLOBAL_ENABLE &= ((uint8)(~PWMHBro_BLOCK_EN_MASK));
        PWMHBro_GLOBAL_STBY_ENABLE &= ((uint8)(~PWMHBro_BLOCK_STBY_EN_MASK));
    #endif /* (PWMHBro_UsingFixedFunction) */
}

#if (PWMHBro_UseOneCompareMode)
    #if (PWMHBro_CompareMode1SW)


        /*******************************************************************************
        * Function Name: PWMHBro_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PWMHBro_SetCompareMode(uint8 comparemode) 
        {
            #if(PWMHBro_UsingFixedFunction)

                #if(0 != PWMHBro_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWMHBro_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != PWMHBro_CTRL_CMPMODE1_SHIFT) */

                PWMHBro_CONTROL3 &= ((uint8)(~PWMHBro_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                PWMHBro_CONTROL3 |= comparemodemasked;

            #elif (PWMHBro_UseControl)

                #if(0 != PWMHBro_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << PWMHBro_CTRL_CMPMODE1_SHIFT)) &
                                                PWMHBro_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & PWMHBro_CTRL_CMPMODE1_MASK;
                #endif /* (0 != PWMHBro_CTRL_CMPMODE1_SHIFT) */

                #if(0 != PWMHBro_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << PWMHBro_CTRL_CMPMODE2_SHIFT)) &
                                               PWMHBro_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & PWMHBro_CTRL_CMPMODE2_MASK;
                #endif /* (0 != PWMHBro_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                PWMHBro_CONTROL &= ((uint8)(~(PWMHBro_CTRL_CMPMODE1_MASK |
                                            PWMHBro_CTRL_CMPMODE2_MASK)));
                PWMHBro_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (PWMHBro_UsingFixedFunction) */
        }
    #endif /* PWMHBro_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (PWMHBro_CompareMode1SW)


        /*******************************************************************************
        * Function Name: PWMHBro_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PWMHBro_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != PWMHBro_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWMHBro_CTRL_CMPMODE1_SHIFT)) &
                                           PWMHBro_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & PWMHBro_CTRL_CMPMODE1_MASK;
            #endif /* (0 != PWMHBro_CTRL_CMPMODE1_SHIFT) */

            #if (PWMHBro_UseControl)
                PWMHBro_CONTROL &= ((uint8)(~PWMHBro_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                PWMHBro_CONTROL |= comparemodemasked;
            #endif /* (PWMHBro_UseControl) */
        }
    #endif /* PWMHBro_CompareMode1SW */

#if (PWMHBro_CompareMode2SW)


    /*******************************************************************************
    * Function Name: PWMHBro_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMHBro_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != PWMHBro_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWMHBro_CTRL_CMPMODE2_SHIFT)) &
                                                 PWMHBro_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & PWMHBro_CTRL_CMPMODE2_MASK;
        #endif /* (0 != PWMHBro_CTRL_CMPMODE2_SHIFT) */

        #if (PWMHBro_UseControl)
            PWMHBro_CONTROL &= ((uint8)(~PWMHBro_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            PWMHBro_CONTROL |= comparemodemasked;
        #endif /* (PWMHBro_UseControl) */
    }
    #endif /*PWMHBro_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!PWMHBro_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWMHBro_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void PWMHBro_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(PWMHBro_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: PWMHBro_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint8 PWMHBro_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(PWMHBro_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG8(PWMHBro_CAPTURE_LSB_PTR));
    }

    #if (PWMHBro_UseStatus)


        /*******************************************************************************
        * Function Name: PWMHBro_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PWMHBro_ClearFIFO(void) 
        {
            while(0u != (PWMHBro_ReadStatusRegister() & PWMHBro_STATUS_FIFONEMPTY))
            {
                (void)PWMHBro_ReadCapture();
            }
        }

    #endif /* PWMHBro_UseStatus */

#endif /* !PWMHBro_UsingFixedFunction */


/*******************************************************************************
* Function Name: PWMHBro_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void PWMHBro_WritePeriod(uint8 period) 
{
    #if(PWMHBro_UsingFixedFunction)
        CY_SET_REG16(PWMHBro_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(PWMHBro_PERIOD_LSB_PTR, period);
    #endif /* (PWMHBro_UsingFixedFunction) */
}

#if (PWMHBro_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PWMHBro_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void PWMHBro_WriteCompare(uint8 compare) \
                                       
    {
        #if(PWMHBro_UsingFixedFunction)
            CY_SET_REG16(PWMHBro_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(PWMHBro_COMPARE1_LSB_PTR, compare);
        #endif /* (PWMHBro_UsingFixedFunction) */

        #if (PWMHBro_PWMMode == PWMHBro__B_PWM__DITHER)
            #if(PWMHBro_UsingFixedFunction)
                CY_SET_REG16(PWMHBro_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG8(PWMHBro_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (PWMHBro_UsingFixedFunction) */
        #endif /* (PWMHBro_PWMMode == PWMHBro__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: PWMHBro_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMHBro_WriteCompare1(uint8 compare) \
                                        
    {
        #if(PWMHBro_UsingFixedFunction)
            CY_SET_REG16(PWMHBro_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(PWMHBro_COMPARE1_LSB_PTR, compare);
        #endif /* (PWMHBro_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: PWMHBro_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMHBro_WriteCompare2(uint8 compare) \
                                        
    {
        #if(PWMHBro_UsingFixedFunction)
            CY_SET_REG16(PWMHBro_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(PWMHBro_COMPARE2_LSB_PTR, compare);
        #endif /* (PWMHBro_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (PWMHBro_DeadBandUsed)


    /*******************************************************************************
    * Function Name: PWMHBro_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMHBro_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!PWMHBro_DeadBand2_4)
            CY_SET_REG8(PWMHBro_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            PWMHBro_DEADBAND_COUNT &= ((uint8)(~PWMHBro_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(PWMHBro_DEADBAND_COUNT_SHIFT)
                PWMHBro_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << PWMHBro_DEADBAND_COUNT_SHIFT)) &
                                                    PWMHBro_DEADBAND_COUNT_MASK;
            #else
                PWMHBro_DEADBAND_COUNT |= deadtime & PWMHBro_DEADBAND_COUNT_MASK;
            #endif /* (PWMHBro_DEADBAND_COUNT_SHIFT) */

        #endif /* (!PWMHBro_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: PWMHBro_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 PWMHBro_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!PWMHBro_DeadBand2_4)
            return (CY_GET_REG8(PWMHBro_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(PWMHBro_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(PWMHBro_DEADBAND_COUNT & PWMHBro_DEADBAND_COUNT_MASK)) >>
                                                                           PWMHBro_DEADBAND_COUNT_SHIFT));
            #else
                return (PWMHBro_DEADBAND_COUNT & PWMHBro_DEADBAND_COUNT_MASK);
            #endif /* (PWMHBro_DEADBAND_COUNT_SHIFT) */
        #endif /* (!PWMHBro_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (PWMHBro_UseStatus || PWMHBro_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWMHBro_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMHBro_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(PWMHBro_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: PWMHBro_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 PWMHBro_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(PWMHBro_STATUS_PTR));
    }

#endif /* (PWMHBro_UseStatus || PWMHBro_UsingFixedFunction) */


#if (PWMHBro_UseControl)


    /*******************************************************************************
    * Function Name: PWMHBro_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 PWMHBro_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(PWMHBro_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: PWMHBro_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMHBro_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(PWMHBro_CONTROL_PTR, control);
    }

#endif /* (PWMHBro_UseControl) */


#if (!PWMHBro_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWMHBro_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint8 PWMHBro_ReadCapture(void) 
    {
        return (CY_GET_REG8(PWMHBro_CAPTURE_LSB_PTR));
    }

#endif /* (!PWMHBro_UsingFixedFunction) */


#if (PWMHBro_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PWMHBro_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint8 PWMHBro_ReadCompare(void) 
    {
        #if(PWMHBro_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(PWMHBro_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(PWMHBro_COMPARE1_LSB_PTR));
        #endif /* (PWMHBro_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: PWMHBro_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 PWMHBro_ReadCompare1(void) 
    {
        return (CY_GET_REG8(PWMHBro_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: PWMHBro_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 PWMHBro_ReadCompare2(void) 
    {
        return (CY_GET_REG8(PWMHBro_COMPARE2_LSB_PTR));
    }

#endif /* (PWMHBro_UseOneCompareMode) */


/*******************************************************************************
* Function Name: PWMHBro_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint8 PWMHBro_ReadPeriod(void) 
{
    #if(PWMHBro_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PWMHBro_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(PWMHBro_PERIOD_LSB_PTR));
    #endif /* (PWMHBro_UsingFixedFunction) */
}

#if ( PWMHBro_KillModeMinTime)


    /*******************************************************************************
    * Function Name: PWMHBro_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMHBro_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(PWMHBro_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: PWMHBro_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 PWMHBro_ReadKillTime(void) 
    {
        return (CY_GET_REG8(PWMHBro_KILLMODEMINTIME_PTR));
    }

#endif /* ( PWMHBro_KillModeMinTime) */

/* [] END OF FILE */
