/*
 * Animation.h
 *
 *  Created on: 22 июля 2014 г.
 *      Author: snickers
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <SDL2/SDL.h>
#include "Core/Vec2.h"

class Animation {
public:
    Animation();

public:
	void OnAnimation();
	void SetFrameRate(Uint16 rate);
	void SetCurrentFrame(Uint16 frame);
	void SetBeginFrame(Uint16 frame);
	void SetMaxFrame(Uint16 frame);
    void SetFrameSize(const Vec2& size);

	Uint16 GetBeginFrame() const;
	Uint16 GetMaxFrame() const;
    Uint16 GetCurrentFrame() const;
    Uint16 GetFrameRate() const;
    Vec2 GetFrameSize() const;

private:
	Uint16 _begin_frame;
	Uint16 _max_frame;
	Uint16 _current_frame;
	Uint16 _frame_rate;
	Uint16 _frame_inc;
	Uint64 _old_time;
    Vec2 _frame_size;
};

#endif /* ANIMATION_H_ */
