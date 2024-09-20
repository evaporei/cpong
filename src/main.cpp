#include <stdio.h>
#include "raylib.h"

#define WIDTH 1280
#define HEIGHT 720

#define TITLE "pong"
#define FONT_SIZE 32

int main(void) {
#ifndef DEBUG
    SetTraceLogLevel(LOG_ERROR);
#endif
    InitWindow(WIDTH, HEIGHT, "game");

    Font font = LoadFontEx("./font.ttf", FONT_SIZE, NULL, 0);

    Vector2 title_size = MeasureTextEx(font, TITLE, FONT_SIZE, 0);
    Vector2 title_pos = Vector2{
        (WIDTH / 2.f) - title_size.x / 2.f,
        (60.f / 2) - title_size.y / 2.f
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(Color{ 40, 45, 52, 255 });
            DrawTextEx(font, "pong", title_pos, FONT_SIZE, 0, BLACK);
        EndDrawing();
    }

    UnloadFont(font);

    CloseWindow();

    return 0;
}
