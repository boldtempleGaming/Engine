#include "CheckBox.h"

CheckBox::CheckBox(const Vec2& pos, const Vec2& size,
        const int& widget_width, const std::string& label) :
Widget(pos, size) {
    _checked = false;
    _clicked = false;
    _style_unchecked = Vec2(24, 0);
    _style_checked = Vec2(24, 24);

    _style = _style_unchecked;

    _box = new Box(Vec2::ZERO,
                   Vec2(widget_width, size.y),
                   Resources::GetDefaultFont(),
                   Resources::GetDefaultFontPtsize());


    _box->SetText(label);
    Vec2 txt_size = _box->GetTextSize();
    _box->SetOffset({static_cast<int>(size.x + 4.0), static_cast<int>((size.y - txt_size.y)/2), 4, 4});
    _box->SetText(label);

    Connect(_box);

    this->IgnoreClick(true);
    SetBackGround(Resources::GetDefaultStyle(), Vec2(24, 0), 8);

    _box->AddAction("mouseup", [this](){
        if (_checked) {
            _checked = false;
            SetBackGround("pgui.png", _style_unchecked, 8);
        } else {
            _checked = true;
            SetBackGround("pgui.png", _style_checked, 8);
        }
    }, this);
}

CheckBox::~CheckBox() {
}

void CheckBox::OnUpdate() {
    Widget::OnUpdate();
}

void CheckBox::OnRender() {
    if (IsVisible()) {
        _back.Draw(Object::GetGlobalPos(), Object::GetSize(), GUI::GetCamera());
    }
}

void CheckBox::OnTopMouseEvent() {
    Widget::OnTopMouseEvent();

}

void CheckBox::SetState(bool checked) {
    _checked = checked;
    //FIXME background
}

bool CheckBox::GetState() {
    return _checked;
}
