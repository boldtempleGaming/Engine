/*!
 boldtemple Gaming ©, http://gaming.boldtemple.net
 OpenSource Project - Check Development, License & Readme Sections.

 BGE - boldtemple Cross Platform Game Engine
 /main.cpp
 !*/

#include <iostream>

#include "Engine.h"
#include "constants.h"
#include "GUI/Cursor.h"
#include "Core/sys.h"
#include "Core/FPScounter.h"

#include "GUI/Widget.h"
#include "GUI/Widgets/Box.h"
#include "GUI/Widgets/ScrollArea.h"

#include "Demo/Jim.h"

using namespace std;


FPS_counter fps;
ScrollArea* area;

void Engine::OnInit() {
    Window::SetMode(800, 600, false);

    Jim* jim = new Jim(Vec2(0, 0));
    GetRoot()->Connect(jim);

    Box* box = new Box(GetRoot(), Vec2(128, 64), Vec2(64,64));
    box->SetBackGround("pgui.png", Vec2(0,0), 8);

    area = new ScrollArea(GetRoot(), Vec2(300, 200), Vec2(256, 256));
    area->Connect(new Jim(Vec2(0, 0)) ); 
    area->Connect(new Jim(Vec2(0, 144)) );

}

void Engine::OnEvent(SDL_Event* event, const Uint8* keyboardState) {
        if(event->type == SDL_MOUSEWHEEL){
            area->Scroll(Vec2(0, event->wheel.y * 10 )); //TODO REMOVE SCrolling area
        }
}

void Engine::OnUpdate() {
    fps.OnUpdate();
}

void Engine::OnRender() {

}

void Engine::OnCleanUp() {

}

#undef main
int main() {
    Engine engine;
    engine.Start();
    return 0;
}
