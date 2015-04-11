/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widget.cpp
!*/

#include "GUI/Widget.h"

Widget::Widget(Object* owner, const Vec2& pos, const Vec2& size):
    _visible(true), _bg_visible(true), _size(size)
{
    _back.SetFrameSize(size);
    SetPos(pos);

    if(owner){
        owner->Connect(this);
    }
}

Widget::~Widget() {
    if (_back.GetTexture() != nullptr) {
        SDL_DestroyTexture(_back.GetTexture());
    }
}

void Widget::Show(bool show){
    _visible = show;
}

void Widget::SetBackGround(const std::string& tileset,const Vec2& skin, int tile_size){
    SDL_Rect rect = {0,0,_size.x, _size.y};

    SDL_Texture* texture_back = SDL_CreateTexture(Window::GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                               SDL_TEXTUREACCESS_TARGET, rect.w, rect.h); //TODO Memory leak, not saved SDL_Texture
    SDL_SetTextureBlendMode(texture_back, SDL_BLENDMODE_BLEND);

    SDL_Texture* texture_skin = Surface::LoadTexture(tileset);

    Surface::GetSkinnedRect(texture_skin, texture_back, &skin, &rect, tile_size);

    _back.SetTexture(texture_back);
}

const Vec2& Widget::GetSize() const{
    return _size;
}
const bool& Widget::IsVisible() const{
    return _visible;
}

const bool& Widget::BackIsVisible() const{
    return _bg_visible;
}
