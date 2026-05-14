#pragma once
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

struct rcc_cr {
  volatile uint32_t _rsvd3: 2;
  volatile uint32_t SYSDIV: 3;
  volatile uint32_t HSIKERDIV: 3;
  volatile uint32_t HSION: 1;
  volatile uint32_t HSIKERON: 1;
  volatile uint32_t HSIRDY: 1;
  volatile uint32_t HSIDIV: 3;
  volatile uint32_t _rsvd2: 2;
  volatile uint32_t HSEON: 1;
  volatile uint32_t HSERDY: 1;
  volatile uint32_t HSEBYP: 1;
  volatile uint32_t CSSON: 1;
  volatile uint32_t _rsvd1: 2;
  volatile uint32_t HSIUSB48ON: 1;
  volatile uint32_t HSIUSB48RDY: 1;
  volatile uint32_t _rsvd0: 8;
} __attribute__((packed));
static_assert(sizeof(struct rcc_cr)==4, "Wrong size of bitfield");

struct rcc_icscr {
  volatile uint32_t HSICAL: 8;
  volatile uint32_t HSITRIM: 7;
  volatile uint32_t _rsvd0: 17;
} __attribute__((packed));
static_assert(sizeof(struct rcc_icscr)==4, "Wrong size of bitfield");

struct rcc_cfgr {
  volatile uint32_t SW: 3;
  volatile uint32_t SWS: 3;
  volatile uint32_t _rsvd1: 2;
  volatile uint32_t HPRE: 4;
  volatile uint32_t PPRE: 3;
  volatile uint32_t _rsvd0: 1;
  volatile uint32_t MCOS2EL: 4;
  volatile uint32_t MCO2PRE: 4;
  volatile uint32_t MCOSEL: 4;
  volatile uint32_t MCOPRE: 4;
} __attribute__((packed));
static_assert(sizeof(struct rcc_cfgr)==4, "Wrong size of bitfield");

struct rcc_crrcr {
  volatile uint32_t HSIUSB48CAL: 9;
  volatile uint32_t _rsvd0: 23;
} __attribute__((packed));
static_assert(sizeof(struct rcc_crrcr)==4, "Wrong size of bitfield");

struct rcc_cier {
  volatile uint32_t LSIRDYIE: 1;
  volatile uint32_t LSERDYIE: 1;
  volatile uint32_t HSIUSB48RDYIE: 1;
  volatile uint32_t HSIRDYIE: 1;
  volatile uint32_t HSERDYIE: 1;
  volatile uint32_t _rsvd0: 27;
} __attribute__((packed));
static_assert(sizeof(struct rcc_cier)==4, "Wrong size of bitfield");

struct rcc_cifr {
  volatile uint32_t LSIRDYIF: 1;
  volatile uint32_t LSERDYIF: 1;
  volatile uint32_t HSIUSB48RDYIF: 1;
  volatile uint32_t HSIRDYIF: 1;
  volatile uint32_t HSERDYIF: 1;
  volatile uint32_t _rsvd0: 3;
  volatile uint32_t CSSF: 1;
  volatile uint32_t LSECSSF: 1;
  volatile uint32_t _rsvd1: 22;
} __attribute__((packed));
static_assert(sizeof(struct rcc_cifr)==4, "Wrong size of bitfield");

struct rcc_cicr {
  volatile uint32_t LSIRDYIC: 1;
  volatile uint32_t LSERDYIC: 1;
  volatile uint32_t HSIUSB48RDYIC: 1;
  volatile uint32_t HSIRDYIC: 1;
  volatile uint32_t HSERDYIC: 1;
  volatile uint32_t _rsvd0: 3;
  volatile uint32_t CSSC: 1;
  volatile uint32_t LSECSSC: 1;
  volatile uint32_t _rsvd1: 22;
} __attribute__((packed));
static_assert(sizeof(struct rcc_cicr)==4, "Wrong size of bitfield");

struct rcc_ioprstr {
  volatile uint32_t GPIOARST: 1;
  volatile uint32_t GPIOBRST: 1;
  volatile uint32_t GPIOCRST: 1;
  volatile uint32_t GPIODRST: 1;
  volatile uint32_t _rsvd0: 1;
  volatile uint32_t GPIOFRST: 1;
  volatile uint32_t _rsvd1: 26;
} __attribute__((packed));
static_assert(sizeof(struct rcc_ioprstr)==4, "Wrong size of bitfield");

