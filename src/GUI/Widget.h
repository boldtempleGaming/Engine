/*
 * Widget.h
 *
 *  Created on: 24 сент. 2014 г.
 *      Author: snickers
 */

#ifndef WIDGET_H_
#define WIDGET_H_

#include <iostream>
#include <list>

#include <SDL2/SDL.h>

#include "Core/Vec2.h"
#include "GUI/Cursor.h"

enum widget_state{
    WGT_RELESED = 0,
    WGT_PRESSED
};

class Widget {
public:
    static bool some_locked;
        widget_state _state;
    
	Widget(Widget* parent = nullptr, int x = 0, int y = 0, int w = 0,
			int h = 0);
	virtual ~Widget();
        
        static std::list<Widget*> ClickList; // Looks like a hack :C //stores widgets collided with cursor on click

	virtual void Move(const int& x, const int& y);

	void SetParent(Widget* parent);
	void SetWidth(const int& width);
	void SetHeight(const int& height);
	void SetVisible(const bool& visible);
        void SetCallback(void (*callback)(void));// for OnClick()
        
        void AddChild(Widget* child);
	void RemoveChild(Widget* child);

	Widget* GetParent();
	SDL_Rect GetRect();
	const bool& isVisible();

	virtual void OnEvent(SDL_Event* event);//TODO implement
	virtual void OnUpdate();
	virtual void OnRender();
        virtual void OnClick();

	void OnUpdateChildren();
	void OnRenderChildren();

protected:
    struct Style{
        Vec2 normal = Vec2(0, 0);
        Vec2 hover = Vec2(24, 0);
        Vec2 pressed = Vec2(48, 0);
    } style;
    
        void (*_callback)(void); // function for OnClick()
	SDL_Rect _rect;
	int screen_X; //Позиция на экране
	int screen_Y;
        
        bool _isFixed ;
        bool _show_background;
        
        //Vec2 cur_style;
        SDL_Texture* _skin;  
        SDL_Texture* _back;
        
        void SetBackground(Vec2* style_pos);
        
private: 
        int drag_x;
        int drag_y;
    
        SDL_Rect tmp;
        SDL_Rect rect_cursor;
    
	Widget* _parent;
	bool _visible;
	bool _is_removing; 
        std::list<Widget*> ChildrenList;
};

#endif /* WIDGET_H_ */
