#pragma once
#include <inttypes.h>
#include <stdint.h>
#include "register.h"
#include "rcc.h"
#include "clock.h"

#define TIM1_BASE_ADDR 0x40012C00

extern struct adv_control_timer *tim1;

struct tim1_cr1 {
  volatile uint32_t CEN: 1;
  volatile uint32_t UDIS: 1;
  volatile uint32_t URS: 1;
  volatile uint32_t OPM: 1;
  volatile uint32_t DIR: 1;
  volatile uint32_t CMS: 2;
  volatile uint32_t ARPE: 1;
  volatile uint32_t CKD: 2;
  volatile uint32_t _rsvd1: 1;
  volatile uint32_t UIFREMAP: 1;
  volatile uint32_t _rsvd0: 20;
} __attribute__((packed));
static_assert(sizeof(struct tim1_cr1)==4, "Wrong size of bitfield");

struct tim1_cr2 {
  volatile uint32_t CCPC: 1;
  volatile uint32_t _rsvd0: 1;
  volatile uint32_t CCUS: 1;
  volatile uint32_t CCDS: 1;
  volatile uint32_t MMS: 3;
  volatile uint32_t TI1S: 1;
  volatile uint32_t OIS1: 1;
  volatile uint32_t OIS1N: 1;
  volatile uint32_t OIS2: 1;
  volatile uint32_t OIS2N: 1;
  volatile uint32_t OIS3: 1;
  volatile uint32_t OIS3N: 1;
  volatile uint32_t OIS4: 1;
  volatile uint32_t _rsvd1: 1;
  volatile uint32_t OIS5: 1;
  volatile uint32_t _rsvd2: 1;
  volatile uint32_t OIS6: 1;
  volatile uint32_t _rsvd3: 1;
  volatile uint32_t MMS2: 4;
  volatile uint32_t _rsvd4: 8;
} __attribute__((packed));
static_assert(sizeof(struct tim1_cr2)==4, "Wrong size of bitfield");

struct tim1_smcr {
  volatile uint32_t SMS: 3;
  volatile uint32_t OCCS: 1;
  volatile uint32_t TS: 3;
  volatile uint32_t MSM: 1;
  volatile uint32_t ETF: 4;
  volatile uint32_t ETPS: 2;
  volatile uint32_t ECE: 1;
  volatile uint32_t ETP: 1;
  volatile uint32_t SMS_3: 1;
  volatile uint32_t _rsvd1: 3;
  volatile uint32_t TS_4: 2;
  volatile uint32_t _rsvd2: 10;
} __attribute__((packed));
static_assert(sizeof(struct tim1_smcr)==4, "wrong size of bitfield");

struct tim1_dier {
  volatile uint32_t UIE: 1;
  volatile uint32_t CC1IE: 1;
  volatile uint32_t CC2IE: 1;
  volatile uint32_t CC3IE: 1;
  volatile uint32_t CC4IE: 1;
  volatile uint32_t COMIE: 1;
  volatile uint32_t TIE: 1;
  volatile uint32_t BIE: 1;
  volatile uint32_t UDE: 1;
  volatile uint32_t CC1DE: 1;
  volatile uint32_t CC2DE: 1;
  volatile uint32_t CC3DE: 1;
  volatile uint32_t CC4DE: 1;
  volatile uint32_t COMDE: 1;
  volatile uint32_t TDE: 1;
  volatile uint32_t _rsvd0: 17;
} __attribute__((packed));
static_assert(sizeof(struct tim1_dier)==4, "wrong size of bitfield");

struct tim1_sr {
  volatile uint32_t UIF: 1;
  volatile uint32_t CC1IF: 1;
  volatile uint32_t CC2IF: 1;
  volatile uint32_t CC3IF: 1;
  volatile uint32_t CC4IF: 1;
  volatile uint32_t COMIF: 1;
  volatile uint32_t TIF: 1;
  volatile uint32_t BIF: 1;
  volatile uint32_t B2IF: 1;
  volatile uint32_t CC1OF: 1;
  volatile uint32_t CC2OF: 1;
  volatile uint32_t CC3OF: 1;
  volatile uint32_t CC4OF: 1;
  volatile uint32_t SBIF: 1;
  volatile uint32_t _rsvd0: 2;
  volatile uint32_t CC5IF: 1;
  volatile uint32_t CC6IF: 1;
  volatile uint32_t _rsvd1: 14;
} __attribute__((packed));
static_assert(sizeof(struct tim1_sr)==4, "wrong size of bitfield");

