/*
 * KeyBoard.h
 *
 *  Created on: 07 сент. 2014 г.
 *      Author: snickers
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <SDL2/SDL.h>

class KeyBoard {
public:
	KeyBoard();
	virtual ~KeyBoard();

	bool isKeyDown(SDL_Scancode scancode);
private:
	static const Uint8 *Keyboard_State;

};

#endif /* KEYBOARD_H_ */
