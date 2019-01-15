/*
 * Leader code
 *      Updates 15/01-19 include:
 *      -   restructuring of code (Kristoffer/Alexander)
 * The nrf24 radio is configured to transmit 2 byte payload.
 */

#include "project.h"

#include <stdbool.h>
#include <stdio.h>

// Debugging
#define DEBUGSPEED false
#define DEBUGTXDATA false
#define DEBUGALL false
char txBuffer[100];

// Measured values from TF-3 controller
volatile uint16 steeringVal = 1500; // Initial value is to avoid speeding at startup
volatile uint16 throttleVal = 1550; // Initial value is to avoid speeding at startup

// Ring buffer variables
const unsigned char throttleBufferSize = 5;
long throttleSum=5*1500;
uint16 throttleFiltered = 1550;
uint16 throttleBuffer[5]={1550,1550,1550,1550,1550};
uint8 throttleBufferIndex = 0;

// NRF data to transmit.
unsigned char txData[2] = {0,0};

// Left and Right timings of servo motor.
const uint16 t_left  = 1750;
const uint16 t_right = 1100;

// Flags for loop
bool throttleFlag = 1;
bool steeringFlag = 1;
bool sendFlag = 1;

// Other variables
uint8_t MAX_SPEED = 255;

CY_ISR(isr_SEND) //Activated from a timer in topdesign, every 10 ms.
{
    // Just set flag for the main loop
    sendFlag=1;

}


// saves timer value and calculate the throttleValue
CY_ISR(isr_THROTTLE_FALL)
{
    // Timer_ReadCapture is counting from 10000 down to microseconds of HIGH time on throttle signal.
    throttleVal = (10000-throttleTimer_ReadCapture());

    // Failsafe, If outside range 900 - 2100, reset throttleval to neutral position.
    if(throttleVal > 2100 || throttleVal < 900)
    {
        throttleVal = 1550;
    }

    // Capping to specific values, used for mapping and maths in SetMotorPWM().
    if (throttleVal < 1000)
    {
        throttleVal = 1000;
    }
    else if (throttleVal > 2000)
    {
        throttleVal = 2000;
    }
    throttleFlag = 1; // Also set flag

}


CY_ISR(isr_STEERING_FALL)
{
    // SteeringTimer_ReadCapture is counting from 10000 down to microseconds of HIGH time on steering signal.
    steeringVal = (10000-steeringTimer_ReadCapture());
    steeringFlag = 1; // Also set flag

    // Failsafe
    if(steeringVal > (t_left + 200) || steeringVal < (t_right - 200))
    {
        steeringVal = (t_left + t_right) / 2;
    }

    // Capping for use in flag function
    if(steeringVal > t_left)
    {
        steeringVal = t_left;
    }
    else if(steeringVal < t_right)
    {
        steeringVal = t_right;
    }

}

// Function used to map a value from one range to another. Stolen from https://forum.arduino.cc/index.php?topic=280819.0
int16_t map(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
  return (x - in_min) * (out_max - out_min + 1) / (in_max - in_min + 1) + out_min;

}


// remove old measurement from PWMSum add new and return average of sum.
uint16 throttleFilter(uint16 Measurement)
{
    // Remove old data from throttleSum
    throttleSum -= throttleBuffer[throttleBufferIndex];

    // Save new data in ringbuffer and add to throttleSum.
    throttleBuffer[throttleBufferIndex] = Measurement;
    throttleSum += throttleBuffer[throttleBufferIndex];

    // Increment index and check for wrap-arround.
    throttleBufferIndex++;
    if(throttleBufferIndex >= throttleBufferSize)
    {
        throttleBufferIndex=0;
    }

    //return average
    return throttleSum / throttleBufferSize;
}

