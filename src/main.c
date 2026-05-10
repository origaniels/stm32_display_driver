#include "rcc.h"
#include "gpio.h"
#include "clock.h"
#include "uart.h"
#include "timer.h"
#include "music.h"
#include "i2c.h"
#include "ssd1306.h"

int main() {
  sysclock_init();
  systick_init();
  init_i2c1();

  bool out = true;

  setup_timer1_pwm(TONE_A5);
    delay(5000);
  set_tim1_pwm_off();
  struct pin pin = (struct pin){BANKA, 5};
  struct pin pin_debug = (struct pin){BANKA, 6};

  struct pin scl = (struct pin){BANKB, 8};
  struct pin sda = (struct pin){BANKB, 9};
  gpio_set_mode(scl, GPIO_MODE_AF);
  gpio_set_mode(sda, GPIO_MODE_AF);
  gpio_set_af(sda, 6);
  gpio_set_af(scl, 6);
  GPIOB->OTYPER |=  (0x3 << 8);    // Open-drain
  GPIOB->PUPDR  &= ~(0xF << 16);
  GPIOB->PUPDR  |=  (0x5 << 16);


  gpio_set_mode(pin, GPIO_MODE_AF);
  gpio_set_mode(pin_debug, GPIO_MODE_OUTPUT);
  gpio_set_af(pin, 5);
  for (int i = 0; i<5; i++){
    /* Debug clock frequency with led */
    gpio_write(pin_debug, out);
    out = !out;
    delay(500);
  }

  uint8_t data_on[] = {CTRL_MULT_CMD, CMD_ENTIRE_DISPLAY_ON};
  uint8_t data_off[] = {CTRL_MULT_CMD, CMD_ENTIRE_DISPLAY_RAM};
  uint8_t display_on[] = {
    CTRL_MULT_CMD,
    CMD_SET_DIS_OFF,
    CMD_CHARGE_PUMP_SETTING, CMD_CHARGE_PUMP_EN,
    CMD_SET_DIS_ON};
  if (send_byte(0b0111100, display_on, 5)) gpio_write(pin_debug, 1);
  while (1) {

    gpio_write(pin_debug, 0);
    if (send_byte(0b0111100, data_on, 2)) gpio_write(pin_debug, 1);
    play_song_cords(ieji_cords, 22);
    if (send_byte(0b0111100, data_off, 2)) gpio_write(pin_debug, 1);
    delay(4000);
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
