/*
 * constants.h
 *
 *  Created on: 24 июля 2014 г.
 *      Author: Admin
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>
#include <SDL2/SDL.h>

#include "GUI/colors.h"
//---------Константы---------

const bool MAX_FPS = false;//false;

const int LOGIC_WIN_WIDTH = 800;
const int LOGIC_WIN_HEIGHT = 400;

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 100;

const int TILE_SHEET_SIZE = 16;
const int TILE_SIZE = 32;

const std::string SPRITES_PATH = "../Data/Sprites/";
const std::string FONTS_PATH = "../Data/Fonts/";
const std::string SOUNDS_PATH = "../Data/Sounds/";

const SDL_Color BACKGROUND_COLOR = COLOR_GRAY;

const std::string DEFAULT_FONT = "PressStart2P.ttf";
const int DEFAULT_PTSIZE = 9;
//---------------------------
#endif /* CONSTANTS_H_ */

