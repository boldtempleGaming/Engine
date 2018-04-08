/*!
 boldtemple Gaming ©, http://gaming.boldtemple.net
 OpenSource Project - Check Development, License & Readme Sections.

 BGE - boldtemple Cross Platform Game Engine
 /main.cpp
 !*/
#include "Engine.h"

#undef main

#ifndef BUILD_STATIC_LIB
void Engine::OnInit() {

}

void Engine::OnEvent(SDL_Event *event, const Uint8 *keyboardState) {

}

void Engine::OnUpdate() {

}

void Engine::OnRender() {

}

void Engine::OnCleanUp() {

}

int main() {
    Engine engine;
    engine.Start();
    return 0;
}
#endif
