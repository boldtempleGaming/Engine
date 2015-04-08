/*
 * Map.h
 *
 *  Created on: 24 июля 2014 г.
 *      Author: snickers
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include <stdio.h>

#include "constants.h"
#include "GUI/Window.h"
#include "Render/Surface.h"
#include "Core/Tile.h"
#include "Render/Camera.h"



class Map {
public:
	Map();
	virtual ~Map();

	SDL_Texture* texture_tileset;
	SDL_Rect map_rect;

	bool update;

	void LayTiles();//укладка плиток

	bool OnLoad(std::string fpath);
	void OnRender(int mapX, int mapY);

private:
	std::vector<Tile> TileList;
	std::vector<SDL_Rect> TileMap;
};

#endif /* MAP_H_ */
