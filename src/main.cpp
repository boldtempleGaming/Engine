/*!
 boldtemple Gaming ©, http://gaming.boldtemple.net
 OpenSource Project - Check Development, License & Readme Sections.

 BGE - boldtemple Cross Platform Game Engine
 /main.cpp
 !*/

#include <iostream>

#include "Engine.h"


#include "Demo/map/Map.h"
#include "Demo/Jim.h"

using namespace std;
Map test_map;

void Engine::OnInit() {
    Window::SetMode(800, 600, false);
    //U can set map size in constants.h file
    //Load and set map tileset texture
    test_map.texture_tileset = Surface::LoadTexture("overworld_1.png");

    if (!test_map.OnLoad("map.txt") && test_map.texture_tileset) {
        cout << "Can't load map" << endl;
        Engine::Stop();
    }

    ScrollArea* area = new ScrollArea(Engine::GetRoot(), Vec2(100, 100), Vec2(300, 300));

    Jim* jim = new Jim(Vec2(20,20));
    jim->Connect(new Jim(Vec2(0, 0)));
    area->Connect(new Jim(Vec2(0, 0)));

    Engine::GetRoot()->Connect(jim);
}

void Engine::OnEvent(SDL_Event* event, const Uint8* keyboardState) {
    if (event->type == SDL_MOUSEWHEEL) {
        //on mouse wheel event
    } else if (event->type == SDL_KEYDOWN) {
        //Move camera w,a,s,d

        Camera* cam = Window::GetCamera();

        int code = event->key.keysym.scancode;

        switch(code){
        case SDL_SCANCODE_D:
            cam->SetPos(Vec2(cam->X() + 10, cam->Y()));
            break;
        case SDL_SCANCODE_A:
            cam->SetPos(Vec2(cam->X() - 10, cam->Y()));
            break;
        case SDL_SCANCODE_W:
            cam->SetPos(Vec2(cam->X(), cam->Y() - 10));
            break;
        case SDL_SCANCODE_S:
            cam->SetPos(Vec2(cam->X(), cam->Y() + 10));
            break;
        case SDL_SCANCODE_KP_PLUS:
            Window::SetMode(Window::GetWidth() + 10, Window::GetHeight() + 5, false);
            break;
        case SDL_SCANCODE_KP_MINUS:
            Window::SetMode(Window::GetWidth() - 10, Window::GetHeight() - 5, false);
            break;
        }

    }

}

void Engine::OnUpdate() {

}

void Engine::OnRender() {

    ///test_map.OnRender(0, 0);
    SDL_Rect rct = {100, 100, 300, 300};

    Surface::DrawRect(&rct, 100, 100, 100, 60);
}

void Engine::OnCleanUp() {

}

#undef main
int main() {
    Engine engine;
    engine.Start();
    return 0;
}
