#include "FPScounter.h"

FPS_counter::FPS_counter() {
    old_time = 0;
    last_time = 0;

    speed_factor = 0;

    frames = 0;
    num_frames = 0;
}

void FPS_counter::OnUpdate() {
    if (old_time + 1000 < SDL_GetTicks()) {
        old_time = SDL_GetTicks();

        num_frames = frames;

        frames = 0;
    }

    speed_factor = ((SDL_GetTicks() - last_time) / 1000.0f) * 32.0f;

    last_time = SDL_GetTicks();

    frames++;
}

unsigned int FPS_counter::GetFPS() {
    return num_frames;
}
