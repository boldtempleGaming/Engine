/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /IO/Keyboard.cpp
!*/

#include "Keyboard.h"

const Uint8 *(Keyboard::Keyboard_State) = SDL_GetKeyboardState(nullptr);

bool Keyboard::isKeyDown(keycode key){
	return Keyboard_State[key];
}