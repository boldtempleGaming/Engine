/*
 * Text.cpp
 *
 *  Created on: 13 авг. 2014 г.
 *      Author: snickers
 */

#include "Text.h"

Text::Text() {

	_font = nullptr;
	_texture = nullptr;
	_visible = false;
	_rect = {0, 0, 0, 0};
	_color = COLOR_WHITE;

}

Text::~Text() {

	SDL_DestroyTexture(_texture);
	//Fonts will be destroyed with GUI

}

void Text::Init(const int &x, const int &y, const std::string& text,
		const std::string& font, const int& ptsize) {

	_fpath = font;
	_visible = true;
	_font = GUI::LoadFont(font, ptsize);
	SetPos(x, y);
	SetText(text);

}

void Text::Draw() {

	if (_visible) {
		Surface::Draw(_texture, &_rect);
	}

}

void Text::Show(const bool enabled) {

	_visible = enabled;

}

void Text::SetColor(const SDL_Color& color) {

	_color = color;
        //GetTexture();

}

void Text::SetText(const std::string& text) {

	_text = text;
	GetTexture();

}

void Text::SetPos(const int &x, const int &y) {

	_rect.x = x;
	_rect.y = y;

}

void Text::SetSize(const int &ptsize) {

	//Load font with new size (makes a copy)
	_font = GUI::LoadFont(_fpath, ptsize);
	//Update text texture
	GetTexture();
}

int Text::GetW(){
    return _rect.w;
}

int Text::GetH(){
    return _rect.h;
}

//Generates new texture
void Text::GetTexture() {

	if (_font) {
		if (_texture) {
			SDL_DestroyTexture(_texture);
			_texture = nullptr;
		}

		/*SDL_Surface* surface = TTF_RenderUTF8_Solid(_font, _text.c_str(),
				_color);
*/
                SDL_Surface* surface = TTF_RenderUTF8_Solid(_font,_text.c_str(), _color);
		_texture = SDL_CreateTextureFromSurface(Window::GetRenderer(), surface);
		//Get texture size
		SDL_QueryTexture(_texture, nullptr, nullptr, &_rect.w, &_rect.h);
		//Remove surface
		SDL_FreeSurface(surface);
	} else {
		std::cout << "Nullptr font at text: " << _text << std::endl;
	}

}