struct rcc_ahbrstr {
  volatile uint32_t DMA1RST: 1;
  volatile uint32_t _rsvd0: 7;
  volatile uint32_t FLASHRST: 1;
  volatile uint32_t _rsvd1: 3;
  volatile uint32_t CRCRST: 1;
  volatile uint32_t _rsvd2: 19;
} __attribute__((packed));
static_assert(sizeof(struct rcc_ahbrstr)==4, "Wrong size of bitfield");

struct rcc_apbrstr1 {
  volatile uint32_t TIM2RST: 1;
  volatile uint32_t TIM3RST: 1;
  volatile uint32_t _rsvd0: 10;
  volatile uint32_t FDCAN1RST: 1;
  volatile uint32_t USBRST: 1;
  volatile uint32_t SPI2RST: 1;
  volatile uint32_t _rsvd1: 1;
  volatile uint32_t CRSRST: 1;
  volatile uint32_t USART2RST: 1;
  volatile uint32_t USART3RST: 1;
  volatile uint32_t USART4RST: 1;
  volatile uint32_t _rsvd2: 1;
  volatile uint32_t I2C1RST: 1;
  volatile uint32_t I2C2RST: 1;
  volatile uint32_t _rsvd3: 4;
  volatile uint32_t DBGRST: 1;
  volatile uint32_t PWRRST: 1;
  volatile uint32_t _rsvd4: 3;
} __attribute__((packed));
static_assert(sizeof(struct rcc_apbrstr1)==4, "Wrong size of bitfield");

struct rcc_apbrstr2 {
  volatile uint32_t SYSCFGRST: 1;
  volatile uint32_t _rsvd0: 10;
  volatile uint32_t TIM1RST: 1;
  volatile uint32_t SPI1RST: 1;
  volatile uint32_t _rsvd1: 1;
  volatile uint32_t USART1RST: 1;
  volatile uint32_t TIM14RST: 1;
  volatile uint32_t TIM15RST: 1;
  volatile uint32_t TIM16RST: 1;
  volatile uint32_t TIM17RST: 1;
  volatile uint32_t _rsvd2: 1;
  volatile uint32_t ADCRST: 1;
  volatile uint32_t _rsvd3: 11;
} __attribute__((packed));
static_assert(sizeof(struct rcc_apbrstr2)==4, "Wrong size of bitfield");

struct rcc_iopenr {
  volatile uint32_t GPIOAEN: 1;
  volatile uint32_t GPIOBEN: 1;
  volatile uint32_t GPIOCEN: 1;
  volatile uint32_t GPIODEN: 1;
  volatile uint32_t _rsvd0: 1;
  volatile uint32_t GPIOFEN: 1;
  volatile uint32_t _rsvd1: 26;
} __attribute__((packed));
static_assert(sizeof(struct rcc_iopenr)==4, "Wrong size of bitfield");

struct rcc_ahbenr {
  volatile uint32_t DMA1EN: 1;
  volatile uint32_t _rsvd0: 7;
  volatile uint32_t FLASHEN: 1;
  volatile uint32_t _rsvd1: 3;
  volatile uint32_t CRCEN: 1;
  volatile uint32_t _rsvd2: 19;
} __attribute__((packed));
static_assert(sizeof(struct rcc_ahbenr)==4, "Wrong size of bitfield");

struct rcc_apbenr1 {
  volatile uint32_t TIM2EN: 1;
  volatile uint32_t TIM3EN: 1;
  volatile uint32_t _rsvd0: 8;
  volatile uint32_t RTCAPBEN: 1;
  volatile uint32_t WWDGEN: 1;
  volatile uint32_t FDCAN1EN: 1;
  volatile uint32_t USBEN: 1;
  volatile uint32_t SPI2EN: 1;
  volatile uint32_t _rsvd1: 1;
  volatile uint32_t CRSEN: 1;
  volatile uint32_t USART2EN: 1;
  volatile uint32_t USART3EN: 1;
  volatile uint32_t USART4EN: 1;
  volatile uint32_t _rsvd2: 1;
  volatile uint32_t I2C1EN: 1;
  volatile uint32_t I2C2EN: 1;
  volatile uint32_t _rsvd3: 4;
  volatile uint32_t DBGEN: 1;
  volatile uint32_t PWREN: 1;
  volatile uint32_t _rsvd4: 3;
} __attribute__((packed));
static_assert(sizeof(struct rcc_apbenr1)==4, "Wrong size of bitfield");

