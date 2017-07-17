#include "ProgressBar.h"

ProgressBar::ProgressBar(const Vec2 &pos, const Vec2 &size):
    Box(pos, size,  Resources::GetDefaultFont(), Resources::GetDefaultFontPtsize())
{
    ShowBack(true);
    SetBackGround("pgui.png", Vec2(48,24), 8);

    _progress_texture = nullptr;

    SetValue(0);
}

ProgressBar::~ProgressBar(){
    if(_progress_texture){
        SDL_DestroyTexture(_progress_texture);
    }
}

void ProgressBar::SetPos(const Vec2& pos){
    Box::SetPos(pos);

    UpdateProgressText();
    CalcProgressPos();
}

void ProgressBar::Move(const Vec2& delta_pos){
    Box::Move(delta_pos);

    UpdateProgressText();
    CalcProgressPos();
}

void ProgressBar::OnRender() {
    if (_visible) {
        if (_bg_visible){
            _back.Draw(Object::GetGlobalPos(), Object::GetSize(), GUI::GetCamera());
        }

        if(_progress_texture != nullptr){
            Surface::Draw(_progress_texture, &_progress_draw_rect);
        }

        if(_text_texture != nullptr){
            Surface::Draw(_text_texture, &_text_draw_rect);
        }
    }
}

void ProgressBar::SetText(const std::string &str){
    Box::SetText(str);

    _text_offset.x = (GetSize().x - _text_size.x)/2;
    _text_offset.y = (GetSize().y - _text_size.y)/2;

    Box::SetText(str);
    //CalcTextPos();
    CalcProgressPos();
}

void ProgressBar::UpdateProgressText(){
    SetText(std::to_string(_value) + "%");
}

void ProgressBar::SetValue(int value){
    if(value < 0){
        _value = 0;
    }
    else if(value > 100){
        _value = 100;
    }
    else{
        _value = value;
    }

    RenderProgress();
    UpdateProgressText();
}

int ProgressBar::GetValue(){
    return _value;
}

void ProgressBar::RenderProgress(){
    if(_progress_texture != nullptr){
        SDL_DestroyTexture(_progress_texture);
        _progress_texture = nullptr;
    }

    SDL_Texture* texture_skin = Resources::GetTexture("pgui.png");

    if(!texture_skin){
        return;
    }

    SDL_Rect rect2 = {0, 0, static_cast<int>(GetSize().x - 6), static_cast<int>(GetSize().y - 6)};
    SDL_Rect rect =  {0, 0, static_cast<int>(GetSize().x - 6), static_cast<int>(GetSize().y - 6)};

    _progress_texture = SDL_CreateTexture(Window::GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                                  SDL_TEXTUREACCESS_TARGET, rect.w,
                                                  rect.h);
    SDL_SetTextureBlendMode(_progress_texture, SDL_BLENDMODE_BLEND);

    Vec2 skin(20, 48);
    Surface::GetSkinnedRect(texture_skin, _progress_texture, &skin, &rect2, 4);
}

void ProgressBar::CalcProgressPos(){
    _progress_draw_rect = {static_cast<int>(GetGlobalPos().x + 6),
                           static_cast<int>(GetGlobalPos().y + 6),
                           static_cast<int>(((GetSize().x - 12) * (_value))/100),
                           static_cast<int>(GetSize().y - 12)};
}
