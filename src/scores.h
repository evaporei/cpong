#pragma once

#include "ball.h"

typedef struct Scores {
    unsigned int p1;
    unsigned int p2;
} Scores;

void scores_init(Scores *scores);

void scores_increment(Scores *scores, Direction dir);

void scores_draw(Font *font, Scores scores);
