/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /gui/gui.cpp
!*/

#ifndef FPSCOUNTER_H_
#define FPSCOUNTER_H_

#include <iostream>
#include <SDL2/SDL.h>

class FPS_counter {
public:
    FPS_counter();

    void OnUpdate();
    unsigned int GetFPS();
    float GetSpeedFactor();

private:
    unsigned int old_time;
    unsigned int last_time;

    unsigned int num_frames;
    unsigned int frames;

    float speed_factor;
};

#endif /* FPSCOUNTER_H_ */
