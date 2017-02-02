/*!
 boldtemple Gaming ©, http://gaming.boldtemple.net
 OpenSource Project - Check Development, License & Readme Sections.

 BGE - boldtemple Cross Platform Game Engine
 /Engine.cpp
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

    SetGameSpeed(60);
    //const double MS_PER_UPDATE = double(1000) / _game_speed;
    Uint32 previous = SDL_GetTicks();
    double lag = 0.0;

    while (!quit)
    {
        SDL_Delay(1);

        Uint32 current = SDL_GetTicks();
        Uint32 elapsed = current - previous;
        previous = current;
        lag += elapsed;

        Surface::SetInterpolation(lag / _ms_per_update);
        Core_Render();

        Core_Event(event, keyboardState);

        while (lag > _ms_per_update)
        {
            Core_Update();
            lag -= _ms_per_update;
        }

    }

    delete (event);
    Core_CleanUp();
}

void Engine::Stop() {
    quit = true;
}


Object* Engine::GetRootAtLayer(unsigned int layer) {
    if(layer < _Layers.size() && layer >= 0){
        return _Layers[layer];
    }
    return nullptr;
}

void Engine::AddLayer() {
    _Layers.resize(_Layers.size() + 1, new Object());//increase vector by 1
}

void Engine::SetGameSpeed(int ms){
    if(ms > 0){
        _ms_per_update = double(1000)/ms;
    }
}

int Engine::GetGameSpeed(){
    return 1000/_ms_per_update ;
}

void Engine::DeleteObjects(){
    if(!Object::DeleteCandidates.empty()){
        for(size_t i = 0; i < Object::DeleteCandidates.size(); ++i){
            delete(Object::DeleteCandidates[i]);
        }
        Object::DeleteCandidates.clear();
    }
}

bool Engine::Core_Init() {
    quit = false;

    PhysFS::init(nullptr);
    PhysFS::mount("../Data.zip", "Data", false);
    PhysFS::mount("../Data", "Data", false);
    
    Resources::SetDefaultFont("PressStart2P.ttf");
    Resources::SetDefaultFontPtsize(9);
    Resources::SetDefaultFontStyle("pgui.png");

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Alloc root object
    root_obj = new Object;

    SDL_SetRenderDrawBlendMode(Window::GetRenderer(), SDL_BLENDMODE_BLEND); // https://wiki.libsdl.org/SDL_SetRenderDrawBlendMode

    //SDL_RenderSetLogicalSize(Window::GetRenderer(), LOGIC_WIN_WIDTH,
    //	LOGIC_WIN_HEIGHT); // одинаковый масштаб на разных разрешениях

//    if (SDL_RegisterEvents(EVENT_END - EVENT_NONE) == ((Uint32) -1)) {
//        std::cerr << "Not enough user-defined events left." << std::endl;
//        return false;
//    }

    Audio::Init(8);
    GUI::OnInit();
    
    if (!Window::IsInitialised()) {
        Window::SetMode(800, 640, false);
    }

    Cursor::Init(Resources::GetTexture("cursor.png"), 20, 20);

    OnInit(); //CALL user function OnInit



    std::cout << "Successfully initialized!" << std::endl;
    return true; //success
}

void Engine::Core_Event(SDL_Event* event, const Uint8* keyboardState) {

    Mouse::ResetWheel();
    
    while (SDL_PollEvent(event)) {

        bool ALT_F4 = keyboardState[SDL_SCANCODE_LALT]
                && keyboardState[SDL_SCANCODE_F4];

        if (ALT_F4 || (event->type == SDL_QUIT)) {
            Stop();
            return;
        }

        if (event->type == SDL_MOUSEWHEEL) {
            Mouse::SetWheel(event->wheel.x, event->wheel.y);
        }

        //FIXME WHY?!?!
        //User OnEvent
        OnEvent(event, keyboardState);
    }

}

void Engine::Core_Update() {
    DeleteObjects();

    OnUpdate(); //User OnUpdate

    //Catch mouse button click
    GUI::SetLastCliked(nullptr);

    int length = _Layers.size();
    for(int i = 0; i < length; ++i){
        _Layers[i]->UpdateChildren();
    }

    //root_obj->UpdateChildren();
    if(GUI::GetLastClicked()){
        GUI::GetLastClicked()->OnClick();
    }

    GUI::OnUpdate();

    Collider::ProcessCollisions();
}

void Engine::Core_Render() {
    SDL_RenderClear(Window::GetRenderer());

    OnRender();

    int length = _Layers.size();
    for(int i = 0; i < length; ++i){
        _Layers[i]->RenderChildren();
    }

    GUI::OnRender();

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
