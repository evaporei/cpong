#include "player.h"

#include "constants.h"

#include <raymath.h>

void player_init(Player *player, Vector2 pos, KeyboardKey up, KeyboardKey down) {
    player->pos = pos;
    player->yspeed = 0;
    player->up = up;
    player->down = down;
}

void player_handle_input(Player *p) {
    if (IsKeyDown(p->up)) {
        p->yspeed = -PADDLE_SPEED;
    } else if (IsKeyDown(p->down)) {
        p->yspeed = PADDLE_SPEED;
    } else {
        p->yspeed = 0;
    }
}

void player_update(Player *p) {
    float dt = GetFrameTime();

    p->pos.y += p->yspeed * dt;
    p->pos.y = Clamp(p->pos.y, 0, HEIGHT - PADDLE_HEIGHT);
}

void player_draw(Player p) {
    DrawRectangle(p.pos.x, p.pos.y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
}
