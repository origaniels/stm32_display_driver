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

extern volatile uint32_t ticks;

void sysclock_init();

void systick_init();
volatile uint32_t systick_ticks();
void Systick_handler();

void delay(uint32_t ms);
