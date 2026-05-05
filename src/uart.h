#pragma once

#include <inttypes.h>
#include <stddef.h>
#include "gpio.h"
#include "rcc.h"
#include "register.h"

struct uart {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t CR3;
    uint32_t BRR;
    uint32_t GTPR;
    uint32_t RTOR;
    uint32_t RQR;
    uint32_t ISR;
    uint32_t ICR;
    uint32_t RDR;
    uint32_t TDR;
    uint32_t PRESEC;
};

#define USART2 ((struct uart *)0x40004400)
#define USART3 ((struct uart *)0x40004800)
#define USART4 ((struct uart *)0x40004C00)
#define USART1 ((struct uart *)0x40013800)

#define FREQ 12000000
#define BAUD 115200UL
#define BRR_VALUE ((FREQ) / BAUD)

void uart_init(struct uart *uart);
int uart_read_ready(struct uart *uart);
uint8_t uart_read_byte(struct uart *uart);
void uart_write_byte(struct uart *uart, uint8_t byte);
void uart_write_buf(struct uart *uart, char *buf, size_t len);
