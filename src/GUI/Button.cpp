/* 
 * File:   Button.cpp
 * Author: WinPooh32
 * 
 * Created on 2 Feb 2015 г., 18:44
 */

#include "Button.h"
#include <iostream>

Button::Button(SDL_Rect rect, std::string lable, void (*OnClick)()){
    this->SetCallback(OnClick);
    
    _pt_size = DEFAULT_PTSIZE;
    
    _rect.w = rect.w;
    _rect.h = rect.h;
    
    if(lable.length() > 0) _lable.Init(0, 0, lable,  DEFAULT_FONT, _pt_size);
    
    _skin = Surface::LoadTexture("pgui.png");
    
    Vec2 pos;
    SetBackground(&pos);
    
    Move(rect.x, rect.y);
    //cur_style = style.normal;
}

Button::Button(const Button& orig){
}

Button::~Button(){
    
}

void Button::OnUpdate(){
    if(this == GUI::GetHoveredWidget()){
        if(Cursor::button == SDL_BUTTON_LEFT){
            if (_state != STATE_PRESSED){
                _state = STATE_PRESSED;
                SetBackground(&style.pressed);
            }
        }else if (_state != STATE_HOVERED){
            
            if(_state == STATE_PRESSED){
                if(_callback != nullptr){
                    (*_callback)();
                }
            }
            _state = STATE_HOVERED;
            SetBackground(&style.hover);
        }
    }else if (_state != STATE_NORMAL){
        _state = STATE_NORMAL;
        SetBackground(&style.normal);
    }
    
    Widget::OnUpdate();
}

void Button::OnRender(){
    SDL_Rect draw = {screen_X, screen_Y, _rect.w, _rect.h};
    
    if(_show_background){
        Surface::Draw(_back, &draw);
    }
    //Surface::DrawRect(&draw, 0, 200, 0, 255);
    _lable.Draw();
}

void Button::Move(const int& x, const int& y){
    Widget::Move(x, y);
    _lable.SetPos(screen_X + _rect.w/2 - _lable.GetW()*0.5f, 
                  screen_Y + _rect.h/2 - _lable.GetH()*0.5f);
}
