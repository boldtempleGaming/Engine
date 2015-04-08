/*
 * Text.h
 *
 *  Created on: 13 авг. 2014 г.
 *      Author: snickers
 */

#ifndef TEXT_H_
#define TEXT_H_

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "GUI/colors.h"
#include "GUI/Window.h"
#include "GUI/GUI.h"
#include "Render/Surface.h"

class Text {
public:
    	std::string _text;
	Text();
	virtual ~Text();

	void Init(const int& x, const int& y, const std::string& text,
			const std::string& font, const int& ptsize);

	void Draw();

	void Show(const bool enabled);
	void SetColor(const SDL_Color& color);
	void SetText(const std::string& text);
	//void SetFont()
	void SetSize(const int& ptsize);
	void SetPos(const int& x, const int& y);
        
        int GetW();
        int GetH();

private:
	SDL_Texture* _texture;
	TTF_Font* _font;

	std::string _fpath;

	SDL_Rect _rect;
	SDL_Color _color;

	bool _visible;

	void GetTexture();

};

#endif /* TEXT_H_ */
