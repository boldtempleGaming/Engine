/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widgets/Box.cpp
!*/

#include "GUI/Widgets/Box.h"

Box::Box(const Vec2& pos, const Vec2& size, const std::string& font, int font_pt_size) :
        Widget(pos, size)
{
    ShowBack(false);
    _text.Init(0, 0, "", font, font_pt_size);

    _text_texture = nullptr;
    _has_icon = false;
    
    SetSize(size);
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
            _back.Draw(Object::GetGlobalPos(), Object::GetSize(), GUI::GetCamera());
        }

        if(_has_icon){
            _icon.Draw(Object::GetGlobalPos(), Object::GetSize(), GUI::GetCamera());
        }

        if(_text_texture != nullptr){
            Surface::Draw(_text_texture, &_text_draw_rect);
        }
    }
}

void Box::Move(const Vec2 &delta_pos){
    SetPos(GetPos() + delta_pos);
}

void Box::SetPos(const Vec2 &pos) {
    Widget::SetPos(pos);

    _text_draw_rect = {
        static_cast<int>(GetGlobalPos().x - GUI::GetCamera()->X()),
        static_cast<int>(GetGlobalPos().y - GUI::GetCamera()->Y()),
        static_cast<int>(GetSize().x - TEXT_OFFSET),
        static_cast<int>(GetSize().y - TEXT_OFFSET)
    };
}

void Box::SetSize(const Vec2& size) {
    Object::SetSize(size);

    if (_text_texture) {
        SDL_DestroyTexture(_text_texture);
    }

    _text_texture = SDL_CreateTexture(Window::GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, size.x - TEXT_OFFSET,
            size.y - TEXT_OFFSET);
    SDL_SetTextureBlendMode(_text_texture, SDL_BLENDMODE_BLEND);
}


void  Box::OnClick(){
}

void Box::SetIcon(const std::string& icon){
    SDL_Texture* texture = Resources::GetTexture(icon);
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    _icon.SetTexture(texture);
    _icon.SetFrame(0);
    _icon.SetFrameSize(Vec2(w, h));

    _has_icon = true;
}

void Box::SetText(const std::string &str) {
    if(str.empty()){
        if(_text_texture){
            SDL_DestroyTexture(_text_texture);
            _text_texture = nullptr;
        }
        return;
    }

    SDL_Color background = Window::GetBackgroundColor();

    //change the rendering target
    SDL_SetRenderTarget(Window::GetRenderer(), _text_texture);
    SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 0); //  transparent surface
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
    SDL_SetRenderDrawColor(Window::GetRenderer(), background.r, background.g, background.b, 255);
    SDL_SetRenderTarget(Window::GetRenderer(), nullptr);
}
