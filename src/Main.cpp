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
  const uint kData01Pin = 4;
  const uint kData02Pin = 5;

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
  gpio_init(kData01Pin);
  gpio_set_dir(kData01Pin, GPIO_IN);
  gpio_init(kData02Pin);
  gpio_set_dir(kData02Pin, GPIO_IN);

  // Set the initial state.
  gpio_put(kLatchPin, 1);
  gpio_put(kClockPin, 0);
  sleep_us(1);

  while (true) {
    uint8_t data01{0};
    uint8_t data02{0};

    // Sample the pins.
    gpio_put(kLatchPin, 0);
    sleep_us(1);
    gpio_put(kLatchPin, 1);
    sleep_us(1);

    for (int i = 0; i < 8; i++) {
      // Read each bit in.
      bool q1 = gpio_get(kData01Pin);
      data01 = data01 << 1;
      data01 += q1 ? 1 : 0;

      bool q2 = gpio_get(kData02Pin);
      data02 = data02 << 1;
      data02 += q2 ? 1 : 0;

      sleep_us(1);

      // Tick tock.
      gpio_put(kClockPin, 1);
      sleep_us(1);
      gpio_put(kClockPin, 0);
      sleep_us(1);
    }
    printf("Data 01: %0XH    Data 02: %0XH\n", data01, data02);

    // Slow it all down and give me a chance to read the output.
    gpio_put(kLEDPin, 1);
    sleep_ms(100);
    gpio_put(kLEDPin, 0);
    sleep_ms(100);
  }

  return 0;
}
