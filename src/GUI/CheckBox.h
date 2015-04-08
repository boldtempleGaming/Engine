/* 
 * File:   CheckBox.h
 * Author: WinPooh32
 *
 * Created on 7 Feb 2015 г., 2:07
 */

#ifndef CHECKBOX_H
#define	CHECKBOX_H

#include "Core/Vec2.h"
#include "GUI/Widget.h"
#include "GUI/Button.h"

class CheckBox: public Widget {
public:
    CheckBox(SDL_Rect* rect, std::string lable);
    CheckBox(const CheckBox& orig);
    virtual ~CheckBox();
    
    virtual void OnUpdate();
    //virtual void OnClick();
    virtual void OnRender();

private:
    Vec2 _style_unchecked;
    Vec2 _style_checked;
    bool _is_checked;
    Button_State _state;
    
    void OnCheck();
};

#endif	/* CHECKBOX_H */

