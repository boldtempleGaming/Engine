/*
 * Camera.cpp
 *
 *  Created on: 26 июля 2014 г.
 *      Author: snickers
 */

#include "Camera.h"

#include <iostream>

SDL_Rect Camera::cam_rect;

void Camera::Init(int x, int y, int w, int h) {
	cam_rect = {x,y,w,h};
}

void Camera::SetViewport(int width, int height) {
	cam_rect.w = width;
	cam_rect.h = height;
}

bool Camera::InView(SDL_Rect* rect) {
	//return SDL_HasIntersection(&cam_rect, rect);

	//std::cout << cam_rect.x << " " << cam_rect.w << std::endl;

	bool inX, inY;

	inX = rect->x > -rect->w  && rect->x < cam_rect.w + rect->w ;
	inY = rect->y > -rect->h  && rect->y < cam_rect.h + rect->h ;

	return inX && inY;
}

bool Camera::InView(int x, int y, int h, int w) {
	//SDL_Rect tmp_rect = {x, y, h, w};
	//return SDL_HasIntersection(&cam_rect, &tmp_rect);

	//std::cout << x << " " << y  << std::endl;

	bool inX, inY;

	inX = x > -w && x < cam_rect.w + w;
	inY = y > -h && y < cam_rect.h + h;

	return inX && inY;
}

void Camera::Move(int dx, int dy) {
	cam_rect.x += dx;
	cam_rect.y += dy;
}

int Camera::X() {
	return cam_rect.x;
}

int Camera::Y() {
	return cam_rect.y;
}