struct tim1_egr {
  volatile uint32_t UG: 1;
  volatile uint32_t CC1G: 1;
  volatile uint32_t CC2G: 1;
  volatile uint32_t CC3G: 1;
  volatile uint32_t CC4G: 1;
  volatile uint32_t COMG: 1;
  volatile uint32_t TG: 1;
  volatile uint32_t BG: 1;
  volatile uint32_t B2G: 1;
  volatile uint32_t _rsvd1: 23;
} __attribute__((packed));
static_assert(sizeof(struct tim1_egr)==4, "wrong size of bitfield");

struct tim1_ccmr1_base {
  volatile uint32_t CC1S: 2;
  volatile uint32_t IC1PSC: 2;
  volatile uint32_t IC1F: 4;
  volatile uint32_t CC2S: 2;
  volatile uint32_t IC2PSC: 2;
  volatile uint32_t IC2F: 4;
  volatile uint32_t _rsvd1: 16;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccmr1_base)==4, "wrong size of bitfield");

struct tim1_ccmr1_alt {
  volatile uint32_t CC1S: 2;
  volatile uint32_t OC1FE: 1;
  volatile uint32_t OC1PE: 1;
  volatile uint32_t OC1M: 3;
  volatile uint32_t OC1CE: 1;
  volatile uint32_t CC2S: 2;
  volatile uint32_t OC2FE: 1;
  volatile uint32_t OC2PE: 1;
  volatile uint32_t OC2M: 3;
  volatile uint32_t OC2CE: 1;
  volatile uint32_t OC1M_3: 1;
  volatile uint32_t _rsvd1: 7;
  volatile uint32_t OC2M_3: 1;
  volatile uint32_t _rsvd2: 7;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccmr1_alt)==4, "wrong size of bitfield");

union tim1_ccmr1 {
  struct tim1_ccmr1_base base;
  struct tim1_ccmr1_alt alt;
};
static_assert(sizeof(union tim1_ccmr1)==4, "wrong size of bitfield");

struct tim1_ccmr2_base {
  volatile uint32_t CC3S: 2;
  volatile uint32_t IC3PSC: 2;
  volatile uint32_t IC3F: 4;
  volatile uint32_t CC4S: 2;
  volatile uint32_t IC4PSC: 2;
  volatile uint32_t IC4F: 4;
  volatile uint32_t _rsvd1: 16;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccmr2_base)==4, "wrong size of bitfield");

struct tim1_ccmr2_alt {
  volatile uint32_t CC3S: 2;
  volatile uint32_t OC3FE: 1;
  volatile uint32_t OC3PE: 1;
  volatile uint32_t OC3M: 3;
  volatile uint32_t OC3CE: 1;
  volatile uint32_t CC4S: 2;
  volatile uint32_t OC4FE: 1;
  volatile uint32_t OC4PE: 1;
  volatile uint32_t OC4M: 3;
  volatile uint32_t OC4CE: 1;
  volatile uint32_t OC3M_3: 1;
  volatile uint32_t _rsvd1: 7;
  volatile uint32_t OC4M_3: 1;
  volatile uint32_t _rsvd2: 7;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccmr2_alt)==4, "wrong size of bitfield");

union tim1_ccmr2 {
  struct tim1_ccmr2_base base;
  struct tim1_ccmr2_alt alt;
};
static_assert(sizeof(union tim1_ccmr2)==4, "wrong size of bitfield");

