/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.

  BGE - boldtemple Cross Platform Game Engine
  /engine.h
!*/

#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "constants.h"

#include "Core/type_events.h"
#include "Core/Object.h"

#include "GUI/GUI.h"
#include "GUI/Window.h"
#include "GUI/Cursor.h"
#include "GUI/Widget.h"
#include "GUI/Widgets/Box.h"
#include "GUI/Widgets/ScrollArea.h"

#include "Render/Camera.h"
#include "Render/Surface.h"
#include "Render/Animation.h"

class Engine {
public:
    bool quit;

    Engine();
    virtual ~Engine();
    void SetVideo(int w, int h, bool full_screen, std::string win_title);
    void Start();
    void Stop();

private:
    Object* root_obj;

    Object* GetRoot();

    bool Core_Init();
    void Core_Event(SDL_Event* event, const Uint8* keyboardState);
    void Core_Update();
    void Core_Render();
    void Core_CleanUp();

    virtual void OnInit();
    virtual void OnEvent(SDL_Event* event, const Uint8* keyboardState);
    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnCleanUp();
};

#endif /* ENGINE_H_ */
