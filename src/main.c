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

VL53L1_Dev_t dev;
VL53L1_DEV Dev = &dev;
int status;

static void task1(void *args) {
  (void)args;

  uint8_t ready;

  static VL53L1_RangingMeasurementData_t RangingData;

  for (;;) {
    status = VL53L1_GetMeasurementDataReady(Dev, &ready);
    usart_send_blocking(USART2, status + 48);
    usart_send_blocking(USART2, ':');
    // usart_send_blocking(USART2, ready + 48);
    usart_send_blocking(USART2, '\n');
    /*
    usart_send_blocking(USART2, 'G');
    usart_send_blocking(USART2, ' ');
    usart_send_blocking(USART2, ready + 48);
    usart_send_blocking(USART2, '\n');
    */
    if (!status && ready) {
      status = VL53L1_GetRangingMeasurementData(Dev, &RangingData);
      usart_send_blocking(USART2, status + 108);
      usart_send_blocking(USART2, '\n');
      /*
      usart_send_blocking(USART2, 'R');
      usart_send_blocking(USART2, ' ');
      usart_send_blocking(USART2, status);
      usart_send_blocking(USART2, '\n');
      */
      if (!status) {
        // usart_send_blocking(USART2, 'D');
        // usart_send_blocking(USART2, RangingData.RangeMilliMeter & 0xFF);
        // usart_send_blocking(USART2, RangingData.RangeStatus);
        // usart_send_blocking(USART2, '\n');
      }
      status = VL53L1_ClearInterruptAndStartMeasurement(Dev);
    }

    // usart_send_blocking(USART2, 'H');
    // usart_send_blocking(USART2, '\n');
  }
}

static void task2(void *args) {
  (void)args;
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
  i2c_set_speed(I2C1, i2c_speed_sm_100k, 8);
  i2c_peripheral_enable(I2C1);

  Dev->I2cDevAddr = 0x29;
  status = VL53L1_DataInit(Dev);
  usart_send_blocking(USART2, status + 48);
  usart_send_blocking(USART2, '\n');
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

  xTaskCreate(task2, "LED", 200, NULL, configMAX_PRIORITIES - 1, NULL);
  vTaskStartScheduler();
  for (;;)
    ;

  return 0;
}

// End
