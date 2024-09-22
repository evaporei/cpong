#pragma once

#include <raylib.h>

typedef struct Sounds {
    Sound paddle_hit;
    Sound score;
    Sound wall_hit;
} Sounds;

void sounds_init(Sounds *sounds);
void sounds_play(Sound *sound);
