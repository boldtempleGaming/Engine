/*
 * Widget.cpp
 *
 *  Created on: 24 сент. 2014 г.
 *      Author: snickers
 */

#include "Widget.h"
#include "GUI.h"

std::list<Widget*> Widget::ClickList;
bool Widget::some_locked = false;

Widget::Widget(Widget* parent, int x, int y, int w, int h) {
	SetParent(parent);
        SetVisible(true);
        
	_rect = {x, y, w, h};
        
        screen_X = x;
        screen_Y = y;
        
        _is_removing = false;
        _isFixed = true;
        _show_background = true;
        _callback = nullptr;
        
        _skin = nullptr;  
        _back = nullptr;
}

Widget::~Widget() {
        _is_removing = true;
	//Delete all chindren
	for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
		if ((*it) != nullptr) {
			delete (*it);
		}
	}
	ChildrenList.clear();
        
        //Ask parent to remove this child
	if (_parent != nullptr) {
		_parent->RemoveChild(this);
	}
}

void Widget::Move(const int& x, const int& y) {
    
        _rect.x = x;
        _rect.y = y;
        
        drag_x = _rect.x;
        drag_y = _rect.y;
    
    if(_parent == nullptr){
        screen_X = _rect.x;
        screen_Y = _rect.y;
    }else{
        screen_X = _parent->screen_X + _rect.x;
        screen_Y = _parent->screen_Y + _rect.y;
    }
        for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
            (*it)->Move((*it)->_rect.x, (*it)->_rect.y);
	}
} 

void Widget::SetParent(Widget* parent) {

	_parent = parent;

	if (_parent != nullptr) {
		_parent->AddChild(this);
	}

}

void Widget::SetWidth(const int& width) {
	_rect.w = width;
}

void Widget::SetHeight(const int& height) {
	_rect.h = height;
}

void Widget::SetVisible(const bool& visible) {
	_visible = visible;
}

void Widget::SetCallback(void (*callback)(void)){
    _callback = callback;
}

void Widget::SetBackground(Vec2* style_pos){
    if (_show_background) {
        if (!_back) {
            SDL_DestroyTexture(_back); 
           _back = SDL_CreateTexture(Window::GetRenderer(), SDL_PIXELFORMAT_RGBA8888, 
                                      SDL_TEXTUREACCESS_TARGET, _rect.w + 2, _rect.h + 2);
            SDL_SetTextureBlendMode(_back, SDL_BLENDMODE_BLEND);
        }
        SDL_Rect rct = {0, 0, _rect.w, _rect.h};
        Surface::GetSkinnedRect(_skin, _back, style_pos, &rct);
    }
}

Widget* Widget::GetParent() {
	return _parent;
}

SDL_Rect Widget::GetRect() {
	return _rect;
}

const bool& Widget::isVisible() {
	return _visible;
}

void Widget::OnEvent(SDL_Event* event) {

}


void Widget::OnUpdate() {
    
    if(some_locked) return;
    tmp = {screen_X, screen_Y, _rect.w, _rect.h};
    rect_cursor = {Cursor::X(), Cursor::Y(), 1, 1}; //TODO WTF PERFOMANCE???
    if(this == GUI::GetHoveredWidget()){
        if(SDL_IntersectRect(&rect_cursor, &tmp, &tmp) != SDL_TRUE){
            GUI::SetHoveredWidget(nullptr);
        }
    } else if(SDL_IntersectRect(&rect_cursor, &tmp, &tmp) == SDL_TRUE){
        GUI::SetHoveredWidget(this);
    }
}

void Widget::OnRender() {
	//do nothing
}

void Widget::OnClick(){
    if(!_isFixed) {
        Move(_rect.x + Cursor::cursor_rect.x - Cursor::last_rect.x,
             _rect.y + Cursor::cursor_rect.y - Cursor::last_rect.y);
    }
}

void Widget::OnUpdateChildren() {

	if (ChildrenList.empty()) {
		return;
	}

	for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
		(*it)->OnUpdate();
		(*it)->OnUpdateChildren();
	}

}

void Widget::OnRenderChildren() {

	if (ChildrenList.empty() || !_visible) {
		return;
	}

	for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
		(*it)->OnRender();
		(*it)->OnRenderChildren();
	}

}

void Widget::AddChild(Widget* child) {

	if (!ChildrenList.empty()) {
		for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
			if (*it == child) {
				std::cout << "Widget::AddChild() DEBUG: child is existed."
						<< std::endl; //TODO Is checking for child existance needed?
				return;
			}
		}
	}

	ChildrenList.push_back(child);

}

void Widget::RemoveChild(Widget* child) {
	if (ChildrenList.empty() || child == nullptr || _is_removing) {
		return;
	}

	for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
		if (*it == child) {
			std::cout << "Widget::RemoveChild() DEBUG: child was deleted."<< std::endl;
                        ChildrenList.erase(it);
			return;
		}
	}

}
