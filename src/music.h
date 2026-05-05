#include "clock.h"
#include "timer.h"
#include <stdint.h>

enum tone {
 TONE_A5 = 1000000/880,
 TONE_C5 = 1000000/523,
 TONE_B4 = 1000000/493,
 TONE_A4 = 1000000/440,
 TONE_G4 = 1000000/392,
 TONE_F4 = 1000000/349,
 TONE_E4 = 1000000/329,
 TONE_C4 = 1000000/261,
 TONE_A3_SHARP = 1000000/233,
 TONE_A3 = 1000000/220,
 TONE_F3 = 1000000/174,
 TONE_C2 = 1000000/130
};

enum duration {
  CROCHE = 400,
  CROCHE_POINTEE = 600,
  NOIRE = 800,
  NOIRE_POINTEE = 1200,
  BLANCHE = 1600
};

struct note {
  enum tone tone;
  enum duration duration_ms;
};

struct cord {
  enum tone *tones;
  enum duration duration_ms;
  uint8_t size;
};

void play_cord(struct cord *cord) {
  uint32_t final_ticks = systick_ticks()+cord->duration_ms*TICKS_PER_MILLISECONDS;
  set_tim1_pwm_on();
  while (final_ticks > systick_ticks())
  {
    for (uint32_t i = 0; i<cord->size; i++) {
      set_tim1_pwm_freq(cord->tones[i]);
      delay(50);
    }
  }
}

void play_song_cords(struct cord *song, uint32_t length) {
  set_tim1_pwm_on();
  for (uint32_t i = 0; i<length; i++) {
    play_cord(&song[i]);
    set_tim1_pwm_ccr1(0);
    delay(1);
    set_tim1_pwm_ccr1(BASE_CCR1);
  }
  set_tim1_pwm_off();
}

void play_song(struct note *song, uint32_t length) {
  set_tim1_pwm_on();
  for (uint32_t i = 0; i<length; i++) {
    set_tim1_pwm_freq(song[i].tone);
    delay(song[i].duration_ms);
    set_tim1_pwm_ccr1(0);
    delay(1);
    set_tim1_pwm_ccr1(BASE_CCR1);
  }
  set_tim1_pwm_off();
}

struct note ieji[22] = {
  {TONE_A4, NOIRE},
  {TONE_C5, CROCHE},
  {TONE_C5, NOIRE},
  {TONE_A4, NOIRE},
  {TONE_G4, CROCHE},
  {TONE_F4, NOIRE_POINTEE},

  {TONE_G4, NOIRE},
  {TONE_A4, CROCHE},
  {TONE_C5, NOIRE},
  {TONE_A4, CROCHE},
  {TONE_G4, NOIRE_POINTEE},

  {TONE_A4, NOIRE},
  {TONE_C5, CROCHE},
  {TONE_C5, NOIRE},
  {TONE_A4, NOIRE},
  {TONE_G4, CROCHE},
  {TONE_F4, NOIRE_POINTEE},

  {TONE_G4, CROCHE_POINTEE},
  {TONE_A4, CROCHE_POINTEE},
  {TONE_G4, NOIRE},
  {TONE_F4, CROCHE},
  {TONE_F4, BLANCHE},
};

enum tone ieji_cord0 [2]   = {TONE_A4, TONE_F3};
enum tone ieji_cord1 [2]   = {TONE_C5, TONE_F3};
enum tone ieji_cord2 [2]   = {TONE_C5, TONE_F3};
enum tone ieji_cord3 [2]   = {TONE_A4, TONE_C4};
enum tone ieji_cord4 [2]   = {TONE_G4, TONE_C4};
enum tone ieji_cord5 [2]   = {TONE_F4, TONE_C4};

enum tone ieji_cord6 [2]   = {TONE_G4, TONE_C4};
enum tone ieji_cord7 [2]   = {TONE_A4, TONE_C4};
enum tone ieji_cord8 [2]   = {TONE_C5, TONE_C4};
enum tone ieji_cord9 [2]   = {TONE_A4, TONE_C4};
enum tone ieji_cord10[2]  = {TONE_G4, TONE_C4};

enum tone ieji_cord11[2]  = {TONE_A4, TONE_F3};
enum tone ieji_cord12[2]  = {TONE_C5, TONE_F3};
enum tone ieji_cord13[2]  = {TONE_C5, TONE_F3};
enum tone ieji_cord14[2]  = {TONE_A4, TONE_A3};
enum tone ieji_cord15[2]  = {TONE_G4, TONE_A3};
enum tone ieji_cord16[2]  = {TONE_F4, TONE_A3};

enum tone ieji_cord17[2]  = {TONE_G4, TONE_A3_SHARP};
enum tone ieji_cord18[2]  = {TONE_A4, TONE_A3_SHARP};
enum tone ieji_cord19[2]  = {TONE_G4, TONE_C4};
enum tone ieji_cord20[2]  = {TONE_F4, TONE_C4};
enum tone ieji_cord21[2]  = {TONE_F4, TONE_A3};

struct cord ieji_cords[22] = {
  {ieji_cord0 ,     NOIRE, 2},
  {ieji_cord1 ,     CROCHE, 2},
  {ieji_cord2 ,     NOIRE, 2},
  {ieji_cord3 ,     NOIRE, 2},
  {ieji_cord4 ,     CROCHE, 2},
  {ieji_cord5 ,     NOIRE_POINTEE, 2},
  {ieji_cord6 ,     NOIRE, 2},
  {ieji_cord7 ,     CROCHE, 2},
  {ieji_cord8 ,     NOIRE, 2},
  {ieji_cord9 ,     CROCHE, 2},
  {ieji_cord10,     NOIRE_POINTEE, 2},
  {ieji_cord11,     NOIRE, 2},
  {ieji_cord12,     CROCHE, 2},
  {ieji_cord13,     NOIRE, 2},
  {ieji_cord14,     NOIRE, 2},
  {ieji_cord15,     CROCHE, 2},
  {ieji_cord16,     NOIRE_POINTEE, 2},
  {ieji_cord17,     CROCHE_POINTEE, 2},
  {ieji_cord18,     CROCHE_POINTEE, 2},
  {ieji_cord19,     NOIRE, 2},
  {ieji_cord20,     CROCHE, 2},
  {ieji_cord21,     BLANCHE, 2},
};
enum tone test_tones[2] = {TONE_E4, TONE_G4};
struct cord test_cord = {
  .size = 2,
  .duration_ms = 2000,
  .tones = test_tones
};

