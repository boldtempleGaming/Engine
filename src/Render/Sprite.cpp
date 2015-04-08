/*
 * Sprite.cpp
 *
 *  Created on: 05 марта 2015 г.
 *      Author: snickers
 */

#include <Render/Sprite.h>
#include <iostream>

Sprite::Sprite() :
    _texture(nullptr),
    _flip(SDL_FLIP_NONE),
    _angle(0),
    _frames_per_width(1),
    _frames_per_height(1)
{
    //Constructor
    _anim_rect.w = -1;
}

Sprite::~Sprite() {

}

void Sprite::Draw(const Vec2& pos, const Vec2& size) {
    //TODO What about performance?
    //Same performance (~1000 objects) when not animated xD

    if(_anim_rect.w < 0){
        std::cout << " >> !WARNING! <<  Sprite " << this << " undefined source frame size!" << std::endl;
    }

    SDL_Rect src_rect;
    if(_frames_per_width != 0)
        src_rect.x = (_anim_control.GetCurrentFrame() % _frames_per_width) * _anim_rect.w;
    else
        src_rect.x = 0;

    if(_frames_per_height != 0)
        src_rect.y = (_anim_control.GetCurrentFrame() / _frames_per_width) * _anim_rect.h;
    else
        src_rect.y = 0;

    src_rect.w = _anim_rect.w;
    src_rect.h = _anim_rect.h;

    SDL_Rect dst_rect = { pos.x, pos.y, size.x, size.y};

    Surface::Draw(_texture, &src_rect, &dst_rect, _angle, _flip);
    _anim_control.OnAnimation(); //update animation state
}

void Sprite::SetTexture(SDL_Texture* texture) {
    _texture = texture;

    //Get texture size
    if (_texture) {
        SDL_QueryTexture(_texture, nullptr, nullptr, &_src_rect.w,
                &_src_rect.h);
    }
}

void Sprite::SetAngle(int angle) {
    _angle = angle % 360;
}

void Sprite::SetFlip(SDL_RendererFlip flip) {
    _flip = flip;
}

SDL_Texture* Sprite::GetTexture() const {
    return _texture;
}

int Sprite::GetAngle() const {
    return _angle;
}

/*==Animation control==*/

void Sprite::SetAnimation(const Animation& anim){
    if(anim.GetBeginFrame() != _anim_control.GetBeginFrame() && anim.GetMaxFrame() != _anim_control.GetMaxFrame() ){
        _anim_control = anim;
        SetFrame(_anim_control.GetCurrentFrame());
    }
}

void Sprite::SetAnimation(int begin_frame, int end_frame) {
    _anim_control.SetBeginFrame(begin_frame);
    _anim_control.SetMaxFrame(end_frame);
}

void Sprite::SetFrameSize(const Vec2& frame_size) {
    _anim_rect.w = frame_size.x;
    _anim_rect.h = frame_size.y;
    SetFrame(_anim_control.GetCurrentFrame());
}

void Sprite::SetFrame(int frame) {
    if (_src_rect.w == 0 ||_anim_rect.w == 0 || _src_rect.h == 0 || _anim_rect.h == 0) {
        _frames_per_width = 1;
        _frames_per_height = 1;
    } else {
        _frames_per_width = _src_rect.w / _anim_rect.w;
        _frames_per_height = _src_rect.h / _anim_rect.h;
    }

    _anim_control.SetCurrentFrame(frame);
}

void Sprite::SetAnimationRate(int frame_rate) {
    _anim_control.SetFrameRate(frame_rate);
}

Sprite&  Sprite::operator = (Sprite const & right){
    if(this != &right){
        _texture = right._texture;
        _flip = right._flip;
        _angle = right._angle;

        if (right._frames_per_width == 0 ) {
            _frames_per_width = 1;
        }else{
            _frames_per_width = right._frames_per_width;
        }

        if (right._frames_per_height == 0 ) {
            _frames_per_height  = 1;
        }else{
            _frames_per_height  = right._frames_per_height ;
        }

        _src_rect = right._src_rect;
        _anim_rect = right._anim_rect;
        _anim_control = right._anim_control;
    }
    return *this;
}
