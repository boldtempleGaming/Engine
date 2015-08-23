#include "Window.h"

Camera Window::_camera;
SDL_Window* Window::_window = nullptr;
SDL_Renderer* Window::_renderer = nullptr;
std::string Window::_title = "No Title";
int Window::_w = 1280;
int Window::_h = 720;
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
    //Выравниваем окно по центру экрна
    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, _w, _h,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP * _full_screen);
    if (_window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }

    //RENDER INIT------------------------------------------------------
    _renderer = SDL_CreateRenderer(_window, -1,
                                  SDL_RENDERER_ACCELERATED); // SDL_RENDERER_PRESENTVSYNC
    if (_renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError()
        << std::endl;
        return false;
    }

    SDL_RenderSetLogicalSize(Window::GetRenderer(), _w, _h);

    return true;
}

void ShowError(bool& error) {
    error = true;
    std::cerr << SDL_GetError() << std::endl;
}

const std::string& Window::GetTitle() {
    return _title;
}

bool Window::SetMode(int w, int h, bool full_screen, std::string title) {
    _w = w;
    _h = h;
    _full_screen = full_screen;
    _title = _title;

    _camera.SetViewport(Vec2(_w, _h));
    GUI::GetCamera()->SetViewport(Vec2(_w, _h));

    //Check window existence
    if (IsInitialised()) {
        bool error = false;

        SDL_SetWindowTitle(_window, _title.c_str());
        SDL_SetWindowSize(_window, _w, _h);

        if (SDL_SetWindowFullscreen(_window, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP * _full_screen) < 0) {
            ShowError(error);
        }

        SDL_RenderSetLogicalSize(Window::GetRenderer(), _w, _h);
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
    SetMode(w, _h, _full_screen, _title);
}

void Window::SetHeight(const int &h) {
    SetMode(_w, h, _full_screen, _title);
}

int Window::GetWidth() {
    return _w;
}

int Window::GetHeight() {
    return _h;
}

bool Window::IsInitialised() {
    return _window != nullptr && _renderer != nullptr;
}

bool Window::IsFullscreen() {
    return _full_screen;
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
    SDL_SetRenderDrawColor(Window::GetRenderer(), _color_background.r, _color_background.g, _color_background.b, _color_background.a);
}

SDL_Color Window::GetBackgroundColor() {
    return _color_background;
}
