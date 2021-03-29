#include <gb/gb.h>
#include <gb/console.h>
#include <gb/font.h>

#include <stdio.h>
#include <rand.h>
#include <stdlib.h>

#include "sprites/car.c"
#include "sprites/boost.c"
#include "sprites/ball.c"
#include "sprites/cursor.c"

#include "backgrounds/title.h"
#include "backgrounds/arena.h"

#define FLOOR               140u
#define CEILING             24u
#define GAME_SPEED          3 // Higher is slower
#define BALL_FLOOR          136u    

#define ARENA_X_MIN         16
#define ARENA_X_MAX         144

#define GRAVITY             1
#define JUMP_ACCELERATION   10
#define ACCELERATION        1
#define ROTATION_SPEED      15
#define BOOST_ACCELERATION  1

#define NUM_CARS            1
#define CAR_1_START_X       20
#define CAR_1_START_y       136

#define BALL_START_X        80
#define BALL_VELOCITY       2
#define BALL_BUMP_VERT      10 // Slight upward velocity for hitting the ball
#define BOUNCE_DECAY        5

typedef enum {
    TITLE,
    GAME,
    CREDITS
} screen_t;

const unsigned char fade_pallettes[] = {
    0xFFU, 0xFEU, 0xF9U, 0xE4U,
};

void load_credits_font() {
    font_init();
    font_t credits_font;
    credits_font = font_load(font_ibm);
    font_set(credits_font);
}

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

void draw_boost_sprite(UINT8 n, UINT8 x, UINT8 y, UINT8 rot, UINT8 t) {
    UINT8 game_spr = (n * 4) + 4;
    UINT8 spr_num = 25;
    INT8 x_o = 0;
    INT8 y_o = 0;
    UINT8 tick_prop = 0x00;
    UINT8 mod_prop = 0x00;
    UINT8 quadrant = rot / 32;

    if (quadrant == 0) // Car hood up, facing right
    {
        x_o = -8;
        y_o = 4;
        tick_prop = S_FLIPY;
    }
    else if (quadrant ==  1) // Car hood up, facing downward right
    {
        spr_num = t ? 26 : 27;
        x_o = -4;
        y_o = -4;
        mod_prop = S_FLIPY;
    }
    else if (quadrant ==  2) // Car hood facing right, nose down
    {
        spr_num = 28;
        x_o = 4;
        y_o = -8;
        tick_prop = S_FLIPX;
        mod_prop = S_FLIPY;
    }
    else if (quadrant ==  3) // Car hood down, facing downward left
    {
        spr_num = t ? 26 : 27;
        x_o = 12;
        y_o = -4;
        mod_prop = S_FLIPY | S_FLIPX;
    }
    else if (quadrant ==  4) // Car hood down, facing left
    {
        x_o = 16;
        y_o = 4;
        tick_prop = S_FLIPY;
        mod_prop = S_FLIPX;
    }
    else if (quadrant ==  5) // Car hood down, facing upward left
    {
        spr_num = t ? 26 : 27;
        x_o = 12;
        y_o = 12;
        mod_prop = S_FLIPX;
    }
    else if (quadrant ==  6) // Car hood facing left, nose up
    {
        spr_num = 28;
        x_o = 4;
        y_o = 16;
        tick_prop = S_FLIPX;
    }
    else if (quadrant ==  7) // Car hood up, facing upward right
    {
        spr_num = t ? 26 : 27;
        x_o = -4;
        y_o = 12;
    }

    set_sprite_tile(game_spr, spr_num);
    move_sprite(game_spr, x + x_o, y + y_o);
    set_sprite_prop(game_spr, mod_prop);

    if (t) {
        set_sprite_prop(game_spr, get_sprite_prop(game_spr) | tick_prop);
    } else {
        set_sprite_prop(game_spr, get_sprite_prop(game_spr) & ~tick_prop);
    }
}

void kill_boost_sprite(UINT8 n) {
    move_sprite((n * 4) + 4, 255, 255); // offscreen
}

void move_car_sprite(UINT8 n, UINT8 x, UINT8 y, UINT8 rot) {
    INT8 spr_offset = n * 4;

    move_sprite(0 + spr_offset, x,     y    );
    move_sprite(1 + spr_offset, x,     y + 8);
    move_sprite(2 + spr_offset, x + 8, y    );
    move_sprite(3 + spr_offset, x + 8, y + 8);

    draw_car_roll(n, rot);
}

void initialize_cars(INT8 n) {
    set_sprite_data(0, 24, car);
    set_sprite_data(25, 4, boost);

    for(INT8 i = 0; i < n; i++) {
        for(INT8 j = 0; j < 4; j++) {
            set_sprite_tile(j + (4 * i), j);

            if (i % 2 == 1) {
                set_sprite_prop(j + (4 * i), get_sprite_prop(i) | S_FLIPX);
            }
        }

        if (i == 1) {
            move_car_sprite(i, CAR_1_START_X, CAR_1_START_y, 0);
        } 
        else {
            // TODO: Refactor for 2 cars
        }
    }
}

INT8 debounced_input(INT8 target, INT8 new, INT8 old) {
    return (new & target) && !(old & target);
}

