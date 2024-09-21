#pragma once

#include <raylib.h>

#include "state.h"

typedef struct Ball {
    Vector2 pos;
    Vector2 velocity;
} Ball;

void ball_init(Ball *ball);
void ball_update(Ball *ball, State state);
void ball_draw(Ball ball);