struct rcc_apbenr2 {
  volatile uint32_t SYSCFGEN: 1;
  volatile uint32_t _rsvd0: 10;
  volatile uint32_t TIM1EN: 1;
  volatile uint32_t SPI1EN: 1;
  volatile uint32_t _rsvd1: 1;
  volatile uint32_t USART1EN: 1;
  volatile uint32_t TIM14EN: 1;
  volatile uint32_t TIM15EN: 1;
  volatile uint32_t TIM16EN: 1;
  volatile uint32_t TIM17EN: 1;
  volatile uint32_t _rsvd2: 1;
  volatile uint32_t ADCEN: 1;
  volatile uint32_t _rsvd3: 11;
} __attribute__((packed));
static_assert(sizeof(struct rcc_apbenr2)==4, "Wrong size of bitfield");

struct rcc_iopsmenr {
  volatile uint32_t GPIOASMEN: 1;
  volatile uint32_t GPIOBSMEN: 1;
  volatile uint32_t GPIOCSMEN: 1;
  volatile uint32_t GPIODSMEN: 1;
  volatile uint32_t _rsvd0: 1;
  volatile uint32_t GPIOFSMEN: 1;
  volatile uint32_t _rsvd1: 24;
} __attribute__((packed));
static_assert(sizeof(struct rcc_iopsmenr)==4, "Wrong size of bitfield");

struct rcc_ahbsmenr {
  volatile uint32_t DMA1SMEN: 1;
  volatile uint32_t _rsvd0: 7;
  volatile uint32_t FLASHSMEN: 1;
  volatile uint32_t SRAMSMEN: 1;
  volatile uint32_t _rsvd1: 2;
  volatile uint32_t CRCSMEN: 1;
  volatile uint32_t _rsvd2: 19;
} __attribute__((packed));
static_assert(sizeof(struct rcc_ahbsmenr)==4, "Wrong size of bitfield");

struct rcc_apbsmenr1 {
  volatile uint32_t TIM2SMEN: 1;
  volatile uint32_t TIM3SMEN: 1;
  volatile uint32_t _rsvd0: 8;
  volatile uint32_t RTCAPBSMEN: 1;
  volatile uint32_t WWDGSMEN: 1;
  volatile uint32_t FDCAN1SMEN: 1;
  volatile uint32_t USBSMEN: 1;
  volatile uint32_t SPI2SMEN: 1;
  volatile uint32_t _rsvd1: 1;
  volatile uint32_t CRSSMEN: 1;
  volatile uint32_t USART2SMEN: 1;
  volatile uint32_t USART3SMEN: 1;
  volatile uint32_t USART4SMEN: 1;
  volatile uint32_t _rsvd2: 1;
  volatile uint32_t I2C1SMEN: 1;
  volatile uint32_t I2C2SMEN: 1;
  volatile uint32_t _rsvd3: 4;
  volatile uint32_t DBGSMEN: 1;
  volatile uint32_t PWRSMEN: 1;
  volatile uint32_t _rsvd4: 3;
} __attribute__((packed));
static_assert(sizeof(struct rcc_apbsmenr1)==4, "Wrong size of bitfield");

struct rcc_apbsmenr2 {
  volatile uint32_t SYSCFGSMEN: 1;
  volatile uint32_t _rsvd0: 10;
  volatile uint32_t TIM1SMEN: 1;
  volatile uint32_t SPI1SMEN: 1;
  volatile uint32_t _rsvd1: 1;
  volatile uint32_t USART1SMEN: 1;
  volatile uint32_t TIM14SMEN: 1;
  volatile uint32_t TIM15SMEN: 1;
  volatile uint32_t TIM16SMEN: 1;
  volatile uint32_t TIM17SMEN: 1;
  volatile uint32_t _rsvd2: 1;
  volatile uint32_t ADCSMEN: 1;
  volatile uint32_t _rsvd3: 11;
} __attribute__((packed));
static_assert(sizeof(struct rcc_apbsmenr2)==4, "Wrong size of bitfield");

