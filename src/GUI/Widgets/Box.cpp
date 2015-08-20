/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widgets/Box.cpp
!*/

#include "GUI/Widgets/Box.h"
#include <iostream>
#include <sstream>

Box::Box(Object* owner, const Vec2& pos, const Vec2& size, const std::string& font, int font_pt_size) :
        Widget(owner, pos, size)
{
    ShowBack(false);
    _text.Init(0, 0, "", font, font_pt_size);

    _text_texture = SDL_CreateTexture(Window::GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_TARGET, GetSize().x - TEXT_OFFSET,
                                      GetSize().y - TEXT_OFFSET);
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
            _back.Draw(Object::GetGlobalPos(), Object::GetSize(), GUI::GetCamera() );
        }
        Surface::Draw(_text_texture, &_text_draw_rect);
    }
}

void Box::SetPos(const Vec2 &pos) {
    Object::SetPos(pos);

    _text_draw_rect = {GetPos().x,
                  GetPos().y,
                  GetSize().x - TEXT_OFFSET,
                  GetSize().y - TEXT_OFFSET};
}

void  Box::OnClick(){

}

void Box::SetText(const std::string &str) {
    //change the rendering target
    SDL_SetRenderTarget(Window::GetRenderer(), _text_texture);
    SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 0); // tranceparent surface
    SDL_RenderClear(Window::GetRenderer());

    std::istringstream stream(str);
    std::string line;

    int row = TEXT_OFFSET;
    int max_width = 0;

    while(std::getline(stream, line)){
        _text.SetText(line);
        _text.SetPos(TEXT_OFFSET, row);
        _text.Draw();

        row += _text.GetH() + LINE_SPACE;

        if(_text.GetW() > max_width){
            max_width = _text.GetW();
        }
    }

    _text_size.x = max_width;
    _text_size.y = row - LINE_SPACE - TEXT_OFFSET;

    if(_text_size.x > GetSize().x - TEXT_OFFSET){
        _text_size.x = GetSize().x - TEXT_OFFSET;
    }

    if(_text_size.y > GetSize().y - TEXT_OFFSET){
        _text_size.y = GetSize().y - TEXT_OFFSET;
    }

    SetPos(GetPos());

    //back to default target
    SDL_SetRenderDrawColor(Window::GetRenderer(), BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255);
    SDL_SetRenderTarget(Window::GetRenderer(), nullptr);
}