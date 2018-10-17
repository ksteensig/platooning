//#include <vl53l1_api.h>
//#include "usart.h"

// int main(void) { return usart(); }

/* Simple LED task demo:
 *
 * The LED on PC13 is toggled in task1.
 */
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"
#include "vl53l1_api.h"
#include "vl53l1_platform.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,
                                          signed portCHAR *pcTaskName);

void vApplicationStackOverflowHook(xTaskHandle *pxTask,
                                   signed portCHAR *pcTaskName) {
  (void)pxTask;
  (void)pcTaskName;
  for (;;)
    ;
}

static void task2(void *args) {
  VL53L1_DEV Dev = args;
  int status;
  int8_t ready;
  static VL53L1_RangingMeasurementData_t RangingData;

  for (;;) {
    status = VL53L1_WaitMeasurementDataReady(Dev);
    if (!status) {
      status = VL53L1_GetRangingMeasurementData(Dev, &RangingData);
      usart_send_blocking(USART2, RangingData.RangeStatus + 48);
      if (status == 0) {
        gpio_toggle(GPIOD, GPIO12);
      }
      status = VL53L1_ClearInterruptAndStartMeasurement(Dev);
      vTaskDelay(50);
    }
  }
}

// VL53L1_GetRangeStatusString

int main(void) {
  VL53L1_Dev_t dev;
  VL53L1_DEV Dev = &dev;

  rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOD);
  rcc_periph_clock_enable(RCC_USART2);
  rcc_periph_clock_enable(RCC_GPIOB);
  rcc_periph_clock_enable(RCC_I2C1);

  gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
  gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);

  gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6 | GPIO7);
  gpio_set_output_options(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_100MHZ,
                          GPIO6 | GPIO7);
  gpio_set_af(GPIOB, GPIO_AF4, GPIO6 | GPIO7);

  usart_set_baudrate(USART2, 115200);
  usart_set_databits(USART2, 8);
  usart_set_stopbits(USART2, USART_STOPBITS_1);
  usart_set_mode(USART2, USART_MODE_TX_RX);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
  usart_enable(USART2);

  i2c_peripheral_disable(I2C1);
  i2c_reset(I2C1);
  // i2c_set_clock_frequency(I2C1, I2C_CR2_FREQ_8MHZ);
  i2c_set_speed(I2C1, i2c_speed_sm_100k, 42);
  i2c_peripheral_enable(I2C1);

  Dev->I2cDevAddr = 0x29;
  int status;

  // status = VL53L1_WaitDeviceBooted(Dev);

  for (uint64_t i = 0; i < 100000000000; i++)
    ;

  while (1) {
    i2c_send_start(I2C1);

    while (!((I2C_SR1(I2C1) & I2C_SR1_SB) &
             (I2C_SR2(I2C1) & (I2C_SR2_MSL | I2C_SR2_BUSY))))
      ;

    i2c_send_7bit_address(I2C1, Dev->I2cDevAddr, I2C_WRITE);

    while (!(I2C_SR1(I2C1) & I2C_SR1_ADDR))
      ;
  }

  status = VL53L1_DataInit(Dev);
  usart_send_blocking(USART2, status + 48);
  usart_send_blocking(USART2, '\n');
  /*
  status = VL53L1_StaticInit(Dev);
  usart_send_blocking(USART2, status + 48);
  usart_send_blocking(USART2, '\n');
  status = VL53L1_SetDistanceMode(Dev, VL53L1_DISTANCEMODE_SHORT);
  usart_send_blocking(USART2, status + 48);
  usart_send_blocking(USART2, '\n');
  status = VL53L1_SetMeasurementTimingBudgetMicroSeconds(Dev, 50000);
  usart_send_blocking(USART2, status + 48);
  usart_send_blocking(USART2, '\n');
  status = VL53L1_SetInterMeasurementPeriodMilliSeconds(
      Dev, 50);  // reduced to 50 ms from 500 ms in ST example
  usart_send_blocking(USART2, status + 48);
  usart_send_blocking(USART2, '\n');
  status = VL53L1_StartMeasurement(Dev);
  usart_send_blocking(USART2, status + 48);
  usart_send_blocking(USART2, '\n');
  */

  xTaskCreate(task2, "LED", 200, NULL, configMAX_PRIORITIES - 1, (void *)Dev);
  vTaskStartScheduler();
  for (;;)
    ;

  return 0;
}

// End
