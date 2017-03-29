#include "CheckBox.h"

CheckBox::CheckBox(const Vec2& pos, const Vec2& size,
        const int& widget_width, const std::string& label) :
Widget(pos, size) {
    _checked = false;
    _clicked = false;
    _state = BUTTON_NORMAL;
    _style_unchecked = Vec2(24, 0);
    _style_checked = Vec2(24, 24);

    _style = _style_unchecked;

    _box = new Box(Vec2(0, 0),
                   Vec2(100, 100),
                   Resources::GetDefaultFont(),
                   Resources::GetDefaultFontPtsize());
    Connect(_box);

    _box->IgnoreClick(true);
    _box->ShowBack(false);
    _box->SetText(label);

    SetBackGround(Resources::GetDefaultStyle(), Vec2(24, 0), 8);
}

CheckBox::~CheckBox() {
    //delete(_box);
}

void CheckBox::OnUpdate() {
    CheckClick(_camera);

    if (_clicked) {
        if (_state == BUTTON_NORMAL || _state == BUTTON_RELEASED) {
            _state = BUTTON_HOVERED;
        } else if (_state == BUTTON_HOVERED) {

        }
        _clicked = false;
    } else {
        if (_state == BUTTON_HOVERED) {
            _state = BUTTON_RELEASED;

            if (_checked) {
                _checked = false;
                SetBackGround("pgui.png", _style_unchecked, 8);
            } else {
                _checked = true;
                SetBackGround("pgui.png", _style_checked, 8);
            }
        } else if (_state == BUTTON_RELEASED) {
            _state = BUTTON_NORMAL;
        }
    }
}

void CheckBox::OnRender() {
    if (IsVisible()) {
        _back.Draw(Object::GetGlobalPos(), Object::GetSize(), GUI::GetCamera());
    }
}

void CheckBox::OnClick() {
    _clicked = true;
}

void CheckBox::SetState(bool checked) {
    _checked = checked;
}

bool CheckBox::GetState() {
    return _checked;
}
