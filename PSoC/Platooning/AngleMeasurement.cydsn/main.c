#include "project.h"

#include <stdio.h>
#include <stdbool.h>

volatile bool irq_flag = false;

// here we will store the received data
unsigned char data;

// Executed when the IRQ pin triggers an interrupt
CY_ISR_PROTO(IRQ_Handler);

#define DATA_SIZE 200

uint16_t DataA[DATA_SIZE];
uint16_t DataB[DATA_SIZE];

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

uint16_t d_t1;
uint16_t d_t2;

CY_ISR(ISR_START_Handler)
{
    d_t2 = Counter_ReadCounter();
    Control_Reg_Write(0x00);
    ADC_SAR_A_StartConvert();
    ADC_SAR_B_StartConvert();
}

CY_ISR(ISR_OUT_A_Handler)
{
    ADC_SAR_A_StopConvert();
    ISR_A_done = 1;
}

CY_ISR(ISR_OUT_B_Handler)
{
    ADC_SAR_B_StopConvert();
    ISR_B_done = 1;
}

CY_ISR(IRQ_Handler)
{
    irq_flag = true;
    IRQ_ClearInterrupt();
}

int16_t calculate_angle(int16_t time_delta, float angle_conversion_factor)
{
    return time_delta * angle_conversion_factor;
}

int main(void)
{
    const angle_conversion_factor = 0;
    
    UART_Start();
    Clock_In_Start();
    Counter_Clock_Start();
    ADC_SAR_A_Start();
    ADC_SAR_B_Start();
    Maximum_Peak_Detector_A_Start();
    Maximum_Peak_Detector_B_Start();
    ADC_SAR_A_IRQ_Enable();
    ADC_SAR_B_IRQ_Enable();
    Comp_A_Start();
    Comp_B_Start();
    Control_Reg_Write(0x01);
    ISR_START_StartEx(ISR_START_Handler);
    ISR_A_StartEx(ISR_OUT_A_Handler);
    ISR_B_StartEx(ISR_OUT_B_Handler);
    
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
    
    
    CyDmaChEnable(DMA_A_Chan, 1);
    CyDmaChEnable(DMA_B_Chan, 1);
    
    CyGlobalIntEnable;
    const uint8_t RX_ADDR[5]= {0xBA, 0xAD, 0xC0, 0xFF, 0xEE};
    
    // Set the Handler for the IRQ interrupt
    isr_IRQ_StartEx(IRQ_Handler);
    
    nRF24_start();
    nRF24_set_rx_pipe_address(NRF_ADDR_PIPE0, RX_ADDR, 5);
    nRF24_start_listening();
    
    while (1) {
        
        //UART_PutString("\n");
        
        while(false == irq_flag);
            
        // Get and clear the flag that caused the IRQ interrupt,
        nrf_irq flag = nRF24_get_irq_flag();
        nRF24_clear_irq_flag(flag);
            
        LED_Write(~LED_Read());
            
        // get the data from the transmitter
        nRF24_get_rx_payload(&data, 1);
            
        // send data via UART
     //   UART_PutString("R: ");
        UART_PutChar(data);
        UART_PutCRLF(0);
            
        irq_flag = false;
    }
    char output[200];
    

    for(;;)
    {
        if (ISR_A_done && ISR_B_done) {
            CyGlobalIntDisable;
            uint16_t a = 0, b = 0;
            uint8_t ai = 0, bi = 0;
            
            for (uint8_t i = 0; i < DATA_SIZE; i++) {
                if (DataA[i] > a) {
                    a = DataA[i];
                    ai = i;
                }
                
                if (DataB[i] > b) {
                    b = DataB[i];
                    bi = i;
                }
            }
            
            int16_t angle = calculate_angle(ai - bi, angle_conversion_factor);
            uint16_t distance = (d_t2 - d_t1) * 343;
            
            ISR_A_done = ISR_B_done = 0;
            Control_Reg_Write(0x01);
            
            CyGlobalIntEnable;
        }
    }
}
