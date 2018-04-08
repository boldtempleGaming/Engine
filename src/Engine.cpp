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

    //const double MS_PER_UPDATE = double(1000) / _game_speed;
    Uint32 previous = SDL_GetTicks();
    double lag = 0.0;

    while (!quit)
    {
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

            DeleteObjects();
            
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
    if(layer < _Layers.size()){
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

    SetGameSpeed(60);

    #ifdef USE_PHYSFS
    PhysFS::init(nullptr);

    PhysFS::mount("../Data.zip", "Data", false);
    PhysFS::mount("../Data", "Data", false);
    PhysFS::mount("../tmp", "tmp", false);

    PhysFS::setWriteDir("../tmp");
    #endif

    Resources::SetDefaultFont("PressStart2P.ttf");
    Resources::SetDefaultFontPtsize(9);
    Resources::SetDefaultFontStyle("pgui.png");

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawBlendMode(Window::GetRenderer(), SDL_BLENDMODE_ADD); // https://wiki.libsdl.org/SDL_SetRenderDrawBlendMode

    Audio::Init(8);
    GUI::OnInit();
    
    if (!Window::IsInitialised()) {
        Window::SetMode(800, 640, false);
    }

    Surface::BeginViewport(Vec2::ZERO, Window::GetSize());

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

        Window::OnEvent(event);

        if (ALT_F4 || (event->type == SDL_QUIT)) {
            Stop();
            return;
        }

        if (event->type == SDL_MOUSEWHEEL) {
            Mouse::SetWheel(event->wheel.x, event->wheel.y);
        }
        
        //User OnEvent
        OnEvent(event, keyboardState);
    }

}

void Engine::Core_Update() {
    GUI::SetTopObject(nullptr);
    GUI::SetTopWheeled(nullptr);

    OnUpdate(); //User OnUpdate

    int length = _Layers.size();
    for(int i = 0; i < length; ++i){
        _Layers[i]->UpdateChildren();
    }

    
    Collider::ProcessCollisions();
    Audio::CalcListenersPanning();
}

void Engine::Core_Render() {
    auto bk = Window::GetBackgroundColor();

    SDL_SetRenderDrawColor(Window::GetRenderer(), bk.r, bk.b, bk.g, bk.a);
    SDL_RenderClear(Window::GetRenderer());

    OnRender();

    int length = _Layers.size();
    for(int i = 0; i < length; ++i){
        _Layers[i]->RenderChildren();
    }

    GUI::OnUpdate();
    GUI::OnRender();
    Cursor::Draw();

    SDL_RenderPresent(Window::GetRenderer());
}

void Engine::Core_CleanUp() {
    OnCleanUp(); //User CleanUp

    std::cout << "Unloading resources..." << std::endl;
    Resources::UnloadAll();

    std::cout << "Destroy objects..." << std::endl;


    std::cout << "Closing window..." << std::endl;
    Window::OnCleanUp();

    TTF_Quit();
    SDL_Quit();

    std::cout << "Quitting..." << std::endl;
}
