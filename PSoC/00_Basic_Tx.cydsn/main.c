/*
 * 01_Basic_Tx
 * 
 * The nrf24 radio is configured to transmit 1 byte payload.
 */

#include "project.h"

#include <stdbool.h>
#include <stdio.h>


int main(void)
{
    const uint8_t TX_ADDR[5]= {0xBA, 0xAD, 0xC0, 0xFF, 0xEE};
    unsigned char data = '2';
    
    CyGlobalIntEnable;
    
    UART_Start();
    UART_PutChar(0x0C);
    UART_PutString("Basic project: Tx\r\n");
    
    nRF24_start();
    nRF24_set_rx_pipe_address(NRF_ADDR_PIPE0, TX_ADDR, 5);
    // set tx pipe address to match the receiver address
    nRF24_set_tx_address(TX_ADDR, 5);

    while (1) {
    
      //UART_PutChar(0x0C);
        //UART_PutString("Type a letter...");
        // wait until we get a letter to send
        //while(0 == UART_GetRxBufferSize());
        // get the letter
        //data = UART_GetChar();
        
       //UART_PutString("\r\nSending letter ");
        //UART_PutCRLF(data);
        nRF24_transmit(&data, 1);
        //UART_ClearRxBuffer();
        //UART_ClearTxBuffer();
        CyDelay(1);
    }
}



/* [] END OF FILE */
