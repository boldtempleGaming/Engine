#include "Timer.h"

const Uint32 Timer::SECOND = 1000;
const Uint32 Timer::MINUTE = Timer::SECOND * 60;
const Uint32 Timer::HOUR = Timer::MINUTE * 60;

Uint32 Timer::Now(){
    return SDL_GetTicks();
}
