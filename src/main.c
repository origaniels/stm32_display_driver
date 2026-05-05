#include "rcc.h"
#include "gpio.h"
#include "clock.h"
#include "uart.h"
#include "timer.h"
#include "music.h"

int main() {
  sysclock_init();
  systick_init();

  bool out = true;

  setup_timer1_pwm(TONE_A5);
    delay(5000);
  set_tim1_pwm_off();
  struct pin pin = (struct pin){BANKA, 5};
  struct pin pin_debug = (struct pin){BANKA, 6};
  gpio_set_mode(pin, GPIO_MODE_AF);
  gpio_set_mode(pin_debug, GPIO_MODE_OUTPUT);
  gpio_set_af(pin, 5);
  for (int i = 0; i<5; i++){
    /* Debug clock frequency with led */
    gpio_write(pin_debug, out);
    out = !out;
    delay(500);
  }

  while (1) {
    gpio_write(pin_debug, 0);
    play_song_cords(ieji_cords, 22);
    gpio_write(pin_debug, 1);
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
