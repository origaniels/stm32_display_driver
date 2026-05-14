#pragma once
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

void play_cord(struct cord *cord);
void play_song_cords(struct cord *song, uint32_t length);
void play_song(struct note *song, uint32_t length);

extern struct note ieji[22];
extern enum tone ieji_cord0 [2];
extern enum tone ieji_cord1 [2];
extern enum tone ieji_cord2 [2];
extern enum tone ieji_cord3 [2];
extern enum tone ieji_cord4 [2];
extern enum tone ieji_cord5 [2];
extern enum tone ieji_cord6 [2];
extern enum tone ieji_cord7 [2];
extern enum tone ieji_cord8 [2];
extern enum tone ieji_cord9 [2];
extern enum tone ieji_cord10[2];
extern enum tone ieji_cord11[2];
extern enum tone ieji_cord12[2];
extern enum tone ieji_cord13[2];
extern enum tone ieji_cord14[2];
extern enum tone ieji_cord15[2];
extern enum tone ieji_cord16[2];
extern enum tone ieji_cord17[2];
extern enum tone ieji_cord18[2];
extern enum tone ieji_cord19[2];
extern enum tone ieji_cord20[2];
extern enum tone ieji_cord21[2];
extern struct cord ieji_cords[22];

extern enum tone test_tones[2];
extern struct cord test_cord;

