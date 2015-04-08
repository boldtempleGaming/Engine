/*
 * GUI.h
 *
 *  Created on: 13 авг. 2014 г.
 *      Author: snickers
 */

#ifndef GUI_H_
#define GUI_H_

#include <string>
#include <iostream>
#include <map>

#include <SDL2/SDL_ttf.h>

#include "Core/sys.h"
#include "Widget.h"
#include "../constants.h"

class GUI {
public:
	GUI();
	virtual ~GUI();

	static TTF_Font* LoadFont(const std::string& fname, const int& ptsize);
	
        static void OnInit();
        static void OnUpdate();
        static void OnRender();
	static void OnCleanUp();
        
        static Widget* GetRoot();
        static void SetHoveredWidget(Widget* wgt);
        static Widget* GetHoveredWidget();

private:
        static Widget* _root;
        static Widget* _wgt_hovered;
	static std::map <std::string, TTF_Font* > Fonts;
};

#endif /* GUI_H_ */
