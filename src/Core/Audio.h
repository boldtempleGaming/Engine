#ifndef ENGINE_AUDIO_H
#define ENGINE_AUDIO_H

#include <iostream>
#include <string>

#include <cmath>
#include <SDL2/SDL_mixer.h>
#include <Core/Vec2.h>

enum audio_type{
    AUDIO_SOUND = 0,
    AUDIO_MUSIC
};

class Audio {
public:
    static const int MAX_VOLUME = 255;
    static const int MIN_VOLUME = 0;

    static void Init(int alloc_channels = 16);
    static void Quit();

    static int ChannelsAllocated();

    static void Play(Mix_Chunk* sound, int loops = 0);
    static void Play(Mix_Music* music, int loops = 0);

    Audio(Mix_Chunk* sound);
    Audio(Mix_Music* sound);
    Audio(const std::string& file_path, audio_type type = AUDIO_SOUND);

    void Play(int loops = 0);

    void SetPanning(const Vec2& pos, const Vec2& viewport_size, uint32_t max_offset = 0);
    void SetDistance(uint8_t dist);
    void AddDistance(int dx);
    Vec2 GetPosition();
    uint8_t GetDistance();

    bool IsLoaded();
    bool IsPlaying();
    audio_type Type();

private:
    audio_type _type;
    void* _audio_data = nullptr; // use dynamic or static cast to set type
    int _channel = -1; // stopped
    bool _is_playing = false;
    uint8_t _distance = 0;
    uint32_t _max_offset = 2000;
    Vec2 _position;
};


#endif //ENGINE_AUDIO_H
