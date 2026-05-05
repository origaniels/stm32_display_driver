#include "gpio.h"
#include "rcc.h"
#include "register.h"


struct gpio *const banks[6] = {
  GPIOA,
  GPIOB,
  GPIOC,
  GPIOD,
  0x0, /* Reserved word */
  GPIOF,
};


void gpio_set_mode(struct pin pin, uint8_t mode) {
  switch (pin.bank) {
  case BANKA:
    RCC->IOPENR.GPIOAEN = 1;
    break;
  case BANKB:
    RCC->IOPENR.GPIOBEN = 1;
    break;
  case BANKC:
    RCC->IOPENR.GPIOCEN = 1;
    break;
  case BANKD:
    RCC->IOPENR.GPIODEN = 1;
    break;
  case BANKF:
    RCC->IOPENR.GPIOFEN = 1;
    break;
  default:
    break;
  }

  banks[pin.bank]->MODER &= ~(3U << (pin.id * 2));
  banks[pin.bank]->MODER |= (mode & 3) << (pin.id * 2);
}

void gpio_write(struct pin pin, bool val) {
    banks[pin.bank]->BSRR = (1U << pin.id) << (val ? 0 : 16);
}

void gpio_set_af(struct pin pin, uint8_t af_num) {
    int n = pin.id;
    banks[pin.bank]->AFR[n >> 3] &= ~(15UL << ((n & 7) * 4));
    banks[pin.bank]->AFR[n >> 3] |= ((uint32_t) af_num) << ((n & 7) * 4);
}

