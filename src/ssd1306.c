#include "ssd1306.h"
#include <stdint.h>


enum addr_mode cur_addr_mode = ADDR_MODE_PAGE;

/* configures the ssd1306 display over i2c
 * Assumes i2c was already configured on the correct pins. */
int ssd1306_init() {
  if (ssd1306_set_addr_mode(ADDR_MODE_PAGE)) return 1;

  uint8_t display_on[] = {
    CTRL_MULT_CMD,
    CMD_SET_DIS_OFF,
    CMD_CHARGE_PUMP_SETTING, CMD_CHARGE_PUMP_EN,
    CMD_SET_DIS_ON};
  if (send_bytes(SSD1306_DEV_ADDR, display_on, sizeof(display_on))) return 1;

  uint8_t data_off[] = {CTRL_MULT_CMD, CMD_ENTIRE_DISPLAY_RAM};
  if (send_bytes(SSD1306_DEV_ADDR, data_off, sizeof(data_off))) return 1;
  return 0;
}

int ssd1306_set_addr_mode(enum addr_mode mode) {
  uint8_t set_mode[] = {
    CTRL_MULT_CMD,
    CMD_SET_ADDR_MODE,
    mode
  };
  if (send_bytes(SSD1306_DEV_ADDR, set_mode, sizeof(set_mode))) return 1;

  cur_addr_mode = mode;
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

    send_bytes(SSD1306_DEV_ADDR, set_page, 4);
    send_bytes(SSD1306_DEV_ADDR, clear_page, SSD1306_NB_COL_PER_PAGE+1);
  }
}

int ssd1306_stop_scroll() {
  uint8_t set_scroll_off[] = {
    CTRL_SINGLE_CMD,
    CMD_SCROLL_OFF
  };
  return send_bytes(SSD1306_DEV_ADDR, set_scroll_off, 2);
}

int ssd1306_start_scroll() {
  uint8_t set_scroll_on[] = {
    CTRL_SINGLE_CMD,
    CMD_SCROLL_ON
  };
  return send_bytes(SSD1306_DEV_ADDR, set_scroll_on, 2);
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

    uint8_t area[] = {
      CTRL_MULT_CMD,
      CMD_SCROLL_VERT_AREA,
      0x00,
      0x40
    };
    if (send_bytes(SSD1306_DEV_ADDR, area, sizeof(area))) return 1;
    uint8_t configure[] = {
      CTRL_MULT_CMD,
      CMD_SCROLL_VERT_HOR_CFG(vertical_direction),
      0x0, // dummy byte according to spec.
      start_page,
      speed,
      end_page,
      vertical_offset,
    };
    if (send_bytes(SSD1306_DEV_ADDR, configure, sizeof(configure))) return 1;
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
    if (send_bytes(SSD1306_DEV_ADDR, configure, sizeof(configure))) return 1;
  }

  return 0;
}

/* Displays an image on the display.
 * img is an array of unsigned char. With a maximum size of 128*8 bytes.
 * It's layout is a succession of pages.
 * Each page being a succession of columns */
int ssd1306_write_image(uint8_t *img, const uint8_t nb_pages, const uint8_t nb_col,
                uint8_t start_page, uint8_t start_col) {
  if (nb_pages > SSD1306_NB_PAGES) return 1;
  if (!nb_pages) return 1;
  if (nb_pages+start_page > SSD1306_NB_PAGES) return 1;

  if (!nb_col) return 1;
  if (nb_col > SSD1306_NB_COL_PER_PAGE) return 1;
  if (nb_col+start_col > SSD1306_NB_COL_PER_PAGE) return 1;

  switch (cur_addr_mode) {
    case ADDR_MODE_PAGE:
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

        if (send_bytes(SSD1306_DEV_ADDR, set_page_num, 4)) return 1;
        if (send_bytes(SSD1306_DEV_ADDR, data, nb_col+1)) return 1;
      }
      break;
    case ADDR_MODE_HORIZONTAL:
      {
        uint8_t page_addr[] = {
          CTRL_MULT_CMD,
          CMD_SET_PAGE_ADDR,
          start_page,
          start_page+nb_pages-1,
        };
        uint8_t col_addr[] = {
          CTRL_MULT_CMD,
          CMD_SET_COL_ADDR,
          start_col,
          start_col+nb_col-1,
        };

        if (send_bytes(SSD1306_DEV_ADDR, page_addr, sizeof(page_addr))) return 1;
        if (send_bytes(SSD1306_DEV_ADDR, col_addr, sizeof(col_addr))) return 1;

        uint32_t remaining_col = nb_pages * nb_col;
        uint8_t size = SSD1306_MAX_BYTES_PER_CMD;
        uint8_t data[size];
        uint8_t count;
        data[0] = CTRL_MULT_DATA;
        while (remaining_col > size-1) {
          for (int i = 0; i<size-1; i++) {
            data[i+1] = img[(size-1)*count + i];
          }
          if (send_bytes(SSD1306_DEV_ADDR, data, sizeof(data))) return 1;
          count++;
        }
        if (remaining_col > 1) {
          for (int i = 0; i<remaining_col; i++) {
            data[i+1] = img[(size-1)*count + i];
          }
          if (send_bytes(SSD1306_DEV_ADDR, data, remaining_col+1)) return 1;
        } else if (remaining_col) {
          data[0] = CTRL_SINGLE_DATA;
          data[1] = img[(size-1)*count];
          if (send_bytes(SSD1306_DEV_ADDR, data, 2)) return 1;
        }
        break;
      }
    default: return 1;
  }

  return 0;
}
