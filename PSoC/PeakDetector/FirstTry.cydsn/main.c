/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdint.h>
#include "stdio.h"


char TransmitBufferUSB[16];
#define DATA_LENGTH 100

typedef struct {
    uint16_t time;
    int16 value;
} datapoint;

datapoint DataA[DATA_LENGTH];
datapoint DataB[DATA_LENGTH];
uint8 indexA = 0;
uint8 indexB = 0;


CY_ISR(ISR_A_Interrupt){
    //sprintf(TransmitBufferUSB, "\tEntered ISR_A - A:%d - B:%d\n\r",indexA, indexB);
    //UART_1_PutString(TransmitBufferUSB);
    
    if (!indexA && !indexB) {
        
        //sprintf(TransmitBufferUSB, "resetting counter... ");
        //UART_1_PutString(TransmitBufferUSB);
        Counter_WriteCounter(0);
        
    //sprintf(TransmitBufferUSB, "Counter reset.\n\r");
    //UART_1_PutString(TransmitBufferUSB);
    }
    
    //sprintf(TransmitBufferUSB, "Starting sample...");
    //UART_1_PutString(TransmitBufferUSB);
    //Sample 1 value
    ADC_A_StartConvert();
    //sprintf(TransmitBufferUSB, "Sample started...");
    //UART_1_PutString(TransmitBufferUSB);
    
    //Wait for result
    while(!ADC_A_IsEndConversion(ADC_A_WAIT_FOR_RESULT)){}
    //sprintf(TransmitBufferUSB, "Sample ended.\n\rGetting results...");
    //UART_1_PutString(TransmitBufferUSB);
    
    //Save result to 'value'
    
    DataA[indexA] = (datapoint) {ADC_A_GetResult16(), 
                                 Counter_ReadCounter()};
    indexA++;
    //sprintf(TransmitBufferUSB, "Got results okay. DataA[%d].time = %d\n\r", indexA, DataA[indexA].time);
    //UART_1_PutString(TransmitBufferUSB);
    
}

CY_ISR(ISR_B_Interrupt){
    //sprintf(TransmitBufferUSB, "Entered ISR_B - A:%d - B:%d\n\r",indexA, indexB);
    //UART_1_PutString(TransmitBufferUSB);
    
    
    if (!indexB && !indexB) {
        Counter_WriteCounter(0);
    }
    
    //Sample 1 value
    ADC_B_StartConvert();
    //Wait for result
    while(!ADC_B_IsEndConversion(ADC_B_WAIT_FOR_RESULT)){}
    
    
    //Save result to 'value'
    DataB[indexB] = (datapoint) {ADC_B_GetResult16(),
                                 Counter_ReadCounter()};
    indexB++;
    
}

int32_t calc_delta_time() {
    uint8_t DataA_Pos = 0;
    uint8_t DataB_Pos = 0;
    
    int16_t tmp_amp = 0;
    
    for (uint8_t i = 0; i < DATA_LENGTH; i++) {
        if (DataA[i].value > tmp_amp) {
            DataA_Pos = i;
        }
    }
    
    tmp_amp = 0;
    
    for (uint8_t i = 0; i < DATA_LENGTH; i++) {
        if (DataB[i].value > tmp_amp) {
            DataB_Pos = i;
        }
    }
    
    return DataA[DataA_Pos].time - DataB[DataB_Pos].time;
}

int8_t convert_time_to_angle(float time_to_angle_factor, 
                                    int32_t time_delta) {
    return (int8_t)(time_to_angle_factor * time_delta);
}

int main(void)
{    
    Mixer_PD_A_Start();
    Mixer_PD_A_Start();
    Comp_PD_A_Start();
    Comp_PD_B_Start();
    Mixer_A_Start();
    Mixer_B_Start();
    ADC_A_Start();
    ADC_B_Start();
    UART_1_Start();
    sprintf(TransmitBufferUSB,"\n\n\n\n\rHello World\n\r");
    UART_1_PutString(TransmitBufferUSB);
    
    ISR_PIN_A_StartEx(ISR_A_Interrupt);
    ISR_PIN_B_StartEx(ISR_B_Interrupt);
    
    
    sprintf(TransmitBufferUSB, "A:%d - B:%d\n\r",indexA, indexB);
    UART_1_PutString(TransmitBufferUSB);
    CyGlobalIntEnable; /* Enable global interrupts. */
    sprintf(TransmitBufferUSB, "\n\n\n\rISR IS FIXED\n\r");
    UART_1_PutString(TransmitBufferUSB);
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    const float time_to_angle_factor = 0.2058;
    int8_t angle = 0;
    sprintf(TransmitBufferUSB, "A:%d - B:%d\n",indexA, indexB);
    UART_1_PutString(TransmitBufferUSB);
    
    for(;;)
    {
        /* if DataA and DataB are full,
         * then calculate the angle and reset indices
         */
        sprintf(TransmitBufferUSB, "A:%d - B:%d\n\r",indexA, indexB);
        UART_1_PutString(TransmitBufferUSB);
        if (indexA > 100 && indexB > 100) {
            CyGlobalIntDisable;
            int32_t time_delta = calc_delta_time();
            angle = convert_time_to_angle(time_to_angle_factor, 
                                          time_delta);
            sprintf(TransmitBufferUSB, "%d\n", angle);
            UART_1_PutString(TransmitBufferUSB);
            
            indexA = indexB = 0;
            CyGlobalIntEnable;
        }
    }
}

/* [] END OF FILE */
