/*!
 boldtemple Gaming ©, http://gaming.boldtemple.net
 OpenSource Project - Check Development, License & Readme Sections.

 BGE - boldtemple Cross Platform Game Engine
 /GUI/Widgets/ScrollArea.cpp
 !*/

#include "ScrollArea.h"

ScrollArea::ScrollArea(const Vec2& pos, const Vec2& size) :
        Widget(pos, size, new Camera()) {
    _camera->SetPos(GetGlobalPos());
    _camera->SetViewport(size);

    _scroll_cam_scope = false;
}

ScrollArea::~ScrollArea() {
    delete _camera;
}

void ScrollArea::OnUpdate() {

}

void ScrollArea::OnRender() {

}

//Implements drawing children to texture
void ScrollArea::RenderChildren() {
    if (_visible && _bg_visible) {
        SetTmpCam();

        SDL_Rect new_view = {
            static_cast<int>(_pos.x),
            static_cast<int>(_pos.y),
            static_cast<int>(_size.x), 
            static_cast<int>(_size.y)
        };
        
        SDL_RenderSetViewport(Window::GetRenderer(), &new_view);
        Object::RenderChildren();
        SDL_RenderSetViewport(Window::GetRenderer(), nullptr);

        SetTmpCam();
    }
}

void ScrollArea::UpdateChildren() {
    SetTmpCam();
    Object::UpdateChildren();
    SetTmpCam();
}

void ScrollArea::Connect(Object* obj){
    SetTmpCam();
    Widget::Connect(obj);
    MoveChildern(Vec2::ZERO);
    SetTmpCam();
}

void ScrollArea::Move(const Vec2& delta_pos){
    SetTmpCam();
    Widget::Move(delta_pos);
    _camera->SetPos(GetGlobalPos());
    SetTmpCam();
}

void ScrollArea::SetPos(const Vec2& new_pos){
    SetTmpCam();
    Widget::SetPos(new_pos);
    _camera->SetPos(GetGlobalPos());
    SetTmpCam();
}

void ScrollArea::Scroll(const Vec2& direct) {
    SetTmpCam();
    Object::MoveChildern(direct);
    SetTmpCam();
}

//Vertical scroll
void ScrollArea::ScrollV(int step) {
    SetTmpCam();
    Object::MoveChildern(Vec2(0, step));
    SetTmpCam();
}

//Horizontal scroll
void ScrollArea::ScollH(int step) {
    SetTmpCam();
    Object::MoveChildern(Vec2(step, 0));
    SetTmpCam();
}

void ScrollArea::SetTmpCam(){
    if(_scroll_cam_scope){
        GUI::GetCamera()->SetPos(_old_cam_pos);
        _scroll_cam_scope = false;
    }
    else{
        _old_cam_pos = GUI::GetCamera()->GetPos();
        GUI::GetCamera()->SetPos(GetGlobalPos());
        _scroll_cam_scope = true;
    }
}
