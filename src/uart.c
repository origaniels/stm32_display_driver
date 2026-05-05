#include "uart.h"

void uart_init(struct uart *uart) {
  uint8_t af = 1;
  struct pin rx, tx;

  if (uart == USART1) RCC->APBENR2.USART1EN = 1;
  if (uart == USART2) RCC->APBENR1.USART2EN = 1;
  if (uart == USART3) RCC->APBENR1.USART3EN = 1;

	if (uart == USART1) RCC->APBRSTR2.USART1RST = 1;
  if (uart == USART2) RCC->APBRSTR1.USART2RST = 1;
  if (uart == USART3) RCC->APBRSTR1.USART3RST = 1;

  if (uart == USART1) tx = (struct pin){BANKA, 2}, rx = (struct pin){BANKA, 3};
  if (uart == USART3) tx = (struct pin){BANKA, 2}, rx = (struct pin){BANKA, 3};

  if (uart == USART2) tx = (struct pin){BANKA, 2}, rx = (struct pin){BANKA, 3};
  gpio_set_mode(tx, GPIO_MODE_AF);
  gpio_set_af(tx, af);
  gpio_set_mode(rx, GPIO_MODE_AF);
  gpio_set_af(rx, af);
  uart->BRR = BRR_VALUE;
  uart->CR2 = 0;
	uart->CR3 = 0;
  uart->CR1 = 0;
  SET_BIT(uart->CR1, 2);
  SET_BIT(uart->CR1, 3);
  SET_BIT(uart->CR1, 0);
}

int uart_read_ready(struct uart *uart) {
  return uart->ISR & BIT(5);
}

uint8_t uart_read_byte(struct uart *uart) {
  return (uint8_t) (uart->RDR & 255);
}

void uart_write_byte(struct uart *uart, uint8_t byte) {
	uart->TDR = byte;
  while (!(uart->ISR & BIT(7))) {}
}

void uart_write_buf(struct uart *uart, char *buf, size_t len) {
  while (len-- > 0) uart_write_byte(uart, *(uint8_t *) buf++);
}
