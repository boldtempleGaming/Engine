#include "Audio.h"

int Audio::_g_volume = 100;
int Audio::_mus_volume = 100;

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

void Audio::SetGlobalVolume(int volume){
    if(volume > 100) _g_volume = 100;
    else if(volume < 0) _g_volume = 0;
    else _g_volume = volume;

    Mix_Volume(-1, ((int)MIX_MAX_VOLUME * _g_volume) / 100);
}

void Audio::SetMusicVolume(int volume){
    if(volume > 100) _mus_volume = 100;
    else if(volume < 0) _mus_volume = 0;
    else _mus_volume = volume;

    Mix_VolumeMusic(((int)MIX_MAX_VOLUME * _mus_volume) / 100);
}

void Audio::SetVolume(int volume){
    if(_type == AUDIO_SOUND){
        if(volume > 100) _volume = 100;
        else if(volume < 0) _volume = 0;
        else _volume = volume;

        Mix_Volume(_channel, ((int)MIX_MAX_VOLUME * _volume) / 100);
    }
    else if(_type == AUDIO_MUSIC){
        SetMusicVolume(volume);
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

    setup_audio_on_play();
}

void Audio::Stop(){
    _is_playing = false;
    Mix_HaltChannel(_channel);
}


void Audio::SetPanning(const Vec2& pos, const Vec2& viewport_size, Uint32 max_offset){
    if(_type == AUDIO_SOUND){
        _position = pos;

        if(max_offset != 0) _max_offset = max_offset;

        int ofst_x =  pos.x - viewport_size.x*0.5f;
        int ofst_y =  pos.y - viewport_size.y*0.5f;

        int left;
        int right;
        int max_vol;

        if(ofst_y < 0){
            max_vol = MAX_VOLUME + (static_cast<float>(MAX_VOLUME)/_max_offset) * ofst_y;
        }else if(ofst_y >= 0){
            max_vol = MAX_VOLUME - (static_cast<float>(MAX_VOLUME)/_max_offset) * ofst_y;
        }else{
            max_vol = MAX_VOLUME;
        }

        if(max_vol < 0) max_vol = MIN_VOLUME;
        else if(max_vol > MAX_VOLUME) max_vol = MAX_VOLUME;

        if(ofst_x < 0){
            left = max_vol + (static_cast<float>(max_vol)/_max_offset) * ofst_x;
            right = max_vol + (static_cast<float>(max_vol)/(0.5f*_max_offset)) * ofst_x;
        }else if (ofst_x > 0){
            left = max_vol - (static_cast<float>(max_vol)/(0.5f*_max_offset)) * ofst_x;
            right = max_vol - (static_cast<float>(max_vol)/_max_offset) * ofst_x;
        }else{
            left = right = max_vol;
        }

        if(left > max_vol || left < 0) left = 0;
        if(right > max_vol || right < 0) right = 0;

        std::cout <<"max_vol " << max_vol <<" left " << left << " right" << right << std::endl;
        Mix_SetPanning(_channel, left, right);
    }
}

void Audio::SetDistance(Uint8 dist){
    if(_type == AUDIO_SOUND){
        _distance = (dist < MAX_VOLUME) ? dist : MAX_VOLUME;
        Mix_SetDistance(_channel, _distance);
    }
}

void Audio::AddDistance(int dx){
    int tmp = static_cast<int>(_distance) + dx;

    if( tmp <= 0 ){
        SetDistance(0);
    }else if(tmp > MAX_VOLUME){
        SetDistance(MAX_VOLUME);
    }else{
        SetDistance(tmp);
    }
}

Vec2 Audio::GetPosition(){
    return _position;
}

Uint8 Audio::GetDistance(){
    return _distance;
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

void Audio::setup_audio_on_play(){
    if(_volume < 100){
        SetVolume(_volume);
    }else if(_mus_volume < 100){
        SetMusicVolume(_mus_volume);
    }

    if(_distance > 0){
        SetDistance(_distance);
    }
}
