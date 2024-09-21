#include <stdio.h>

#include <raylib.h>
#include <raymath.h>

#include "constants.h"
#include "state.h"
#include "ball.h"

typedef struct Player {
    Vector2 pos;
    unsigned int score;
    float yspeed;
} Player;

void handle_key_pressed(State *state, Ball *ball) {
    if (IsKeyPressed(KEY_SPACE)) {
        switch (*state) {
            case START_STATE:
                *state = PLAY_STATE;
                break;
            case PLAY_STATE:
                ball_init(ball);
                *state = START_STATE;
                break;
        }
    }
}

void handle_input(Player *p1, Player *p2) {
    if (IsKeyDown(KEY_W)) {
        p1->yspeed = -PADDLE_SPEED;
    } else if (IsKeyDown(KEY_S)) {
        p1->yspeed = PADDLE_SPEED;
    } else {
        p1->yspeed = 0;
    }

    if (IsKeyDown(KEY_UP)) {
        p2->yspeed = -PADDLE_SPEED;
    } else if (IsKeyDown(KEY_DOWN)) {
        p2->yspeed = PADDLE_SPEED;
    } else {
        p2->yspeed = 0;
    }
}

void update(State state, Player *p1, Player *p2, Ball *ball) {
    float dt = GetFrameTime();

    p1->pos.y += p1->yspeed * dt;
    p2->pos.y += p2->yspeed * dt;

    p1->pos.y = Clamp(p1->pos.y, 0, HEIGHT - PADDLE_HEIGHT);
    p2->pos.y = Clamp(p2->pos.y, 0, HEIGHT - PADDLE_HEIGHT);

    ball_update(ball, state);
}

int main(void) {
#ifndef DEBUG
    SetTraceLogLevel(LOG_ERROR);
#endif
    InitWindow(WIDTH, HEIGHT, TITLE);

    State state = START_STATE;

    Font font = LoadFontEx("./font.ttf", SMALL_FONT_SIZE, NULL, 0);

    Vector2 title_size = MeasureTextEx(font, TITLE, SMALL_FONT_SIZE, 0);
    Vector2 title_pos = Vector2{
        (WIDTH / 2.f) - title_size.x / 2.f,
        (60.f / 2) - title_size.y / 2.f
    };

    Player p1 = { .pos = Vector2{15, 90}, .score = 0, .yspeed = 0 };
    Player p2 = { .pos = Vector2{WIDTH - 30, HEIGHT - 150}, .score = 0, .yspeed = 0 };

    Ball ball;
    ball_init(&ball);

    while (!WindowShouldClose()) {
        handle_key_pressed(&state, &ball);
        handle_input(&p1, &p2);

        update(state, &p1, &p2, &ball);

        BeginDrawing();
            ClearBackground(Color{ 40, 45, 52, 255 });
#ifdef DEBUG
            DrawFPS(0, 0);
            // debug_state(state);
#endif

            DrawTextEx(font, TITLE, title_pos, SMALL_FONT_SIZE, 0, WHITE);

            DrawTextEx(font, TextFormat("%d", p1.score), Vector2{WIDTH / 2.f - 150, HEIGHT / 3.f}, SCORE_FONT_SIZE, 0, WHITE);
            DrawTextEx(font, TextFormat("%d", p2.score), Vector2{WIDTH / 2.f + 120, HEIGHT / 3.f}, SCORE_FONT_SIZE, 0, WHITE);

            DrawRectangle(p1.pos.x, p1.pos.y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);

            DrawRectangle(p2.pos.x, p2.pos.y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);

            ball_draw(ball);
        EndDrawing();
    }

    UnloadFont(font);

    CloseWindow();

    return 0;
}
