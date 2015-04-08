/*
 * FPScounter.h
 *
 *  Created on: 06 нояб. 2014 г.
 *      Author: Админ
 */

#ifndef FPSCOUNTER_H_
#define FPSCOUNTER_H_

#include <iostream>
#include <SDL2/SDL.h>

class FPS_counter {
public:
	FPS_counter();

	void OnUpdate();
	int GetFPS();
	float GetSpeedFactor();

private:
	int old_time;
	int last_time;

	int num_frames;
	int frames;

	float speed_factor;

};

#endif /* FPSCOUNTER_H_ */
