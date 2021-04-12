#include <gb/gb.h>
#include <gb/console.h>
#include <gb/font.h>

#include <stdio.h>
#include <rand.h>
#include <stdlib.h>

#include "sprites/car.c"
#include "sprites/boost.c"
#include "sprites/player_tags.c"
#include "sprites/ball.c"
#include "sprites/cursor.c"
#include "sprites/numbers.c"

// Debug pixels for hitboxes
#include "sprites/pixel.c"

#include "backgrounds/title.h"
#include "backgrounds/arena.h"

<<<<<<< HEAD
#include "sounds/sound.c"

#define CPU_DISABLED        1 // Debug flag, 1 disables CPU inputs
=======
#define CPU_DISABLED        0 // Debug flag, 1 disables CPU inputs
#define HITBOXES_ENABLED    0 // Weird things can happen, use at risk
>>>>>>> main

#define FLOOR               140u
#define CEILING             24u
#define GAME_SPEED          3 // Higher is slower
#define BALL_FLOOR          136u
#define MAX_SCORE           5

#define ARENA_X_MIN         16
#define ARENA_X_MAX         144
#define GOAL_Y_MIN          53
#define GOAL_Y_MAX          83
#define SCORE_Y_POS         93

#define GRAVITY             1
#define JUMP_ACCELERATION   10
#define ACCELERATION        1
#define ROTATION_SPEED      15
#define BOOST_ACCELERATION  1
#define GOAL_EXPL_VELOCITY  15

#define NUM_CARS            2
#define CAR_1_START_X       20
#define CAR_1_START_y       136
#define CAR_2_START_X       140
#define CAR_2_START_Y       136

#define COUNTDOWN_X         84
#define COUNTDOWN_Y         60

#define BALL_START_X        80
#define BALL_VELOCITY       2
#define BALL_BUMP_VERT      7 // Slight upward velocity for hitting the ball
#define BOUNCE_DECAY        5

#define CPU_PREDICTION      5 // How many ticks to spend predicting ball position

typedef enum {
    TITLE,
    GAME,
    CREDITS,
    PLAYER_WINS,
    CPU_WINS
} screen_t;

const unsigned char fade_palettes[] = {
    0xFFU, 0xFEU, 0xF9U, 0xE4U,
};

void load_font() {
    font_init();
    font_t credits_font;
    credits_font = font_load(font_ibm);
    font_set(credits_font);
}

UINT8 rotation_quadrant(UINT8 rot) {
    return rot / 32;
}

