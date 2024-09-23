#include <stdio.h>

#include <raylib.h>
#include <raymath.h>

#include "constants.h"
#include "state.h"
#include "ball.h"
#include "player.h"
#include "scores.h"
#include "sounds.h"

Sounds sounds;

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

void player_god_ai(Player *player, Ball ball) {
    player->pos.y = ball.pos.y;
}

void handle_input(Player *p1, Player *p2) {
    player_handle_input(p1);
    /* player_handle_input(p2); */
}

void handle_collisions(State state, Player *p1, Player *p2, Ball *ball) {
    if (ball_collides(ball, p1)) {
        sounds_play(&sounds.paddle_hit);
        ball_bounce_paddle(ball, p1, RIGHT_DIR);
    } else if (ball_collides(ball, p2)) {
        sounds_play(&sounds.paddle_hit);
        ball_bounce_paddle(ball, p2, LEFT_DIR);
    }
    if (ball_bounce_wall(ball)) {
        sounds_play(&sounds.wall_hit);
    }
}

void handle_score(State *state, Ball *ball, Scores *scores, unsigned int *winning_player) {
    Direction dir = ball_is_out_of_game(ball);

    if (dir != NONE_DIR) {
        sounds_play(&sounds.score);
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
    InitAudioDevice();

    sounds_init(&sounds);

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
        // not using p2 if playing with AI
        handle_input(&p1, &p2);
        player_god_ai(&p2, ball);

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

            scores_draw(&font, scores);

            if (state == WIN_STATE) {
                DrawTextEx(font, TextFormat("player %d wins!", winning_player), win_pos, SMALL_FONT_SIZE, 0, WHITE);
            }

            draw(p1, p2, ball);
        EndDrawing();
    }

    UnloadFont(font);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
