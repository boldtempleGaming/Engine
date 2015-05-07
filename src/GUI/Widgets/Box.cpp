/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widgets/Box.cpp
!*/

#include "GUI/Widgets/Box.h"
#include <iostream>

Box::Box(Object* owner, const Vec2& pos, const Vec2& size) :
        Widget(owner, pos, size)
{

}

Box::~Box() {

}

void Box::OnUpdate(){
    Object::CheckClick();
}

void Box::OnRender() {
    if (_visible) {
        if (_bg_visible){
            _back.Draw(Object::GetGlobalPos(), Object::GetSize(), Window::GetCamera() );
        }
    }
}

void  Box::OnClick(){
    std::cout << "YOHOHO BOX clicked: "<< GetId() << std::endl;
}
