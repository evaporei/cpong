#pragma once

#include <raylib.h>

typedef struct Player {
    Vector2 pos;
    unsigned int score;
    float yspeed;
    KeyboardKey up;
    KeyboardKey down;
} Player;

void player_init(Player *player, Vector2 pos, KeyboardKey up, KeyboardKey down);
void player_handle_input(Player *player);
void player_update(Player *player);
void player_draw(Player player);