struct tim1_ccer {
  volatile uint32_t CC1E: 1;
  volatile uint32_t CC1P: 1;
  volatile uint32_t CC1NE: 1;
  volatile uint32_t CC1NP: 1;
  volatile uint32_t CC2E: 1;
  volatile uint32_t CC2P: 1;
  volatile uint32_t CC2NE: 1;
  volatile uint32_t CC2NP: 1;
  volatile uint32_t CC3E: 1;
  volatile uint32_t CC3P: 1;
  volatile uint32_t CC3NE: 1;
  volatile uint32_t CC3NP: 1;
  volatile uint32_t CC4E: 1;
  volatile uint32_t CC4P: 1;
  volatile uint32_t _rsvd0: 1;
  volatile uint32_t CC4NP: 1;
  volatile uint32_t CC5E: 1;
  volatile uint32_t CC5P: 1;
  volatile uint32_t _rsvd1: 2;
  volatile uint32_t CC6E: 1;
  volatile uint32_t CC6P: 1;
  volatile uint32_t _rsvd2: 10;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccer)==4, "wrong size of bitfield");

struct tim1_cnt {
  volatile uint32_t CNT: 16;
  volatile uint32_t _rsvd2: 15;
  volatile uint32_t UIFCPY: 1;
} __attribute__((packed));
static_assert(sizeof(struct tim1_cnt)==4, "wrong size of bitfield");

struct tim1_psc {
  volatile uint32_t PSC: 16;
  volatile uint32_t _rsvd2: 16;
} __attribute__((packed));
static_assert(sizeof(struct tim1_psc)==4, "wrong size of bitfield");

struct tim1_arr {
  volatile uint32_t ARR: 16;
  volatile uint32_t _rsvd2: 16;
} __attribute__((packed));
static_assert(sizeof(struct tim1_arr)==4, "wrong size of bitfield");

struct tim1_rcr {
  volatile uint32_t REP: 16;
  volatile uint32_t _rsvd2: 16;
} __attribute__((packed));
static_assert(sizeof(struct tim1_rcr)==4, "wrong size of bitfield");

struct tim1_ccr1 {
  volatile uint32_t CCR1: 16;
  volatile uint32_t _rsvd2: 16;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccr1)==4, "wrong size of bitfield");

struct tim1_ccr2 {
  volatile uint32_t CCR2: 16;
  volatile uint32_t _rsvd2: 16;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccr2)==4, "wrong size of bitfield");

struct tim1_ccr3 {
  volatile uint32_t CCR3: 16;
  volatile uint32_t _rsvd2: 16;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccr3)==4, "wrong size of bitfield");

struct tim1_ccr4 {
  volatile uint32_t CCR4: 16;
  volatile uint32_t _rsvd2: 16;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccr4)==4, "wrong size of bitfield");

struct tim1_bdtr {
  volatile uint32_t DGT: 8;
  volatile uint32_t LOCK: 2;
  volatile uint32_t OSSI: 1;
  volatile uint32_t OSSR: 1;
  volatile uint32_t BKE: 1;
  volatile uint32_t BKP: 1;
  volatile uint32_t AOE: 1;
  volatile uint32_t MOE: 1;
  volatile uint32_t BKF: 4;
  volatile uint32_t BK2F: 4;
  volatile uint32_t BK2E: 1;
  volatile uint32_t BK2P: 1;
  volatile uint32_t BKDSRM: 1;
  volatile uint32_t BK2DSRM: 1;
  volatile uint32_t BKBID: 1;
  volatile uint32_t BK2BID: 1;
  volatile uint32_t _rsvd2: 2;
} __attribute__((packed));
static_assert(sizeof(struct tim1_bdtr)==4, "wrong size of bitfield");

struct tim1_dcr {
  volatile uint32_t DBA: 5;
  volatile uint32_t DBL: 5;
  volatile uint32_t _rsvd2: 22;
} __attribute__((packed));
static_assert(sizeof(struct tim1_dcr)==4, "wrong size of bitfield");

struct tim1_dmar {
  volatile uint32_t DMAB: 32;
} __attribute__((packed));
static_assert(sizeof(struct tim1_dmar)==4, "wrong size of bitfield");

