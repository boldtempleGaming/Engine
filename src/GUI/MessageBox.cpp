/*
 * TextBox.cpp
 *
 *  Created on: 08 нояб. 2014 г.
 *      Author: snickers
 */

#include "MessageBox.h"
    
    //TODO move it
    // size of border tile 
    int dx = 16; 
    int dy = 16;

MessageBox::MessageBox(Widget* parent, SDL_Rect rect,  std::string  message, bool show_background) {
	SetParent(parent);
        SetVisible(true);
        
        if(message.length() > 0){
            SetText(message);
        }
	_rect = rect;
        _rect.w += dx;
        _rect.y += dy;
        
        _pt_size = DEFAULT_PTSIZE;
        
        _skin = Surface::LoadTexture("pgui.png");
        
        _show_background = show_background;
        _isFixed = false;
        _back = nullptr;
        _style_pos = Vec2(0, 24); //TODO remove
}

MessageBox::~MessageBox() {
	for(auto it = Lines.begin(); it != Lines.end(); it++){
            delete (*it);
        }
        if(_back) SDL_DestroyTexture(_back);
}

void MessageBox::OnEvent(SDL_Event* event){

}

void MessageBox::OnUpdate(){
    Widget::OnUpdate();
} 

void MessageBox::OnRender(){
    SDL_Rect rect4draw = {screen_X, screen_Y, _rect.w, _rect.h};
    //Surface::DrawRect(&rect4draw, COLOR_OLIVE); //gray rect
    if(_show_background){
        Surface::Draw(_back, &rect4draw);
    }
    
    for(auto it = Lines.begin(); it != Lines.end(); it++){
        (*it)->Draw();
    }
}

void MessageBox::OnClick(){
    Widget::OnClick();
   // cur_style = style.pressed;
   //SetBackground(_rect);
}

void MessageBox::Move(const int& x, const int& y){
    Widget::Move(x, y);
    SetPos(x,y);
}

void MessageBox::SetPos(const int& x, const int& y){
    int i = 0;
    for(auto it = Lines.begin(); it != Lines.end(); it++){
        (*it)->SetPos(screen_X + dx/2, screen_Y + dy/2 + i * _pt_size);
        i++;
    }
}

void MessageBox::SetText(const std::string& str){
    for(auto it = Lines.begin(); it != Lines.end(); it++){
        delete(*it);
    }
    Lines.clear();
    
    //_text.SetText(str);
    bool done = false;
    int cur_p = 0; 
    int last_p = 0;
    int len;
    int x = screen_X + dx/2;
    int y = screen_Y + dy/2;
    int max = 0;
    
    
    while(!done){
       cur_p = str.find('\n', ++cur_p);
       if(cur_p == -1){
           cur_p = str.length();
           done = true;
       }
       len = cur_p - last_p;
       if(len > 0){
           Text* text_line = new Text;
           text_line->Init(x, y, str.substr(last_p, len), DEFAULT_FONT, _pt_size); //TODO
           y += _pt_size;
           Lines.push_back(text_line);
           
           //Set max for rect width
           if(text_line->GetW() > max) max = text_line->GetW();
       }
       last_p = 1 + cur_p;
    }
    
    if( _rect.w != max + dx ||  _rect.h != Lines.size() * _pt_size + dy){
        _rect.w = max + dx;
        _rect.h = Lines.size() * _pt_size + dy;

        _rect.w += 8 - _rect.w % 8;//TODO Hack with message box size
        _rect.h += 8 - _rect.h % 8;

        SetBackground(&_style_pos);
    }
}

