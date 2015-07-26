//
// Created by winpooh on 23.07.15.
//

#include "Resources.h"

const char* Resources::SPRITES_PATH = "../Data/Sprites/";
const char* Resources::FONTS_PATH = "../Data/Fonts/";
const char* Resources::SOUNDS_PATH = "../Data/Sounds/";

std::map<std::string, SDL_Texture*> Resources::_Textures;
std::map<std::string, TTF_Font*> Resources::_Fonts;
std::map<std::string, Mix_Chunk*> Resources::_Sounds;
std::map<std::string, Mix_Music*> Resources::_Musics;

SDL_Texture* Resources::GetTextue(std::string file_path){
    return nullptr;
}

TTF_Font* Resources::GetFont(std::string file_path){
    return nullptr;
}

Mix_Chunk* Resources::GetSound(std::string file_path){
    Mix_Chunk* chunk;
    file_path = std::string(SOUNDS_PATH) + file_path;

    if(_Sounds.count(file_path) == 0){
        chunk = Mix_LoadWAV(file_path.c_str());
        if(chunk){
            _Sounds[file_path] = chunk;
        }else{
            std::cerr << " >> !WARNING! << Couldn't open sound: " << file_path << std::endl;
        }
    }else{
        chunk = _Sounds[file_path];
    }

    return chunk;
}

Mix_Music* Resources::GetMusic(std::string file_path){
    Mix_Music* music;
    file_path = std::string(SOUNDS_PATH) + file_path;

    if(_Musics.count(file_path) == 0){
        music = Mix_LoadMUS(file_path.c_str());
        if(music){
            _Musics[file_path] = music;
        }else{
            std::cerr << " >> !WARNING! << Couldn't open music: " << file_path << std::endl;
        }
    }else{
        music = _Musics[file_path];
    }

    return music;
}