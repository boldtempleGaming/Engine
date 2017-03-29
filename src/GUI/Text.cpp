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
}

void Text::Init(const int &x, const int &y, const std::string& text,
        const std::string& font, const int& ptsize) {
    _fpath = font;
    _visible = true;
    _font = Resources::GetFont(font, ptsize);
    SetPos(x, y);
    SetText(text);
}

void Text::Draw() {
    if (_visible && _texture) {
        Surface::Draw(_texture, &_rect);
    }
}

void Text::Show(const bool enabled) {
    _visible = enabled;
}

void Text::SetColor(const SDL_Color& color) {
    _color = color;
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
    _font = Resources::GetFont(_fpath, ptsize);
    //Update texture text
    GetTexture();
}

int Text::GetW() {
    return _rect.w;
}

int Text::GetH() {
    return _rect.h;
}

//Generates new texture
void Text::GetTexture() {
    if (_font) {
        if (_texture) {
            SDL_DestroyTexture(_texture);
            _texture = nullptr;
        }

        if(_text.length() > 0){
            SDL_Surface* surface = TTF_RenderUTF8_Solid(_font, _text.c_str(), _color);

            if (surface) {
                //Get texture size
                _rect.w = surface->w;
                _rect.h = surface->h;

                SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);

                _texture = SDL_CreateTextureFromSurface(Window::GetRenderer(), surface);

                //Remove surface
                SDL_FreeSurface(surface);
            }else{
                std::cerr << ">> !ERROR! << " << " Text:: " << SDL_GetError() << std::endl;
            }
        }
    } else {
        std::cerr << ">> !ERROR! << nullptr font at text: " << _text << std::endl;
    }
}
