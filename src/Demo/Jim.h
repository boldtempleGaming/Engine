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
#include <IO/KeyBoard.h>
#include <Core/Timer.h>

class Jim: public Object {
public:
    Jim();
    Jim(const Vec2& pos);
    virtual ~Jim();

    void OnUpdate();
    void OnRender();
    virtual void OnClick();

    bool _is_player = false;

private:
    Sprite _sprite;
    Animation _anim_control;
    KeyBoard _key_board;
    Timer _timer_controls;

    short unsigned int _frame_rate;

    Animation anim_run;
    Animation anim_stay;

    //Vec2 _vel;
};

#endif /* SRC_DEMO_JIM_H_ */
