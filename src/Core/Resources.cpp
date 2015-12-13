#include "Resources.h"

const char*     Resources::SPRITES_PATH = "../Data/Sprites/";
const char*     Resources::FONTS_PATH = "../Data/Fonts/";
const char*     Resources::SOUNDS_PATH = "../Data/Sounds/";

std::map<std::string, SDL_Texture*>     Resources::_Textures;
std::map<std::string, TTF_Font*>        Resources::_Fonts;
std::map<std::string, Audio*>           Resources::_Sounds;

std::string     Resources::_default_font;
int             Resources::_default_font_ptsize;
std::string     Resources::_default_style;

const std::string& Resources::GetDefaultFont(){
    return _default_font;
}

const int& Resources::GetDefaultFontPtsize(){
    return _default_font_ptsize;
}

const std::string& Resources::GetDefaultStyle(){
    return _default_style;
}
    
void Resources::SetDefaultFont(const std::string font){
    _default_font = font;
}

void Resources::SetDefaultFontPtsize(const int& ptsize){
    if(ptsize >= 0){
        _default_font_ptsize = ptsize;
    }
}

void Resources::SetDefaultFontStyle(const std::string style){
    _default_style = style;
}

SDL_Texture* Resources::GetTexture(std::string file_path){
    SDL_Texture* texture;
    file_path = std::string(SPRITES_PATH) + file_path;

    if(_Textures.count(file_path) == 0){
        std::cout << "Loading texture " << file_path << std::endl;

        texture = IMG_LoadTexture(Window::GetRenderer(), file_path.c_str());
        if(texture != nullptr){
            _Textures[file_path] = texture;
        }else{
            std::cerr << " >> !WARNING! << " << SDL_GetError() << std::endl;
            if (!Window::GetRenderer())
                std::cerr << " Is Renderer initialized?" << std::endl;
        }
    }else{
        texture = _Textures[file_path];
    }

    return texture;
}

TTF_Font* Resources::GetFont(std::string file_path, int ptsize){
    TTF_Font* font;
    std::string sized_path = file_path + int_to_str(ptsize);
    file_path = std::string(FONTS_PATH) + file_path;

    if(_Fonts.count(sized_path) == 0){
        std::cout << "Loading font " << file_path << std::endl;

        font = TTF_OpenFont(file_path.c_str(), ptsize);
        if(font != nullptr){
            _Fonts[sized_path] = font;
        }else{
            std::cerr << " >> !WARNING! << Couldn't open font: " << file_path << std::endl;
        }
    }else{
        font = _Fonts[sized_path];
    }
    return font;
}

Audio* Resources::GetAudio(std::string file_path, audio_type type){
    Audio* audio;
    file_path = std::string(SOUNDS_PATH) + file_path;

    if(_Sounds.count(file_path) == 0){
        std::cout << "Loading sound " << file_path << std::endl;

        audio = new Audio(file_path, type);
        if(audio->IsLoaded()){
            _Sounds[file_path] = audio;
        }else{
            std::cerr << " >> !WARNING! << Couldn't open sound: " << file_path << std::endl;
            delete(audio);
            audio = nullptr;
        }
    }else{
        audio = _Sounds[file_path];
        if(audio->Type() != type){
            delete(audio);

            std::cout << "Loading sound "  << file_path << std::endl;

            audio = new Audio(file_path, type);
            if(audio->IsLoaded()){
                _Sounds[file_path] = audio;
            }else{
                std::cerr << " >> !WARNING! << Couldn't open sound: " << file_path << std::endl;
                delete(audio);
                _Sounds.erase(file_path);
                audio = nullptr;
            }
        }
    }

    return audio;
}

void Resources::UnloadTexture(std::string file_path){
    SDL_Texture* texture = _Textures[file_path];
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}

void Resources::UnloadFont(std::string file_path){
    TTF_Font* font = _Fonts[file_path];
    if(font != nullptr){
        TTF_CloseFont(font);
    }
}

void Resources::UnloadSound(std::string file_path){
    Audio* audio = _Sounds[file_path];
    delete(audio);
}

void Resources::UnloadAll(){
    for(auto it = _Textures.begin(); it != _Textures.end(); it++){
        SDL_Texture* texture = (*it).second;
        if(texture != nullptr){
            SDL_DestroyTexture(texture);
        }
    }
    _Textures.clear();

    for(auto it = _Fonts.begin(); it != _Fonts.end(); it++){
        TTF_Font* font = (*it).second;
        if(font != nullptr){
            TTF_CloseFont(font);
        }
    }
    _Fonts.clear();

    for(auto it = _Sounds.begin(); it != _Sounds.end(); it++){
        delete((*it).second);
    }
    _Sounds.clear();
}
