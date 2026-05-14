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

/* configures the ssd1306 display over i2c
 * Assumes i2c was already configured on the correct pins. */
int ssd1306_init() {
  uint8_t display_on[] = {
    CTRL_MULT_CMD,
    CMD_SET_DIS_OFF,
    CMD_CHARGE_PUMP_SETTING, CMD_CHARGE_PUMP_EN,
    CMD_SET_DIS_ON};
  if (send_byte(SSD1306_DEV_ADDR, display_on, sizeof(display_on))) return 1;

  uint8_t data_off[] = {CTRL_MULT_CMD, CMD_ENTIRE_DISPLAY_RAM};
  if (send_byte(SSD1306_DEV_ADDR, data_off, sizeof(data_off))) return 1;
  return 0;
}

void ssd1306_clear_display() {
  uint8_t clear_page[SSD1306_NB_COL_PER_PAGE+1];
  for (int i = 0; i<SSD1306_NB_COL_PER_PAGE; i++){
    clear_page[i+1] = 0x00;
  }
  clear_page[0] = CTRL_MULT_DATA;

  for (int i = 0; i<SSD1306_NB_PAGES; i++){
    uint8_t set_page[] = {
      CTRL_MULT_CMD,
      CMD_SET_PAGE_START(i),
      CMD_COL_START_ADDR_LOW(0),
      CMD_COL_START_ADDR_HIGH(0)
    };

    send_byte(SSD1306_DEV_ADDR, set_page, 4);
    send_byte(SSD1306_DEV_ADDR, clear_page, SSD1306_NB_COL_PER_PAGE+1);
  }
}

enum scroll_speed {
  SPD_2FRAMES=0b111,
  SPD_3FRAMES=0b100,
  SPD_4FRAMES=0b101,
  SPD_5FRAMES=0b000,
  SPD_25FRAMES=0b110,
};

int ssd1306_stop_scroll() {
  uint8_t set_scroll_off[] = {
    CTRL_SINGLE_CMD,
    CMD_SCROLL_OFF
  };
  return send_byte(SSD1306_DEV_ADDR, set_scroll_off, 2);
}

int ssd1306_start_scroll() {
  uint8_t set_scroll_on[] = {
    CTRL_SINGLE_CMD,
    CMD_SCROLL_ON
  };
  return send_byte(SSD1306_DEV_ADDR, set_scroll_on, 2);
}

/* Configures the scrolling mechanism.
 * direction=true => right scrolling
 * direction=false => left scrolling
 * vertical_offset!=0 => vertical scrolling
 */
int ssd1306_configure_scroll(bool direction, uint8_t start_page, uint8_t end_page,
                              enum scroll_speed speed, uint8_t vertical_offset) {
  /* Check for invalid parameters */
  if (end_page>7 || start_page>7 || vertical_offset>63) return 1;

  if (ssd1306_stop_scroll()) return 1;

  if (vertical_offset) {
    uint8_t vertical_direction = 1<<direction;
    uint8_t configure[] = {
      CTRL_MULT_CMD,
      CMD_SCROLL_VERT_HOR_CFG(vertical_direction),
      0x0, // dummy byte according to spec.
      start_page,
      speed,
      end_page,
      vertical_offset,
    };
    if (send_byte(SSD1306_DEV_ADDR, configure, sizeof(configure))) return 1;
  } else {
    uint8_t configure[] = {
      CTRL_MULT_CMD,
      CMD_SCROLL_HOR_CFG(direction),
      0x0, // dummy byte according to spec.
      start_page,
      speed,
      end_page,
      0x0, // dummy byte
      0xff, // dummy byte
    };
    if (send_byte(SSD1306_DEV_ADDR, configure, sizeof(configure))) return 1;
  }

  return 0;
}

/* Displays an image on the display.
 * img is an array of unsigned char. With a maximum size of 128*8 bytes.
 * It's layout is a succession of pages.
 * Each page being a succession of columns */
int ssd1306_write_image(uint8_t *img, const uint8_t nb_pages, const uint8_t nb_col,
                uint8_t start_page, uint8_t start_col) {
  for (int page = 0; page<nb_pages; page++) {
    uint8_t set_page_num[] = {
      CTRL_MULT_CMD,
      CMD_SET_PAGE_START(page+start_page),
      CMD_COL_START_ADDR_LOW(start_col & 0xF),
      CMD_COL_START_ADDR_HIGH(start_col>>4)
    };

    uint8_t data[nb_col+1];
    for (int i = 0; i<nb_col; i++) {
      data[i+1] = img[(page*nb_col)+i];
    }
    data[0] = CTRL_MULT_DATA;

    if (send_byte(SSD1306_DEV_ADDR, set_page_num, 4)) return 1;
    if (send_byte(SSD1306_DEV_ADDR, data, nb_col+1)) return 1;
  }
  return 0;
}
