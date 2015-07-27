/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.

  BGE - boldtemple Cross Platform Game Engine
  /gui/gui.h
!*/

#ifndef GUI_H_
#define GUI_H_

#include <string>
#include <iostream>
#include <map>

#include <SDL2/SDL_ttf.h>

#include "constants.h"
#include "Core/sys.h"
#include "Core/Object.h"

class Object;

class GUI {
public:
    GUI();
    virtual ~GUI();

    static void OnInit();
    static void OnUpdate();
    static void OnRender();

    static void SetLastCliked(Object* obj);
    static Object* GetLastClicked();

private:
    static Object* _last_clicked;
};

#endif /* GUI_H_ */
