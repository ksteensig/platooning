#include "project.h"

#include <stdio.h>

#define DATA_SIZE 1200

int16_t DataA[DATA_SIZE];
int16_t DataB[DATA_SIZE];

#define DMA_A_BYTES_PER_BURST 2
#define DMA_A_REQUEST_PER_BURST 0
#define DMA_A_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_A_DST_BASE (CYDEV_SRAM_BASE)

#define DMA_B_BYTES_PER_BURST 2
#define DMA_B_REQUEST_PER_BURST 0
#define DMA_B_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_B_DST_BASE (CYDEV_SRAM_BASE)

uint8 DMA_A_Chan;
uint8 DMA_A_TD[1];

uint8 DMA_B_Chan;
uint8 DMA_B_TD[1];

uint8_t ISR_A_done = 0;
uint8_t ISR_B_done = 0;

uint16_t inc_a = 0;
uint16_t inc_b = 0;
uint16_t inc_s = 0;

CY_ISR(ISR_START_Handler)
{
    Control_Reg_Write(0x01);
    CyDmaChEnable(DMA_A_Chan, 1);
    CyDmaChEnable(DMA_B_Chan, 1);
    inc_s++;
}

CY_ISR(ISR_A_Handler)
{
    inc_a++;
    ISR_A_done = 1;
    ADC_SAR_A_StopConvert();
}

CY_ISR(ISR_B_Handler)
{
    inc_b++;
    ISR_B_done = 1;
    ADC_SAR_B_StopConvert();
}

int main(void)
{
    
    UART_Start();
    Clock_In_Start();
    Sample_Hold_A_Start();
    Sample_Hold_B_Start();
    ADC_SAR_A_Start();
    ADC_SAR_B_Start();
    ADC_SAR_A_IRQ_Disable();
    ADC_SAR_B_IRQ_Disable();
    Comp_A_Start();
    Comp_B_Start();
    Control_Reg_Write(0x02);
    ISR_START_StartEx(ISR_START_Handler);
    ISR_A_StartEx(ISR_A_Handler);
    ISR_B_StartEx(ISR_B_Handler);
   
    DMA_A_Chan = DMA_A_DmaInitialize(DMA_A_BYTES_PER_BURST, DMA_A_REQUEST_PER_BURST, 
        HI16(DMA_A_SRC_BASE), HI16(DMA_A_DST_BASE));
    DMA_A_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_A_TD[0], DATA_SIZE * 2, DMA_A_TD[0], DMA_A__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_A_TD[0], LO16((uint32)ADC_SAR_A_SAR_WRK0_PTR), LO16((uint32)DataA));
    CyDmaChSetInitialTd(DMA_A_Chan, DMA_A_TD[0]);
    
    DMA_B_Chan = DMA_B_DmaInitialize(DMA_B_BYTES_PER_BURST, DMA_B_REQUEST_PER_BURST, 
        HI16(DMA_B_SRC_BASE), HI16(DMA_B_DST_BASE));
    DMA_B_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_B_TD[0], DATA_SIZE * 2, DMA_B_TD[0], DMA_B__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_B_TD[0], LO16((uint32)ADC_SAR_B_SAR_WRK0_PTR), LO16((uint32)DataB));
    CyDmaChSetInitialTd(DMA_B_Chan, DMA_B_TD[0]);
    
    CyGlobalIntEnable;
    
    ADC_SAR_A_StartConvert();
    ADC_SAR_B_StartConvert();
    
    char output[200];
    
    

    for(;;)
    {
        //sprintf(output, "Comp_A=%d, Comp_B=%d, Control_Reg=%d, Status_Reg=%d\n", Comp_A_GetCompare(), Comp_B_GetCompare(), Control_Reg_Read(), Status_Reg_Read());
        //UART_PutString(output);
        if (ISR_A_done && ISR_B_done) {
            CyGlobalIntDisable;
            CyDmaChDisable(DMA_A_Chan);
            CyDmaChDisable(DMA_B_Chan);
            
            ISR_A_done = ISR_B_done = 0;
            Control_Reg_Write(0x02);
            int16_t a = 0;
            int16_t b = 0; 
            uint16_t ai = 0, bi = 0;
            
            for (uint16_t i = 0; i < DATA_SIZE; i++) {
                if (DataA[i] > a) {
                    a = DataA[i];
                    ai = i;
                }
                
                DataA[i] = 0;
            }
            
            for (uint16_t i = 0; i < DATA_SIZE; i++) {
                if (DataB[i] > b) {
                    b = DataB[i];
                    bi = i;
                }
                
                DataB[i] = 0;
            }
            
            //sprintf(output, "Time delta: %d, a: %d & b: %d\n", (ai - bi), ai, bi);
            
            sprintf(output, "Amplitude %d : %d\n", DataA[ai], DataB[bi]);
            
            UART_PutString(output);
            
            inc_a = inc_b = inc_s = 0;
           
            
            CyGlobalIntEnable;
        }
    }
}
