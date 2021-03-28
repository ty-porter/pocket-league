#include <gb/gb.h>
#include <gb/console.h>
#include <gb/font.h>

#include <stdio.h>
#include <rand.h>

#include "sprites/car.c"
#include "backgrounds/arena.h"

#define FLOOR               140u
#define GAME_SPEED          3 // Higher is slower

#define ARENA_X_MIN         16
#define ARENA_X_MAX         144

#define GRAVITY             1
#define MAX_VELOCITY        5
#define JUMP_ACCELERATION   10
#define ACCELERATION        1

#define CAR_1_START_X       64
#define CAR_1_START_y       64

/* Rolls the car clockwise based on *rot* param (INT8 0 - 255) */
void draw_car_roll(INT8 n, UINT8 rot) {
    UINT8 quadrant = rot / 32;

    UINT8 invert_x = 0;
    UINT8 invert_y = 0;
    unsigned char sprites[];

    if (quadrant == 0) // Car hood up, facing right
    {
        unsigned char sprites[] = { 0, 1, 2, 3 };
    }
    else if (quadrant ==  1) // Car hood up, facing downward right
    {
        unsigned char sprites[] = { 12, 13, 14, 15 };
    }
    else if (quadrant ==  2) // Car hood facing right, nose down
    {
        unsigned char sprites[] = { 11, 10, 9, 8 };
        invert_x = 1;
        invert_y = 1;
    }
    else if (quadrant ==  3) // Car hood down, facing downward left
    {
        unsigned char sprites[] = { 20, 21, 22, 23 };
    }
    else if (quadrant ==  4) // Car hood down, facing left
    {
        unsigned char sprites[] = { 3, 2, 1, 0 };
        invert_x = 1;
        invert_y = 1;
    }
    else if (quadrant ==  5) // Car hood down, facing upward left
    {
        unsigned char sprites[] = { 16, 17, 18, 19 };
    }
    else if (quadrant ==  6) // Car hood facing left, nose up
    {
        unsigned char sprites[] = { 8, 9, 10, 11 };
    }
    else if (quadrant ==  7) // Car hood up, facing upward right
    {
        unsigned char sprites[] = { 4, 5, 6, 7 };
    }
    else // Default
    {
        unsigned char sprites[] = { 0, 1, 2, 3 }; 
    }

    for (INT8 i = 0; i < 4; i++) {
        set_sprite_tile(i + (4 * n), sprites[i]);

        if (invert_y) {
            set_sprite_prop(i + (4 * n), get_sprite_prop(i + (4 * n)) | S_FLIPY);
        } else {
            set_sprite_prop(i + (4 * n), get_sprite_prop(i + (4 * n)) & ~S_FLIPY);
        }

        if (invert_x) {
            set_sprite_prop(i + (4 * n), get_sprite_prop(i + (4 * n)) | S_FLIPX);
        } else {
            set_sprite_prop(i + (4 * n), get_sprite_prop(i + (4 * n)) & ~S_FLIPX);
        }
    }
}

void move_car_sprite(INT8 n, INT8 x, INT8 y, INT8 rot) {
    INT8 spr_offset = n * 4;

    move_sprite(0 + spr_offset, x,     y    );
    move_sprite(1 + spr_offset, x,     y + 8);
    move_sprite(2 + spr_offset, x + 8, y    );
    move_sprite(3 + spr_offset, x + 8, y + 8);

    draw_car_roll(n, rot);
}

void initialize_cars(INT8 n) {
    set_sprite_data(0, 24, car);

    for(INT8 i = 0; i < n; i++) {
        for(INT8 j = 0; j < 4; j++) {
            set_sprite_tile(j + (4 * i), j);

            if (i % 2 == 1) {
                set_sprite_prop(j + (4 * i), get_sprite_prop(i) | S_FLIPX);
            }
        }

        move_car_sprite(i, 32 * 2 * (i + 1), 64, 0);
    }
}

INT8 debounced_input(INT8 target, INT8 new, INT8 old) {
    return (new & target) && !(old & target);
}

void clamp_velocity(INT8 *d_x, INT8 *d_y) {
    if (*d_x > MAX_VELOCITY) {
        *d_x = MAX_VELOCITY;
    } 
    else if (*d_x < MAX_VELOCITY) {
        *d_x = -MAX_VELOCITY;
    }

    if (*d_y > MAX_VELOCITY) {
        *d_y = MAX_VELOCITY;
    } 
    else if (*d_y < MAX_VELOCITY) {
        *d_y = -MAX_VELOCITY;
    }
}

void initialize_background() {
    set_bkg_data(0x0, arena_tile_count, arena_tile_data);
    set_bkg_tiles(0, 0, arena_tile_map_width, arena_tile_map_height, arena_map_data);
}

void main() {
    BGP_REG = OBP0_REG = OBP1_REG = 0xE4;

    SPRITES_8x8;

    initialize_background();
    initialize_cars(1);

    SHOW_BKG; SHOW_SPRITES;

    INT8 key1    = joypad();
    INT8 key2    = key1;

    INT8 d_x = 0;
    INT8 d_y = 0;

    UINT8 x_pos = CAR_1_START_X;
    UINT8 y_pos = CAR_1_START_y;

    UINT8 rotation = 0;
    UINT8 tick = 0;

    while(1) {
        wait_vbl_done();

        if (tick % GAME_SPEED != 0) {
            tick++;
            continue;
        }

        // Read the keys
        key2 = key1;
        key1 = joypad();

        // Jump
        if (debounced_input(J_A, key1, key2) && y_pos == FLOOR) {
            d_y = -JUMP_ACCELERATION;
        }

        // Drive
        if (key1 & J_RIGHT)  {
            d_x += ACCELERATION;
        }
        else if (key1 & J_LEFT) {
            d_x -= ACCELERATION;
        }
        else {
            if (d_x > 0) {
                d_x -= ACCELERATION;

                if (d_x <= 0) {
                    d_x = 0;
                }
            }

            if (d_x < 0) {
                d_x += ACCELERATION;

                if (d_x >= 0) {
                    d_x = 0;
                }
            }
        }

        x_pos += d_x;
        y_pos += d_y;

        if (x_pos >= ARENA_X_MAX) {
            x_pos = ARENA_X_MAX;
            d_x = 0;
        } 
        else if (x_pos <= ARENA_X_MIN) {
            x_pos = ARENA_X_MIN;
            d_x = 0;
        }

        if (y_pos >= FLOOR) {
            y_pos = FLOOR;
            d_y = 0;
        } 
        else if (y_pos < FLOOR) {
            d_y += GRAVITY;
        }

        // TODO: WIP
        // clamp_velocity(&d_x, &d_y);

        move_car_sprite(0, x_pos + d_x, y_pos + d_y, rotation);

        tick++;
    }
}
