#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <stdbool.h>
#include <stdint.h>

#include "core/uart.h"

#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

#define UART_PORT (GPIOC)
#define RX_PIN (GPIO7)
#define TX_PIN (GPIO6)

static void system_setup(void) {
  rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
}

void gpio_setup(void) {
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);

  rcc_periph_clock_enable(RCC_GPIOC);
  gpio_mode_setup(UART_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, RX_PIN | TX_PIN);
  gpio_set_af(UART_PORT, GPIO_AF8, RX_PIN | TX_PIN);
}

int main(void) {
  system_setup();
  gpio_setup();
  uart_setup();

  while (1) {
    if (uart_data_available()) {
      uint8_t data = uart_read_byte();
      uart_write_byte(data - 1);
    }
  }

  return 0;
}