struct rcc_ccipr {
  volatile uint32_t USART1SEL: 2;
  volatile uint32_t _rsvd0: 6;
  volatile uint32_t FDCAN1SEL: 2;
  volatile uint32_t _rsvd1: 2;
  volatile uint32_t I2C1SEL: 2;
  volatile uint32_t I2S1SEL: 2;
  volatile uint32_t _rsvd2: 14;
  volatile uint32_t ADCSEL: 2;
} __attribute__((packed));
static_assert(sizeof(struct rcc_ccipr)==4, "Wrong size of bitfield");

struct rcc_ccipr2 {
  volatile uint32_t _rsvd0: 12;
  volatile uint32_t USBSEL: 1;
  volatile uint32_t _rsvd1: 19;
} __attribute__((packed));
static_assert(sizeof(struct rcc_ccipr2)==4, "Wrong size of bitfield");

struct rcc_csr1 {
  volatile uint32_t LSEON: 1;
  volatile uint32_t LSERDY: 1;
  volatile uint32_t LSEBYP: 1;
  volatile uint32_t LSEDRV: 1;
  volatile uint32_t _rsvd0: 1;
  volatile uint32_t LSECSSON: 1;
  volatile uint32_t LSECSSD: 1;
  volatile uint32_t _rsvd1: 1;
  volatile uint32_t RTCSEL: 2;
  volatile uint32_t _rsvd2: 5;
  volatile uint32_t RTCEN: 1;
  volatile uint32_t RTCRST: 1;
  volatile uint32_t _rsvd3: 7;
  volatile uint32_t LSCOEN: 1;
  volatile uint32_t LSCOSEL: 1;
  volatile uint32_t _rsvd4: 6;
} __attribute__((packed));
static_assert(sizeof(struct rcc_csr1)==4, "Wrong size of bitfield");

struct rcc_csr2 {
  volatile uint32_t LSION: 1;
  volatile uint32_t LSIRDY: 1;
  volatile uint32_t _rsvd0: 21;
  volatile uint32_t RMVF: 1;
  volatile uint32_t _rsvd1: 1;
  volatile uint32_t OBLRSTF: 1;
  volatile uint32_t PINRSTF: 1;
  volatile uint32_t PWRRSTF: 1;
  volatile uint32_t SFTRSTF: 1;
  volatile uint32_t IWDGRSTF: 1;
  volatile uint32_t WWDGRSTF: 1;
  volatile uint32_t LPWRRSTF: 1;
} __attribute__((packed));
static_assert(sizeof(struct rcc_csr1)==4, "Wrong size of bitfield");

struct rcc {
  volatile struct rcc_cr CR;
  volatile struct rcc_icscr ICSCR;
  volatile struct rcc_cfgr CFGR;
  volatile uint32_t RESERVED1[2];
  volatile struct rcc_crrcr CRRCR;
  volatile struct rcc_cier CIER;
  volatile struct rcc_cifr CIFR;
  volatile struct rcc_cicr CICR;
  volatile struct rcc_ioprstr IOPRSTR;
  volatile struct rcc_ahbrstr AHBRSTR;
  volatile struct rcc_apbrstr1 APBRSTR1;
  volatile struct rcc_apbrstr2 APBRSTR2;
  volatile struct rcc_iopenr IOPENR;
  volatile struct rcc_ahbenr AHBENR;
  volatile struct rcc_apbenr1 APBENR1;
  volatile struct rcc_apbenr2 APBENR2;
  volatile struct rcc_iopsmenr IOPSMENR;
  volatile struct rcc_ahbsmenr AHBSMENR;
  volatile struct rcc_apbsmenr1 APBSMENR1;
  volatile struct rcc_apbsmenr2 APBSMENR2;
  volatile struct rcc_ccipr CCIPR;
  volatile struct rcc_ccipr2 CCIPR2;
  volatile struct rcc_csr1 CSR1;
  volatile struct rcc_csr2 CSR2;
};




#define RCC ((struct rcc *)0x40021000)
