#include "Window.h"

Camera Window::_camera;
SDL_Window* Window::_window = nullptr;
SDL_Renderer* Window::_renderer = nullptr;
std::string Window::_title = "No Title";
Vec2 Window::_size(1280, 720);
bool Window::_full_screen = false;
SDL_Color Window::_color_background = COLOR_GRAY;

Window::Window(){

}

Window::~Window(){

}

bool Window::Init() {

    if (_window) {
        SDL_DestroyWindow(_window);
    }

    //WINDOW INIT------------------------------------------------------
    //Centering window on the screen
    _window = SDL_CreateWindow(_title.c_str(),
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               _size.x, _size.y,
                               SDL_WINDOW_FULLSCREEN_DESKTOP * _full_screen);
    if (_window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }
    
    //Set the best scaling quality(anisotropic filtering)
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

    //RENDER INIT------------------------------------------------------
    _renderer = SDL_CreateRenderer(_window, -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // SDL_RENDERER_PRESENTVSYNC
    if (_renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError()
        << std::endl;
        return false;
    }
    
    SDL_SetRenderDrawColor(Window::GetRenderer(), _color_background.r,
                               _color_background.g, _color_background.b, 0);

    SDL_RenderSetLogicalSize(Window::GetRenderer(), _size.x, _size.y);

    return true;
}

void ShowError(bool& error) {
    error = true;
    std::cerr << SDL_GetError() << std::endl;
}

const std::string& Window::GetTitle() {
    return _title;
}

bool Window::SetMode(int w, int h, bool full_screen, const std::string &title) {
    SetSize(Vec2(w, h));

    _full_screen = full_screen;
    _title = title;

    _camera.SetViewport(_size, Vec2::ZERO);
    GUI::GetCamera()->SetViewport(_size, Vec2::ZERO);

    //Check window existence
    if (IsInitialised()) {
        bool error = false;

        SDL_SetWindowTitle(_window, _title.c_str());
        SDL_SetWindowSize(_window, _size.x, _size.y);

        if (SDL_SetWindowFullscreen(_window,  SDL_WINDOW_FULLSCREEN_DESKTOP * _full_screen) < 0) {
            ShowError(error);
        }

        SDL_RenderSetLogicalSize(Window::GetRenderer(), _size.x, _size.y);
        return !error;
    } else {
        return Init();
    }
}

SDL_Window* Window::GetWindow() {
    return _window;
}

SDL_Renderer* Window::GetRenderer() {
    return _renderer;
}

Camera* Window::GetCamera() {
    return &_camera;
}

void Window::SetWidth(const int &w) {
    SetMode(w, _size.y, _full_screen, _title);
}

void Window::SetHeight(const int &h) {
    SetMode(_size.x, h, _full_screen, _title);
}

void Window::SetSize(const Vec2 &size){
    _size = size;
}

int Window::GetWidth() {
    return _size.x;
}

int Window::GetHeight() {
    return _size.y;
}

Vec2 Window::GetSize(){
    return _size;
}

bool Window::IsInitialised() {
    return _window != nullptr && _renderer != nullptr;
}

bool Window::IsFullscreen() {
    return _full_screen;
}

void Window::OnEvent(const SDL_Event* event){
    if (event->type == SDL_WINDOWEVENT) {
            switch (event->window.event) {
//            case SDL_WINDOWEVENT_SHOWN:
//                break;
//            case SDL_WINDOWEVENT_HIDDEN:
//                break;
//            case SDL_WINDOWEVENT_EXPOSED:
//                break;
//            case SDL_WINDOWEVENT_MOVED:
//                break;
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                SetSize(Vec2(event->window.data1,
                             event->window.data2));
                break;
//            case SDL_WINDOWEVENT_MINIMIZED:
//                break;
//            case SDL_WINDOWEVENT_MAXIMIZED:
//                break;
//            case SDL_WINDOWEVENT_RESTORED:
//                break;
//            case SDL_WINDOWEVENT_ENTER:
//                break;
//            case SDL_WINDOWEVENT_LEAVE:
//                break;
//            case SDL_WINDOWEVENT_FOCUS_GAINED:
//                break;
//            case SDL_WINDOWEVENT_FOCUS_LOST:
//                break;
//            case SDL_WINDOWEVENT_CLOSE:
//                break;
//    #if SDL_VERSION_ATLEAST(2, 0, 5)
//            case SDL_WINDOWEVENT_TAKE_FOCUS:
//                SDL_Log("Window %d is offered a focus", event->window.windowID);
//                break;
//            case SDL_WINDOWEVENT_HIT_TEST:
//                SDL_Log("Window %d has a special hit test", event->window.windowID);
//                break;
//    #endif
//            default:
//                SDL_Log("Window %d got unknown event %d",
//                        event->window.windowID, event->window.event);
//                break;
            }
        }

}

void Window::OnCleanUp() {
    if (_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
}

void Window::SetBackgroundColor(const SDL_Color& color) {
    _color_background = color;
}

SDL_Color Window::GetBackgroundColor() {
    return _color_background;
}
