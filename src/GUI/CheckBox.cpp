/* 
 * File:   CheckBox.cpp
 * Author: WinPooh32
 * 
 * Created on 7 Feb 2015 г., 2:07
 */

#include "CheckBox.h"

void CheckBox::OnCheck()
{
    if (_is_checked) {
        _is_checked = false;
        SetBackground(&_style_unchecked);
    } else {
        _is_checked = true;
        SetBackground(&_style_checked);
    }
}

CheckBox::CheckBox(SDL_Rect* rect, std::string lable)
{
    if (rect)_rect = *rect;
    else _rect = {0, 0, 0, 0};
    
    Move(_rect.x, _rect.y);

    _skin = Surface::LoadTexture("pgui.png");
    _show_background = true;
    _style_unchecked = Vec2(0, 0);
    _style_checked = Vec2(24, 24);
    _is_checked = false;
    _state = STATE_NORMAL;

    SetBackground(&_style_unchecked);
}

void CheckBox::OnRender()
{
    SDL_Rect draw = {screen_X, screen_Y, _rect.w, _rect.h};

    if (_show_background) {
        Surface::Draw(_back, &draw);
    }
    //Surface::DrawRect(&draw, 0, 200, 0, 255);
    //_lable.Draw();
}

CheckBox::CheckBox(const CheckBox& orig)
{
}

CheckBox::~CheckBox()
{
}

void CheckBox::OnUpdate()
{
    if(this == GUI::GetHoveredWidget()){
        if(Cursor::button == SDL_BUTTON_LEFT){
            if (_state != STATE_PRESSED){
                _state = STATE_PRESSED;
            }
        }else if (_state != STATE_HOVERED){
            
            if(_state == STATE_PRESSED){
                OnCheck();
            }
            _state = STATE_HOVERED;
        }
    }
    Widget::OnUpdate();
}
