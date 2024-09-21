#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#define WIDTH 1280
#define HEIGHT 720

#define TITLE "pong"
#define SMALL_FONT_SIZE 32
#define SCORE_FONT_SIZE 96

#define PADDLE_WIDTH 15
#define PADDLE_HEIGHT 60

#define PADDLE_SPEED 600

#define BALL_WIDTH 12
#define BALL_HEIGHT 12

#define BALL_VEL_X 300.f
#define BALL_VEL_Y 150.f

typedef enum State {
    START_STATE,
    PLAY_STATE
} State;

typedef struct Player {
    Vector2 pos;
    unsigned int score;
} Player;

void handleKeyPressed(State *state) {
    if (IsKeyPressed(KEY_SPACE)) {
        switch (*state) {
            case START_STATE:
                *state = PLAY_STATE;
                break;
            case PLAY_STATE:
                *state = START_STATE;
                break;
        }
    }
}

void handleInput(Player *p1, Player *p2) {
    float dt = GetFrameTime();

    if (IsKeyDown(KEY_W)) {
        p1->pos.y = p1->pos.y - PADDLE_SPEED * dt;
    } else if (IsKeyDown(KEY_S)) {
        p1->pos.y = p1->pos.y + PADDLE_SPEED * dt;
    }

    if (IsKeyDown(KEY_UP)) {
        p2->pos.y = p2->pos.y - PADDLE_SPEED * dt;
    } else if (IsKeyDown(KEY_DOWN)) {
        p2->pos.y = p2->pos.y + PADDLE_SPEED * dt;
    }
}

void debugState(State state) {
    switch (state) {
        case START_STATE:
            DrawText("start", 0, 0, 8, WHITE);
            break;
        case PLAY_STATE:
            DrawText("play", 0, 0, 8, WHITE);
            break;
    }
}

typedef struct Ball {
    Vector2 pos;
    Vector2 velocity;
} Ball;

int main(void) {
#ifndef DEBUG
    SetTraceLogLevel(LOG_ERROR);
#endif
    InitWindow(WIDTH, HEIGHT, "pong");

    // SetRandomSeed(time(NULL));

    State state = START_STATE;

    Font font = LoadFontEx("./font.ttf", SMALL_FONT_SIZE, NULL, 0);

    Vector2 title_size = MeasureTextEx(font, TITLE, SMALL_FONT_SIZE, 0);
    Vector2 title_pos = Vector2{
        (WIDTH / 2.f) - title_size.x / 2.f,
        (60.f / 2) - title_size.y / 2.f
    };

    Player p1 = { .pos = Vector2{15, 90}, .score = 0 };
    Player p2 = { .pos = Vector2{WIDTH - 30, HEIGHT - 150}, .score = 0 };

    Ball ball = {
        .pos = Vector2{WIDTH / 2.f - BALL_WIDTH / 2.f, HEIGHT / 2.f - BALL_HEIGHT / 2.f},
        .velocity = Vector2{GetRandomValue(0, 1) ? BALL_VEL_X : -BALL_VEL_X, GetRandomValue(0, 1) ? BALL_VEL_Y : -BALL_VEL_Y}
    };

    while (!WindowShouldClose()) {
        handleKeyPressed(&state);
        handleInput(&p1, &p2);

        if (state == PLAY_STATE) {
            ball.pos = Vector2Add(ball.pos, Vector2Scale(ball.velocity, GetFrameTime()));
        }

        BeginDrawing();
            ClearBackground(Color{ 40, 45, 52, 255 });
            debugState(state);

            // DrawFPS(0, 0);
            DrawTextEx(font, "pong", title_pos, SMALL_FONT_SIZE, 0, WHITE);

            DrawTextEx(font, TextFormat("%d", p1.score), Vector2{WIDTH / 2.f - 150, HEIGHT / 3.f}, SCORE_FONT_SIZE, 0, WHITE);
            DrawTextEx(font, TextFormat("%d", p2.score), Vector2{WIDTH / 2.f + 120, HEIGHT / 3.f}, SCORE_FONT_SIZE, 0, WHITE);

            DrawRectangle(p1.pos.x, p1.pos.y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);

            DrawRectangle(p2.pos.x, p2.pos.y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);

            DrawRectangle(ball.pos.x, ball.pos.y, BALL_WIDTH, BALL_HEIGHT, WHITE);
        EndDrawing();
    }

    UnloadFont(font);

    CloseWindow();

    return 0;
}
