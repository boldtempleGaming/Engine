/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.

  BGE - boldtemple Cross Platform Game Engine
  /Core/Timer.h
!*/

#ifndef TIMER_H_
#define TIMER_H_

#include <iostream>
#include <SDL2/SDL.h>

static const int SECOND = 1000;
static const int MINUTE = SECOND * 60;
static const int HOUR = MINUTE * 60;

class Timer {
public:
    Timer();
    void Start();
    void Stop();
    void Pause(bool p);
    bool isPaused();
    Uint32 GetTime();

private:
    Uint32 begin_time;
    Uint32 paused_time;
    bool pause;
};

inline
Timer::Timer() {
    begin_time = 0;
    paused_time = 0;
    pause = false;
}

inline
void Timer::Start() {
    //Doesn't start if not stopped
    if (begin_time == 0) {
        pause = false;
        begin_time = SDL_GetTicks();
    }
}

inline
void Timer::Stop() {
    begin_time = 0;
    paused_time = 0;
}

inline
void Timer::Pause(bool p) {
    pause = p;
    paused_time = SDL_GetTicks() - begin_time;
}

inline
bool Timer::isPaused() {
    return pause;
}

inline
Uint32 Timer::GetTime() {
    if (pause) {
        return paused_time;
    } else if (begin_time) {
        return SDL_GetTicks() - begin_time;
    } else {
        return 0;
    }
}

#endif /* TIMER_H_ */
