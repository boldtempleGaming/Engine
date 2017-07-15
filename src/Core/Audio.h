#ifndef ENGINE_AUDIO_H
#define ENGINE_AUDIO_H

#include <iostream>
#include <string>

#include <cmath>
#include <SDL2/SDL_mixer.h>

#include "Core/Resources.h"
#include "Core/Vec2.h"

class Audio {
public:
    static void Init(int alloc_channels = 16);
    static void Quit();

    static int ChannelsAllocated();

    static void Play(Mix_Chunk* sound, int loops = 0);
    static void Play(Mix_Music* music, int loops = 0);

    static void SetMasterVolume(int volume);
    static int GetMasterVolume();

    static void SetMusicVolume(int volume);
    static int GetMusicVolume();


    Audio();
    Audio(Mix_Chunk* sound);
    Audio(Mix_Music* sound);
    Audio(const std::string& file_path, bool isMusic = false);
    ~Audio();

    void SetSound(const std::string& sound, bool isMusic = false);

    void Play(int loops = 0);
    void Stop();

    void SetVolume(int volume);
    void SetPanning(const Vec2& pos, const Vec2& viewport_size, Uint32 max_offset = 0);
    void SetDistance(Uint8 dist);
    void AddDistance(int dx);

    int GetVolume();
    Vec2 GetPosition();
    Uint8 GetDistance();

    bool IsLoaded();
    bool IsPlaying();
    bool Type();

private:
    static const int MAX_VOLUME = 255;
    static const int MIN_VOLUME = 0;

    static int _g_volume;
    static int _mus_volume;

    bool _isMusic;
    void* _audio_data = nullptr; // use dynamic or static cast to set type
    int _channel = INT32_MIN; // stopped
    Uint8 _distance = 0;
    Uint8 _volume = 100;
    Uint32 _max_offset = 2000;
    Vec2 _position;

    void setup_audio_on_play();
};


#endif //ENGINE_AUDIO_H
