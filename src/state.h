#pragma once

typedef enum State {
    START_STATE,
    PLAY_STATE
} State;

#ifdef DEBUG
void debug_state(State state);
#endif