void move_ball_sprite(UINT8 x, UINT8 y, INT8 t) {
    UINT8 sprite_start = NUM_CARS * 4 + 1;

    for (INT8 i = 0; i < 4; i++) {
        set_sprite_tile(sprite_start + i, t % 2 == 0 ? 30 : 31);
    }

    move_sprite(sprite_start, x, y);

    move_sprite(sprite_start + 1, x, y + 8);
    set_sprite_prop(sprite_start + 1, S_FLIPY);

    move_sprite(sprite_start + 2, x + 8, y);
    set_sprite_prop(sprite_start + 2, S_FLIPX);
    
    move_sprite(sprite_start + 3, x + 8, y + 8);
    set_sprite_prop(sprite_start + 3, S_FLIPY | S_FLIPX);
}

void initialize_ball() {
    set_sprite_data(30, 2, ball);
    
    move_ball_sprite(BALL_START_X, BALL_FLOOR, 0);
}

void initialize_cursor() {
    // Set the data
    set_sprite_data(0, 1, cursor);

    // Set the tile to the sprite
    set_sprite_tile(0, 0);
}

void initialize_title_background() {
    set_bkg_data(0x0, title_tile_count, title_tile_data);
    set_bkg_tiles(0, 0, title_tile_map_width, title_tile_map_height, title_map_data);
}

void initialize_game_background() {
    set_bkg_data(0x0, arena_tile_count, arena_tile_data);
    set_bkg_tiles(0, 0, arena_tile_map_width, arena_tile_map_height, arena_map_data);
}

void calculate_boost_velocity_vectors(UINT8 rot, INT8 *d_x, INT8 *d_y) {
    UINT8 quadrant = rot / 32;
    INT8 x_mod = 0;
    INT8 y_mod = 0;

    if (quadrant == 0) // Car hood up, facing right
    {
        x_mod = 1;
    }
    else if (quadrant ==  1) // Car hood up, facing downward right
    {
        x_mod = 1;
        y_mod = 1;
    }
    else if (quadrant ==  2) // Car hood facing right, nose down
    {
        y_mod = 1;
    }
    else if (quadrant ==  3) // Car hood down, facing downward left
    {
        x_mod = -1;
        y_mod =  1;
    }
    else if (quadrant ==  4) // Car hood down, facing left
    {
        x_mod = -1;
    }
    else if (quadrant ==  5) // Car hood down, facing upward left
    {
        x_mod = -1;
        y_mod = -1;
    }
    else if (quadrant ==  6) // Car hood facing left, nose up
    {
        y_mod = -1;
    }
    else if (quadrant ==  7) // Car hood up, facing upward right
    {
        x_mod =  1;
        y_mod = -1;
    }
    else // Default
    {

    }

    *d_x += BOOST_ACCELERATION * x_mod;
    *d_y += BOOST_ACCELERATION * y_mod;
}

void calculate_ball_velocity_vectors(UINT8 x, UINT8 y, INT8 d_x, INT8 d_y, UINT8 ball_x, UINT8 ball_y, INT8 *ball_d_x, INT8 *ball_d_y) {
    if ((x <= ball_x + 16 && x >= ball_x - 16) && (y <= ball_y + 11 && y >= ball_y - 5)) {
        *ball_d_x = d_x * BALL_VELOCITY;
        *ball_d_y = d_y - (BALL_BUMP_VERT * abs(d_x) / 10);
    }
}

screen_t title() {
    BGP_REG = fade_pallettes[0];
    OBP0_REG = OBP1_REG = 0xE4;

    SPRITES_8x8;

    // Input
    // Reading from joypad keeps held inputs from prev. screen from changing to next screen
    INT8 key1    = joypad();
    INT8 key2    = key1;
    UINT8 cursor = 0;

    screen_t next_screen = TITLE;

    initialize_title_background();

    // Fade in the title screen
    // Hides the tile changes from credits
    for (INT8 i = 0; i < 4; i++) {
        BGP_REG = fade_pallettes[i];
        delay(25);
    }

    initialize_cursor();

    SHOW_BKG; SHOW_SPRITES;

    while(1) {
        // Read the keys
        key2 = key1;
        key1 = joypad();

        // Move the cursor
        if (debounced_input(J_DOWN, key1, key2) && cursor != 1) {
            cursor = 1;
        }

        if (debounced_input(J_UP, key1, key2) && cursor != 0) {
            cursor = 0;
        }

        if (cursor == 0) {
            move_sprite(0, 60, 77); // Start
        }
        else {
            move_sprite(0, 51, 89); // Credits
        }

        // Check selection when start is pressed
        if (debounced_input(J_START, key1, key2)) {
            // Move the cursor off the screen
            move_sprite(0, 255, 255);

            if (cursor == 0) {
                // Here we go!
                next_screen = GAME;
                return next_screen;
            }

            if (cursor == 1) {
                // Credits
                next_screen = CREDITS;
                return next_screen;
            }
        }
    }
}

