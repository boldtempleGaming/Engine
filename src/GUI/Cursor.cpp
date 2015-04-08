/*
 * Cursor.cpp
 *
 *  Created on: 26 июля 2014 г.
 *      Author: Admin
 */

#include "Cursor.h"

Uint8 Cursor::button = 0;
Uint8 Cursor::state = 0;
Uint8 Cursor::clicks = 0;
Timer Cursor::timer;
SDL_Texture* Cursor::cursor_texture = nullptr;
SDL_Rect Cursor::cursor_rect;
SDL_Rect Cursor::last_rect;

void Cursor::Init(SDL_Texture* cursor, int w, int h){
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_bool(0));

	if(cursor != nullptr){
		cursor_texture = cursor;
	}

	cursor_rect = {0,0,w,h};
        last_rect = cursor_rect;
}

void Cursor::Update(){
        if(last_rect.x != cursor_rect.x || last_rect.y != cursor_rect.x){
            last_rect.x = cursor_rect.x;
            last_rect.y = cursor_rect.y;
        }
            
    Uint8 state = SDL_GetMouseState( &(cursor_rect.x),  &(cursor_rect.y) );
        
        if(state & SDL_BUTTON(SDL_BUTTON_LEFT)) button = SDL_BUTTON_LEFT;
        else if (state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) button = SDL_BUTTON_MIDDLE;
        else if (state & SDL_BUTTON(SDL_BUTTON_RIGHT)) button = SDL_BUTTON_RIGHT;
        else button = 0;
        
        if(state != 0) state = SDL_PRESSED;
        else state = SDL_RELEASED;    
}

void Cursor::Draw(){
	Surface::Draw(cursor_texture, &cursor_rect);
}

int Cursor::X(){
	return cursor_rect.x;
}

int Cursor::Y(){
	return cursor_rect.y;
}
