/*
 * Jim.h
 *
 *  Created on: 11 марта 2015 г.
 *      Author: Админ
 */

#ifndef SRC_DEMO_JIM_H_
#define SRC_DEMO_JIM_H_

#include <Core/Object.h>
#include <Render/Animation.h>
#include <Render/Sprite.h>
#include <IO/Keyboard.h>
#include <Core/Timer.h>

class Jim: public Object {
public:
    Jim();
    Jim(const Vec2& pos);
    virtual ~Jim();

    void OnUpdate();
    void OnRender();
    void OnCollide(Object* obj);
    virtual void OnClick();

    bool _is_player = false;

private:
    Sprite _sprite;
    Animation _anim_control;
    Timer _timer_controls;

    short unsigned int _frame_rate;

    Animation anim_run;
    Animation anim_stay;

    Vec2 _prev_pos;
    Vec2 _move_vel;
    Vec2 _jump_vel;
    bool _onGround;
};

#endif /* SRC_DEMO_JIM_H_ */
