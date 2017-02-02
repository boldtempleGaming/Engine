#ifndef ENGINE_RESOURCES_H
#define ENGINE_RESOURCES_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <cstring>

#include <physfs.hpp>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <Common/sys.h>
#include <GUI/Window.h>
#include <Core/Audio.h>

class Resources {
public:
    static const char* SPRITES_PATH;
    static const char* FONTS_PATH;
    static const char* SOUNDS_PATH;

    static const std::string& GetDefaultFont();
    static const int& GetDefaultFontPtsize();
    static const std::string& GetDefaultStyle();
    
    static void SetDefaultFont(const std::string font);
    static void SetDefaultFontPtsize(const int& ptsize);
    static void SetDefaultFontStyle(const std::string style);
    
    static SDL_Texture* GetTexture(std::string file_path);
    static TTF_Font *GetFont(std::string file_path, int ptsize);
    static Audio* GetAudio(std::string file_path, audio_type type = AUDIO_SOUND);

    static void UnloadTexture(std::string file_path);
    static void UnloadFont(std::string file_path);
    static void UnloadSound(std::string file_path);
    static void UnloadAll();

private:
    Resources(){}

    struct FontsBufWrapper{
        std::unordered_map<int, TTF_Font*> Fonts;
        std::vector<char> RawBuffer;
    };

    struct AudiosBufWrapper{
        Audio* audio;
        std::vector<char> RawBuffer;
    };
    
    static std::unordered_map<std::string, SDL_Texture*> _Textures;
    static std::unordered_map<std::string, FontsBufWrapper> _Fonts;
    static std::unordered_map<std::string, AudiosBufWrapper> _Sounds;
    static std::string _default_font;
    static int _default_font_ptsize;
    static std::string _default_style;

    static SDL_RWops* ReadFile(const std::string& file_path, std::vector<char> &buffer);

    static SDL_Texture* ReadRWtexture(const std::string& file_path);

    static TTF_Font* ReadFontFromMem(int ptsize, std::vector<char> &buffer);
    static TTF_Font* ReadRWfont(const std::string& file_path, int ptsize, std::vector<char>& buffer);

    static Audio* ReadRWaudio(const std::string& file_path, audio_type type, std::vector<char> &buffer);
};


#endif //ENGINE_RESOURCES_H
