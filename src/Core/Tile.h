/*
 * Tile.h
 *
 *  Created on: 24 июля 2014 г.
 *      Author: snickers
 */

#ifndef TILE_H_
#define TILE_H_

#include <SDL2/SDL.h>

enum Type {
	TILE_TYPE_NONE = 0,
	TILE_TYPE_WATER,
	TILE_TYPE_SAND,
	TILE_TYPE_GRASS
};

class Tile {
public:
	Tile();
	virtual ~Tile();

	Uint8 tileID;
	Uint8 typeID;

	static SDL_Rect InTileSetPos(const int tile_size, const int x, const int y);
};

#endif /* TILE_H_ */
