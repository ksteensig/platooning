/****************************************************************************
* This file is part of the nRF24 Custom Component for PSoC Devices.
*
* Copyright (C) 2017 Carlos Diaz <carlos.santiago.diaz@gmail.com>
*
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
****************************************************************************/

/**
* @file nRF24_HAL.c
*
* @brief The nRF24 radio is controlled via SPI, this file have all the SPI
* communication between the PSoC and the nRF24 radio.
*/

#include <stdint.h>
#include <string.h>

#include "nRF24_CONFIG.h"
#include "nRF24_HAL.h"

#if defined (_PSOC6)
# include "gpio/cy_gpio.h"
#else // (_PSOC_UDB) || (_PSOC4)
# if defined (_PSOC4_SCB)
#  include "SPI_SPI_UART.h" // may be no longer necessary
# endif
# include "CE.h"
# include "SS.h"
#endif

/* GPIO Control */

/**
 * GPIO control in PSoC6 and PSoC4/PSoC5LP is a little bit different,
 * so here we try to unify them.
 *
 * @param[in] nrf_gpio state 
 */
void nRF24_ss_write(nrf_gpio state)
{
    if (GPIO_CLEAR == state) {
#if defined (_PSOC6)
    Cy_GPIO_Clr(SS_PORT, SS_NUM);
#else // _PSoC4_SCB | _PSOC_UDB
    SS_Write(0);
#endif
    } else { // GPIO_SET
#if defined (_PSOC6)
    Cy_GPIO_Set(SS_PORT, SS_NUM);
#else // _PSoC4_SCB | _PSOC_UDB
    SS_Write(1);
#endif
    }
}

void nRF24_ce_write(nrf_gpio state)
{
    if (GPIO_CLEAR == state) {
#if defined (_PSOC6)
    Cy_GPIO_Clr(CE_PORT, CE_NUM);
#else // _PSoC4_SCB | _PSOC_UDB
    CE_Write(0);
#endif
    } else { // GPIO_SET
#if defined (_PSOC6)
    Cy_GPIO_Set(CE_PORT, CE_NUM);
#else // _PSoC4_SCB | _PSOC_UDB
    CE_Write(1);
#endif
    }
}

// xfer xfer_size bytes to the nrf24 radio and get back xfer_size bytes back
// from it.
// in[0] is always the NRF_COMMAND
// out[0] is always the STATUS_REGISTER
//
// Example of use:
// - To read the radio status register and save it in status_reg variable:
//
// uint8_t NRF_DUMMY = 0xFF;
// uint8_t status_reg = 0;
// nrf24_spi_xfer(&NRF_DUMMY, &status_reg, 1);
//
// TODO:
// This function will be the only way to transfer/get data from the radio,
// that way we can eliminate duplicated code on the NRF_HAL and NRF_COMMANDS
// files. Also that way we can ease the implementation of the custom spi_xfer
// function.
void nRF24_spi_xfer(const uint8_t *in, uint8_t *out, const size_t xfer_size)
{
    nRF24_spi_clear_fifo();

    nRF24_ss_write(GPIO_CLEAR);

#if defined (_PSOC6)
    for(size_t i = 0; i < xfer_size; i++){
        while(Cy_SCB_Write(SPI_HW, in[i]) == 0);
        while (Cy_SCB_GetNumInRxFifo(SPI_HW) == 0) {}
        out[i] = Cy_SCB_ReadRxFifo(SPI_HW);
    }
#elif defined (_PSOC4_SCB)
    for (size_t i = 0; i < xfer_size; i++) {
        SPI_SpiUartWriteTxData(in[i]);
        while (SPI_SpiUartGetRxBufferSize() == 0){}
        out[i] = SPI_SpiUartReadRxData();
    }
#elif defined (_PSOC_UDB)
    for (size_t i = 0; i < xfer_size; i++) {
        SPI_WriteTxData(in[i]);
        while (!(SPI_ReadTxStatus() & SPI_STS_BYTE_COMPLETE)) {
        }
        out[i] = SPI_ReadRxData();
    }
#else
    #error "Non valid PSoC device identified."
#endif

    nRF24_ss_write(GPIO_SET);
}

void nRF24_spi_clear_fifo(void)
{
#if defined (_PSOC6)
    Cy_SCB_ClearRxFifo(SPI_HW);
    Cy_SCB_ClearTxFifo(SPI_HW);
#elif defined (_PSOC4_SCB)
    SPI_SpiUartClearRxBuffer();
    SPI_SpiUartClearTxBuffer();
#elif defined (_PSOC_UDB)
    SPI_ClearFIFO();
#else
    #error "Non valid PSoC device identified."
#endif
}

/**
 * Read the specified nRF24 register (1byte).
 * 
 * TODO: So here the microcontroller just need to write 2 uint8_t's
 * to the nrf24 radio and read the last stored uint8_t.
 *
 * @param const nrf_register reg: Register to be read.
 *
 * @return uint8_t: Content of the specified register.
 */
