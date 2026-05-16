#include "i2c.h"

void init_i2c1() {
  RCC->APBENR1.I2C1EN = 1;
  I2C1->TIMINGR = 0x00303D5B;
  SET_BIT(I2C1->CR1, 0); //PE
}

int send_bytes(uint8_t addr, uint8_t *data, uint8_t size) {
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
