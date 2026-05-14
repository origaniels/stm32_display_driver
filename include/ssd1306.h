#pragma once
#include "i2c.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>

#define SSD1306_DEV_ADDR 0b0111100
#define SSD1306_NB_PAGES 8
#define SSD1306_NB_COL_PER_PAGE 128

#define CTRL_SINGLE_CMD   0b10000000
#define CTRL_MULT_CMD     0b00000000
#define CTRL_SINGLE_DATA  0b11000000
#define CTRL_MULT_DATA    0b01000000

#define CMD_SET_CONTRAST        0b10000001
#define CMD_ENTIRE_DISPLAY_ON   0b10100101
#define CMD_ENTIRE_DISPLAY_RAM  0b10100100
#define CMD_SET_NORMAL          0b10100110
#define CMD_SET_INVERSE         0b10100111
#define CMD_SET_DIS_ON          0b10101111
#define CMD_SET_DIS_OFF         0b10101110
#define CMD_SCROLL_ON           0b00101111
#define CMD_SCROLL_OFF          0b00101110
#define CMD_SCROLL_HOR_CFG(X)       (0b0010011<<1) | X
#define CMD_SCROLL_VERT_HOR_CFG(X)  (0b001010<<2) | X
#define CMD_SCROLL_VERT_AREA    0b10100011
#define CMD_COL_START_ADDR_LOW(X)   (0b0000<<4) | X   /* 0 <= X <= 15 */
#define CMD_COL_START_ADDR_HIGH(X)  (0b0001<<4) | X  /* 0 <= X <= 15 */
#define CMD_SET_ADDR_MODE       0b00100000
#define CMD_SET_COL_ADDR        0b00100001
#define CMD_SET_PAGE_ADDR       0b00100010
#define CMD_SET_PAGE_START(X)         (0b10110<<3) | X /* 0 <= X <= 7 */
#define CMD_SET_DIS_START_LINE(X)     (0b01<<6) | X /* 0 <= X <= 64 */
#define CMD_SET_SEGMENT_REMAP_NORMAL      0b10100000
#define CMD_SET_SEGMENT_REMAP_REVERSE     0b10100000
#define CMD_SET_MULTIPLEX_RATIO           0b10101000
#define CMD_SET_COM_OUT_SCAN_DIR_NORMAL   0b11000000
#define CMD_SET_COM_OUT_SCAN_DIR_REVERSE  0b11000000
#define CMD_SET_DIS_OFFSET                0b11010011
#define CMD_SET_COM_PINS                  0b11011010
#define CMD_SET_CLK_OSC_FREQ              0b11010101
#define CMD_SET_PRE_CHARGE_PERIOD         0b11011001
#define CMD_SET_VCOMH_DESEL_LVL           0b11011011
#define CMD_NOP                           0b11100011
#define CMD_CHARGE_PUMP_SETTING           0b10001101
#define CMD_CHARGE_PUMP_EN                0b00010100
#define CMD_CHARGE_PUMP_DIS               0b00010000

int ssd1306_init();
void ssd1306_clear_display();

enum scroll_speed {
  SPD_2FRAMES=0b111,
  SPD_3FRAMES=0b100,
  SPD_4FRAMES=0b101,
  SPD_5FRAMES=0b000,
  SPD_25FRAMES=0b110,
};

int ssd1306_stop_scroll();
int ssd1306_start_scroll();
int ssd1306_configure_scroll(bool direction, uint8_t start_page, uint8_t end_page,
                              enum scroll_speed speed, uint8_t vertical_offset);
int ssd1306_write_image(uint8_t *img, const uint8_t nb_pages, const uint8_t nb_col,
                uint8_t start_page, uint8_t start_col);
