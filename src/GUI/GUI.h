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

#include "Common/constants.h"
#include "Common/sys.h"

#include "Core/Object.h"

#include "Render/Camera.h"

#include "GUI/Window.h"

class Object;
class GUI {
public:
    GUI();
    virtual ~GUI();

    static Camera* GetCamera();

    static void OnInit();
    static void OnUpdate();
    static void OnRender();

    static void SetTopObject(Object* obj);
    static void SetTopWheeled(Object* obj);

    static Object* GetLastClicked();
    static Object* GetTopWheeled();

private:
    static Object* _top_mouse_btn;
    static Object* _top_wheeled;
    static Camera* _camera;
};

#endif /* GUI_H_ */
