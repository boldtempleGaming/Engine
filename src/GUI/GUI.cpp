/*
 * GUI.cpp
 *
 *  Created on: 13 авг. 2014 г.
 *      Author: WinPooh32
 */

#include "GUI.h"

Widget* GUI::_root;
Widget* GUI::_wgt_hovered = nullptr;
std::map <std::string, TTF_Font*> GUI::Fonts;

GUI::GUI() {
	// TODO Auto-generated constructor stub
}

GUI::~GUI() {
	// TODO Auto-generated destructor stub
}

void GUI::OnInit(){

	//TTF FONTS INIT---------------------------------------------------
	if (TTF_Init() == -1) {
		std::cout << "TTF_Init Error: " << SDL_GetError() << std::endl;
	}
        
        _root = new Widget();
        SetHoveredWidget(nullptr);
}
/*Open and store font with individual size*/
TTF_Font* GUI::LoadFont(const std::string& fpath, const int& ptsize){

	std::string real_path = FONTS_PATH + fpath;
	std::string size_path = fpath + int_to_str(ptsize);

	//Store font with size
	TTF_Font* font = Fonts[size_path];

	if (font == nullptr) {

		font = TTF_OpenFont(real_path.c_str(), ptsize);

		if (font != nullptr) {
			Fonts[size_path] = font;
		} else {
			std::cout << " >> !WARNING! << " << SDL_GetError() << std::endl;
		}

	}
	return font;
}

void GUI::OnUpdate(){
    if (_root != nullptr) {
        _root->OnUpdateChildren();
        
        if(Cursor::button == SDL_BUTTON_LEFT){
            Widget* w = GUI::GetHoveredWidget();
            if(w){
                w->OnClick();
                Widget::some_locked = true;
            }
        }else if(Widget::some_locked){
            Widget::some_locked = false;
        }
        
    }
}

void GUI::OnRender(){
    if (_root != nullptr) {
	_root->OnRenderChildren();  
    }
}

void GUI::OnCleanUp(){

	//Cleaning fonts
	auto iterator = Fonts.begin();
	while( iterator != Fonts.end()){
		TTF_CloseFont((*iterator).second);
		iterator++;
	}
	Fonts.clear();

	//Cleaning Widgets
	delete _root;
}

Widget* GUI::GetRoot(){
    return _root;
}

void GUI::SetHoveredWidget(Widget* wgt){
    _wgt_hovered = wgt;
}

Widget* GUI::GetHoveredWidget(){
    return _wgt_hovered;
}
