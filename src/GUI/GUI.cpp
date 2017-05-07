/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/gui.cpp
!*/

#include "GUI.h"

Object* GUI::_top_mouse_btn = nullptr;
Object* GUI::_top_wheeled = nullptr;
Camera* GUI::_camera = nullptr;

GUI::GUI() {

}

GUI::~GUI() {

}

Camera* GUI::GetCamera() {
    return _camera;
}


void GUI::OnInit(){
	//TTF FONTS INIT---------------------------------------------------
	if (TTF_Init() == -1) {
		std::cout << "TTF_Init Error: " << SDL_GetError() << std::endl;
	}

    //Init GUI camera
    _camera = new Camera(Vec2::ZERO, Vec2(Window::GetWidth(), Window::GetHeight()));
}

void GUI::OnUpdate(){
    if(_top_mouse_btn){
        _top_mouse_btn->OnTopMouseEvent();
    }

    if(_top_wheeled){
       _top_wheeled->OnTopMouseWheelEvent();
    }
}

void GUI::OnRender(){

}

void  GUI::SetTopObject(Object* obj){
    _top_mouse_btn = obj;
}

void GUI::SetTopWheeled(Object* obj){
    _top_wheeled = obj;
}

Object* GUI::GetLastClicked(){
    return _top_mouse_btn;
}

Object* GUI::GetTopWheeled(){
    return _top_wheeled;
}
