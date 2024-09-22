#pragma once

#include <raylib.h>

#include "state.h"
#include "player.h"

typedef enum Direction {
    LEFT_DIR,
    RIGHT_DIR
} Direction;

typedef struct Ball {
    Vector2 pos;
    Vector2 velocity;
} Ball;

void ball_init(Ball *ball);
bool ball_collides(Ball *ball, Player *player);
void ball_bounce_paddle(Ball *ball, Player *player, Direction dir);
void ball_bounce_wall(Ball *ball);
void ball_update(Ball *ball, State state);
void ball_draw(Ball ball);