/* Rolls the car clockwise based on *rot* param (INT8 0 - 255) */
void draw_car_roll(INT8 n, UINT8 rot) {
    UINT8 quadrant = rotation_quadrant(rot);

    UINT8 invert_x = 0;
    UINT8 invert_y = 0;
    unsigned char sprites[];

    if (quadrant == 0) // Car hood up, facing right
    {
        if (n == 0) {
            unsigned char sprites[] = { 0, 1, 2, 3 };
        } else
        {
            unsigned char sprites[] = { 2, 3, 0, 1};
            invert_x = 1;
        }
    }
    else if (quadrant ==  1) // Car hood up, facing downward right
    {
        if (n == 0) {
            unsigned char sprites[] = { 12, 13, 14, 15 };
        } else {
            unsigned char sprites[] = { 6, 7, 4, 5 };
            invert_x = 1;
        }
    }
    else if (quadrant ==  2) // Car hood facing right, nose down
    {
        if (n == 0) {
            unsigned char sprites[] = { 11, 10, 9, 8 };
            invert_x = 1;
            invert_y = 1;
        } else {
            unsigned char sprites[] = { 10, 11, 8, 9 };
            invert_x = 1;
        }
    }
    else if (quadrant ==  3) // Car hood down, facing downward left
    {
        if (n == 0) {
            unsigned char sprites[] = { 20, 21, 22, 23 };
        } else {
            unsigned char sprites[] = { 18, 19, 16, 17 };
            invert_x = 1;
        }
    }
    else if (quadrant ==  4) // Car hood down, facing left
    {
        if (n == 0) {
            unsigned char sprites[] = { 3, 2, 1, 0 };
            invert_x = 1;
            invert_y = 1;
        } else {
            unsigned char sprites[] = { 1, 0, 3, 2 };
            invert_y = 1;
        }
    }
    else if (quadrant ==  5) // Car hood down, facing upward left
    {
        if (n == 0) {
            unsigned char sprites[] = { 16, 17, 18, 19 };
        } else {
            unsigned char sprites[] = { 22, 23, 20, 21 };
            invert_x = 1;
        }
    }
    else if (quadrant ==  6) // Car hood facing left, nose up
    {
        if (n == 0) {
            unsigned char sprites[] = { 8, 9, 10, 11 };
        } else {
            unsigned char sprites[] = { 9, 8, 11, 10 };
            invert_y = 1;
        }
    }
    else if (quadrant ==  7) // Car hood up, facing upward right
    {
        if (n == 0) {
            unsigned char sprites[] = { 4, 5, 6, 7 };
        } else {
            unsigned char sprites[] = { 17, 16, 19, 18 };
            invert_y = 1;
        }
    }
    else // Default
    {
        if (n == 0) {
            unsigned char sprites[] = { 0, 1, 2, 3 };
        } else
        {
            unsigned char sprites[] = { 2, 3, 0, 1};
            invert_x = 1;
        }
    }

    for (INT8 i = 0; i < 4; i++) {
        set_sprite_tile(i + (5 * n), sprites[i]);

        if (invert_y) {
            set_sprite_prop(i + (5 * n), get_sprite_prop(i + (5 * n)) | S_FLIPY);
        } else {
            set_sprite_prop(i + (5 * n), get_sprite_prop(i + (5 * n)) & ~S_FLIPY);
        }

        if (invert_x) {
            set_sprite_prop(i + (5 * n), get_sprite_prop(i + (5 * n)) | S_FLIPX);
        } else {
            set_sprite_prop(i + (5 * n), get_sprite_prop(i + (5 * n)) & ~S_FLIPX);
        }
    }
}

void draw_boost_sprite(UINT8 n, UINT8 x, UINT8 y, UINT8 rot, UINT8 t) {
    UINT8 game_spr = (n * 5) + 4;
    UINT8 spr_num = 25;
    INT8 x_o = 0;
    INT8 y_o = 0;
    UINT8 tick_prop = 0x00;
    UINT8 mod_prop = 0x00;
    UINT8 quadrant = rotation_quadrant(rot);

    unsigned char cpu_offset[] = { 4, 5, 6, 7, 0, 1, 2, 3 };

    if (n == 1) {
        quadrant = cpu_offset[quadrant];
    }

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
    move_sprite((n * 5) + 4, 255, 255); // offscreen
}

void calculate_ball_hitbox(UINT8 x, UINT8 y, UINT8 *x1, UINT8 *y1, UINT8 *x2, UINT8 *y2) {
    *x1 = x;
    *x2 = x + 15;
    *y1 = y;
    *y2 = y + 15;
}

