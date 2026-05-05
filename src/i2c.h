#pragma once
#include <inttypes.h>
#include <stdint.h>
#include "register.h"
#include "rcc.h"

struct i2c_cr2 {
  volatile uint32_t SADD: 10;
  volatile uint32_t RD_WRN: 1;
  volatile uint32_t ADD10: 1;
  volatile uint32_t HEAD10R: 1;
  volatile uint32_t START: 1;
  volatile uint32_t STOP: 1;
  volatile uint32_t NACK: 1;
  volatile uint32_t NBYTES: 8;
  volatile uint32_t RELOAD: 1;
  volatile uint32_t AUTOEND: 1;
  volatile uint32_t PECBYTE: 1;
  volatile uint32_t _rsvd: 5;
}__attribute__((packed));
static_assert(sizeof(struct i2c_cr2)==4, "Wrong size of bitfield");


struct i2c {
  volatile uint32_t CR1;
  volatile struct i2c_cr2 CR2;
  volatile uint32_t OAR1;
  volatile uint32_t OAR2;
  volatile uint32_t TIMINGR;
  volatile uint32_t TIMEOUTR;
  volatile uint32_t ISR;
  volatile uint32_t ICR;
  volatile uint32_t PECR;
  volatile uint32_t RXDR;
  volatile uint32_t TXDR;
};

#define I2C1 ((struct i2c *)0x40005400)

void init_i2c1() {
  RCC->APBENR1.I2C1EN = 1;
  I2C1->TIMINGR = 0x00303D5B;
  SET_BIT(I2C1->CR1, 0); //PE
}

int send_byte(uint8_t addr, uint8_t *data, uint8_t size) {
  I2C1->CR2.SADD = addr<<1;
  I2C1->CR2.NBYTES = size;
  I2C1->CR2.AUTOEND = 1;


  I2C1->CR2.RD_WRN = 0;
  I2C1->CR2.START = 1;
  for (int i = 0; i<size; i++) {
    while ((I2C1->ISR & 0b10)==0) {
      if ((I2C1->ISR & 0b10000)) return 1;
    }
    I2C1->TXDR = data[i];
  }
  return 0;
}

