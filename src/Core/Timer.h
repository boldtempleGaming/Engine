/*
 * Timer.h
 *
 *  Created on: 07 сент. 2014 г.
 *      Author: snickers
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <SDL2/SDL.h>

const int SECOND = 1000;
const int MINUTE = SECOND * 60;
const int HOUR = MINUTE * 60;

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

#endif /* TIMER_H_ */
