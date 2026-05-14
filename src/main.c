#include "rcc.h"
#include "gpio.h"
#include "clock.h"
#include "uart.h"
#include "timer.h"
#include "music.h"
#include "i2c.h"
#include "ssd1306.h"
#include <stdint.h>

int main() {
  sysclock_init();
  systick_init();
  init_i2c1();

  bool out = true;

  struct pin pin = (struct pin){BANKA, 5};
  struct pin pin_debug = (struct pin){BANKA, 6};

  /* configure gpio for i2c */
  struct pin scl = (struct pin){BANKB, 8};
  struct pin sda = (struct pin){BANKB, 9};
  gpio_set_mode(scl, GPIO_MODE_AF);
  gpio_set_mode(sda, GPIO_MODE_AF);
  gpio_set_af(sda, 6);
  gpio_set_af(scl, 6);
  GPIOB->OTYPER |=  (0x3 << 8);
  GPIOB->PUPDR  &= ~(0xF << 16);
  GPIOB->PUPDR  |=  (0x5 << 16);

  gpio_set_mode(pin, GPIO_MODE_AF);
  gpio_set_mode(pin_debug, GPIO_MODE_OUTPUT);
  gpio_set_af(pin, 5);


  ssd1306_init();
  const uint8_t invader_nb_pages = 1;
  const uint8_t invader_nb_col = 8;
  uint8_t invader[] = {
    0b00011001,
    0b00111010,
    0b01101101,
    0b01111010,
    0b01111010,
    0b01101101,
    0b00111010,
    0b00011001
  };

  ssd1306_clear_display();
  ssd1306_write_image(invader, invader_nb_pages, invader_nb_col, 4, 64);
  ssd1306_write_image(invader, invader_nb_pages, invader_nb_col, 6, 42);


  uint8_t start_page = 3, end_page = 5;
  uint8_t vertical_offset = 1;
  bool direction = false;
  ssd1306_configure_scroll(direction, start_page, end_page, SPD_3FRAMES, vertical_offset);
  while (1) {
    ssd1306_start_scroll();
    delay(10000);
    ssd1306_stop_scroll();
    delay(500);
  }

  return 0;
}


__attribute__((naked, noreturn)) void _reset() {
  extern long _sbss, _ebss, _sdata, _edata, _sidata;
  for (long *dst = &_sbss; dst < &_ebss; dst++)
      *dst = 0;
  for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;)
      *dst++ = *src++;

  main();
  for (;;) (void) 0;
}

extern void _estack();

__attribute__((section(".vectors"))) void (*const tab[16 + 91])(void) = {
  [0] = _estack,
  [1] = _reset,
  [15] = Systick_handler
};
