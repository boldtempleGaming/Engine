/*
 * Tile.cpp
 *
 *  Created on: 24 июля 2014 г.
 *      Author: snickers
 */

#include "Tile.h"

Tile::Tile() {
	tileID = 0;
	typeID = TILE_TYPE_NONE;
}

Tile::~Tile() {

}

SDL_Rect Tile::InTileSetPos(const int tile_size, const int x, const int y) {
	return SDL_Rect { x * tile_size, y * tile_size, tile_size, tile_size };
}

