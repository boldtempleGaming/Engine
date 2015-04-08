/*
 * Engine.cpp
 *
 *  Created on: 20 сент. 2014 г.
 *      Author: snickers
 */

#include "Engine.h"

#include "Core/Object.h"
//#include "Core/TstEntity.h"
//#include "Demo/Jim.h"
Object* root_obj;

Engine::Engine() {
    quit = false;
}

Engine::~Engine() {
    Core_CleanUp(); //Очищаем все
}

void SetVideo(int w, int h, bool full_screen, std::string win_title) {
    Window::SetMode(w, h, full_screen, win_title);
}

void Engine::Start() {

    if (!Core_Init()) {
        return;
    }


    //================= /
    root_obj = new Object;

    /*
    TstEntity* ent = new TstEntity;
    Vec2 pos = Vec2(500, 0);
    ent->SetPos(&pos);

    TstEntity* ent2 = new TstEntity;
    pos = {-200, 50};
    ent2->SetPos(&pos);

    TstEntity* ent3 = new TstEntity;
    pos = {150, 0};
    ent3->SetPos(&pos);

    root_obj->Connect(ent);
    ent->Connect(ent2);
    ent2->Connect(ent3);

    for(int i = 0; i < 1; i++)
        for(int j = 0; j < 1; j++)
            root_obj->Connect(new Jim(Vec2(j*72*2, i*72*2)));
   //=================
    */

    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    SDL_Event* event = new SDL_Event;
    double previous = SDL_GetTicks();
    double lag = 0.0;
    int MS_PER_UPDATE = 20;

    while (!quit) {
        SDL_Delay(5);
        double current = SDL_GetTicks();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        Core_Event(event, keyboardState);

        while (lag >= MS_PER_UPDATE) {
            lag -= MS_PER_UPDATE;
            Core_Update();
            root_obj->OnUpdate();
        }

        Surface::SetInterpolation( lag / MS_PER_UPDATE );
        Core_Render(lag / MS_PER_UPDATE);
    }

}

bool Engine::Core_Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    GUI::OnInit();

    OnInit(); //CALL user function OnInit

    Cursor::Init(Surface::LoadTexture("cursor.png"), 16, 16);

    if (!Window::IsInitialised()) {
        Window::SetMode(640, 470, false, "Wooden Engine");
    }

    SDL_SetRenderDrawBlendMode(Window::GetRenderer(), SDL_BLENDMODE_BLEND); // https://wiki.libsdl.org/SDL_SetRenderDrawBlendMode

    Camera::Init(0, 0, Window::GetWidth(), Window::GetHeight());

    //SDL_RenderSetLogicalSize(Window::GetRenderer(), LOGIC_WIN_WIDTH,
    //	LOGIC_WIN_HEIGHT); // одинаковый масштаб на разных разрешениях

    if (SDL_RegisterEvents(EVENT_END - EVENT_NONE) == ((Uint32) -1)) {
        std::cout << "Not enough user-defined events left." << std::endl;
        return false;
    }

    std::cout << "Successfully initialized!" << std::endl;
    return true; //success
}

void Engine::Core_Event(SDL_Event* event, const Uint8* keyboardState) {

    while (SDL_PollEvent(event)) {

        bool ALT_F4 = keyboardState[SDL_SCANCODE_LALT]
                && keyboardState[SDL_SCANCODE_F4];
        bool ESCAPE = keyboardState[SDL_SCANCODE_ESCAPE];

        if (ESCAPE || ALT_F4 || (event->type == SDL_QUIT)) {
            quit = true;
            return;
        }

        if (event->type == EVENT_MOVE) {
            CollideList.push_back((Entity::move_info*) event->user.data1);
        }

        //Send click to Widget
        if (event->type > 0) {

        }

        //TODO WHY?!?!
        //User OnEvent
        OnEvent(event, keyboardState);
    }

}

void Engine::Core_Update() {

    Cursor::Update();

    SDL_Rect result;
    for (unsigned int i = 0; i < Entity::EntityList.size(); i++) {
        if (Entity::EntityList[i] != nullptr) {
            Entity* victim = Entity::EntityList[i];

            //Check collision
            for (auto it = CollideList.begin(); it != CollideList.end(); it++) {
                Entity* collider = (*it)->entity;

                if (victim != collider && collider != nullptr)
                    if (SDL_IntersectRect(&victim->rect, &collider->rect,
                            &result) == SDL_TRUE) {
                        victim->OnCollide(collider);
                        collider->OnCollide(victim);

                        std::cout << "Collision" << std::endl;
                    }

            }

            Entity::EntityList[i]->OnUpdate();
        }
    }
    CollideList.clear();
    GUI::OnUpdate();
    OnUpdate(); //User OnUpdate
}

void Engine::Core_Render(const double& interpolation) {
    SDL_RenderClear(Window::GetRenderer());


    for (unsigned int i = 0; i < Entity::EntityList.size(); i++) {
        if (Entity::EntityList[i] != nullptr) {
            Entity::EntityList[i]->OnRender(interpolation);
        }
    }

    root_obj->OnRender();

    OnRender();

    GUI::OnRender();
    Cursor::Draw();

    SDL_RenderPresent(Window::GetRenderer());
}

void Engine::Core_CleanUp() {
    OnCleanUp(); //User CleanUp

    std::cout << "Unloading textures..." << std::endl;
    Surface::OnCleanUp(); //Destroy all textures

    std::cout << "Killing entities..." << std::endl;
    Entity::EntityList.clear(); //Cleanup all entities

    std::cout << "Cleaning GUI..." << std::endl;
    GUI::OnCleanUp();

    std::cout << "Closing window..." << std::endl;
    Window::OnCleanUp();

    std::cout << "Quitting..." << std::endl;

    TTF_Quit();
    SDL_Quit();
}
