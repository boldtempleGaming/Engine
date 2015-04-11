/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /engine.cpp
!*/

#include "Engine.h"

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

    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    SDL_Event* event = new SDL_Event;
    double previous = SDL_GetTicks();
    double lag = 0.0;
    int MS_PER_UPDATE = 15;

    while (!quit) {
        SDL_Delay(1);
        double current = SDL_GetTicks();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        Core_Event(event, keyboardState);

        while (lag >= MS_PER_UPDATE) {
            lag -= MS_PER_UPDATE;
            Core_Update();
            
            Surface::SetInterpolation( lag / MS_PER_UPDATE );
            Core_Render();
        }
    }

}

Object* Engine::GetRoot(){
    return root_obj;
}

bool Engine::Core_Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    GUI::OnInit();

    //Alloc root object
    root_obj = new Object;

    if (!Window::IsInitialised()) {
        Window::SetMode(640, 470, false);
    }

    OnInit(); //CALL user function OnInit

    SDL_SetRenderDrawBlendMode(Window::GetRenderer(), SDL_BLENDMODE_BLEND); // https://wiki.libsdl.org/SDL_SetRenderDrawBlendMode

    //SDL_RenderSetLogicalSize(Window::GetRenderer(), LOGIC_WIN_WIDTH,
    //	LOGIC_WIN_HEIGHT); // одинаковый масштаб на разных разрешениях

    if (SDL_RegisterEvents(EVENT_END - EVENT_NONE) == ((Uint32) -1)) {
        std::cout << "Not enough user-defined events left." << std::endl;
        return false;
    }

    Cursor::Init(Surface::LoadTexture("cursor.png"), 20, 20);

    Camera::Init(0, 0, Window::GetWidth(), Window::GetHeight());

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
    root_obj->UpdateChildren();
    GUI::OnUpdate();
    OnUpdate(); //User OnUpdate
}

void Engine::Core_Render() {
    SDL_RenderClear(Window::GetRenderer());

    root_obj->RenderChildren();

    OnRender();

    GUI::OnRender();
    Cursor::Draw();

    SDL_RenderPresent(Window::GetRenderer());
}

void Engine::Core_CleanUp() {
    OnCleanUp(); //User CleanUp

    std::cout << "Unloading textures..." << std::endl;
    Surface::OnCleanUp(); //Destroy all textures

    std::cout << "Destroy objects..." << std::endl;
    delete(root_obj);

    std::cout << "Cleaning gui..." << std::endl;
    GUI::OnCleanUp();

    std::cout << "Closing window..." << std::endl;
    Window::OnCleanUp();

    std::cout << "Quitting..." << std::endl;

    TTF_Quit();
    SDL_Quit();
}
