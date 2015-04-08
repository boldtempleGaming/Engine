/*
 * Camera.h
 *
 *  Created on: 26 июля 2014 г.
 *      Author: snickers
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <SDL2/SDL.h>
#include "Core/Entity.h"
#include "constants.h"

class Camera {
public:
	static SDL_Rect cam_rect;
	static void Init(int x, int y, int w, int h);
	static void SetViewport(int width, int height);
	static bool InView(SDL_Rect* rect);
	static bool InView(int x, int y, int h, int w);
	static void Move(int dx, int dy);
	static int X();
	static int Y();
};

#endif /* CAMERA_H_ */
