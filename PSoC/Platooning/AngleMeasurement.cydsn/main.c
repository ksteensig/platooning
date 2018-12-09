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

/* Defines for DMA_A */
#define DMA_A_BYTES_PER_BURST 2
#define DMA_A_REQUEST_PER_BURST 1
#define DMA_A_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_A_DST_BASE (CYDEV_PERIPH_BASE)

/* Variable declarations for DMA_A */
uint8 DMA_A_Chan;
uint8 DMA_A_TD[1];

/* Defines for DMA_B */
#define DMA_B_BYTES_PER_BURST 2
#define DMA_B_REQUEST_PER_BURST 1
#define DMA_B_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_B_DST_BASE (CYDEV_PERIPH_BASE)

/* Variable declarations for DMA_B */
uint8 DMA_B_Chan;
uint8 DMA_B_TD[1];

#define DMA_A_Filter_BYTES_PER_BURST 2
#define DMA_A_Filter_REQUEST_PER_BURST 1
#define DMA_A_Filter_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_A_Filter_DST_BASE (CYDEV_SRAM_BASE)

/* Variable declarations for DMA_A_Filter */
uint8 DMA_A_Filter_Chan;
uint8 DMA_A_Filter_TD[1];

#define DMA_B_Filter_BYTES_PER_BURST 2
#define DMA_B_Filter_REQUEST_PER_BURST 1
#define DMA_B_Filter_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_B_Filter_DST_BASE (CYDEV_SRAM_BASE)

/* Variable declarations for DMA_B_Filter */
uint8 DMA_B_Filter_Chan;
uint8 DMA_B_Filter_TD[1];

volatile uint8_t ISR_A_done = 0;
volatile uint8_t ISR_B_done = 0;

float angle = 0; // angle between front wheel of platoon follower compared to the platoon leader back wheels
int16_t distance = 0; // distance between follower and leader
volatile uint8_t velocity = 0; // platoon leader duty cycle
volatile int8_t leader_angle = 0;
volatile int8_t old_leader_angle = 0;
volatile int8_t old_old_leader_angle = 0;

char output[200];

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

int rec = 1;

