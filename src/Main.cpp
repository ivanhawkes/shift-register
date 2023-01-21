#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "pico/time.h"

int main(void) {
  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
  const uint kSH_LD_PIN = 2;
  const uint kCLK_PIN = 3;
  const uint kQ_PIN = 4;

  // Init the USB / UART IO.
  stdio_init_all();
  adc_init();

  // Init the uart using our preferred settings.
  stdio_uart_init_full(uart0, 115200, 16, 17);

  printf("\n\nShift Register Test\n\n");

  // Control the on-board LED so we have a heartbeat to confirm operation.
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  // Set the pins.
  gpio_init(kSH_LD_PIN);
  gpio_set_dir(kSH_LD_PIN, GPIO_OUT);
  gpio_init(kCLK_PIN);
  gpio_set_dir(kCLK_PIN, GPIO_OUT);
  gpio_init(kQ_PIN);
  gpio_set_dir(kQ_PIN, GPIO_IN);

  // Set the initial state.
  gpio_put(kSH_LD_PIN, 1);
  gpio_put(kCLK_PIN, 1);

  while (true) {
    // Sample the pins.
    gpio_put(kSH_LD_PIN, 0);
    sleep_ms(1);
    gpio_put(kSH_LD_PIN, 1);
    sleep_ms(1);

    for (int i = 0; i < 8; i++) {
      gpio_put(kCLK_PIN, 0);
      sleep_ms(1);

      // Read each bit in.
      bool q = gpio_get(kQ_PIN);
      if (q)
        printf("1");
      else
        printf("0");
      sleep_ms(1);

      // Tick tock.
      gpio_put(kCLK_PIN, 1);
      sleep_ms(1);
    }
    printf("\n");

    // Slow it all down and give me a chance to read the output.
    gpio_put(LED_PIN, 1);
    sleep_ms(500);
    gpio_put(LED_PIN, 0);
    sleep_ms(500);
  }

  return 0;
}
