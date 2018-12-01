#include "project.h"

#include <stdio.h>
#include <stdbool.h>

// here we will store the received data
unsigned char data;

// Executed when the IRQ pin triggers an interrupt
CY_ISR_PROTO(IRQ_Handler);

#define DATA_SIZE 1500

// signal data for signal A and B
uint16_t DataA[DATA_SIZE];
uint16_t DataB[DATA_SIZE];

/* used by the DMA */
#define DMA_A_BYTES_PER_BURST 2
#define DMA_A_REQUEST_PER_BURST 1
#define DMA_A_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_A_DST_BASE (CYDEV_SRAM_BASE)

/* used by the DMA */
#define DMA_B_BYTES_PER_BURST 2
#define DMA_B_REQUEST_PER_BURST 1
#define DMA_B_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_B_DST_BASE (CYDEV_SRAM_BASE)

/* used by the DMA */
uint8 DMA_A_Chan;
uint8 DMA_A_TD[1];

/* used by the DMA */
uint8 DMA_B_Chan;
uint8 DMA_B_TD[1];

uint8_t ISR_A_done = 0;
uint8_t ISR_B_done = 0;

int8_t angle = 0;
uint32_t distance = 0;
uint16_t velocity = 0;

char output[200];

CY_ISR(ISR_START_Handler)
{
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

// network ping interrupt
CY_ISR(IRQ_Handler)
{
    // start ADC A and B when network ping has been received
    ADC_SAR_A_StartConvert();
    ADC_SAR_B_StartConvert();
    
    IRQ_ClearInterrupt();
    nrf_irq flag = nRF24_get_irq_flag();
    nRF24_clear_irq_flag(flag);

    // temp value to hold velocity data
    uint16_t data = 0;
    
    // get the data from the transmitter
    nRF24_get_rx_payload((uint8_t *)&data, 2);
    
    // because the ARM device is little endian, the data is stored in the incorrect order
    // so the data consists of the LSB|MSB of the velocity
    velocity = data << 0x08;
    velocity |= data >> 0x08;
}

int main(void)
{    
    UART_Start();
    Clock_In_Start();
    Clock_In_1_Start();
    ADC_SAR_A_Start();
    ADC_SAR_B_Start();
    Maximum_Peak_Detector_A_Start();
    Maximum_Peak_Detector_B_Start();
    ADC_SAR_A_IRQ_Enable();
    ADC_SAR_B_IRQ_Enable();

    ISR_A_StartEx(ISR_OUT_A_Handler);
    ISR_B_StartEx(ISR_OUT_B_Handler);
    NETWORK_PIN_StartEx(ISR_START_Handler); // test purpose: for simulating a network ping with a wire
    
    /* configuration of DMA, this is black magic done by the DMA Wizard */
    DMA_A_Chan = DMA_A_DmaInitialize(DMA_A_BYTES_PER_BURST, DMA_A_REQUEST_PER_BURST, 
        HI16(DMA_A_SRC_BASE), HI16(DMA_A_DST_BASE));
    DMA_A_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_A_TD[0], DATA_SIZE * 2, DMA_A_TD[0], DMA_A__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_A_TD[0], LO16((uint32)ADC_SAR_A_SAR_WRK0_PTR), LO16((uint32)DataA));
    CyDmaChSetInitialTd(DMA_A_Chan, DMA_A_TD[0]);
    
    /* configuration of DMA, this is black magic done by the DMA Wizard */
    DMA_B_Chan = DMA_B_DmaInitialize(DMA_B_BYTES_PER_BURST, DMA_B_REQUEST_PER_BURST, 
        HI16(DMA_B_SRC_BASE), HI16(DMA_B_DST_BASE));
    DMA_B_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_B_TD[0], DATA_SIZE * 2, DMA_B_TD[0], DMA_B__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_B_TD[0], LO16((uint32)ADC_SAR_B_SAR_WRK0_PTR), LO16((uint32)DataB));
    CyDmaChSetInitialTd(DMA_B_Chan, DMA_B_TD[0]);
    
    /* enable DMA channels */
    CyDmaChEnable(DMA_A_Chan, 1);
    CyDmaChEnable(DMA_B_Chan, 1);
    
    const uint8_t RX_ADDR[5]= {0xBA, 0xAD, 0xC0, 0xFF, 0xEE};
    isr_IRQ_StartEx(IRQ_Handler); // enable real network ping interrupt
    
    // enable nRF24 with settings
    nRF24_start();
    nRF24_set_rx_pipe_address(NRF_ADDR_PIPE0, RX_ADDR, 5);
    nRF24_start_listening();
  
    CyGlobalIntEnable;
    
    for(;;)
    {        
        if (ISR_A_done && ISR_B_done) {
            CyGlobalIntDisable;
            uint16_t a = 0, b = 0;
            
            // ai1, ai2 and ai3 are the first, second and third highest amplitude time indices
            // this means DataA[ai1] > DataA[ai2] > DataA[ai3]
            uint16_t ai1 = 0, ai2 = 0, ai3 = 0;
            
            // bi1, bi2 and bi3 are the first, second and third highest amplitude time indices
            // this means DataB[bi1] > DataB[bi2] > DataB[bi3]
            uint16_t bi1 = 0, bi2 = 0, bi3 = 0;
            
            // find the 3 biggest time indices of DataA and DataB
            for (uint16_t i = 0; i < DATA_SIZE; i++) {
                if (DataA[i] > a) {
                    a = DataA[i];
                    ai3 = ai2;
                    ai2 = ai1;
                    ai1 = i;
                }
                
                if (DataB[i] > b) {
                    b = DataB[i];
                    bi3 = bi2;
                    bi2 = bi1;
                    bi1 = i;
                }
            }
            
            // calculate the average ai and bi
            uint16_t ai = (ai1 + ai2 + ai3)/3.0;
            uint16_t bi = (bi1 + bi2 + bi3)/3.0;
            
            // angle from -60 to 60
            // 2.25 us per sample
            // 1 us = 0.2 degrees
            angle = (ai - bi) * 2.25 * 0.2;
            
            // distance in mm, where speed of sound is 343 mm/ms
            // first convert the time difference from us to ms, and then multiply by the speed of sound
            // use ai and bi depending on which has the closest peak to the network ping
            // The 500 value subtracted has been experimentally found
            if (ai < bi) {
                distance = (ai * 2.25)/1000.0 * 343 - 500;
            } else {
                distance = (bi * 2.25)/1000.0 * 343 - 500;
            }
            
            
            //for (uint16_t i = 0; i < DATA_SIZE; i++) {
                sprintf(output, "%d\n", angle);
                UART_PutString(output); 
            //}

            ISR_A_done = ISR_B_done = 0;
            
            CyGlobalIntEnable;
        }
    }
}
