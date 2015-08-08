/*
 * Jim.cpp
 *
 *  Created on: 11 марта 2015 г.
 *      Author: Админ
 */

#include <Demo/Jim.h>
#include <iostream>
#include <Core/Resources.h>
#include <Core/Collider.h>

Vec2 GRAV(0, 1);

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
    _sprite.SetTexture(Resources::GetTexture("jim_run.png"));
    _sprite.SetFrameSize(Vec2(72, 72));
    //_sprite.SetAnimation(0, 12);
    //_sprite.SetAnimationRate(_frame_rate);
    //_sprite.SetSize(Vec2(72*2, 72*2));

    _sprite.SetAnimation(anim_stay);

    //_sprite.SetAngle(45);
    Object::SetPos(Vec2());

    Collider::RegisterObject(this, Vec2(), GetSize(), false);
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
    _sprite.SetTexture(Resources::GetTexture("jim_run.png"));
    _sprite.SetFrameSize(Vec2(72, 72));
    //_sprite.SetAnimation(0, 12);
    //_sprite.SetAnimationRate(_frame_rate);
    //_sprite.SetSize(Vec2(72*2, 72*2));

    _sprite.SetAnimation(anim_stay);

    //_sprite.SetPos(pos);

    //_pos = pos;
    Object::SetPos(pos);
    _prev_pos = Vec2(1,1) + pos;

    Object::SetSize(Vec2(72*2, 72*2));

    //Window::GetCamera()->SetPos(Vec2(0, 0));
    //Window::GetCamera()->SetViewport(Vec2(500, 500));
    Collider::RegisterObject(this, Vec2(36, -8), GetSize() - Vec2(70, 0), false);

    _jump_vel = Vec2();
}

Jim::~Jim() {
    // TODO Auto-generated destructor stub
}

void Jim::OnClick(){
    std::cout << "YOHOHO JIM clicked: "<< GetId() << std::endl;
}

void Jim::OnUpdate() {
    Object::CheckClick();

    //Move(Vec2(0,3.0f));


    _prev_pos = GetPos();
    //Move(GetVel() + Vec2(0,3));

    _timer_controls.Start();

/*
    if(_collision && !(_prev_pos == GetPos())){
        SetPos(_prev_pos);
        _collision = false;
    }
    else if( !(GetVel() == Vec2()) ){
        //_pos += _vel;
        _prev_pos = GetPos();
        Move(GetVel());
        //std::cout << _pos.x << " " << _pos.y << std::endl;
    }
*/

    if (_timer_controls.GetTime() > 50 && _is_player) {

        bool jump = false;

        if (_key_board.isKeyDown(SDL_SCANCODE_UP)) {
            if(_onGround){
                _jump_vel = Vec2(0, -25.0f);
                jump = true;
                _onGround = false;
            }
        } else if (_key_board.isKeyDown(SDL_SCANCODE_DOWN)) {
            if (!_onGround) {
                _move_vel += (Vec2(0, 5.0f));
            }
        }

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

            if(_onGround){
                _move_vel += ( Vec2(-3.0f, 0) );
                _onGround = false;
            }else{
                _move_vel += ( Vec2(-3.0f,0));
            }

        } else if (_key_board.isKeyDown(SDL_SCANCODE_RIGHT)) {
            _sprite.SetFlip(SDL_FLIP_NONE);
            _sprite.SetAnimation(anim_run);

            if(_onGround || jump){
                _move_vel +=( Vec2(3.0f, 0) );
                _onGround = false;
            }else{
                _move_vel += ( Vec2(3.0f, 0));
            }

        } else if(_onGround){
            _sprite.SetAnimation(anim_stay);
            _move_vel.x = 0;

            //SetVel(GetVel() - Vec2(0.1, 0.1));
            //SetVel(Vec2());
            //SetVel( GRAV );
        }

        _timer_controls.Stop();
    }

    _move_vel.y += GRAV.y;
    SetVel(_move_vel + _jump_vel);

    if(_jump_vel.y <= GRAV.y && !_onGround){
        _jump_vel.y += 1.0f;
    }else{
        _jump_vel.y = GRAV.y;
    }
}

void Jim::OnRender() {
    Vec2 rect_pos;

    if( GetVel().x < 0.1f && GetVel().x > -0.1f && GetVel().y < 0.1f && GetVel().y > -0.1f && _onGround){
        rect_pos = Object::GetGlobalPos();
    }else{
        rect_pos = Object::GetGlobalPos() + GetVel() * Surface::GetInterpolation();
    }

    //SDL_Rect _draw_rect = {rect_pos.x, rect_pos.y, GetSize().x, GetSize().y};

    Collider* col = Collider::GetCollider(this);

    SDL_Rect _draw_rect = {rect_pos.x + col->_offset.x, rect_pos.y + col->_offset.y, col->_size.x, col->_size.y};

    //if(Surface::GetInterpolation() > 0)
    //std::cout << Surface::GetInterpolation() << std::endl;

    SDL_SetRenderDrawColor(Window::GetRenderer(), 255, 255, 0, 255);
    SDL_RenderDrawRect(Window::GetRenderer(), &_draw_rect);
    SDL_SetRenderDrawColor(Window::GetRenderer(), BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255);

    _sprite.Draw(rect_pos, GetSize(), Window::GetCamera());
    //_sprite.Draw(Object::GetGlobalPos(), GetSize(), Window::GetCamera());
    //_sprite.Draw(_pos, _size);
}

void Jim::OnCollide(Object *obj) {
    //std::cout << "On collide! " << obj << std::endl;
    //SetVel(Vec2());
    //_collision = true;
    //SetPos(_prev_pos);

    bool top;
    bool left;

    //Get collision direction
    if(this->GetVel().x == 0){
        if(this->GetGlobalPos().x < obj->GetGlobalPos().x){
            //left
            left = true;
        }else{
            //right
            left = false;
        }
    }
    if(this->GetVel().y == 0){
        if(this->GetGlobalPos().y < obj->GetGlobalPos().y){
            //top
            top = true;
        }else{
            top = false;
            //bottom
        }
    }

    if(!top && !_onGround){
        _move_vel.x = 0;
    }else{
        _move_vel.y = 0;
        _jump_vel.y = 0;
    }

    //Prevent sticking under platform
    if(obj->GetType() == OBJ_GROUND && top){
        _onGround = true;
    }
}
