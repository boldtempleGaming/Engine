/*
 * Jim.cpp
 *
 *  Created on: 11 марта 2015 г.
 *      Author: Админ
 */

#include <Demo/Jim.h>
#include <iostream>
Jim::Jim() {
    _frame_rate = 70;

    //Stay animation
    anim_stay.SetBeginFrame(13);
    anim_stay.SetMaxFrame(20);
    anim_stay.SetCurrentFrame(13);


    //Run animation
    anim_run.SetBeginFrame(0);
    anim_run.SetMaxFrame(12);
    anim_run.SetCurrentFrame(0);

    //_sprite.SetPos(Vec2(150, 150));
    _sprite.SetTexture(Surface::LoadTexture("jim_run.png"));
    _sprite.SetFrameSize(Vec2(72, 72));
    //_sprite.SetAnimation(0, 12);
    //_sprite.SetAnimationRate(_frame_rate);
    //_sprite.SetSize(Vec2(72*2, 72*2));

    _sprite.SetAnimation(anim_stay);

    //_sprite.SetAngle(45);
    Object::SetPos(Vec2());

}

Jim::Jim(const Vec2& pos){
    _frame_rate = 70;

    //Stay animation
    anim_stay.SetBeginFrame(13);
    anim_stay.SetMaxFrame(20);
    anim_stay.SetCurrentFrame(13);


    //Run animation
    anim_run.SetBeginFrame(0);
    anim_run.SetMaxFrame(12);//12
    anim_run.SetCurrentFrame(0);

    //_sprite.SetPos(Vec2(150, 150));
    _sprite.SetTexture(Surface::LoadTexture("jim_run.png"));
    _sprite.SetFrameSize(Vec2(72, 72));
    //_sprite.SetAnimation(0, 12);
    //_sprite.SetAnimationRate(_frame_rate);
    //_sprite.SetSize(Vec2(72*2, 72*2));

    _sprite.SetAnimation(anim_stay);

    //_sprite.SetPos(pos);

    //_pos = pos;
    Object::SetPos(pos);
    Object::SetSize(Vec2(72*2, 72*2));
}

Jim::~Jim() {
    // TODO Auto-generated destructor stub
}

void Jim::OnClick(){
    std::cout << "YOHOHO JIM clicked: "<< GetId() << std::endl;
}

void Jim::OnUpdate() {
    Object::CheckClick();

    _timer_controls.Start();

    if( !(_vel == Vec2(0,0)) ){
        //_pos += _vel;
        Move(_vel);
        //std::cout << _pos.x << " " << _pos.y << std::endl;
    }


    if (_timer_controls.GetTime() > 50) {
        if (_key_board.isKeyDown(SDL_SCANCODE_KP_PLUS)) {

            _frame_rate -= 2;
            _sprite.SetAnimationRate(_frame_rate);
            std::cout  << int(_frame_rate) << std::endl;
        } else if (_key_board.isKeyDown(SDL_SCANCODE_KP_MINUS)) {

            _frame_rate += 2;
            _sprite.SetAnimationRate(_frame_rate);
            std::cout  << int(_frame_rate) << std::endl;
        }

        if (_key_board.isKeyDown(SDL_SCANCODE_LEFT)) {
            _sprite.SetFlip(SDL_FLIP_HORIZONTAL);
            _sprite.SetAnimation(anim_run);

            _vel = Vec2(-5.0f, 0);

        } else if (_key_board.isKeyDown(SDL_SCANCODE_RIGHT)) {
            _sprite.SetFlip(SDL_FLIP_NONE);
            _sprite.SetAnimation(anim_run);

            _vel = Vec2(5.0f, 0);
        }else{
            _sprite.SetAnimation(anim_stay);
            _vel = Vec2(0,0);
        }

        _timer_controls.Stop();
    }
}
void Jim::OnRender() {
    Vec2 rect_pos = Object::GetGlobalPos() + _vel * Surface::GetInterpolation();
    SDL_Rect rect = {rect_pos.x, rect_pos.y, GetSize().x, GetSize().y};

    SDL_SetRenderDrawColor(Window::GetRenderer(), 255, 255, 0, 255);
    SDL_RenderDrawRect(Window::GetRenderer(), &rect);
    SDL_SetRenderDrawColor(Window::GetRenderer(), BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255);

    _sprite.Draw(Object::GetGlobalPos() + _vel * Surface::GetInterpolation(), GetSize());
    //_sprite.Draw(_pos, _size);
}

