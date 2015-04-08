/*
 * KeyBoard.cpp
 *
 *  Created on: 07 сент. 2014 г.
 *      Author: snickers
 */

#include "KeyBoard.h"

const Uint8 *(KeyBoard::Keyboard_State) = SDL_GetKeyboardState(nullptr);

KeyBoard::KeyBoard() {
	// TODO Auto-generated constructor stub
}

KeyBoard::~KeyBoard() {
	// TODO Auto-generated destructor stub
}

bool KeyBoard::isKeyDown(SDL_Scancode scancode){
	return Keyboard_State[scancode];
}
