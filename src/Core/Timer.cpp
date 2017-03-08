#include "Timer.h"

const int Timer::SECOND = 1000;
const int Timer::MINUTE = Timer::SECOND * 60;
const int Timer::HOUR = Timer::MINUTE * 60;

Uint32 Timer::Now(){
    return SDL_GetTicks();
}
