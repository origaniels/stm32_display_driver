#pragma once
#include <inttypes.h>
#include "rcc.h"
#include "register.h"

struct systick {
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile uint32_t CALIB;
};

#define SYSTICK ((struct systick *) 0xe000e010)

#define CLOCKS_PER_SECONDS 48000000
#define CLOCKS_PER_MILLISECONDS CLOCKS_PER_SECONDS / 1000
#define CLOCKS_PER_MICROSECONDS CLOCKS_PER_MILLISECONDS / 1000

#define SYSTICK_PERIOD_MICROSECONDS 1

#define TICK_INTERVAL CLOCKS_PER_MICROSECONDS * SYSTICK_PERIOD_MICROSECONDS

#define TICKS_PER_MILLISECONDS 1000 / SYSTICK_PERIOD_MICROSECONDS

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


static inline void delay(uint32_t ms) {
    uint32_t final_ticks = ticks + TICKS_PER_MILLISECONDS * ms;
    while (final_ticks > ticks) (void)final_ticks;
    return;
}

