#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "pico/time.h"

int main(void) {
  const uint kLEDPin = PICO_DEFAULT_LED_PIN;
  const uint kLatchPin = 2;
  const uint kClockPin = 3;
  const uint kDataPin = 4;

  // Init the USB / UART IO.
  stdio_init_all();
  adc_init();

  // Init the uart using our preferred settings.
  stdio_uart_init_full(uart0, 115200, 16, 17);

  printf("\n\nShift Register Test\n\n");

  // Control the on-board LED so we have a heartbeat to confirm operation.
  gpio_init(kLEDPin);
  gpio_set_dir(kLEDPin, GPIO_OUT);

  // Set the pins.
  gpio_init(kLatchPin);
  gpio_set_dir(kLatchPin, GPIO_OUT);
  gpio_init(kClockPin);
  gpio_set_dir(kClockPin, GPIO_OUT);
  gpio_init(kDataPin);
  gpio_set_dir(kDataPin, GPIO_IN);

  // Set the initial state.
  gpio_put(kLatchPin, 1);
  gpio_put(kClockPin, 1);
  sleep_us(1);

  while (true) {
    // Sample the pins.
    gpio_put(kLatchPin, 0);
    sleep_us(1);
    gpio_put(kLatchPin, 1);
    sleep_us(1);

    printf("Bits: ");
    for (int i = 0; i < 8; i++) {
      // Read each bit in.
      bool q = gpio_get(kDataPin);
      if (q)
        printf("1");
      else
        printf("0");
      sleep_us(1);

      // Tick tock.
      gpio_put(kClockPin, 1);
      sleep_us(1);
      gpio_put(kClockPin, 0);
      sleep_us(1);
    }
    printf("\n");

    // Slow it all down and give me a chance to read the output.
    gpio_put(kLEDPin, 1);
    sleep_us(10000);
    gpio_put(kLEDPin, 0);
    sleep_us(10000);
  }

  return 0;
}
