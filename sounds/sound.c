#include <gb/console.h>

typedef enum {
  NONE,
  HIT,
  BOUNCE,
  DRIVE,
  BOOST
} sound;

void enable_sound() {
  NR52_REG = 0x80;
  NR50_REG = 0x77;
  NR51_REG = 0xFF;
}

void queue_sound_car_engine() {
  NR10_REG = 0x57;
  NR11_REG = 0x3F;
  NR12_REG = 0xA3;
  NR13_REG = 0x4C;
  NR14_REG = 0xC6;
}

void queue_sound_ball_hit() {
  NR41_REG = 0x0A;
  NR42_REG = 0xB1;
  NR43_REG = 0xA8;
  NR44_REG = 0x80;
}

void queue_sound_ball_bounce() {
  NR41_REG = 0x0A;
  NR42_REG = 0x41;
  NR43_REG = 0xA8;
  NR44_REG = 0x80;
}

void queue_car_sound(sound *car_sound) {
  switch (*car_sound) {
      case DRIVE:
        queue_sound_car_engine();
  }

  *car_sound = NONE;
}

void queue_ball_sound(sound *ball_sound) {
  switch (*ball_sound) {
      case HIT:
        queue_sound_ball_hit();
      case BOUNCE:
        queue_sound_ball_bounce();
  }

  *ball_sound = NONE;
}