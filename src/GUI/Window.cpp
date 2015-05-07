/*
 * Window.cpp
 *
 *  Created on: 18 авг. 2014 г.
 *      Author: snickers
 */

#include "Window.h"

Camera Window::camera;
SDL_Window* Window::window = nullptr;
SDL_Renderer* Window::renderer = nullptr;
std::string Window::title = "No Title";
int Window::w = 640;
int Window::h = 470;
bool Window::full_screen = false;

Window::Window(){

}

Window::~Window(){

}

bool Window::Init() {

    if (window) {
        SDL_DestroyWindow(window);
    }

    //WINDOW INIT------------------------------------------------------
    //Выравниваем окно по центру экрна
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, w, h,
            SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN * full_screen);
    if (window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }

    //RENDER INIT------------------------------------------------------
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // SDL_RENDERER_PRESENTVSYNC
    if (renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError()
                << std::endl;
        return false;
    }

    return true;
}

void ShowError(bool& error) {
    error = true;
    std::cout << SDL_GetError() << std::endl;
}

const std::string& Window::GetTitle() {
    return title;
}

bool Window::SetMode(int _w, int _h, bool _full_screen, std::string _title) {
    w = _w;
    h = _h;
    full_screen = _full_screen;
    title = _title;

    camera.SetViewport(Vec2(w, h));

    //Check window existence
    if (IsInitialised()) {
        bool error = false;

        SDL_SetWindowTitle(window, title.c_str());
        SDL_SetWindowSize(window, w, h);

        if (full_screen) {
            if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0) {
                ShowError(error);
            }
        }

        return !error;
    } else {
        return Init();
    }
}

SDL_Window* Window::GetWindow() {
    return window;
}

SDL_Renderer* Window::GetRenderer() {
    return renderer;
}

Camera* Window::GetCamera() {
    return &camera;
}

int Window::GetWidth() {
    return w;
}

int Window::GetHeight() {
    return h;
}

bool Window::IsInitialised() {
    return window != nullptr && renderer != nullptr;
}

void Window::OnCleanUp() {
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
}
