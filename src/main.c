#include <stdio.h>

#include <raylib.h>
#include <raymath.h>

#include "constants.h"
#include "state.h"
#include "ball.h"
#include "player.h"
#include "scores.h"

void handle_key_pressed(State *state, Ball *ball, Scores *scores, unsigned int *winning_player) {
    if (IsKeyPressed(KEY_SPACE)) {
        switch (*state) {
            case START_STATE:
                *state = PLAY_STATE;
                break;
            case PLAY_STATE:
                ball_init(ball);
                *state = START_STATE;
                break;
            case WIN_STATE:
                ball_init(ball);
                scores_init(scores);
                *winning_player = 0;
                *state = START_STATE;
                break;
        }
    }
}

void handle_input(Player *p1, Player *p2) {
    player_handle_input(p1);
    player_handle_input(p2);
}

void handle_collisions(State state, Player *p1, Player *p2, Ball *ball) {
    if (ball_collides(ball, p1)) {
        ball_bounce_paddle(ball, p1, RIGHT_DIR);
    } else if (ball_collides(ball, p2)) {
        ball_bounce_paddle(ball, p2, LEFT_DIR);
    }

    ball_bounce_wall(ball);
}

void handle_score(State *state, Ball *ball, Scores *scores, unsigned int *winning_player) {
    Direction dir = ball_is_out_of_game(ball);

    if (dir != NONE_DIR) {
        ball_init(ball);
        scores_increment(scores, dir);
        if (scores->p1 == WINNING_SCORE) {
            *winning_player = 1;
            *state = WIN_STATE;
        } else if (scores->p2 == WINNING_SCORE) {
            *winning_player = 2;
            *state = WIN_STATE;
        } else {
            *state = START_STATE;
        }
    }
}

void update(State state, Player *p1, Player *p2, Ball *ball) {
    player_update(p1);
    player_update(p2);
    ball_update(ball, state);
}

void draw(Player p1, Player p2, Ball ball) {
    player_draw(p1);
    player_draw(p2);
    ball_draw(ball);
}

int main(void) {
#ifndef DEBUG
    SetTraceLogLevel(LOG_ERROR);
#endif
    InitWindow(WIDTH, HEIGHT, TITLE);

    State state = START_STATE;

    Font font = LoadFontEx("./font.ttf", SMALL_FONT_SIZE, NULL, 0);

    Vector2 title_size = MeasureTextEx(font, TITLE, SMALL_FONT_SIZE, 0);
    Vector2 title_pos = {
        (WIDTH / 2.f) - title_size.x / 2.f,
        (60.f / 2) - title_size.y / 2.f
    };
    Vector2 win_size = MeasureTextEx(font, "player x wins!", SMALL_FONT_SIZE, 0);
    Vector2 win_pos = {
        (WIDTH / 2.f) - win_size.x / 2.f,
        (60.f / 2) - win_size.y / 2.f
    };

    Player p1;
    player_init(&p1, (Vector2){15, 90}, KEY_W, KEY_S);
    Player p2;
    player_init(&p2, (Vector2){WIDTH - 30, HEIGHT - 150}, KEY_UP, KEY_DOWN);

    Ball ball;
    ball_init(&ball);

    Scores scores;
    scores_init(&scores);

    // 0, 1 or 2
    unsigned int winning_player = 0;

    while (!WindowShouldClose()) {
        handle_key_pressed(&state, &ball, &scores, &winning_player);
        handle_input(&p1, &p2);

        if (state == PLAY_STATE) {
            handle_collisions(state, &p1, &p2, &ball);
            handle_score(&state, &ball, &scores, &winning_player);
        }
        update(state, &p1, &p2, &ball);

        BeginDrawing();
            ClearBackground((Color){ 40, 45, 52, 255 });
#ifdef DEBUG
            DrawFPS(0, 0);
            // debug_state(state);
#endif

            if (state == START_STATE && scores.p1 == 0 && scores.p2 == 0) {
                DrawTextEx(font, TITLE, title_pos, SMALL_FONT_SIZE, 0, WHITE);
            }

            DrawTextEx(font, TextFormat("%d", scores.p1), (Vector2){WIDTH / 2.f - 150, HEIGHT / 3.f}, SCORE_FONT_SIZE, 0, WHITE);
            DrawTextEx(font, TextFormat("%d", scores.p2), (Vector2){WIDTH / 2.f + 120, HEIGHT / 3.f}, SCORE_FONT_SIZE, 0, WHITE);
            if (state == WIN_STATE) {
                DrawTextEx(font, TextFormat("player %d wins!", winning_player), win_pos, SMALL_FONT_SIZE, 0, WHITE);
            }

            draw(p1, p2, ball);
        EndDrawing();
    }

    UnloadFont(font);

    CloseWindow();

    return 0;
}
