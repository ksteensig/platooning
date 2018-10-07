#include "usart.h"

int usart(void) {
  unsigned char* str = "Hello world";
  int i;

  while (1) {
    for (i = 0; str[i] != 0; i++) {
      usart_send_blocking(USART2, str[i]);
    }
    usart_send_blocking(USART2, '\r');
    usart_send_blocking(USART2, '\n');
  }

  return 0;
}
