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

#ifndef nRF24_HAL_H
#define nRF24_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "nRF24_DEFS.h"

/* SPI */
void nRF24_spi_xfer(const uint8_t *in, uint8_t *out, const size_t xfer_size);
void nRF24_spi_clear_fifo(void);

uint8_t nRF24_read_register(const nrf_register reg);
void nRF24_read_long_register(const nrf_register reg, uint8_t* data , const size_t size);
void nRF24_write_register(const nrf_register reg, const uint8_t data);
void nRF24_write_long_register(const nrf_register reg, const uint8_t* data, const size_t size);
bool nRF24_read_bit(const nrf_register reg, const uint8_t bit);
void nRF24_clear_bit(const nrf_register reg, const uint8_t bit);
void nRF24_set_bit(const nrf_register reg, const uint8_t bit);

/* GPIO Control */

typedef enum {
    GPIO_CLEAR,
    GPIO_SET
} nrf_gpio;

void nRF24_ss_write(nrf_gpio state);
void nRF24_ce_write(nrf_gpio state);

#endif /* nRF24_HAL_H */

/* [] END OF FILE */
