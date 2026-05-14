#include "timer.h"


struct adv_control_timer *tim1 = (struct adv_control_timer *)TIM1_BASE_ADDR;
void setup_timer1_pwm(uint16_t period_mus) {
  RCC->APBENR2.TIM1EN = 1;
  /* Set prescaling factor to about 1 microsecond */
  tim1->PSC.PSC = BASE_PERIOD;
  tim1->ARR.ARR = period_mus;
  tim1->CCR1.CCR1 = BASE_CCR1;

  tim1->CCMR1.alt.OC1M_3 = 0;
  tim1->CCMR1.alt.OC1M = 0b110;
  tim1->CCMR1.alt.OC1PE = 1;

  tim1->CR1.ARPE = 1;
  tim1->CR1.CEN = 1;

  tim1->CCER.CC1E = 1;
  tim1->BDTR.MOE = 1;

  tim1->EGR.UG = 1;
}

void set_tim1_pwm_freq(uint16_t period_mus) {
  tim1->ARR.ARR = period_mus;
  tim1->EGR.UG = 1;
}

void set_tim1_pwm_ccr1(uint16_t crr1) {
  tim1->CCR1.CCR1 = crr1;
  tim1->EGR.UG = 1;
}

void set_tim1_pwm_off() {
  tim1->CR1.CEN = 0;
  tim1->EGR.UG = 1;
}

void set_tim1_pwm_on() {
  tim1->CR1.CEN = 1;
  tim1->EGR.UG = 1;
}
