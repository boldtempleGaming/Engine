#ifndef ENGINE_RESOURCES_H
#define ENGINE_RESOURCES_H

#include <iostream>
#include <string>
#include <map>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Core/sys.h"
#include "Core/Audio.h"
#include "GUI/Window.h"

class Resources {
public:
    static const char* SPRITES_PATH;
    static const char* FONTS_PATH;
    static const char* SOUNDS_PATH;

    static SDL_Texture* GetTexture(std::string file_path);
    static TTF_Font* GetFont(std::string file_path, int ptsize);
    static Audio* GetAudio(std::string file_path, audio_type type);

    static void UnloadTexture(std::string file_path);
    static void UnloadFont(std::string file_path);
    static void UnloadSound(std::string file_path);
    static void UnloadAll();

private:
    Resources(){};
    static std::map<std::string, SDL_Texture*> _Textures;
    static std::map<std::string, TTF_Font*> _Fonts;
    static std::map<std::string, Audio*> _Sounds;
};


#endif //ENGINE_RESOURCES_H
