#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "pico/time.h"

int main(void) {
  // Init the USB / UART IO.
  stdio_init_all();
  adc_init();

  // Init the uart using our preferred settings.
  stdio_uart_init_full(uart0, 115200, 16, 17);

  printf("Shift Register Test.\n\n");

  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  while (true) {
    gpio_put(LED_PIN, 1);
    sleep_ms(250);
    gpio_put(LED_PIN, 0);
    sleep_ms(250);
  }

  return 0;
}
