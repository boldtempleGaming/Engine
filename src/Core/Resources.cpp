#include "Resources.h"

const char*     Resources::SPRITES_PATH = "Data/Sprites/";
const char*     Resources::FONTS_PATH = "Data/Fonts/";
const char*     Resources::SOUNDS_PATH = "Data/Sounds/";

std::unordered_map<std::string, SDL_Texture*>                 Resources::_Textures;
std::unordered_map<std::string, Resources::FontsBufWrapper>   Resources::_Fonts;
std::unordered_map<std::string, Resources::AudiosBufWrapper>  Resources::_Sounds;

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

        //texture = IMG_LoadTexture(Window::GetRenderer(), file_path.c_str());
        texture = ReadRWtexture(file_path);
        if(texture != nullptr){
            _Textures[file_path] = texture;
        }else{
            std::cerr << " >> !ERROR! << " << SDL_GetError() << std::endl;
            if (!Window::GetRenderer())
                std::cerr << " Is Renderer initialized?" << std::endl;
        }
    }else{
        texture = _Textures[file_path];
    }

    return texture;
}

TTF_Font* Resources::GetFont(std::string file_path, int ptsize){
    //FontBufWrapper font;
    //std::string sized_path = file_path + int_to_str(ptsize);
    file_path = std::string(FONTS_PATH) + file_path;

    if(_Fonts.count(file_path) == 0){
        std::cout << "Loading font " << file_path << std::endl;

        _Fonts[file_path] = FontsBufWrapper();

        //font = TTF_OpenFont(file_path.c_str(), ptsize);
        TTF_Font* font = ReadRWfont(file_path, ptsize, _Fonts[file_path].RawBuffer);
        if(font != nullptr){
            _Fonts[file_path].Fonts[ptsize] = font;
            return font;
        }else{
            std::cerr << " >> !ERROR! << Couldn't open font: " << file_path << std::endl;
        }
    }else{
        FontsBufWrapper* wrapper = &_Fonts[file_path];

        if(wrapper->Fonts.count(ptsize) == 0){
            TTF_Font* font = ReadFontFromMem(ptsize, wrapper->RawBuffer);
            wrapper->Fonts[ptsize] = font;
            return font;
        }else{
            return wrapper->Fonts[ptsize];
        }
    }

    return nullptr;
}

Audio* Resources::GetAudio(std::string file_path, audio_type type){
    Audio* audio = nullptr;
    file_path = std::string(SOUNDS_PATH) + file_path;

    if(_Sounds.count(file_path) == 0){
        std::cout << "Loading sound " << file_path << std::endl;

        _Sounds[file_path] = AudiosBufWrapper();

        audio = ReadRWaudio(file_path, type, _Sounds[file_path].RawBuffer);
        if(audio->IsLoaded()){
            _Sounds[file_path].audio = audio;
        }else{
            std::cerr << " >> !ERROR! << Couldn't open sound: " << file_path << std::endl;

            delete(audio);
            audio = nullptr;
            _Sounds.erase(file_path);
        }
    }else{
        audio = _Sounds[file_path].audio;
        if(audio->Type() != type){
            delete(audio);

            std::cout << "Loading music "  << file_path << std::endl;

            //audio = new Audio(file_path, type);
            audio = ReadRWaudio(file_path, type, _Sounds[file_path].RawBuffer);
            if(audio->IsLoaded()){
                _Sounds[file_path].audio = audio;
            }else{
                std::cerr << " >> !ERROR! << Couldn't open sound: " << file_path << std::endl;

                delete(audio);
                audio = nullptr;
                _Sounds.erase(file_path);
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
    
    //_Textures[file_path] = nullptr;
    _Textures.erase(file_path);
}

void Resources::UnloadFont(std::string file_path){
    FontsBufWrapper* wrapper = &_Fonts[file_path];

    for ( auto it = wrapper->Fonts.begin(); it != wrapper->Fonts.end(); ++it ){
        TTF_CloseFont(it->second);
    }

    _Fonts.erase(file_path);
}

void Resources::UnloadSound(std::string file_path){
    Audio* audio = _Sounds[file_path].audio;
    delete(audio);
    
    //_Sounds[file_path] = nullptr;
    _Sounds.erase(file_path);
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
        FontsBufWrapper* wrapper = &((*it).second);
        for ( auto it = wrapper->Fonts.begin(); it != wrapper->Fonts.end(); ++it ){
            TTF_CloseFont(it->second);
        }
    }
    _Fonts.clear();

    for(auto it = _Sounds.begin(); it != _Sounds.end(); it++){
        delete ((*it).second).audio;
    }
    _Sounds.clear();
}

SDL_RWops* Resources::ReadFile(const std::string& file_path, std::vector<char>& buffer){
    PhysFS::ifstream in_file(file_path);

    if(in_file){
        size_t len = in_file.length();
        buffer.resize(len);

        in_file.read(&buffer[0], len);

        if(in_file){
            return SDL_RWFromMem(&buffer[0], len);
        }else{
            std::cerr << " >> !ERROR! << Couldn't read file: " <<  file_path << std::endl;
        }
    }else{
        std::cerr << " >> !ERROR! << Couldn't open file: " <<  file_path << std::endl;
    }

    return nullptr;
}

SDL_Texture* Resources::ReadRWtexture(const std::string& file_path){
    std::vector<char> buffer;

    SDL_RWops* data = Resources::ReadFile(file_path, buffer);
    SDL_Texture* texture = nullptr;

    if(data != nullptr){
        texture = IMG_LoadTexture_RW(Window::GetRenderer(), data, 1);
    }

    return texture;
}

TTF_Font *Resources::ReadFontFromMem(int ptsize, std::vector<char>& buffer){
    SDL_RWops* data = SDL_RWFromConstMem(&buffer[0], buffer.size());
    return TTF_OpenFontRW(data, 1, ptsize);
}

TTF_Font* Resources::ReadRWfont(const std::string& file_path, int ptsize, std::vector<char>& buffer){
    SDL_RWops* data = Resources::ReadFile(file_path, buffer);
    TTF_Font* font = nullptr;

    if(data != nullptr){
        font = TTF_OpenFontRW(data, 1, ptsize);
    }

    return font;
}

Audio* Resources::ReadRWaudio(const std::string& file_path, audio_type type, std::vector<char>& buffer){
    SDL_RWops* data = Resources::ReadFile(file_path, buffer);
    Audio* audio = nullptr;

    if(data != nullptr){
        if(type == AUDIO_SOUND){
            // This can load WAVE, AIFF, RIFF, OGG, and VOC format
            audio = new Audio(Mix_LoadWAV_RW(data, 1));
        }
        else if(type == AUDIO_MUSIC){
            audio = new Audio(Mix_LoadMUS_RW(data, 1));
        }
    }

    return audio;
}