UINT8 * calculate_car_hitbox(UINT8 x, UINT8 y, UINT8 rot) {
    UINT8 quadrant = rotation_quadrant(rot);
    UINT8 hitbox[12] = { 
        255, 255, 255, 255,
        255, 255, 255, 255,
        255, 255, 255, 255
    };

    if (quadrant == 0 || quadrant == 4) {
        hitbox[0] = x;
        hitbox[1] = x + 15;
        hitbox[2] = y + 6;
        hitbox[3] = y + 10;
    }
    else if (quadrant == 1 || quadrant == 5) {
        hitbox[0] = x + 2;
        hitbox[1] = x + 8;
        hitbox[2] = y + 1;
        hitbox[3] = y + 7;

        hitbox[4] = x + 5;
        hitbox[5] = x + 11;
        hitbox[6] = y + 4;
        hitbox[7] = y + 11;

        hitbox[8] = x + 8;
        hitbox[9] = x + 13;
        hitbox[10] = y + 10;
        hitbox[11] = y + 14;
    }
    else if (quadrant == 3 || quadrant == 7) {
        hitbox[0] = x + 8;
        hitbox[1] = x + 14;
        hitbox[2] = y + 2;
        hitbox[3] = y + 6;

        hitbox[4] = x + 4;
        hitbox[5] = x + 11;
        hitbox[6] = y + 4;
        hitbox[7] = y + 11;

        hitbox[8] = x + 1;
        hitbox[9] = x + 6;
        hitbox[10] = y + 10;
        hitbox[11] = y + 13;
    }
    else if (quadrant == 2 || quadrant == 6) {
        hitbox[0] = x + 6;
        hitbox[1] = x + 10;
        hitbox[2] = y;
        hitbox[3] = y + 15;
    }

    return hitbox;
}

void draw_car_hitbox(UINT8 x, UINT8 y, UINT8 rot) {
    UINT8 *hitbox;

    hitbox = calculate_car_hitbox(x, y, rot);

    for (INT8 i = 0; i < 3; i++) {
        for (INT8 j = 0; j < 4; j++) {
            set_sprite_tile(23 + (4 * i) + j, 47);

            move_sprite(23 + (4 * i), hitbox[4 * i    ], hitbox[4 * i + 2]);
            move_sprite(24 + (4 * i), hitbox[4 * i    ], hitbox[4 * i + 3]);
            move_sprite(25 + (4 * i), hitbox[4 * i + 1], hitbox[4 * i + 2]);
            move_sprite(26 + (4 * i), hitbox[4 * i + 1], hitbox[4 * i + 3]);
        }
    }

    move_sprite(14, 255, 255); // Move player tag offscreen
}

void draw_ball_hitbox(UINT8 x, UINT8 y) {
    UINT8 x1 = x;
    UINT8 x2 = x;
    UINT8 y1 = y;
    UINT8 y2 = y;

    calculate_ball_hitbox(x, y, &x1, &y1, &x2, &y2);

    for (INT8 i = 0; i < 4; i++) {
        set_sprite_tile(i + 19, 47);
    }

    move_sprite(19, x1, y1);
    move_sprite(20, x1, y2);
    move_sprite(21, x2, y1);
    move_sprite(22, x2, y2);
}

void move_car_sprite(UINT8 n, UINT8 x, UINT8 y, UINT8 rot) {
    INT8 spr_offset = n * 5;
    
    move_sprite(0 + spr_offset, x,     y    );
    move_sprite(1 + spr_offset, x,     y + 8);
    move_sprite(2 + spr_offset, x + 8, y    );
    move_sprite(3 + spr_offset, x + 8, y + 8);

    if (n == 0) {
        move_sprite(14, x + 4, y + 12);
    } else {
        move_sprite(15, x + 4, y + 12);
    }

    draw_car_roll(n, rot);
}

void initialize_cars(INT8 n) {
    set_sprite_data(0, 24, car);
    set_sprite_data(25, 4, boost);
    set_sprite_data(32, 2, player_tags);

    for(INT8 i = 0; i < n; i++) {
        for(INT8 j = 0; j < 4; j++) {
            set_sprite_tile(j + (5 * i), j);

            if (i % 2 == 1) {
                set_sprite_prop(j + (5 * i), S_FLIPX);
            }
        }

        if (i == 0) {
            set_sprite_tile(14, 32); // Player Tag 1
            move_car_sprite(i, CAR_1_START_X, CAR_1_START_y, 0);
        } 
        else if (i == 1) {
            set_sprite_tile(15, 33); // Player Tag 2
            move_car_sprite(i, CAR_2_START_X, CAR_2_START_Y, 0);
        }
    }
}

INT8 debounced_input(INT8 target, INT8 new, INT8 old) {
    return (new & target) && !(old & target);
}

