/*
 * 01_Basic_Tx
 * 
 * The nrf24 radio is configured to transmit 1 byte payload.
 */

#include "project.h"

#include <stdbool.h>
#include <stdio.h>

volatile uint16 SteeringVal = 1500;
volatile uint16 ThrottleVal = 1550;

    const unsigned char PWMBufferSize = 5;
    long PWMSum=5*1500;
    uint16 PWMFiltered = 1550;
    uint16 PWMBuffer[5]={1550,1550,1550,1550,1550};
    bool newThrottleVal = 1;
    bool newSteeringVal = 1;
    bool newSendVal = 1;
    uint8 bufIndex = 0;
    unsigned char txData[2] = {0,0};
    
    
    const uint16 t_left  = 1750;
    const uint16 t_right = 1100;
 //   uint16 t_center=(t_left+t_right)/2;
    
    
    
CY_ISR(isr_SEND)
{
  //  LED_Write(1);
newSendVal=1;

}

// saves timer value and calculate the throttleValue 
CY_ISR(isr_THROTTLE_FALL)
{
    ThrottleVal = (10000-Timer_ReadCapture());
    
    uint16_t PWMVal = -ThrottleVal/4+375;
    
    if (PWMVal > 60 && PWMVal < 90) {
        PWMVal = 60;
    } else if (PWMVal > 90) {
        PWMVal = 130;
    }
    
    ThrottleVal = -(PWMVal - 375) * 4;
    
    newThrottleVal = 1;

}

CY_ISR(isr_STEERING_FALL)
{
    SteeringVal = (10000-SteeringTimer_ReadCapture());
    newSteeringVal = 1;

}

// remove old measurement from PWMSum add new and return average of sum.
uint16 PWMFilter(uint16 Measurement)
{
    //if value out of limits set failsafe value 1550
    if(Measurement>2100)
    {
        Measurement=1550;
    }
    if(Measurement<900)
    {
        Measurement=1550;
    }
    
    PWMSum -= PWMBuffer[bufIndex];
    PWMBuffer[bufIndex] = Measurement;
    PWMSum+=PWMBuffer[bufIndex];
    bufIndex++;
    
    if(bufIndex>=PWMBufferSize)
    {
        bufIndex=0;
    }
    return PWMSum/PWMBufferSize;
}

void SetPWM(uint16 Speed)
{
    //set forward speed (0-250)
    if(Speed<1500)
    {        
    //limit lower value used for forward speed        
        if(Speed < 1000)
        {
            Speed=1000;
        }
        
        P1_Write(1);
        P2_Write(0);
        PWMHBro_WriteCompare1((-Speed/4)+375);
        PWMHBro_WriteCompare2(0);
    }
    // pasive PWM brake (0-250)
    else if(Speed > 1600)
    {
        P1_Write(0);
        P2_Write(0);
        PWMHBro_WriteCompare1(255);
        PWMHBro_WriteCompare2(255);
        // PWM_WriteCompare1((Speed-1600)/1.6);
    }
    // coast mode (disabled by setting pwm to 255)
    else
    {
        P1_Write(0);
        P2_Write(0);
        PWMHBro_WriteCompare1(0);
        PWMHBro_WriteCompare2(0);
    }
}

    
int main(void)
{
      



    // interrupt setup for throttle and send 
    CyGlobalIntEnable;
       
    isr_send_StartEx(isr_SEND);
    isr_throttle_Fall_StartEx(isr_THROTTLE_FALL);
    isr_steering_Fall_StartEx(isr_STEERING_FALL);
    
    // Throttle component init
    Timer_Start();
    Clock_Start();  
    
    // Send component init
    PWMSend_Start();
    
    // H-bridge component init
    PWMHBro_Start();
    HBroClock_Start();
    
    // Servo component init
    PWMServo_Start();
    ServoClock_Start();
    SteeringTimer_Start();

    
    // uart init
    UART_Start();
    UART_PutChar(0x0C);
    UART_PutString("Basic project: Tx\r\n");
    
    // nrf24L01+ init
    const uint8_t TX_ADDR[5]= {0xBA, 0xAD, 0xC0, 0xFF, 0xEE};
    nRF24_start();
    nRF24_set_rx_pipe_address(NRF_ADDR_PIPE0, TX_ADDR, 5);      // set tx pipe address to match the receiver address
    nRF24_set_tx_address(TX_ADDR, 5);
    nRF24_set_tx_address(TX_ADDR, 5);       
        
    
    while (1)
    {
                   
        if(newThrottleVal)
        {
            newThrottleVal=0;
            PWMFiltered=PWMFilter(ThrottleVal);
            SetPWM(PWMFiltered); 
        }
        
        if(newSteeringVal)
        {
            // if steeringVal is out of range center servo
          /*  if(SteeringVal>1900)
            {
                SteeringVal=(1900+1000)/2;
            }
            if(SteeringVal<1000)
            {
                SteeringVal=(1900+1000)/2;
            }*/
            // set servoval and reset steeringVal flag
            PWMServo_WriteCompare(SteeringVal);
            newSteeringVal=0;
        }
        
        
        if(newSendVal)
        {
 
        // sets Throttle value sendt to PF car
        if(PWMFiltered<1500)
        {    
            txData[0] =( -PWMFiltered/4 )+375;
        }
        else
        {
            txData[0] = 0;
        }
        

        
        //txData[1]=SteeringVal/(((t_right-t_left)/60)+((t_left+t_right)/2));
        
         txData[1]=-(SteeringVal-((t_left+t_right)/2))/11;
               
     
            char txBuffer[100];
            
            //sprintf(txBuffer,"ThFilt:%d\t txData: %d\t steerPwm %d\t ServoPwm: %d\n",PWMFiltered,txData[0],SteeringVal,txData[1]);
            //UART_PutString(txBuffer);
              
            nRF24_set_tx_address(TX_ADDR, 5);    
     
    
      //UART_PutChar(0x0C);
       // UART_PutString("Type a letter...");
        // wait until we get a letter to send
        //while(0 == UART_GetRxBufferSize());
        // get the letter
        //data = UART_GetChar();
        

        nRF24_transmit(txData, 2);
        speaker_Write(1);
        CyDelayUs(200);
        speaker_Write(0);
        
        //UART_ClearRxBuffer();
        //UART_ClearTxBuffer();  
        LED_Write(!LED_Read()); 
        newSendVal=0;
        }
    }
}



/* [] END OF FILE */
