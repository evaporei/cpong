#include "sounds.h"

void sounds_init(Sounds *sounds) {
    sounds->paddle_hit = LoadSound("sounds/paddle_hit.wav");
    sounds->score = LoadSound("sounds/score.wav");
    sounds->wall_hit = LoadSound("sounds/wall_hit.wav");
}

void sounds_play(Sound *sound) {
    if (IsSoundReady(*sound)) {
        PlaySound(*sound);
    }
}
