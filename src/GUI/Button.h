/* 
 * File:   Button.h
 * Author: WinPooh32
 *
 * Created on 2 Feb 2015 г., 18:44
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "GUI/Widget.h"
#include "GUI/MessageBox.h"

enum Button_State{
    STATE_NORMAL = 0,
    STATE_HOVERED,
    STATE_PRESSED
};
    
class Button: public Widget{
public:
    Button(SDL_Rect rect, std::string lable, void (*OnClick)());
    Button(const Button& orig);
    virtual ~Button();
    virtual void OnUpdate();
    virtual void OnRender();
    virtual void Move(const int& x, const int& y);
    void SetState(Button_State state);
    
private:
    Button_State _state = STATE_NORMAL;
    
    int _pt_size;
    Text _lable;
    //MessageBox _box_lable;
};

#endif	/* BUTTON_H */

