#include "ball.h"

#include "constants.h"

#include <raymath.h>

void ball_init(Ball *ball) {
    ball->pos = Vector2{WIDTH / 2.f - BALL_WIDTH / 2.f, HEIGHT / 2.f - BALL_HEIGHT / 2.f};
    ball->velocity = Vector2{GetRandomValue(0, 1) ? BALL_VEL_X : -BALL_VEL_X, GetRandomValue(0, 1) ? BALL_VEL_Y : -BALL_VEL_Y};
}

void ball_update(Ball *ball, State state) {
    if (state == PLAY_STATE) {
        ball->pos = Vector2Add(ball->pos, Vector2Scale(ball->velocity, GetFrameTime()));
    }
}

void ball_draw(Ball ball) {
    DrawRectangle(ball.pos.x, ball.pos.y, BALL_WIDTH, BALL_HEIGHT, WHITE);
}