// network ping interrupt
CY_ISR(IRQ_Handler)
{
    //UART_PutString("Enter IRQ\n");
    //CyWdtClear();
    Pin_3_Write(1);
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
    //nRF24_stop_listening();
    velocity = data[0];
    old_old_leader_angle = old_leader_angle;
    old_leader_angle = leader_angle;
    leader_angle = data[1];
    //UART_PutString("Exit IRQ\n");
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
    
    Filter_Start();
    Filter_SetCoherency(Filter_CHANNEL_A, Filter_KEY_MID);
    Filter_SetCoherency(Filter_CHANNEL_B, Filter_KEY_MID);

    /* DMA Configuration for DMA_A */
    DMA_A_Chan = DMA_A_DmaInitialize(DMA_A_BYTES_PER_BURST, DMA_A_REQUEST_PER_BURST, 
        HI16(DMA_A_SRC_BASE), HI16(DMA_A_DST_BASE));
    DMA_A_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_A_TD[0], DATA_SIZE * 2, DMA_A_TD[0], DMA_A__TD_TERMOUT_EN);
    CyDmaTdSetAddress(DMA_A_TD[0], LO16((uint32)ADC_SAR_A_SAR_WRK0_PTR), LO16((uint32)Filter_STAGEA_PTR));
    CyDmaChSetInitialTd(DMA_A_Chan, DMA_A_TD[0]);
    CyDmaChEnable(DMA_A_Chan, 1);
    
    /* DMA Configuration for DMA_B */
    DMA_B_Chan = DMA_B_DmaInitialize(DMA_B_BYTES_PER_BURST, DMA_B_REQUEST_PER_BURST, 
        HI16(DMA_B_SRC_BASE), HI16(DMA_B_DST_BASE));
    DMA_B_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_B_TD[0], DATA_SIZE * 2, DMA_B_TD[0], DMA_B__TD_TERMOUT_EN);
    CyDmaTdSetAddress(DMA_B_TD[0], LO16((uint32)ADC_SAR_B_SAR_WRK0_PTR), LO16((uint32)Filter_STAGEB_PTR));
    CyDmaChSetInitialTd(DMA_B_Chan, DMA_B_TD[0]);
    CyDmaChEnable(DMA_B_Chan, 1);

    DMA_A_Filter_Chan = DMA_A_Filter_DmaInitialize(DMA_A_Filter_BYTES_PER_BURST, DMA_A_Filter_REQUEST_PER_BURST, 
        HI16(DMA_A_Filter_SRC_BASE), HI16(DMA_A_Filter_DST_BASE));
    DMA_A_Filter_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_A_Filter_TD[0], DATA_SIZE, DMA_A_Filter_TD[0], DMA_A_Filter__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_A_Filter_TD[0], LO16((uint32)Filter_HOLDA_PTR), LO16((uint32)DataA));
    CyDmaChSetInitialTd(DMA_A_Filter_Chan, DMA_A_Filter_TD[0]);
    CyDmaChEnable(DMA_A_Filter_Chan, 1);

    DMA_B_Filter_Chan = DMA_B_Filter_DmaInitialize(DMA_B_Filter_BYTES_PER_BURST, DMA_B_Filter_REQUEST_PER_BURST, 
        HI16(DMA_B_Filter_SRC_BASE), HI16(DMA_B_Filter_DST_BASE));
    DMA_B_Filter_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_B_Filter_TD[0], DATA_SIZE * 2, DMA_B_Filter_TD[0], DMA_B_Filter__TD_TERMOUT_EN | CY_DMA_TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_B_Filter_TD[0], LO16((uint32)Filter_HOLDB_PTR), LO16((uint32)DataB));
    CyDmaChSetInitialTd(DMA_B_Filter_Chan, DMA_B_Filter_TD[0]);
    CyDmaChEnable(DMA_B_Filter_Chan, 1);
    
    const uint8_t RX_ADDR[5]= {0xBA, 0xAD, 0xC0, 0xFF, 0xEE};
    isr_IRQ_StartEx(IRQ_Handler); // enable real network ping interrupt
    
    // enable nRF24 with settings
    nRF24_start();
    nRF24_set_rx_pipe_address(NRF_ADDR_PIPE0, RX_ADDR, 5);
    nRF24_start_listening();
    
    // distance control system variables
    int16_t err_dist = 0; // error
    const int16_t reference_dist = 300; // input
    const float Kp_dist = -0.5; // control system value for P-controller (spørg casper og bjørnefar)
    int32_t duty_cycle_dist = 0;
    
    // angle control system variables
    float Kp_ang = -0.7;
    float Kd_ang = -0.01;
    float Ki_ang = -0.1;
    //const float vel_ang = 2.5;
    //const float width_car = 0.17;
    int16_t servo_signal = 0;
    const uint16_t t_right = 1035;
    const uint16_t t_left = 1694;
    const uint16_t t_center = (t_left + t_right)/2;
    const uint8_t theta_tot = 60;
    float angle_servo = 0;
    float prev_error_angle = 0;
    float error_angle = 0;
    uint8_t z_point_angle = 0;
    int16_t servo_signal_RB[4] = {0,0,0,0};
    int8_t servo_signal_counter = 0;
    int16_t servo_signal_avg = 0;
    
    int integrations = 0;
    
    float previous_angle2 = 0;
    float previous_angle1 = 0;
    
    float derivative = 0;
    float integral = 0;
    
    //CyWdtStart(CYWDT_16_TICKS, CYWDT_LPMODE_NOCHANGE);
    CyGlobalIntEnable;
    
    for(;;)
    {
        if (ISR_A_done && ISR_B_done) {
            CyGlobalIntDisable;
            //UART_PutString("Enter handler\n");
            rec = 0;
            
            // defining a and b for the highest amplitude of the signals
            uint16_t a = 0, b = 0;
            uint16_t ai = 0, bi = 0;
            
            // find the 3 biggest time indices of DataA and DataB
            for (uint16_t i = 0; i < DATA_SIZE; i++) {
                if (DataA[i] > a) {
                    a = DataA[i];
                    ai = i;
                }
                
                if (DataB[i] > b) {
                    b = DataB[i];
                    bi = i;
                }
            }
            
            previous_angle2 = previous_angle1;
            previous_angle1 = angle;
            
            // angle from -60 to 60
            // 2.25 us per sample
            // 1 us = 0.2 degrees
            // 0.45 = 2.25 * 0.2
            angle = (ai - bi) * 0.45;

            if (angle > 60 || angle < -60) {
                angle = previous_angle1;
            }
            
            //sprintf(output, "%d\n", angle);
            //UART_PutString(output);
            // distance in mm, where speed of sound is 343 mm/ms
            // first convert the time difference from us to ms, and then multiply by the speed of sound
            // use ai and bi depending on which has the closest peak to the network ping
            // The 500 value subtracted has been experimentally found
            // 0.77 = 2.25/1000.0 * 343
            if (ai < bi) {
                distance = ai*0.77 - 100;
            } else {
                distance = bi * 0.77 -100;
            }

            ISR_A_done = ISR_B_done = 0;
                
            // CONTROL SYSTEM - DISTANCE:
            
            err_dist = reference_dist - distance;
            duty_cycle_dist = Kp_dist * err_dist + velocity;
            
            // if duty_cycle ends up being negative, it needs to be capped at 0
            if (duty_cycle_dist < 0)
            {
                duty_cycle_dist = 0;
            }else if(duty_cycle_dist > 150){
                duty_cycle_dist = 150;
            }
            
            PWM_H_BRIDGE_WriteCompare(duty_cycle_dist);
            
            
        //CONTROL SYSTEM - ANGLE:
            
            float weighted_Kp_angle;
            
            weighted_Kp_angle = Kp_ang;
            
            if (velocity) {
                if (!(Kp_ang/(velocity*0.031*0.58) < Kp_ang)) {
                    weighted_Kp_angle = Kp_ang/(velocity*0.031*0.58);
                }
            }
            
            
            error_angle = z_point_angle - (angle + previous_angle1 + previous_angle2)/3.0;
            derivative = (error_angle - prev_error_angle) / 0.0067; // 0.01 deltatime
            //integral = integral + error_angle * 0.0067;
            angle_servo = weighted_Kp_angle * error_angle /*+ derivative*Kd_ang*/;
            prev_error_angle = error_angle;
            if(angle_servo > 30){
                angle_servo = 30;
            } else if(angle_servo < -30){
                angle_servo = -30;
            }
            
            // ((t_right - t_left)/theta_tot) approx -11
            servo_signal = (angle_servo + old_old_leader_angle/2.0) * -11 + t_center - 40;
            
            if(servo_signal_counter == 3){
                servo_signal_RB[servo_signal_counter] = servo_signal;
                servo_signal_counter = 0;
            }else{
                servo_signal_RB[servo_signal_counter] = servo_signal;
                servo_signal_counter++;
            }
            servo_signal_avg = (servo_signal_RB[0] + servo_signal_RB[1] + servo_signal_RB[2])/3;
                        
            PWM_SERVO_WriteCompare(servo_signal_avg);
            
            Pin_3_Write(0);
            
            //sprintf(output, "%d\n", velocity);
            //UART_PutString(output);
            
            //nRF24_start_listening();
            
            //UART_PutString("Exit Handler\n");
            
            CyGlobalIntEnable;
        }
    }
}

