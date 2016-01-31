#include "Audio.h"

void Audio::Init(int alloc_channels){
    Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);

    // initialize sdl mixer, open up the audio device
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        std::cerr << " >> !ERROR! << Audio isn't initialised! " << Mix_GetError() << std::endl;
    }

    Mix_AllocateChannels(alloc_channels);
}

void Audio::Quit(){
    Mix_CloseAudio();
    Mix_Quit();
}

int Audio::ChannelsAllocated(){
    return Mix_AllocateChannels(-1);
}

void Audio::Play(Mix_Chunk* sound, int loops){
    if(sound != nullptr) {
        Mix_PlayChannel(-1, sound, loops);
    }
}

void Audio::Play(Mix_Music* music, int loops){
    if(music != nullptr){
        Mix_PlayMusic(music, loops);
    }
}

void Audio::Play(int loops){
    if(!IsLoaded()){
        std::cerr << " >> !ERROR! << Trying to play not loaded audio file!" << std::endl;
        return;
    }

    switch(_type){
        case AUDIO_SOUND:
            int free_channel;
            int channels;
            channels = ChannelsAllocated();

            if(!IsPlaying()) {
                //searching for free channel to play
                for (free_channel = 0; free_channel < channels; ++free_channel) {
                    if (Mix_Playing(free_channel) != 1) {
                        break; // free channel found
                    }
                }

                _channel = free_channel; // save occupied channel
            }else{
                free_channel = _channel;
            }

            if(channels == 0 || free_channel >= channels){
                std::cerr << " >> !Warning! << No free audio channels! " << std::endl;
                return; // you can alloc new channels here :)
            }

            Mix_PlayChannel(free_channel, static_cast<Mix_Chunk*>(_audio_data), loops);
            //Mix_ChannelFinished(&Audio::OnHalt); // set callback on channel halting
            break;

        case AUDIO_MUSIC:
            Mix_PlayMusic(static_cast<Mix_Music*>(_audio_data), loops);
            break;
    }
}

Audio::Audio(Mix_Music* music){
    _type = AUDIO_MUSIC;
    _audio_data = music;
}

Audio::Audio(Mix_Chunk* sound){
    _type = AUDIO_SOUND;
    _audio_data = sound;
}

Audio::Audio(const std::string& file_path, audio_type type){
    switch(type){
        case AUDIO_SOUND:
            Mix_Chunk* chunk;
            chunk = Mix_LoadWAV(file_path.c_str());
            if(chunk != nullptr){
                _audio_data = chunk;
                _type = AUDIO_SOUND;
            }else{
                std::cerr << " >> !ERROR! << " << Mix_GetError << std::endl;
            }
            break;
        case AUDIO_MUSIC:
            Mix_Music* music;
            music = Mix_LoadMUS(file_path.c_str());
            if(music != nullptr){
                _audio_data = music;
                _type = AUDIO_MUSIC;
            }
            break;
    }
}

bool Audio::IsLoaded(){
    return (_audio_data != nullptr);
}

bool Audio::IsPlaying(){
    switch(_type){
        case AUDIO_SOUND:
            if(_channel != -1) {
                if (Mix_Playing(_channel) && !Mix_Paused(_channel)) {
                    return true;
                }else{
                    _channel = -1;
                }
            }
            break;
        case AUDIO_MUSIC:
            return (Mix_PlayingMusic() == 1);
            break;
    }
    return false;
}

audio_type Audio::Type(){
    return _type;
}