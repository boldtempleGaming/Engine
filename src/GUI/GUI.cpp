/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/gui.cpp
!*/

#include "GUI.h"

Object* GUI::_top_object = nullptr;
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

}

void GUI::OnRender(){

}

void  GUI::SetTopObject(Object* obj){
    _top_object = obj;
}

Object*  GUI::GetLastClicked(){
    return _top_object;
}
