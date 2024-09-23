#include "scores.h"

#include "constants.h"

void scores_init(Scores *scores) {
    scores->p1 = 0;
    scores->p2 = 0;
}

void scores_increment(Scores *scores, Direction dir) {
    switch (dir) {
        case LEFT_DIR:
            scores->p2++;
            break;
        case RIGHT_DIR:
            scores->p1++;
            break;
        case NONE_DIR:
            __builtin_unreachable();
            break;
    }
}

void scores_draw(Font *font, Scores scores) {
    DrawTextEx(*font, TextFormat("%d", scores.p1), (Vector2){WIDTH / 2.f - 150, HEIGHT / 3.f}, SCORE_FONT_SIZE, 0, WHITE);
    DrawTextEx(*font, TextFormat("%d", scores.p2), (Vector2){WIDTH / 2.f + 120, HEIGHT / 3.f}, SCORE_FONT_SIZE, 0, WHITE);
}
