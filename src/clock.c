#include "clock.h"

volatile uint32_t ticks = 0;

void sysclock_init() {
  /* set HSISYS division factor to 1*/
  RCC->CR.HSIDIV = 0;
}

void systick_init() {
    SET_BIT(SYSTICK->CTRL, 0);
    SET_BIT(SYSTICK->CTRL, 1);
    SET_BIT(SYSTICK->CTRL, 2);
    SYSTICK->LOAD = TICK_INTERVAL;
    SYSTICK->VAL = 0;
}

volatile uint32_t systick_ticks() {
  return ticks;
}

void Systick_handler() {
    ticks++;
}


void delay(uint32_t ms) {
    uint32_t final_ticks = ticks + TICKS_PER_MILLISECONDS * ms;
    while (final_ticks > ticks) (void)final_ticks;
    return;
}
