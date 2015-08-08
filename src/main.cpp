/*!
 boldtemple Gaming ©, http://gaming.boldtemple.net
 OpenSource Project - Check Development, License & Readme Sections.

 BGE - boldtemple Cross Platform Game Engine
 /main.cpp
 !*/

#include <iostream>

#include "Engine.h"


#include "Demo/Platform.h"
#include "Demo/map/Map.h"
#include "Demo/Jim.h"
#include "Core/FPScounter.h"

using namespace std;
//Map test_map;

FPS_counter fps;
Box* box;
Jim *jim1;

void Engine::OnInit() {
    Window::SetMode(1024, 720, false);
    //U can set map size in constants.h file
    //Load and set map tileset texture
//    test_map.texture_tileset = Surface::LoadTexture("overworld_1.png");

/*    if (!test_map.OnLoad("map.txt") && test_map.texture_tileset) {
        cout << "Can't load map" << endl;
        Engine::Stop();
    }
*/
    ScrollArea *area = new ScrollArea(Engine::GetRoot(), Vec2(100, 100), Vec2(300, 300));


    jim1 = new Jim(Vec2(5, 20));
    jim1->_is_player = true;


/*
    for (int i = 1; i < 100; i++) {
        Jim *jim = new Jim(Vec2(160*i, 20));
        Engine::GetRoot()->Connect(jim);
    //jim->Connect(new Jim(Vec2(100, 0)));
    //area->Connect(new Jim(Vec2(0, 0)));
    }
*/

    Engine::GetRoot()->Connect(new Platform(Vec2(0, 400), Vec2(128, 32)));
    Engine::GetRoot()->Connect(new Platform(Vec2(150, 400), Vec2(128, 32)));
    Engine::GetRoot()->Connect(new Platform(Vec2(300, 400), Vec2(128, 32)));

    Engine::GetRoot()->Connect(new Platform(Vec2(215, 400), Vec2(128, 32)));
    Engine::GetRoot()->Connect(new Platform(Vec2(710, 400), Vec2(128, 200)));

    Engine::GetRoot()->Connect(new Platform(Vec2(350, 100), Vec2(128, 300)));
    Engine::GetRoot()->Connect(new Platform(Vec2(200, 200), Vec2(128, 32)));
    Engine::GetRoot()->Connect(new Platform(Vec2(100, 300), Vec2(128, 32)));

    Engine::GetRoot()->Connect(jim1);


    box = new Box(Engine::GetRoot(), Vec2(0, 0), Vec2(160, 64), "PressStart2P.ttf", 8);
    box->SetText("Hey, world!\nА это по-русски!\nHEY again");
}

void Engine::OnEvent(SDL_Event* event, const Uint8* keyboardState) {
    if (event->type == SDL_MOUSEWHEEL) {
        //on mouse wheel event
    } else if (event->type == SDL_KEYDOWN) {
        //Move camera w,a,s,d

        Camera* cam = Window::GetCamera();

        int code = event->key.keysym.scancode;

        switch(code){

            case SDL_SCANCODE_R:
                jim1->SetPos(Vec2(5, 20));
                break;
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
    //std::cout << "FPS: " << int_to_str(fps.GetFPS()) << '\n';
    box->SetText( std::string("FPS: ") + std::string(int_to_str(fps.GetFPS())) );
}

void Engine::OnRender() {
    fps.OnUpdate();
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
