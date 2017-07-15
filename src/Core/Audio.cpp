#include "Audio.h"

int Audio::_g_volume = 100;
int Audio::_mus_volume = 100;
std::set<Audio*> Audio::_WithListeners;

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

void Audio::SetMasterVolume(int volume){
    if(volume > 100) _g_volume = 100;
    else if(volume < 0) _g_volume = 0;
    else _g_volume = volume;

    Mix_Volume(-1, (MIX_MAX_VOLUME * _g_volume) / 100);
}

int Audio::GetMasterVolume(){
    return _g_volume;
}

void Audio::SetMusicVolume(int volume){
    if(volume > 100) _mus_volume = 100;
    else if(volume < 0) _mus_volume = 0;
    else _mus_volume = volume;

    Mix_VolumeMusic((MIX_MAX_VOLUME * _mus_volume) / 100);
}

int Audio::GetMusicVolume(){
    return _mus_volume;
}

void Audio::CalcListenersPanning(){
    for(Audio* audio: _WithListeners) {
        audio->CalcPanning();
    }
}

Audio::Audio(Mix_Music* music){
    _isMusic = true;
    _audio_data = music;
}

Audio::Audio(Mix_Chunk* sound){
    _isMusic = false;
    _audio_data = sound;
}

Audio::Audio(const std::string& file_path, bool isMusic){
    if(isMusic){
        Mix_Music* music;
        music = Mix_LoadMUS(file_path.c_str());

        if(music != nullptr){
            _audio_data = music;
            _isMusic = true;
        }
    }else{
        Mix_Chunk* chunk;
        chunk = Mix_LoadWAV(file_path.c_str());

        if(chunk != nullptr){
            _audio_data = chunk;
            _isMusic = false;
        }else{
            std::cerr << " >> !ERROR! << " << Mix_GetError << std::endl;
        }
    }
}

Audio::~Audio(){
    DelListener();
}

void Audio::SetVolume(int volume){
    if(_isMusic){
        SetMusicVolume(volume);
    }else{
        if(volume > 100) _volume = 100;
        else if(volume < 0) _volume = 0;
        else _volume = volume;

        if(IsPlaying()){
            Mix_Volume(_channel, (MIX_MAX_VOLUME * _volume) / 100);
        }
    }
}

void Audio::Play(int loops){
    if(!IsLoaded()){
        std::cerr << " >> !ERROR! << Trying to play not loaded audio file!" << std::endl;
        return;
    }

    if(_isMusic){
        Mix_PlayMusic(static_cast<Mix_Music*>(_audio_data), loops);
    }else{
        if(IsPlaying()) {
            Stop();
        }

        _channel = Mix_PlayChannel(-1, static_cast<Mix_Chunk*>(_audio_data), loops);
        SetVolume(_volume);
        CalcPanning();

        if(_channel == -1){
            std::cerr << " >> !Warning! << " << Mix_GetError() << std::endl;
            return;
        }

        //Mix_ChannelFinished(&Audio::OnHalt); // set callback on channel halting
    }

    setup_audio_on_play();
}

void Audio::Stop(){
    if(IsPlaying()){
        Mix_HaltChannel(_channel);
    }
}


void Audio::SetPanning(const Vec2& pos, const Vec2& viewport_size, Uint32 max_offset){
    if(!_isMusic && IsPlaying()){
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

        Mix_SetPanning(_channel, left, right);
    }
}

void Audio::SetWorldPos(const Vec2& pos){
    _world_position = pos;
}

void Audio::SetDistance(Uint8 dist){
    if(!_isMusic){
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

void Audio::SetListener(Object* listener, Uint32 max_offset){
    if(listener == nullptr){
        DelListener();
        return;
    }

    _max_offset = max_offset;
    _listener = listener;
    _WithListeners.insert(this);

    CalcPanning();
}

void Audio::DelListener(){
    _listener = nullptr;
    _WithListeners.erase(this);
}

Object* Audio::GetListener(){
    return _listener;
}

int Audio::GetVolume(){
    if(_isMusic){
       return _mus_volume;
    }else{
        return _volume;
    }
}

Vec2 Audio::GetPosition(){
    return _position;
}

Vec2 Audio::GetWorldPos(){
    return _world_position;
}

Uint8 Audio::GetDistance(){
    return _distance;
}

Audio::Audio(){

}

void Audio::SetSound(const std::string &sound, bool isMusic){
    this->_audio_data = Resources::GetAudio(sound, isMusic);
    this->_isMusic = isMusic;
}

bool Audio::IsLoaded(){
    return (_audio_data != nullptr);
}

bool Audio::IsPlaying(){
    if(_isMusic){
        return (Mix_PlayingMusic() == 1);
    }else{
        if(_channel != INT32_MIN) {
            if (Mix_Playing(_channel) && !Mix_Paused(_channel)) {
                return true;
            }else{
                _channel = INT32_MIN;
            }
        }
    }

    return false;
}

bool Audio::Type(){
    return _isMusic;
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

void Audio::CalcPanning(){
    if(_listener != nullptr){
        SetPanning((Window::GetSize()*0.5) - _listener->GetGlobalPos() + _world_position,
                          Window::GetSize(),
                          _max_offset);
    }
}
