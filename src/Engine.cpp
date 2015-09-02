/*!
 boldtemple Gaming ©, http://gaming.boldtemple.net
 OpenSource Project - Check Development, License & Readme Sections.

 BGE - boldtemple Cross Platform Game Engine
 /engine.cpp
 !*/
#include "Engine.h"

Engine::Engine() {

}

Engine::~Engine() {
    if (root_obj)
        Core_CleanUp(); //Очищаем все
}

void SetVideo(int w, int h, bool full_screen, std::string win_title) {
    Window::SetMode(w, h, full_screen, win_title);
}

void Engine::Start() {
    if (!Core_Init()) {
        return;
    }

    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    SDL_Event* event = new SDL_Event;

    const double MS_PER_UPDATE = double(1000) / 60;
    int previous = SDL_GetTicks();
    double lag = 0.0;
    while (!quit)
    {
        SDL_Delay(1);

        int current = SDL_GetTicks();
        int elapsed = current - previous;
        previous = current;
        lag += elapsed;

        Core_Event(event, keyboardState);

        while (lag >= MS_PER_UPDATE)
        {
            Core_Update();
            lag -= MS_PER_UPDATE;
        }

        Surface::SetInterpolation(lag / MS_PER_UPDATE);
        Core_Render();
    }

    delete (event);
    Core_CleanUp();
}

void Engine::Stop() {
    quit = true;
}

Object* Engine::GetRoot() {
    return root_obj;
}

bool Engine::Core_Init() {
    quit = false;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Alloc root object
    root_obj = new Object;

    SDL_SetRenderDrawBlendMode(Window::GetRenderer(), SDL_BLENDMODE_BLEND); // https://wiki.libsdl.org/SDL_SetRenderDrawBlendMode

    //SDL_RenderSetLogicalSize(Window::GetRenderer(), LOGIC_WIN_WIDTH,
    //	LOGIC_WIN_HEIGHT); // одинаковый масштаб на разных разрешениях

    if (SDL_RegisterEvents(EVENT_END - EVENT_NONE) == ((Uint32) -1)) {
        std::cerr << "Not enough user-defined events left." << std::endl;
        return false;
    }

    Audio::Init(8);
    GUI::OnInit();

    OnInit(); //CALL user function OnInit

    if (!Window::IsInitialised()) {
        Window::SetMode(800, 640, false);
    }

    Cursor::Init(Resources::GetTexture("cursor.png"), 20, 20);

    std::cout << "Successfully initialized!" << std::endl;
    return true; //success
}

void Engine::Core_Event(SDL_Event* event, const Uint8* keyboardState) {

    while (SDL_PollEvent(event)) {

        bool ALT_F4 = keyboardState[SDL_SCANCODE_LALT]
                && keyboardState[SDL_SCANCODE_F4];

        if (ALT_F4 || (event->type == SDL_QUIT)) {
            Stop();
            return;
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
    //Catch mouse button click
    GUI::SetLastCliked(nullptr);
    root_obj->UpdateChildren();
    if(GUI::GetLastClicked()){
        GUI::GetLastClicked()->OnClick();
    }

    GUI::OnUpdate();

    OnUpdate(); //User OnUpdate

    Collider::ProcessCollisions();
}

void Engine::Core_Render() {
    SDL_RenderClear(Window::GetRenderer());

    root_obj->RenderChildren();

    OnRender();

    GUI::OnRender();

    Cursor::Update();
    Cursor::Draw();

    SDL_RenderPresent(Window::GetRenderer());
}

void Engine::Core_CleanUp() {
    OnCleanUp(); //User CleanUp

    std::cout << "Unloading resources..." << std::endl;
    Resources::UnloadAll();

    std::cout << "Destroy objects..." << std::endl;
    delete (root_obj);
    root_obj = nullptr;

    std::cout << "Closing window..." << std::endl;
    Window::OnCleanUp();

    TTF_Quit();
    SDL_Quit();

    std::cout << "Quitting..." << std::endl;
}
