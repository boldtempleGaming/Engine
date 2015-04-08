/*
 * Timer.cpp
 *
 *  Created on: 07 сент. 2014 г.
 *      Author: snickers
 */

#include "Timer.h"

#include <iostream>

Timer::Timer() {
	begin_time = 0;
	paused_time = 0;
	pause = false;
}

void Timer::Start() {
	//Don't start if not stopped
	if (begin_time == 0) {
		pause = false;
		begin_time = SDL_GetTicks();
	}
}

void Timer::Stop() {
	begin_time = 0;
	paused_time = 0;
}

void Timer::Pause(bool p) {
	pause = p;
	paused_time = SDL_GetTicks() - begin_time;
}

bool Timer::isPaused() {
	return pause;
}

Uint32 Timer::GetTime() {
	if (pause) {
		return paused_time;
	} else if (begin_time) {
		return SDL_GetTicks() - begin_time;
	} else {
		return 0;
	}
}

