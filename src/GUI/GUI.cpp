/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /gui/gui.cpp
!*/

#include "GUI.h"

std::map <std::string, TTF_Font*> GUI::Fonts;

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

}

void GUI::OnRender(){

}

void GUI::OnCleanUp(){

	//Cleaning fonts
	auto iterator = Fonts.begin();
	while( iterator != Fonts.end()){
		TTF_CloseFont((*iterator).second);
		iterator++;
	}
	Fonts.clear();
}
