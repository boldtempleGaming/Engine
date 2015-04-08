/*
 * Ship.cpp
 *
 *  Created on: 17 сент. 2014 г.
 *      Author: snickers
 */

#include "Ship.h"
#include <iostream>
#include <cmath>

#include "GUI/Window.h"
#include "GUI/Cursor.h"

Ship::Ship() {
	rect.x = 0;
	rect.y = 0;
	speed = 0;
	angle = 0;
	direct = Vec2(1.0f, 0.0f);
}

Ship::~Ship() {
}

void Ship::OnUpdate() {

	//Move ship
	if (speed > 1) { // >1 - anti stairs movement
            Move(Vec2(rect.x += direct.x * speed, rect.y += direct.y * speed));
            speed -= 0.5f;
	}else if(speed < -1){
            Move(Vec2(rect.x += direct.x * speed, rect.y += direct.y * speed));
            speed += 0.5f;
        }

	if (keyb.isKeyDown(SDL_SCANCODE_UP)) {
		if (speed < MAX_SPEED)
			speed += 1.0f;
	}
        
        if (keyb.isKeyDown(SDL_SCANCODE_DOWN)) {
		if (speed > -MAX_SPEED)
			speed -= 1.0f;
	}

	if (keyb.isKeyDown(SDL_SCANCODE_R)) {
            Move(Vec2(0.0f, 0.0f));
		speed = 0;
		direct = Vec2(1.0f, 0.0f);
		angle = 0;
	}


	if (keyb.isKeyDown(SDL_SCANCODE_KP_PLUS)){
		Window::SetMode(Window::GetWidth() + 64, Window::GetHeight() + 64, false, "Проба пера");
		Camera::SetViewport(Window::GetWidth(),  Window::GetHeight());
	}
	if (keyb.isKeyDown(SDL_SCANCODE_KP_MINUS)){
		Window::SetMode(Window::GetWidth() - 64, Window::GetHeight() - 64, false, "Проба пера");
		Camera::SetViewport(Window::GetWidth(),  Window::GetHeight());
	}

	if (keyb.isKeyDown(SDL_SCANCODE_LEFT)) {
		Rotate(-9.0f);
	} else if (keyb.isKeyDown(SDL_SCANCODE_RIGHT)) {
		Rotate(9.0f);
	}
	if (keyb.isKeyDown(SDL_SCANCODE_SPACE)) {
		gun_timer.Start();

		if ( gun_timer.GetTime() > 200 ) {
			Vec2 vect;
			vect.x = this->rect.x + this->rect.w * 3.0f;
			vect.y = this->rect.y + this->rect.h * 3.0f;
			new Bullet(vect, direct, angle);
			gun_timer.Stop();
		}
	}

	//check borders
	//move ship if it not in cam view
	if (rect.x + Camera::X() + rect.w < 0) {
		Move(Vec2(Camera::cam_rect.w + rect.w, rect.y));
	} else if (rect.x + Camera::X() - rect.w > Camera::cam_rect.w) {
		Move(Vec2(-rect.w, rect.y));
	} else if (rect.y + Camera::Y() + rect.h < 0) {
		Move(Vec2(rect.x, Camera::cam_rect.h + rect.h));
	} else if (rect.y + Camera::Y() - rect.h > Camera::cam_rect.h) {
		Move(Vec2(rect.x, -rect.h));
	}

}

void Ship::OnRender(const double& interpolation) {

	float interpolated_speed;
	if(speed > 1){
		interpolated_speed = speed * interpolation;
	}else{
		interpolated_speed = 0;
	}

	SDL_Rect tmpRect = {
			rect.x + Camera::X() + (int)(direct.x * interpolated_speed),
			rect.y + Camera::Y() + (int)(direct.y * interpolated_speed),
			rect.w,
			rect.h };

	if (Camera::InView(&tmpRect)) {

		//TODO REMOVE LINE AND SQUARE drawing
		//Линия и квадратик
		SDL_SetRenderDrawColor(Window::GetRenderer(), 255, 255, 0, 255);
		SDL_RenderDrawLine(Window::GetRenderer(), rect.x + 0.5f * rect.w,
				rect.y + 0.5f * rect.h,
				rect.x + 0.5f * rect.w + direct.x * speed * 10,
				rect.y + 0.5f * rect.h + direct.y * speed * 10);
		SDL_RenderDrawRect(Window::GetRenderer(), &tmpRect);
		SDL_SetRenderDrawColor(Window::GetRenderer(), BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255);
		Surface::Draw(texture, nullptr, &tmpRect, angle+double(90));
	}

}

void Ship::Rotate(const int& da) {
	angle += da;
	//direct = Vec2(0.0f , -1.0f).GetRotated(angle);
	//direct = Vec2(cos(angle * GRADUS), sin(angle * GRADUS));
        if(direct == Vec2(1.0f, 0.0f));
        direct = (Vec2(1.0f, 0.0f)).GetRotated(angle);
}

void Ship::OnCollide(Entity* ent){
	//Move ship
	if (speed > 1) { // >1 - anti stairs movement
            speed = -4;
            Move(Vec2(rect.x += direct.x * speed, rect.y += direct.y * speed));
	}else if(speed < -1){
            speed = 4;
            Move(Vec2(rect.x += direct.x * speed, rect.y += direct.y * speed));
    }
}