void move_ball_sprite(UINT8 x, UINT8 y, INT8 t) {
    UINT8 sprite_start = NUM_CARS * 5;

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

    // Kill any leftover properties
    set_sprite_prop(0, 0x00);
}

void initialize_score(UINT8 plr_score, UINT8 cpu_score) {
    set_sprite_data(34, 12, numbers);

    set_sprite_tile(17, 40 + plr_score);
    set_sprite_tile(18, 40 + cpu_score);

    move_sprite(17, 8, SCORE_Y_POS + 8);
    move_sprite(18, 160, SCORE_Y_POS + 8);
}

void initialize_countdown() {
    set_sprite_tile(16, 36);
    move_sprite(16, COUNTDOWN_X, COUNTDOWN_Y);
}

void initialize_title_background() {
    set_bkg_data(0x0, title_tile_count, title_tile_data);
    set_bkg_tiles(0, 0, title_tile_map_width, title_tile_map_height, title_map_data);
}

void initialize_game_background() {
    set_bkg_data(0x0, arena_tile_count, arena_tile_data);
    set_bkg_tiles(0, 0, arena_tile_map_width, arena_tile_map_height, arena_map_data);
}

void calculate_boost_velocity_vectors(UINT8 n, UINT8 rot, INT8 *d_x, INT8 *d_y) {
    UINT8 quadrant = rotation_quadrant(rot);
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

    if (n == 1) {
        x_mod *= -1;
    }

    *d_x += BOOST_ACCELERATION * x_mod;
    *d_y += BOOST_ACCELERATION * y_mod;
}