screen_t credits() {
    BGP_REG = OBP0_REG = OBP1_REG = 0xE4;

    SPRITES_8x8;

    // Make sure the font tiles are initialized in GB mem
    load_credits_font();

    screen_t next_screen = TITLE;
    
    INT8 key1 = joypad();
    INT8 key2 = key1;

    SHOW_BKG; SHOW_SPRITES;

    printf("  POCKET LEAGUE(c)  \n");
    printf(" 2021  Tyler Porter \n");
    printf("                    \n");
    printf(" Distributed  under \n");
    printf("    MIT  License    \n");
    printf("                  \n\n"); 
    printf("https://github.com/ \n");
    printf("ty-porter/          \n");
    printf("gb-pocket-league      ");

    while(1) {
        // Read the keys
        key2 = key1;
        key1 = joypad();

        if (debounced_input(J_START, key1, key2) ) {
            return next_screen;
        }
    }
}

screen_t game() {
    BGP_REG = OBP0_REG = OBP1_REG = 0xE4;

    SPRITES_8x8;

    initialize_game_background();
    initialize_cars(NUM_CARS);
    initialize_ball();

    SHOW_BKG; SHOW_SPRITES;

    INT8 key1    = joypad();
    INT8 key2    = key1;

    INT8 d_x = 0;
    INT8 d_y = 0;

    INT8 ball_d_x = 0;
    INT8 ball_d_y = 0;

    UINT8 x_pos = CAR_1_START_X;
    UINT8 y_pos = CAR_1_START_y;

    UINT8 ball_x_pos = BALL_START_X;
    UINT8 ball_y_pos = BALL_FLOOR;

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
        if (y_pos == FLOOR) {
            rotation = 0;
            
            if (key1 & J_RIGHT)  {
                d_x += ACCELERATION;
            }
            else if (key1 & J_LEFT) {
                d_x -= ACCELERATION;
            }
            else if (!(key1 & J_B)) {
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
        }
        else {
            if (key1 & J_RIGHT)  {
                rotation += ROTATION_SPEED;
            }
            else if (key1 & J_LEFT) {
                rotation -= ROTATION_SPEED;
            }
        }

        if (key1 & J_B) {
            calculate_boost_velocity_vectors(rotation, &d_x, &d_y);
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

        if (y_pos < CEILING) {
            y_pos = CEILING;
            d_y = 0;
        }


        if (ball_d_x > 0) {
            if (ball_d_x - ACCELERATION >= 0) {
                ball_d_x -= ACCELERATION;
            }
            else {
                ball_d_x = 0;
            }
        } 
        else if (ball_d_x < 0) {
            if (ball_d_x + ACCELERATION <= 0) {
                ball_d_x += ACCELERATION;
            }
            else {
                ball_d_x = 0;
            }
        }

        ball_d_y += GRAVITY;

        if (ball_y_pos + ball_d_y > BALL_FLOOR) {
            ball_y_pos = BALL_FLOOR;
            ball_d_y = (ball_d_y * -1) + (BOUNCE_DECAY * GRAVITY);

            if (ball_d_y > 0) {
                ball_d_y = 0;
            }
        }
        else if (ball_y_pos + ball_d_y < CEILING) {
            ball_d_y *= -1;
            ball_y_pos = CEILING;
        }

        calculate_ball_velocity_vectors(x_pos, y_pos, d_x, d_y, ball_x_pos, ball_y_pos, &ball_d_x, &ball_d_y);

        // Handle overflow errors
        if (abs(ball_d_x) >= ball_x_pos && ball_d_x < 0) {
            ball_x_pos = ARENA_X_MIN;
            ball_d_x *= -1;
        }
        else if (ball_d_x + ball_x_pos > 255) {
            ball_x_pos = ARENA_X_MAX;
            ball_d_x *= -1;
        }

        if (ball_y_pos < abs(ball_d_y) && ball_d_y < 0) {
            ball_y_pos = CEILING;
            ball_d_y *= -1;
        }

        ball_x_pos += ball_d_x;
        ball_y_pos += ball_d_y;

        if (ball_x_pos > ARENA_X_MAX) {
            ball_x_pos = ARENA_X_MAX;
            ball_d_x *= -1;
        }
        else if (ball_x_pos < ARENA_X_MIN) {
            ball_x_pos = ARENA_X_MIN;
            ball_d_x *= -1;
        }

        move_car_sprite(0, x_pos, y_pos, rotation);
        move_ball_sprite(ball_x_pos, ball_y_pos, ball_d_x | ball_d_y ? tick : 0); // Move sprite to position, check if moving for sprite updates

        if (key1 & J_B) {
            draw_boost_sprite(0, x_pos, y_pos, rotation, tick % 2);
        } else {
            kill_boost_sprite(0);
        }

        tick++;
    }
}

void main() {
    BGP_REG = OBP0_REG = OBP1_REG = 0xE4;

    SPRITES_8x8;

    // Current screen, defaults to TITLE
    screen_t current_screen = TITLE;

    while(1) {
        if (current_screen == TITLE) {
            current_screen = title();
        }
        else if (current_screen == GAME) {
            current_screen = game();
        }
        else if (current_screen == CREDITS) {
            current_screen = credits();
        }
    }
}