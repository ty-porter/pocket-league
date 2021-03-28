#include <gb/gb.h>
#include <gb/console.h>
#include <gb/font.h>

#include <stdio.h>
#include <rand.h>

#include "sprites/car.c"

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

void main() {
    BGP_REG = OBP0_REG = OBP1_REG = 0xE4;

    SPRITES_8x8;

    initialize_cars(1);

    SHOW_BKG; SHOW_SPRITES;

    UINT8 timer = 0;
    UINT8 rotation = 0;

    while(1) {
        move_car_sprite(0, 64, 64, rotation);

        if (timer % 3 == 0) {
            rotation++;
        }
        
        timer++;
    }
}
