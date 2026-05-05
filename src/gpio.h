#pragma once
#include <inttypes.h>
#include <stdbool.h>

/* GPIO modes */
enum { GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG };

/* GPIO banks */
enum gpiobank {BANKA, BANKB, BANKC, BANKD, BANKRESERVED, BANKF};

struct gpio {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
    volatile uint32_t BRR;
};

struct pin {
    enum gpiobank bank;
    volatile uint8_t id;
};

/* GPIO API functions */
void gpio_set_af(struct pin pin, uint8_t af_num);
void gpio_write(struct pin pin, bool val);
void gpio_set_mode(struct pin pin, uint8_t mode);


#define GPIOA ((struct gpio *) (0x50000000 + 0x0000))
#define GPIOB ((struct gpio *) (0x50000000 + 0x0400))
#define GPIOC ((struct gpio *) (0x50000000 + 0x0800))
#define GPIOD ((struct gpio *) (0x50000000 + 0x0C00))
#define GPIOF ((struct gpio *) (0x50000000 + 0x1400))
extern struct gpio *const banks[6];


/* BOARD PIN TRANSLATION */
#define A0  ((struct pin){BANKA, 0})
#define A1  ((struct pin){BANKA, 1})
#define A2  ((struct pin){BANKA, 4})
#define A3  ((struct pin){BANKB, 1})
#define A4  ((struct pin){BANKA, 11})
#define A5  ((struct pin){BANKA, 12})

#define D0  ((struct pin){BANKB, 7})
#define D1  ((struct pin){BANKB, 6})
#define D2  ((struct pin){BANKA, 10})
#define D3  ((struct pin){BANKB, 3})
#define D4  ((struct pin){BANKB, 10})
#define D5  ((struct pin){BANKB, 4})
#define D6  ((struct pin){BANKB, 5})
#define D7  ((struct pin){BANKA, 15})
#define D8  ((struct pin){BANKA, 9})
#define D9  ((struct pin){BANKC, 7})
#define D10 ((struct pin){BANKB, 0})
#define D11 ((struct pin){BANKA, 7})
#define D12 ((struct pin){BANKA, 6})
#define D13 ((struct pin){BANKA, 5})
#define D14 ((struct pin){BANKB, 8})
#define D15 ((struct pin){BANKB, 9})
