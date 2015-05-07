/*!
 boldtemple Gaming ©, http://gaming.boldtemple.net
 OpenSource Project - Check Development, License & Readme Sections.

 BGE - boldtemple Cross Platform Game Engine
 /GUI/Widgets/ScrollArea.cpp
 !*/

#include "ScrollArea.h"

ScrollArea::ScrollArea(Object* owner, const Vec2& pos, const Vec2& size) :
        Widget(owner, pos, size) {
    SDL_Texture* texture = SDL_CreateTexture(Window::GetRenderer(),
            SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _size.x,
            _size.y);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    _back.SetTexture(texture);

    _camera.SetPos(pos);
    _camera.SetViewport(size);
}

ScrollArea::~ScrollArea() {

}

//TODO Hack :C
const Vec2& ScrollArea::GetGlobalPos() const{
    static Vec2 tmp = _global_pos;// - _pos;
    return tmp;
}

void ScrollArea::OnUpdate() {

}

void ScrollArea::OnRender() {

}

//Implements drawing children to texture
void ScrollArea::RenderChildren() {
    if (_visible && _bg_visible) {

        /*
        //change the rendering target
        SDL_SetRenderTarget(Window::GetRenderer(), _back.GetTexture());
        SDL_SetRenderDrawColor(Window::GetRenderer(), BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 0);
        SDL_RenderClear(Window::GetRenderer());
         */

        SDL_Rect new_view = {_pos.x, _pos.y, _size.x, _size.y};
        SDL_RenderSetViewport(Window::GetRenderer(), &new_view);

        Object::RenderChildren();

        //back to default target
        //SDL_SetRenderTarget(Window::GetRenderer(), nullptr);

        //draw texture to main renderer
        //_back.Draw(_global_pos, GetSize(), &_camera);

        SDL_RenderSetViewport(Window::GetRenderer(), nullptr);
    }
}

void ScrollArea::Scroll(const Vec2& direct) {
    Object::MoveChildern(direct);
}

//Vertical scroll
void ScrollArea::ScrollV(int step) {
    Object::MoveChildern(Vec2(0, step));
}

//Horizontal scroll
void ScrollArea::ScollH(int step) {
    Object::MoveChildern(Vec2(step, 0));
}
