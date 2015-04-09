/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /io/keyboard.cpp
!*/

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
