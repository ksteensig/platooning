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

#include <libopencm3/stm32/gpio.h>
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

static void task1(void *args) {
  int i;

  (void)args;

  for (;;) {
    usart();
  }
}

int main(void) {
  rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_USART2);
  rcc_periph_clock_enable(RCC_DMA1);

  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
  gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);

  usart_set_baudrate(USART2, 115200);
  usart_set_databits(USART2, 8);
  usart_set_stopbits(USART2, USART_STOPBITS_1);
  usart_set_mode(USART2, USART_MODE_TX_RX);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

  usart_enable(USART2);

  xTaskCreate(task1, "LED", 100, NULL, configMAX_PRIORITIES - 1, NULL);
  vTaskStartScheduler();
  for (;;)
    ;

  return 0;
}

// End
