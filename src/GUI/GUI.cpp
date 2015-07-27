/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /gui/gui.cpp
!*/

#include "GUI.h"

Object* GUI::_last_clicked = nullptr;

GUI::GUI() {

}

GUI::~GUI() {

}

void GUI::OnInit(){
	//TTF FONTS INIT---------------------------------------------------
	if (TTF_Init() == -1) {
		std::cout << "TTF_Init Error: " << SDL_GetError() << std::endl;
	}
}

void GUI::OnUpdate(){

}

void GUI::OnRender(){

}

void  GUI::SetLastCliked(Object* obj){
    _last_clicked = obj;
}

Object*  GUI::GetLastClicked(){
    return _last_clicked;
}
