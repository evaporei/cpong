#include "ball.h"

#include "constants.h"

#include <raymath.h>

void ball_init(Ball *ball) {
    ball->pos = Vector2{WIDTH / 2.f - BALL_WIDTH / 2.f, HEIGHT / 2.f - BALL_HEIGHT / 2.f};
    ball->velocity = Vector2{GetRandomValue(0, 1) ? BALL_VEL_X : -BALL_VEL_X, GetRandomValue(0, 1) ? BALL_VEL_Y : -BALL_VEL_Y};
}

bool ball_collides(Ball *ball, Player *player) {
    if (ball->pos.x > player->pos.x + PADDLE_WIDTH ||
            ball->pos.x + BALL_WIDTH < player->pos.x)
        return false;
    if (ball->pos.y > player->pos.y + PADDLE_HEIGHT ||
            ball->pos.y + BALL_HEIGHT < player->pos.y)
        return false;
    return true;
}

void ball_bounce_paddle(Ball *ball, Player *player, Direction dir) {
    switch (dir) {
        // player 1
        case RIGHT_DIR:
            ball->pos.x = player->pos.x + PADDLE_WIDTH;
            break;
        // player 2
        case LEFT_DIR:
            ball->pos.x = player->pos.x - PADDLE_WIDTH;
            break;
    }
    ball->velocity.x = -ball->velocity.x;
}

void ball_bounce_wall(Ball *ball) {
    if (ball->pos.y < 0) {
        ball->pos.y = 0;
        ball->velocity.y = -ball->velocity.y;
    } else if (ball->pos.y > HEIGHT - BALL_HEIGHT) {
        ball->pos.y = HEIGHT - BALL_HEIGHT;
        ball->velocity.y = -ball->velocity.y;
    }
}

void ball_update(Ball *ball, State state) {
    if (state == PLAY_STATE) {
        ball->pos = Vector2Add(ball->pos, Vector2Scale(ball->velocity, GetFrameTime()));
    }
}

void ball_draw(Ball ball) {
    DrawRectangle(ball.pos.x, ball.pos.y, BALL_WIDTH, BALL_HEIGHT, WHITE);
}
