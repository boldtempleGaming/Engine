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

class Timer {
public:
    static const int SECOND;
    static const int MINUTE;
    static const int HOUR;

    static Uint32 Now();

    Timer();

    void Reset();
    void SetRange(Uint32 range);

    Uint32 GetRange() const;
    Uint32 GetStartTime() const;

    bool InRange() const;
    bool OutRange() const;

private:
    Uint32 _range;
    Uint32 _begin_time;
    Uint32 _finish_time;

    void UpdateFinishTime();
};

inline
Timer::Timer(): _range(0), _begin_time(0), _finish_time(0){
}

inline
void Timer::Reset() {
    _begin_time = SDL_GetTicks();
    UpdateFinishTime();
}

inline
void Timer::SetRange(Uint32 range){
    _range = range;
    UpdateFinishTime();
}

inline
Uint32 Timer::GetRange() const{
    return _range;
}

inline
Uint32 Timer::GetStartTime() const{
    return _begin_time;
}

inline
bool Timer::InRange() const{
    return SDL_GetTicks() < _finish_time;
}

inline
bool Timer::OutRange() const{
    return SDL_GetTicks() >= _finish_time;
}

inline
void Timer::UpdateFinishTime(){
    _finish_time = _begin_time + _range;
}

#endif /* TIMER_H_ */
