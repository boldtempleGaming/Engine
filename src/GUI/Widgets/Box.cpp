/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widgets/Box.cpp
!*/

#include "GUI/Widgets/Box.h"

Box::Box(const Vec2& pos, const Vec2& size, const std::string& font, int font_pt_size) :
        Widget(pos, size)
{
    ShowBack(false);

    _pt_size = font_pt_size;
    _text.Init(0, 0, "", font, font_pt_size);

    _text_size = Vec2::ZERO;
    _text_texture = nullptr;
    _has_icon = false;
    
    SetSize(size);
    SetPos(pos);
}

Box::~Box() {
    SDL_DestroyTexture(_text_texture);
}

void Box::OnRender() {
    if (_visible) {
        if (_bg_visible){
            _back.Draw(Object::GetGlobalPos(), Object::GetSize(), GUI::GetCamera());
        }

        if(_has_icon){
            _icon.Draw(Object::GetGlobalPos(), Object::GetSize(), GUI::GetCamera());
        }

        if(_text_texture != nullptr){
            Surface::Draw(_text_texture, &_text_draw_rect);
        }
    }
}

void Box::SetSize(const Vec2& size) {
    Object::SetSize(size);

    if (_text_texture) {
        SDL_DestroyTexture(_text_texture);
    }

    SetText(_str_text);
    CalcTextPos();
}

void Box::Move(const Vec2 &delta_pos){
    Widget::Move(delta_pos);
    CalcTextPos();
}

void Box::SetPos(const Vec2& pos){
    Widget::SetPos(pos);
    CalcTextPos();
}

void Box::SetIcon(const std::string& icon){
    SDL_Texture* texture = Resources::GetTexture(icon);
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    _icon.SetTexture(texture);
    _icon.SetFrame(0);
    _icon.SetFrameSize(Vec2(w, h));

    _has_icon = true;
}

void Box::SetText(const std::string &str) {
    _str_text = str;

    if(_text_texture){
        SDL_DestroyTexture(_text_texture);
        _text_texture = nullptr;
    }

    if(_str_text.empty()){
        return;
    }else{
        _text_texture = SDL_CreateTexture(Window::GetRenderer(),
                                          SDL_PIXELFORMAT_RGBA8888,
                                          SDL_TEXTUREACCESS_TARGET,
                                          GetSize().x - _text_offset.x - _text_offset.w,
                                          GetSize().y - _text_offset.y - _text_offset.h);
        SDL_SetTextureBlendMode(_text_texture, SDL_BLENDMODE_BLEND);
    }

    SDL_Color background = Window::GetBackgroundColor();

    //change the rendering target
    SDL_SetRenderTarget(Window::GetRenderer(), _text_texture);
    SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 0); //  transparent surface
    SDL_RenderClear(Window::GetRenderer());


    std::istringstream stream(_str_text);
    std::string line;

    int row = 0;
    int max_width = 0;

    int row_step = _pt_size + _line_spacing;

    while(std::getline(stream, line)){
        _text.SetText(line);
        _text.SetPos(0, row);
        _text.Draw();

        row += row_step;//_text.GetH() + _line_spacing;

        if(_text.GetW() >= max_width){
            max_width = _text.GetW();
        }
    }

    //Store size of text to vars
    _text_size.x = max_width;
    _text_size.y = row - _line_spacing;

    if(_text_size.x > GetSize().x - _text_offset.w){
        _text_size.x = GetSize().x - _text_offset.w;
    }

    if(_text_size.y > GetSize().y - _text_offset.h){
        _text_size.y = GetSize().y - _text_offset.h;
    }

    //back to default target
    SDL_SetRenderDrawColor(Window::GetRenderer(), background.r, background.g, background.b, 0);
    SDL_SetRenderTarget(Window::GetRenderer(), nullptr);
}

void Box::SetOffset(const SDL_Rect& offset){
    _text_offset = offset;
}

SDL_Rect Box::GetOffset(){
    return _text_offset;
}

Vec2 Box::GetTextSize() const{
    return _text_size;
}

void Box::CalcTextPos(){
    _text_draw_rect = {
        static_cast<int>(GetGlobalPos().x - _camera->X() +  _text_offset.x),
        static_cast<int>(GetGlobalPos().y - _camera->Y() +  _text_offset.y),
        static_cast<int>(GetSize().x -  _text_offset.x - _text_offset.w),
        static_cast<int>(GetSize().y -  _text_offset.y - _text_offset.h)
    };
}
