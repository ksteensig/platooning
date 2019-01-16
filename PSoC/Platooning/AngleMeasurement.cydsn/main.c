#include "project.h"

#include "dma_initialization.h"
#include "motor.h"
#include "servo.h"
#include "sensor.h"

#include <stdio.h>
#include <stdbool.h>

// Executed when the IRQ pin triggers an interrupt
CY_ISR_PROTO(IRQ_Handler);

/* NRF address */
const uint8_t RX_ADDR[5]= {0xBA, 0xAD, 0xC0, 0xFF, 0xEE};

#define DATA_SIZE 2500

// signal data for signal A and B
uint16_t DataA[DATA_SIZE];
uint16_t DataB[DATA_SIZE];

volatile uint8_t ISR_A_done = 0;
volatile uint8_t ISR_B_done = 0;

char output[200];

volatile sensor_t sensor_data;

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
    CyWdtClear();
    // start ADC A and B when network ping has been received
    ADC_SAR_A_StartConvert();
    ADC_SAR_B_StartConvert();
    
    IRQ_ClearInterrupt();
    nrf_irq flag = nRF24_get_irq_flag();
    nRF24_clear_irq_flag(flag);

    // temp value to hold velocity data
    uint8_t data[2];
    
    // get the data from the transmitter
    nRF24_get_rx_payload(data, 2);
    
    // data[0] = velocity, data[1] = leader_angle
    sensor_update_feedforward_params(&sensor_data, data[0], data[1]);
}

int main(void)
{   
    /* initialize components */
    UART_Start();
    Clock_In_Start();
    Clock_In_1_Start();
    ADC_SAR_A_Start();
    ADC_SAR_B_Start();
    Maximum_Peak_Detector_A_Start();
    Maximum_Peak_Detector_B_Start();
    ADC_SAR_A_IRQ_Enable();
    ADC_SAR_B_IRQ_Enable();
    PWM_H_BRIDGE_Start();
    Clock_1_Start();
    PWM_SERVO_Start();
    Clock_2_Start();
    ISR_A_StartEx(ISR_OUT_A_Handler);
    ISR_B_StartEx(ISR_OUT_B_Handler);
    killswitchP_Write(1);
    N2_Write(0);
    P1_Write(1);
    P2_Write(0);
    
    DMA_A_CHAN_INIT(DATA_SIZE);
    DMA_B_CHAN_INIT(DATA_SIZE);
    DMA_A_FILTER_INIT(DATA_SIZE, DataA);
    DMA_B_FILTER_INIT(DATA_SIZE, DataB);
    
    /* start filter */
    Filter_Start();
    
    /*
     * the filter can filter 32-values
     * Filter_KEY_MID makes the filters trigger on byte 2 or 3 being updated
    */
    Filter_SetCoherency(Filter_CHANNEL_A, Filter_KEY_MID);
    Filter_SetCoherency(Filter_CHANNEL_B, Filter_KEY_MID);
    
    // enable real network ping interrupt
    isr_IRQ_StartEx(IRQ_Handler);
    
    // start the nRF24 with settings
    nRF24_start();
    nRF24_set_rx_pipe_address(NRF_ADDR_PIPE0, RX_ADDR, 5);
    nRF24_start_listening();
    
    // reference_dist = 300, Kp = -0.5
    motor_t motor = motor_init(300, -0.5);
    
    // reference_angle = 0, Kp = -0.5
    servo_t servo = servo_init(0, -0.7);
    
    // start watchdog timer
    CyWdtStart(CYWDT_16_TICKS, CYWDT_LPMODE_NOCHANGE);
    CyGlobalIntEnable;
    
    for(;;)
    {
        if (ISR_A_done && ISR_B_done) {
            CyGlobalIntDisable;
           
            sensor_update_data(&sensor_data, DataA, DataB, DATA_SIZE);
                
            // CONTROL SYSTEM - DISTANCE:
            
            motor_update(&motor, sensor_data.distance, sensor_data.velocity);
            
            //CONTROL SYSTEM - ANGLE:
            
            servo_update(&servo, sensor_data.angle, sensor_data.leader_angle, sensor_data.velocity);
            
            ISR_A_done = ISR_B_done = 0;
            
            CyGlobalIntEnable;
        }
    }
}