struct tim1_ccmr3 {
  volatile uint32_t _rsvd0: 2;
  volatile uint32_t OC5FE: 1;
  volatile uint32_t OC5PE: 1;
  volatile uint32_t OC5M: 3;
  volatile uint32_t OC5E: 1;
  volatile uint32_t _rsvd1: 2;
  volatile uint32_t OC6FE: 1;
  volatile uint32_t OC6PE: 1;
  volatile uint32_t OC6M: 3;
  volatile uint32_t OC6E: 1;
  volatile uint32_t OC5M_3: 1;
  volatile uint32_t _rsvd2: 7;
  volatile uint32_t OC6M_3: 1;
  volatile uint32_t _rsvd3: 7;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccmr3)==4, "wrong size of bitfield");

struct tim1_ccr5 {
  volatile uint32_t CCR5: 16;
  volatile uint32_t _rsvd0: 13;
  volatile uint32_t GC5C1: 1;
  volatile uint32_t GC5C2: 1;
  volatile uint32_t GC5C3: 1;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccr5)==4, "wrong size of bitfield");

struct tim1_ccr6 {
  volatile uint32_t CCR6: 16;
  volatile uint32_t _rsvd0: 16;
} __attribute__((packed));
static_assert(sizeof(struct tim1_ccr6)==4, "wrong size of bitfield");

struct tim1_af1 {
  volatile uint32_t BKINE: 1;
  volatile uint32_t _rsvd0: 8;
  volatile uint32_t BKINP: 1;
  volatile uint32_t _rsvd1: 4;
  volatile uint32_t ETRSEL: 4;
  volatile uint32_t _rsvd2: 14;
} __attribute__((packed));
static_assert(sizeof(struct tim1_af1)==4, "wrong size of bitfield");

struct tim1_af2 {
  volatile uint32_t BK2INE: 1;
  volatile uint32_t _rsvd0: 8;
  volatile uint32_t BK2INP: 1;
  volatile uint32_t _rsvd1: 22;
} __attribute__((packed));
static_assert(sizeof(struct tim1_af2)==4, "wrong size of bitfield");

struct tim1_tisel {
  volatile uint32_t TI1SEL: 4;
  volatile uint32_t _rsvd0: 4;
  volatile uint32_t TI2SEL: 4;
  volatile uint32_t _rsvd1: 4;
  volatile uint32_t TI3SEL: 4;
  volatile uint32_t _rsvd2: 4;
  volatile uint32_t TI4SEL: 4;
  volatile uint32_t _rsvd3: 4;
} __attribute__((packed));
static_assert(sizeof(struct tim1_tisel)==4, "wrong size of bitfield");


struct adv_control_timer {
  volatile struct tim1_cr1 CR1;
  volatile struct tim1_cr2 CR2;
  volatile struct tim1_smcr SMCR;
  volatile struct tim1_dier DIER;
  volatile struct tim1_sr SR;
  volatile struct tim1_egr EGR;
  volatile union  tim1_ccmr1 CCMR1;
  volatile union  tim1_ccmr2 CCMR2;
  volatile struct tim1_ccer CCER;
  volatile struct tim1_cnt CNT;
  volatile struct tim1_psc PSC;
  volatile struct tim1_arr ARR;
  volatile struct tim1_rcr RCR;
  volatile struct tim1_ccr1 CCR1;
  volatile struct tim1_ccr2 CCR2;
  volatile struct tim1_ccr3 CCR3;
  volatile struct tim1_ccr4 CCR4;
  volatile struct tim1_bdtr BDTR;
  volatile struct tim1_dcr DCR;
  volatile struct tim1_dmar DMAR;
  volatile uint32_t _rsvd;
  volatile struct tim1_ccmr3 CCMR3;
  volatile struct tim1_ccr5 CCR5;
  volatile struct tim1_ccr6 CCR6;
  volatile struct tim1_af1 AF1;
  volatile struct tim1_af2 AF2;
  volatile struct tim1_tisel TISEL;
};

#define BASE_PERIOD CLOCKS_PER_MICROSECONDS
#define BASE_CCR1 40

void setup_timer1_pwm(uint16_t period_mus);
void set_tim1_pwm_freq(uint16_t period_mus);
void set_tim1_pwm_ccr1(uint16_t crr1);
void set_tim1_pwm_off();
void set_tim1_pwm_on();
