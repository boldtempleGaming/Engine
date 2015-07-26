//
// Created by WinPooh32 on 23.07.15.
//

#ifndef ENGINE_RESOURCES_H
#define ENGINE_RESOURCES_H

#include <iostream>
#include <string>
#include <map>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <SDL2/SDL_audio.h>


class Resources {
public:
    static const char* SPRITES_PATH;
    static const char* FONTS_PATH;
    static const char* SOUNDS_PATH;

    static SDL_Texture* GetTextue(std::string file_path);
    static TTF_Font* GetFont(std::string file_path);
    static Mix_Chunk* GetSound(std::string file_path);
    static Mix_Music* GetMusic(std::string file_path);

private:
    Resources(){};
    static std::map<std::string, SDL_Texture*> _Textures;
    static std::map<std::string, TTF_Font*> _Fonts;
    static std::map<std::string, Mix_Chunk*> _Sounds;
    static std::map<std::string, Mix_Music*> _Musics;
};


#endif //ENGINE_RESOURCES_H
