#ifndef ENGINE_AUDIO_H
#define ENGINE_AUDIO_H

#include <iostream>
#include <string>

#include <SDL_mixer.h>

enum audio_type{
    AUDIO_SOUND = 0,
    AUDIO_MUSIC
};

class Audio {
public:
    static void Init(int alloc_channels = 16);
    static void Quit();

    static int ChannelsAllocated();

    static void Play(Mix_Chunk* sound, int loops = 0);
    static void Play(Mix_Music* music, int loops = 0);

    Audio(Mix_Chunk* sound);
    Audio(Mix_Music* sound);
    Audio(const std::string& file_path, audio_type type = AUDIO_SOUND);

    void Play(int loops = 0);
    bool IsLoaded();
    bool IsPlaying();
    audio_type Type();

private:
    static const int _max_channels;

    audio_type _type;
    void* _audio_data = nullptr; // use dyn or static cast to set type
    int _channel = -1; // stopped
    bool _is_playing = false;
};


#endif //ENGINE_AUDIO_H
