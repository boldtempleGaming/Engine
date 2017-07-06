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
    IgnoreWheel(false);

    _container = new Object();

    _ChildrenList.push_back(_container);
    _container->SetOwner(this);
    _container->SetPos(Vec2::ZERO);

    CreateTexture();
}

ScrollArea::~ScrollArea() {
    SDL_DestroyTexture(_area);
}

void ScrollArea::SetPos(const Vec2& new_pos){
    Widget::SetPos(new_pos);
    _container->SetPos(GetPos());
}

void ScrollArea::SetSize(const Vec2& size){
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

void ScrollArea::UpdateChildren(){
    Surface::BeginViewport(_global_pos, _size);

    _container->UpdateChildren();

    Surface::EndViewport();
}

//Implements drawing children to texture
void ScrollArea::RenderChildren() {
    if (_visible && _owner) {
        //change the rendering target
        SDL_SetRenderTarget(Window::GetRenderer(), _area);
        SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(Window::GetRenderer());

        Vec2 tmp_pos = _global_pos;
        Vec2 tmp_size = _size;

        Surface::CullViewport(tmp_pos, tmp_size, _owner->_global_pos, _owner->_size);
        Surface::BeginViewport(tmp_pos, tmp_size);

        _container->RenderChildren();

        Surface::EndViewport();

        SDL_Color bg = Window::GetBackgroundColor();
        SDL_SetRenderDrawColor(Window::GetRenderer(), bg.r, bg.g, bg.b, bg.a);

        //change the target back to the default
        SDL_SetRenderTarget(Window::GetRenderer(), nullptr);
    }
}

void ScrollArea::Connect(Object* obj){
    _container->Connect(obj);
}

void ScrollArea::SetContentSize(const Vec2& size){
    _container->SetSize(size);
}

void ScrollArea::SetWidthLimit(const Vec2& width_limit){
    _width_limit = width_limit;
}

void ScrollArea::SetHeightLimit(const Vec2& height_limit){
    _heigth_limit = height_limit;
}

void ScrollArea::Scroll(const Vec2& direction) {
    Vec2 new_pos = _container->GetPos() + direction;
    Vec2 tmp = direction;

    //Check horizontal limits
    if(_width_limit.x != _width_limit.y){
        if(new_pos.x < _width_limit.x){
            tmp.x = _container->GetPos().x - _width_limit.x;
        }
        else if(new_pos.x + this->GetSize().x > _width_limit.y){
            tmp.x = _width_limit.y - (_container->GetPos().x  + this->GetSize().x);
        }
    }

    //Check vertical limits
    if(_heigth_limit.x != _heigth_limit.y){
        if(new_pos.y < _heigth_limit.x){
            tmp.y = _container->GetPos().y - _heigth_limit.x;
        }
        else if(new_pos.y + this->GetSize().y > _heigth_limit.y){
            tmp.y = _heigth_limit.y - (_container->GetPos().y  + this->GetSize().y);
        }
    }

    _container->Move(tmp);
}

//Vertical scroll
void ScrollArea::ScrollV(int step) {
    Scroll(Vec2(0, step));
}

//Horizontal scroll
void ScrollArea::ScrollH(int step) {
    Scroll(Vec2(step, 0));
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
