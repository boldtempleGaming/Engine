#include "Button.h"

Button::Button(Object* owner, const Vec2& pos, const Vec2& size, const std::string& font, int font_pt_size) :
        Box(owner, pos, size, font, font_pt_size){
    ShowBack(true);
    _clicked = false;
}

Button::~Button(){

}

void Button::SetStyle(const std::string& style, const Vec2& pos_normal, const Vec2& pos_pressed, int tile_resolution = 8) {
    _back_style = style;
    _pos_normal = pos_normal;
    _pos_pressed = pos_pressed;
    _tile_resolution = tile_resolution;
    SetBackGround(_back_style, _pos_normal, _tile_resolution);
}

void Button::RegisterAction(std::function<void(void)> action){
    _action = action;
}

void Button::OnUpdate(){
    if(!IsVisible()){
        return;
    }

    CheckClick(GUI::GetCamera());
    if(_clicked){
        if(_state == BUTTON_NORMAL || _state == BUTTON_RELEASED){
            _state = BUTTON_HOVERED;
            SetBackGround(_back_style, _pos_pressed, _tile_resolution);
        }else if(_state == BUTTON_HOVERED){

        }
        _clicked = false;
    }else{
        if(_state == BUTTON_HOVERED){
            _state = BUTTON_RELEASED;
            Action();
        }else if(_state == BUTTON_RELEASED){
            _state = BUTTON_NORMAL;
            SetBackGround(_back_style, _pos_normal, _tile_resolution);
        }
    }

}

void Button::SetPos(const Vec2& pos){
    Object::SetPos(pos);

    //Justify text to center
    _text_draw_rect = {GetPos().x + (GetSize().x - TEXT_OFFSET)/2 - _text_size.x/2,
                       GetPos().y + (GetSize().y - TEXT_OFFSET)/2 - _text_size.y/2,
                       GetSize().x - TEXT_OFFSET,
                       GetSize().y - TEXT_OFFSET};
}

void  Button::OnClick(){
    _clicked = true;
}

void Button::Action(){
    //Call action function or object member
    if(_action != nullptr){
        _action();
    }
}
