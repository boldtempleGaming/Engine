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

const static bool MAX_FPS = false;//false;

const static int LOGIC_WIN_WIDTH = 800;
const static int LOGIC_WIN_HEIGHT = 400;

const static int MAP_WIDTH = 20;
const static int MAP_HEIGHT = 100;

const static int TILE_SHEET_SIZE = 16;
const static int TILE_SIZE = 32;

const static std::string SPRITES_PATH = "../Data/Sprites/";
const static std::string FONTS_PATH = "../Data/Fonts/";
const static std::string SOUNDS_PATH = "../Data/Sounds/";

const static SDL_Color BACKGROUND_COLOR = COLOR_GRAY;

const static std::string DEFAULT_FONT = "PressStart2P.ttf";
const static int DEFAULT_PTSIZE = 9;

#endif /* CONSTANTS_H_ */

