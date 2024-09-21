#include "state.h"

#include <raylib.h>

#ifdef DEBUG
void debug_state(State state) {
    switch (state) {
        case START_STATE:
            DrawText("start", 0, 0, 8, WHITE);
            break;
        case PLAY_STATE:
            DrawText("play", 0, 0, 8, WHITE);
            break;
    }
}
#endif
