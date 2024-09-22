#include "scores.h"

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
