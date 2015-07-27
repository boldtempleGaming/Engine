/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widgets/Box.cpp
!*/

#include "GUI/Widgets/Box.h"
#include <iostream>
#include <sstream>

const int TEXT_OFFSET = 4; // pixels
const int LINE_SPACE = 1;

Box::Box(Object* owner, const Vec2& pos, const Vec2& size, const std::string& font, int font_pt_size) :
        Widget(owner, pos, size)
{
    ShowBack(false);
    _text.Init(TEXT_OFFSET, TEXT_OFFSET, "", font, font_pt_size);

    _text_texture = SDL_CreateTexture(Window::GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_TARGET, GetSize().x - TEXT_OFFSET*2,
                                      GetSize().y - TEXT_OFFSET*2);
    SDL_SetTextureBlendMode(_text_texture, SDL_BLENDMODE_BLEND);

    SetPos(pos);
}

Box::~Box() {
    SDL_DestroyTexture(_text_texture);
}

void Box::OnUpdate(){
    //Object::CheckClick();
}

void Box::OnRender() {
    if (_visible) {
        if (_bg_visible){
            _back.Draw(Object::GetGlobalPos(), Object::GetSize(), Window::GetCamera() );
        }
        Surface::Draw(_text_texture, &_text_rect);
    }
}

void Box::SetPos(const Vec2 &pos) {
    Object::SetPos(pos);

    _text_rect = {GetPos().x + TEXT_OFFSET,
                  GetPos().y + TEXT_OFFSET,
                  GetSize().x - TEXT_OFFSET*2,
                  GetSize().y - TEXT_OFFSET*2};
}

void  Box::OnClick(){
    //std::cout << "YOHOHO BOX clicked: "<< GetId() << std::endl;
}

void Box::SetText(const std::string &str) {
    //change the rendering target
    SDL_SetRenderTarget(Window::GetRenderer(), _text_texture);
    SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 0); // tranceparent surface
    SDL_RenderClear(Window::GetRenderer());

    std::istringstream stream(str);
    std::string line;

    int row = TEXT_OFFSET;

    while(std::getline(stream, line)){
        _text.SetText(line);
        _text.SetPos(TEXT_OFFSET, row);
        _text.Draw();

        row += _text.GetH() + LINE_SPACE;
    }

    //back to default target
    SDL_SetRenderDrawColor(Window::GetRenderer(), BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255);
    SDL_SetRenderTarget(Window::GetRenderer(), nullptr);
}