UINT8 max(UINT8 a, UINT8 b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

UINT8 min(UINT8 a, UINT8 b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

UINT8 detect_collision(UINT8 x, UINT8 y, UINT8 rot, UINT8 ball_x, UINT8 ball_y) {
    UINT8 *car_hitbox;
    
    car_hitbox = calculate_car_hitbox(x, y, rot);
    UINT8 ball_x1;
    UINT8 ball_x2;
    UINT8 ball_y1;
    UINT8 ball_y2;

    calculate_ball_hitbox(ball_x, ball_y, &ball_x1, &ball_y1, &ball_x2, &ball_y2);

    for (INT8 i = 0; i < 3; i++) { // Iterate through the possible hitboxes
        if (car_hitbox[4 * i] == 255) { // Blank hitbox
            continue;
        }

        if (car_hitbox[4 * i + 1] >= ball_x1 && car_hitbox[4 * i] <= ball_x2) {
            if (car_hitbox[4 * i + 3] >= ball_y1 && car_hitbox[4 * i + 2] <= ball_y2) {
                return 1;
            }
        }
    }

    return 0; // Default to FALSE
}

UINT8 calculate_ball_velocity_vectors(UINT8 x, UINT8 y, INT8 d_x, INT8 d_y, UINT8 rot, UINT8 ball_x, UINT8 ball_y, INT8 *ball_d_x, INT8 *ball_d_y) {
    UINT8 collision = detect_collision(x, y, rot, ball_x, ball_y);

    if (collision) {
        *ball_d_x = d_x * BALL_VELOCITY;
        *ball_d_y = d_y - (BALL_BUMP_VERT * abs(d_x) / 10);
    }

    return collision;
}

UINT8 int_distance(UINT8 x, UINT8 y) {
    if (x > y) {
        return x - y;
    } else {
        return y - x;
    }
}

sound tick_car_physics(UINT8 n, UINT8 *x, UINT8 *y, INT8 *d_x, INT8 *d_y, UINT8 *rot, UINT8 input1, UINT8 input2) {
    sound car_sound = NONE;

    // Jump
    if (debounced_input(J_A, input1, input2) && *y == FLOOR) {
        *d_y = -JUMP_ACCELERATION;
    }

    // Drive
    if (*y == FLOOR) {
        *rot = 0;
        
        if (input1 & J_RIGHT)  {
            *d_x += ACCELERATION;

            car_sound = DRIVE;
        }
        else if (input1 & J_LEFT) {
            *d_x -= ACCELERATION;

            car_sound = DRIVE;
        }
        else if (!(input1 & J_B)) {
            if (*d_x > 0) {
                *d_x -= ACCELERATION;

                if (*d_x <= 0) {
                    *d_x = 0;
                }
            }

            if (*d_x < 0) {
                *d_x += ACCELERATION;

                if (*d_x >= 0) {
                    *d_x = 0;
                }
            }
        }
    }
    else {
        if (input1 & J_RIGHT)  {
            *rot += ROTATION_SPEED;
        }
        else if (input1 & J_LEFT) {
            *rot -= ROTATION_SPEED;
        }
    }

    if (input1 & J_B) {
        calculate_boost_velocity_vectors(n, *rot, d_x, d_y);
    }

    *x += *d_x;
    *y += *d_y;

    if (*x >= ARENA_X_MAX) {
        *x = ARENA_X_MAX;
        *d_x = 0;
    } 
    else if (*x <= ARENA_X_MIN) {
        *x = ARENA_X_MIN;
        *d_x = 0;
    }

    if (*y >= FLOOR) {
        *y = FLOOR;
        *d_y = 0;
    } 
    else if (*y < FLOOR) {
        *d_y += GRAVITY;
    }

    if (*y < CEILING) {
        *y = CEILING;
        *d_y = 0;
    }

    return car_sound;
}

sound tick_ball_physics(
    UINT8 *ball_x_pos, UINT8 *ball_y_pos, INT8 *ball_d_x, INT8 *ball_d_y,
    UINT8  plr_x_pos,  UINT8  plr_y_pos,  INT8  plr_d_x,  INT8  plr_d_y,  UINT8 plr_rot,
    UINT8  cpu_x_pos,  UINT8  cpu_y_pos,  INT8  cpu_d_x,  INT8  cpu_d_y,  UINT8 cpu_rot,
    UINT8  skip_collision_checks
) {
    UINT8 ball_sound = NONE;

    if (*ball_d_x > 0) {
        if (*ball_d_x - ACCELERATION >= 0) {
            *ball_d_x -= ACCELERATION;
        }
        else {
            *ball_d_x = 0;
        }
    } 
    else if (*ball_d_x < 0) {
        if (*ball_d_x + ACCELERATION <= 0) {
            *ball_d_x += ACCELERATION;
        }
        else {
            *ball_d_x = 0;
        }
    }

    *ball_d_y += GRAVITY;

    if (*ball_y_pos + *ball_d_y > BALL_FLOOR) {
        *ball_y_pos = BALL_FLOOR;
        *ball_d_y = (*ball_d_y * -1) + (BOUNCE_DECAY * GRAVITY);

        if (*ball_d_y > 0) {
            *ball_d_y = 0;
        } else {
            ball_sound = BOUNCE;
        }
    }
    else if (*ball_y_pos + *ball_d_y < CEILING) {
        *ball_d_y *= -1;
        *ball_y_pos = CEILING;
        
        ball_sound = BOUNCE;
    }

    if (!skip_collision_checks) {
        UINT8 player_collision = calculate_ball_velocity_vectors(cpu_x_pos, cpu_y_pos, cpu_d_x, cpu_d_y, cpu_rot, *ball_x_pos, *ball_y_pos, ball_d_x, ball_d_y);
        UINT8 cpu_collision = calculate_ball_velocity_vectors(plr_x_pos, plr_y_pos, plr_d_x, plr_d_y, plr_rot, *ball_x_pos, *ball_y_pos, ball_d_x, ball_d_y);

        if (player_collision && cpu_collision) { // Pinch!
            *ball_d_x += (plr_d_x + cpu_d_x);
            *ball_d_y += (plr_d_y + cpu_d_y);
        }
    }

    UINT8 in_goal = (*ball_y_pos > GOAL_Y_MIN && *ball_y_pos < GOAL_Y_MAX);

    if (!in_goal) { // Not in the goal, should bounce
        // Handle X overflow errors
        if (abs(*ball_d_x) >= *ball_x_pos && *ball_d_x < 0) {
            *ball_x_pos = ARENA_X_MIN;
            *ball_d_x *= -1;

            ball_sound = BOUNCE;
        }
        else if (*ball_d_x + *ball_x_pos > 255) {
            *ball_x_pos = ARENA_X_MAX;
            *ball_d_x *= -1;

            ball_sound = BOUNCE;
        }
    } else {
        if (abs(*ball_d_x) >= *ball_x_pos && *ball_d_x < 0) {
            *ball_x_pos = 0;
            *ball_d_x *= 0;
        }
    }

    // Handle Y overflow errors
    if (*ball_y_pos < abs(*ball_d_y) && *ball_d_y < 0) {
        *ball_y_pos = CEILING;
        *ball_d_y *= -1;

        ball_sound = BOUNCE;
    }

    *ball_x_pos += *ball_d_x;
    *ball_y_pos += *ball_d_y;

    if (!in_goal) { // Not in the goal, should bounce
        if (*ball_x_pos > ARENA_X_MAX) {
            *ball_x_pos = ARENA_X_MAX;
            *ball_d_x *= -1;

            ball_sound = BOUNCE;
        }
        else if (*ball_x_pos < ARENA_X_MIN) {
            *ball_x_pos = ARENA_X_MIN;
            *ball_d_x *= -1;

            ball_sound = BOUNCE;
        }
    }

    if (player_collision || cpu_collision) {
        ball_sound = HIT;
    }

    return ball_sound;
}

UINT8 calculate_ball_quadrant(UINT8 car_x, UINT8 car_y, UINT8 ball_x, UINT8 ball_y) {
    if (car_x - 8 <= ball_x && car_x + 8 >= ball_x) {
        if (car_y < ball_y) {
            return 2;
        } else {
            return 6;
        }
    }
    else if (car_y - 16 <= ball_y && car_y + 16 >= ball_y) {
        if (car_x < ball_x) {
            return 4;
        } else {
            return 0;
        }
    }
    else if (car_y - 16 > ball_y) {
        if (car_x < ball_x) {
            return 3;
        } else {
            return 4;
        }
    } 
    else {
        if (car_x < ball_x) {
            return 5;
        } else {
            return 6;
        }
    }
}

INT8 calculate_cpu_input(UINT8 x, UINT8 y, UINT8 rot, UINT8 ball_x, UINT8 ball_y, INT8 ball_d_x, INT8 ball_d_y) {
    UINT8 counter = 0;
    UINT8 input = 0x00; // Nothing
    UINT8 quadrant = 0;

    while (counter < CPU_PREDICTION) {
        tick_ball_physics(
            &ball_x, &ball_y, &ball_d_x, &ball_d_y,
            255, 255, 255, 255, 0,
            255, 255, 255, 255, 0,
            1 // skip collision checking
        );

        counter++;
    }

    if (int_distance(ball_y, y) < 15) { // Same Y value, should drive if on the floor
        if (y == FLOOR) {
            if (x < ball_x) {
                input = J_RIGHT;
            } else {
                input = J_LEFT;
            }
        }
    } 
    else if(int_distance(ball_y, y) >= 15) { // Not same Y, should jump or rotate
        if (y == FLOOR && int_distance(ball_x, ball_y) < 20) { // On the floor and close
            input =  J_A;
        } else {
            if (ball_x > x) {
                input = input | J_RIGHT;
            } else {
                input = input | J_LEFT;
            }
        }
    }

    quadrant = calculate_ball_quadrant(x, y, ball_x, ball_y);

    if (rotation_quadrant(rot) == quadrant) {
        input = input | J_B;
    }

    return input;
}

void hide_everything() {
    for (UINT8 i = 0; i < 40; i++) {
        move_sprite(i, 255, 255);
    }
}

screen_t title() {
    BGP_REG = fade_palettes[0];
    OBP0_REG = OBP1_REG = 0xE4;

    SPRITES_8x8;

    INT8 key1    = joypad();
    INT8 key2    = key1;
    UINT8 cursor = 0;

    screen_t next_screen = TITLE;

    initialize_title_background();

    // Fade in the title screen
    // Hides the tile changes from credits
    for (INT8 i = 0; i < 4; i++) {
        BGP_REG = fade_palettes[i];
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
    load_font();

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

    enable_sound();
    
    if (HITBOXES_ENABLED) {
        set_sprite_data(47, 1, pixel);
    }

    SHOW_BKG; SHOW_SPRITES;

    INT8 key1 = 0x00;
    INT8 key2 = 0x00;

    INT8 cpu_key1 = 0x00;
    INT8 cpu_key2 = 0x00;

    INT8 plr_d_x = 0;
    INT8 plr_d_y = 0;

    INT8 cpu_d_x = 0;
    INT8 cpu_d_y = 0;

    INT8 ball_d_x = 0;
    INT8 ball_d_y = 0;

    UINT8 plr_x_pos = CAR_1_START_X;
    UINT8 plr_y_pos = CAR_1_START_y;

    UINT8 cpu_x_pos = CAR_2_START_X;
    UINT8 cpu_y_pos = CAR_2_START_Y;

    UINT8 ball_x_pos = BALL_START_X;
    UINT8 ball_y_pos = BALL_FLOOR;

    UINT8 plr_rot = 0;
    UINT8 cpu_rot = 0;
    UINT8 tick = 0;

    UINT8 plr_goal = 0;
    UINT8 cpu_goal = 0;

    UINT8 score_flag = 0; // Not scored yet
    UINT8 controls_enabled = 0; // Disable before countdown
    UINT8 countdown = 3;

    UINT8 reset_flag = 1; // Reset the game for next play
    UINT8 reset_countdown = 0; // How long to wait before resetting

    sound car_sound = NONE;
    sound ball_sound = NONE;

    while(1) {
        wait_vbl_done();
        
        if (reset_flag) {
            initialize_score(plr_goal, cpu_goal);
            initialize_countdown();

            key1 = 0x00;
            key2 = 0x00;

            cpu_key1 = 0x00;
            cpu_key2 = 0x00;

            plr_d_x = 0;
            plr_d_y = 0;

            cpu_d_x = 0;
            cpu_d_y = 0;

            ball_d_x = 0;
            ball_d_y = 0;

            plr_x_pos = CAR_1_START_X;
            plr_y_pos = CAR_1_START_y;

            cpu_x_pos = CAR_2_START_X;
            cpu_y_pos = CAR_2_START_Y;

            ball_x_pos = BALL_START_X;
            ball_y_pos = BALL_FLOOR;

            plr_rot = 0;
            cpu_rot = 0;
            tick = 0;

            score_flag = 0;
            controls_enabled = 0;
            countdown = 3;
            reset_flag = 0;
            reset_countdown = 0;

            car_sound = NONE;
            ball_sound = NONE;
        }

        if (tick % GAME_SPEED != 0) {
            tick++;
            continue;
        }

        if (controls_enabled) {
            // Read the keys
            key2 = key1;
            key1 = joypad();

            if (CPU_DISABLED != 1) {
                cpu_key2 = cpu_key1;
                cpu_key1 = calculate_cpu_input(cpu_x_pos, cpu_y_pos, cpu_rot, ball_x_pos, ball_y_pos, ball_d_x, ball_d_y);
            }

            if (score_flag) { // Kill CPU controls after scoring
                cpu_key1 = 0x00;
                cpu_key2 = 0x00;
            }
        }
        else {
            if ((tick + 1) % 25 == 0) {
                countdown--;
            }

            if (countdown < 1) { // Start the game!
                move_sprite(16, 255, 255);
                controls_enabled = 1;
            } 
            else {
                set_sprite_tile(16, 34 + countdown);
            }
        }

        if (score_flag) {
            ball_x_pos = 255;
            ball_y_pos = 255;
            ball_d_x = 0;
            ball_d_y = 0;

            if ((tick + 1) % 25 == 0) {
                reset_countdown--;
            }

            if (reset_countdown < 1) {
                reset_flag = 1;

                if (cpu_goal >= MAX_SCORE || plr_goal >= MAX_SCORE) {
                    hide_everything();

                    if (cpu_goal > plr_goal) {
                        return CPU_WINS;
                    }
                    else {
                        return PLAYER_WINS;
                    }
                }
            }
        }

        car_sound = tick_car_physics(0, &plr_x_pos, &plr_y_pos, &plr_d_x, &plr_d_y, &plr_rot, key1,     key2);
        tick_car_physics(1, &cpu_x_pos, &cpu_y_pos, &cpu_d_x, &cpu_d_y, &cpu_rot, cpu_key1, cpu_key2);

        if (score_flag == 0) {
            ball_sound = tick_ball_physics(
                &ball_x_pos, &ball_y_pos, &ball_d_x, &ball_d_y,          // Ball data
                 plr_x_pos,   plr_y_pos,   plr_d_x,   plr_d_y,  plr_rot, // Player data
                 cpu_x_pos,   cpu_y_pos,   cpu_d_x,   cpu_d_y,  cpu_rot, // CPU data
                 0                                                       // enable collision checking
            );
        }

        move_car_sprite(0, plr_x_pos, plr_y_pos, plr_rot);
        move_car_sprite(1, cpu_x_pos, cpu_y_pos, cpu_rot);

        move_ball_sprite(ball_x_pos, ball_y_pos, ball_d_x | ball_d_y ? tick : 0); // Move sprite to position, check if moving for sprite updates

        if (ball_x_pos < ARENA_X_MIN - 8 && !score_flag) { // In the left goal!
            cpu_goal += 1;
            score_flag = 1;
            reset_countdown = 3;

            set_sprite_tile(18, 40 + cpu_goal);

            plr_d_x = GOAL_EXPL_VELOCITY;
            cpu_d_x = GOAL_EXPL_VELOCITY;
        } 
        else if (ball_x_pos > ARENA_X_MAX + 8 && !score_flag) { // In the right goal!
            plr_goal += 1;
            score_flag = 1;
            reset_countdown = 3;

            set_sprite_tile(17, 40 + plr_goal);

            plr_d_x = -GOAL_EXPL_VELOCITY;
            cpu_d_x = -GOAL_EXPL_VELOCITY;
        }

        if (key1 & J_B) {
            draw_boost_sprite(0, plr_x_pos, plr_y_pos, plr_rot, tick % 2);
        } else {
            kill_boost_sprite(0);
        }

        if (cpu_key1 & J_B) {
            draw_boost_sprite(1, cpu_x_pos, cpu_y_pos, cpu_rot, tick % 2);
        } else {
            kill_boost_sprite(1);
        }

        // queue_car_sound(&car_sound);
        queue_ball_sound(&ball_sound);
        
        if (HITBOXES_ENABLED) { // Overlay the hitbox
            draw_car_hitbox(plr_x_pos, plr_y_pos, plr_rot);
            draw_ball_hitbox(ball_x_pos, ball_y_pos);
        }

        tick++;
    }
}

screen_t game_end(screen_t type) {
    BGP_REG = OBP0_REG = OBP1_REG = 0xE4;

    SPRITES_8x8;

    load_font();

    SHOW_BKG; SHOW_SPRITES;

    while(1) {
        delay(500);

        if (type == PLAYER_WINS) {
            printf("                    \n");
            printf("        Wow!        \n");
            delay(1000);
            printf("     Calculated.    \n");
            delay(2000);
            printf("      YOU  WIN      \n");
        } else {
            printf("                    \n");
            printf("    What a save!    \n");
            delay(1000);
            printf("       Sorry!       \n");
            delay(2000);
            printf("      YOU LOSE      \n");
        }

        delay(3000);

        return TITLE;
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
        else if (current_screen == PLAYER_WINS || current_screen == CPU_WINS) {
            current_screen = game_end(current_screen);
        }
    }
}