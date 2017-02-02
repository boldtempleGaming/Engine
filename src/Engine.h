/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.

  BGE - boldtemple Cross Platform Game Engine
  /Engine.h
!*/

#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Common/constants.h>

#include <GUI/GUI.h>
#include <GUI/Window.h>
#include <GUI/Cursor.h>

#include <Core/Object.h>
#include <Core/Resources.h>
#include <Core/Collider.h>

#include <Render/Camera.h>
#include <Render/Surface.h>

#include <IO/Mouse.h>
#include <IO/Keyboard.h>

class Engine {
public:
    bool quit;

    Engine();
    virtual ~Engine();
    void SetVideo(int w, int h, bool full_screen, std::string win_title);
    void Start();
    void Stop();

    Object* GetRootAtLayer(unsigned int layer);
    void AddLayer();

    void SetGameSpeed(int ms);
    int GetGameSpeed();

private:
    std::vector<Object*> _Layers;
    std::vector<Object*> _DeleteCandidates;
    Object* root_obj;
    double _ms_per_update;

    void DeleteObjects();

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
