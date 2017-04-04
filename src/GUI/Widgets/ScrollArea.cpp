/*!
 boldtemple Gaming ©, http://gaming.boldtemple.net
 OpenSource Project - Check Development, License & Readme Sections.

 BGE - boldtemple Cross Platform Game Engine
 /GUI/Widgets/ScrollArea.cpp
 !*/

#include "ScrollArea.h"

ScrollArea::ScrollArea(const Vec2& pos, const Vec2& size) :
        Widget(pos, size) {
    ShowBack(false);
    IgnoreClick(false);

    CreateTexture();
}

ScrollArea::~ScrollArea() {
    SDL_DestroyTexture(_area);
}

void ScrollArea::SetSize(const Vec2 &size){
    Widget::SetSize(size);
    CreateTexture();
}

void ScrollArea::OnRender() {
    if (_bg_visible){
        _back.Draw(Object::GetGlobalPos(), Object::GetSize(), GUI::GetCamera());
    }

    static SDL_Rect new_view;
    new_view = {
        static_cast<int>(_global_pos.x - GUI::GetCamera()->X()),
        static_cast<int>(_global_pos.y - GUI::GetCamera()->Y()),
        static_cast<int>(_size.x),
        static_cast<int>(_size.y)
    };
    Surface::Draw(_area, &new_view);
}

//Implements drawing children to texture
void ScrollArea::RenderChildren() {
    if (_visible) {
        //change the rendering target
        SDL_SetRenderTarget(Window::GetRenderer(), _area);
        SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(Window::GetRenderer());

        Surface::BeginViewport(_global_pos, _size);

        Object::RenderChildren();

        Surface::EndViewport();

        SDL_Color bg = Window::GetBackgroundColor();
        SDL_SetRenderDrawColor(Window::GetRenderer(), bg.r, bg.g, bg.b, bg.a);

        //change the target back to the default
        SDL_SetRenderTarget(Window::GetRenderer(), nullptr);
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
void ScrollArea::ScrollH(int step) {
    Object::MoveChildern(Vec2(step, 0));
}

void ScrollArea::CreateTexture(){
    if(_area){
        SDL_DestroyTexture(_area);
    }

    _area = SDL_CreateTexture(Window::GetRenderer(),
                              SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_TARGET,
                              static_cast<int>(GetSize().x),
                              static_cast<int>(GetSize().y));

    SDL_SetTextureBlendMode(_area, SDL_BLENDMODE_BLEND);

    //Clean texture
    SDL_SetRenderTarget(Window::GetRenderer(), _area);
    SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 0);
    SDL_RenderClear(Window::GetRenderer());

    SDL_Color bg = Window::GetBackgroundColor();
    SDL_SetRenderDrawColor(Window::GetRenderer(), bg.r, bg.g, bg.b, bg.a);

    //change the target back to the default
    SDL_SetRenderTarget(Window::GetRenderer(), nullptr);
}
