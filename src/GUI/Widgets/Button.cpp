#include "Button.h"

Button::Button(const Vec2& pos, const Vec2& size, const std::string& font, int font_pt_size) :
Box(pos, size, font, font_pt_size) {
    ShowBack(true);
    _clicked = false;
    _action = nullptr;
}

Button::~Button() {

}

void Button::SetStyle(const std::string& style, const Vec2& pos_normal, const Vec2& pos_pressed, int tile_resolution = 8) {
    _back_style = style;
    _pos_normal = pos_normal;
    _pos_pressed = pos_pressed;
    _tile_resolution = tile_resolution;
    SetBackGround(_back_style, _pos_normal, _tile_resolution);
}

void Button::RegisterAction(std::function<void(void) > action) {
    _action = action;
}

void Button::SetText(const std::string& str){
    Box::SetText(str);

    _text_offset.x = GetSize().x/2 - _text_size.x/2;
    _text_offset.y = GetSize().y/2 - _text_size.y/2;

    Box::SetText(str);
    CalcTextPos();
}

void Button::OnUpdate() {
    if (!IsVisible()) {
        return;
    }

    CheckClick(_camera);
    if (_clicked) {
        if (_state == BUTTON_NORMAL || _state == BUTTON_RELEASED) {
            _state = BUTTON_HOVERED;
            SetBackGround(_back_style, _pos_pressed, _tile_resolution);
        } else if (_state == BUTTON_HOVERED) {

        }
        _clicked = false;
    } else {
        if (_state == BUTTON_HOVERED) {
            _state = BUTTON_RELEASED;
            Action();
        } else if (_state == BUTTON_RELEASED) {
            _state = BUTTON_NORMAL;
            SetBackGround(_back_style, _pos_normal, _tile_resolution);
        }
    }

}

void Button::SetPos(const Vec2& pos) {
    Box::SetPos(pos);

//    //Justify text to center
//    _text_draw_rect = {
//        static_cast<int> ((GetGlobalPos().x + (GetSize().x - TEXT_OFFSET) / 2 - _text_size.x / 2) - GUI::GetCamera()->X()),
//        static_cast<int> ((GetGlobalPos().y + (GetSize().y - TEXT_OFFSET) / 2 - _text_size.y / 2) - GUI::GetCamera()->Y()),
//        static_cast<int> (GetSize().x - TEXT_OFFSET),
//        static_cast<int> (GetSize().y - TEXT_OFFSET)
//    };

}

void Button::OnClick() {
    _clicked = true;
}

void Button::Action() {
    //Call action function or object member
    if (_action != nullptr) {
        _action();
    }
}