void SetMotorPWM(uint16 Speed) // Speed should range 1000-2000
{
    if(Speed<1500) // set forward speed
    {
        if(Speed < 1000){ Speed = 1000;} // Limit lower value

        P1_Write(1); // Enables forward driving
        P2_Write(0); // Disables backwards driving
        PWMHBro_WriteCompare1(map(Speed, 1499, 1000, 0, MAX_SPEED));
        PWMHBro_WriteCompare2(0);
    }
    else if(Speed > 1600) // short PWM brake
    {
        /*  Short the motors wires through ground. Meaning we close the upper
        *   FETS and open the lower FETS. See Schematic for H-bridge */

        P1_Write(0);                // Close the High-Side MOSFET
        P2_Write(0);                // Close the other High-Side MOSFET
        PWMHBro_WriteCompare1(255); // Open the Low-Side MOSFET
        PWMHBro_WriteCompare2(255); // Open the other Low-Side MOSFET
        // PWM_WriteCompare1((Speed-1600)/1.6);
    }
    else // coast mode
    {
        P1_Write(0);
        P2_Write(0);
        PWMHBro_WriteCompare1(0);
        PWMHBro_WriteCompare2(0);
    }

    if(DEBUGSPEED || DEBUGALL)
    {
        sprintf(txBuffer, "Speed = %d, mapped to: %d\n\r", Speed, map(Speed, 1499, 1000, 0, MAX_SPEED));
        UART_PutString(txBuffer);
    }

}


int main(void)
{

    // interrupt setup for throttle, steering and send
    CyGlobalIntEnable;
    isr_send_StartEx(isr_SEND);
    isr_throttle_Fall_StartEx(isr_THROTTLE_FALL);
    isr_steering_Fall_StartEx(isr_STEERING_FALL);

    // Throttle component init
    throttleTimer_Start();
    Clock_Start();

    // Send component init
    PWMSend_Start();

    // H-bridge component init
    PWMHBro_Start();
    HBroClock_Start();

    // Servo component init
    PWMServo_Start();
    ServoClock_Start();
    steeringTimer_Start();

    // uart init
    UART_Start();

    // nrf24L01+ init
    const uint8_t TX_ADDR[5]= {0xBA, 0xAD, 0xC0, 0xFF, 0xEE}; // This might be the MAC adress on the receiver... Need someone to confirm.
    nRF24_start();
    nRF24_set_rx_pipe_address(NRF_ADDR_PIPE0, TX_ADDR, 5);    // set tx pipe address to match the receiver address
    nRF24_set_tx_address(TX_ADDR, 5);
    nRF24_set_tx_address(TX_ADDR, 5);

    while (1)
    {

        if(throttleFlag) // throttleFlag is set in CY_ISR(isr_THROTTLE_FALL)
        {
            throttleFlag = 0;
            throttleFiltered = throttleFilter(throttleVal);
            SetMotorPWM(throttleFiltered);
        }

        if(steeringFlag)
        {
            // set servo PWM time and reset steeringFlag
            PWMServo_WriteCompare(steeringVal);
            steeringFlag = 0;
        }

        if(sendFlag)
        {

            // sets Throttle value sendt to PF car
            if(throttleFiltered<1500) // If throttle is pressed throttleFiltered will be under 1500.
            {
                txData[0] = map(throttleFiltered, 1499, 1000, 0, MAX_SPEED);
            }
            else
            {
                txData[0] = 0;
            }

            txData[1]=-(steeringVal-((t_left+t_right)/2))/11;

            if(DEBUGTXDATA || DEBUGALL)
            {
                sprintf(txBuffer,"ThrotFilt: %d\t txData: %d\t txData[1]: %d\t steeringVal: %d\t \n\r", throttleFiltered, txData[0], txData[1], steeringVal);
                UART_PutString(txBuffer);
            }

            //nRF24_set_tx_address(TX_ADDR, 5);

            nRF24_transmit(txData, 2);

            speaker_Write(1);
            CyDelayUs(200);
            speaker_Write(0);

            LED_Write(!LED_Read());
            sendFlag=0;
        }
    }
}

/* [] END OF FILE */
