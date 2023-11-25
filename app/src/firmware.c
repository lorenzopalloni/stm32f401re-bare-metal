#include <libopencm3/cm3/scb.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <stdbool.h>
#include <stdint.h>

#include "core/system.h"
#include "core/uart.h"
#include "timer.h"

#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

#define UART_PORT (GPIOC)
#define RX_PIN (GPIO7)
#define TX_PIN (GPIO6)

#define BOOTLOADER_SIZE 0x8000U

static void vector_setup(void) { SCB_VTOR = BOOTLOADER_SIZE; }

static void gpio_setup(void) {
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(LED_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LED_PIN);
  gpio_set_af(LED_PORT, GPIO_AF1, LED_PIN);

  rcc_periph_clock_enable(RCC_GPIOC);
  gpio_mode_setup(UART_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, RX_PIN | TX_PIN);
  gpio_set_af(UART_PORT, GPIO_AF8, RX_PIN | TX_PIN);
}

int main(void) {
  vector_setup();
  system_setup();
  gpio_setup();
  uart_setup();
  timer_setup();

  uint64_t tick = system_get_ticks();
  float duty_cycle = 0.0f;

  while (1) {
    if (system_get_ticks() - tick >= 10) {
      if (duty_cycle > 100.0f) {
        duty_cycle = 0.0f;
      }
      timer_pwm_set_duty_cycle(duty_cycle);

      duty_cycle += 1.0f;
      tick = system_get_ticks();
    }

    if (uart_data_available()) {
      uint8_t data = uart_read_byte();
      uart_write_byte(data - 1);
    }
  }

  return 0;
}