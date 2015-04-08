/*
 * TextBox.h
 *
 *  Created on: 08 нояб. 2014 г.
 *      Author: snickers
 */

#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include <list>
#include <iostream>
#include <string>
#include <list>

#include "Render/Surface.h"
#include "GUI/Widget.h"
#include "GUI/Text.h"
#include "GUI/colors.h"

class MessageBox: public Widget {
public:
	MessageBox(Widget* parent = nullptr, SDL_Rect rect = {0, 0, 0, 0}, 
                std::string  message = "", bool show_background = true);
	virtual ~MessageBox();

	virtual void OnEvent(SDL_Event* event);//TODO to implement it
	virtual void OnUpdate();
	virtual void OnRender();
        virtual void OnClick();
        virtual void Move(const int& x, const int& y);

	void SetPos(const int& x, const int& y);
	void SetText(const std::string& str);

private:    
        Vec2 _style_pos;
        int _pt_size;
        int _x, _y; 
        std::list<Text*> Lines;
	Text _text;
};

#endif /* TEXTBOX_H_ */