uint8_t nRF24_read_register(const nrf_register reg)
{
    const uint8_t _nrf_cmd[] = {
        NRF_CMD_R_REGISTER | reg, NRF_CMD_NOP
    };
    uint8_t _nrf_data[2] = {0};
    
    nRF24_spi_xfer(_nrf_cmd, _nrf_data, sizeof(_nrf_cmd) / sizeof(_nrf_cmd[0]));

    return _nrf_data[1];
}

/**
 * Read the specified nRF24 register (bigger than 1 byte).
 *
 * @param const nrf_register reg: Register to be read.
 * @param uint8_t* data: Pointer to where the content of the register
 * will be stored.
 * @param size_t size: Size of the register and data.
 */
void nRF24_read_long_register(const nrf_register reg,
                                           uint8_t* data, const size_t size)
{
    uint8_t nrf_data[size + 1];
    uint8_t dummy[size + 1];
    
    dummy[0] = NRF_CMD_R_REGISTER | reg;

    // Send the command and get the status
    nRF24_spi_xfer(dummy, nrf_data, sizeof(dummy));

    // Copy data without the status register to the user pointer
    memcpy(data, &nrf_data[1], size);
}

/**
 * Write to the specified nRF24 Register (1byte).
 *
 * @param const nrf_register reg: Register to be written.
 * @param const uint8_t data: Data to be written into the specified register.
 */
void nRF24_write_register(const nrf_register reg, const uint8_t data)
{
    const uint8_t data_to_write[] = {NRF_CMD_W_REGISTER | reg, data};
    uint8_t nrf_data[2] = {0};
    
    nRF24_spi_xfer(data_to_write, nrf_data, sizeof(data_to_write));
}

/**
 * Write one or more bytes to the specified nRF24 Register.
 *
 * @param const nrf_register reg: Register to be written.
 * @param const uint8_t* data: Data to writen into the register.
 * @param size_t size: Bytes of the data to be written in the specified register.
 */
void nRF24_write_long_register(const nrf_register reg,
                                            const uint8_t* data, const size_t size)
{
    uint8_t data_to_nrf[size + 1];
    uint8_t data_from_nrf[size + 1];
    
    // Set the write command and the register to write to
    data_to_nrf[0] = NRF_CMD_W_REGISTER | reg;
    // add the data given by the user
    memcpy(&data_to_nrf[1], data, size);

    nRF24_spi_xfer(data_to_nrf, data_from_nrf, sizeof(data_to_nrf));
}

/**
 * Read the content of the specified bit of the specified nrf_register.
 *
 * @param const nrf_register reg: Register to be read.
 * @param uint8_t bit: Bit to be read.
 *
 * @return bool: Return the content of the bit.
 */
bool nRF24_read_bit(const nrf_register reg, const uint8_t bit)
{
    return (nRF24_read_register(reg) & (1 << bit)) != 0;
}

/**
 * Set (1) or clear (0) the specified bit of the specified nRF24 register.
 *
 * First we read the specified register and check the content of the specified
 * bit, exit early if the bit already is the value we wanted, otherwise we set
 * the bit to the specified value.
 *
 * @param const nrf_register reg: Register to be written.
 * @param const uint8_t bit: Position of the bit to be written.
 * @param const bool value: Value (1 or 0) to write into the bit.
 */
static void nRF24_write_bit(const nrf_register reg,
                                  const uint8_t bit, const bool value)
{
    uint8_t temp = nRF24_read_register(reg);

    // Read the bit value before writing to it.
    // Check if the bit is 1
    if ((temp & (1 << bit)) != 0) {
        // it is 1, return if we wanted to set it to 1
        if (value) {
            return;
        }
    } else { // the bit is 0
        // it is 0, return if we wanted to set it to 0
        if (!value) {
            return;
        }
    }

    // Calculate the new value to be written into the register
    temp = value ? temp | (1 << bit) : temp & ~(1 << bit);

    nRF24_write_register(reg, temp);
}

/**
 * Set to 0 the specified bit of the specified nRF24 register.
 *
 * @param const nrf_register reg: Register to be written.
 * @param const uint8_t bit: Bit to be written.
 */
void nRF24_clear_bit(const nrf_register reg, const uint8_t bit)
{
    if (8 < bit) {
        return;
    }

    nRF24_write_bit(reg, bit, 0);
}

/**
 * Set to 1 the specified bit of the specified nRF24 register.
 *
 * @param const nrf_register reg: Register to be written.
 * @param const uint8_t bit: Bit to be written.
 */
void nRF24_set_bit(const nrf_register reg, const uint8_t bit)
{
    if (8 < bit) {
        return;
    }

    nRF24_write_bit(reg, bit, 1);
}

/* [] END OF FILE */
