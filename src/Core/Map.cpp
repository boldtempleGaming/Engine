/*
 * Map.cpp
 *
 *  Created on: 24 июля 2014 г.
 *      Author: snickers
 */

#include "Map.h"

#include <string>
#include <iostream>

Map::Map() {
	texture_tileset = nullptr;
	map_rect = {0, 0, MAP_WIDTH, MAP_HEIGHT};
	update = true;
}

Map::~Map() {

}

//Без стыда скопирастил :}
bool Map::OnLoad(std::string fname) {

	std::cout << "Loading level \"" << fname << "\"" << std::endl;

	TileList.clear();

	FILE* FileHandle = fopen(fname.c_str(), "r");

	if (FileHandle == nullptr) {
		return false;
	}

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			Tile tempTile;

			fscanf(FileHandle, "%d:%d ", (int*)&tempTile.tileID, (int*)&tempTile.typeID);

			TileList.push_back(tempTile);
		}
		fscanf(FileHandle, "\n");
	}

	fclose(FileHandle);

	return true;
}

std::string printTile(int tile) {
	switch (tile) {
	case TILE_TYPE_NONE:
		return "Water";
	case TILE_TYPE_GRASS:
		return "Grass";
	default:
		return "Unknown";
	}
}

void Map::LayTiles() {

	TileMap.clear();

	int id = 0;
	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {

			SDL_Rect tile_texture_rect;
			int tileUp, tileDown, tileLeft, tileRight, pos;
			tileUp = tileDown = tileLeft = tileRight = TILE_TYPE_NONE;

			pos = id - MAP_WIDTH; //up
			if (pos >= 0) {
				tileUp = TileList[pos].typeID;
			}

			pos = id + MAP_WIDTH; //down
			if (pos <= MAP_WIDTH * MAP_HEIGHT) {
				tileDown = TileList[pos].typeID;
			}

			pos = id - 1; //left
			if (pos >= 0) {
				tileLeft = TileList[pos].typeID;
			}

			pos = id + 1; //right
			if (pos <= MAP_WIDTH * MAP_HEIGHT) {
				tileRight = TileList[pos].typeID;
			}

			/*
			 std::cout << "X: " <<  X << " Y: " << Y << std::endl;
			 std::cout << "Up: " <<  printTile(tileUp) << std::endl;
			 std::cout << "Left: " <<  printTile(tileLeft) << std::endl;
			 std::cout << "Right: " <<  printTile(tileRight) << std::endl;
			 std::cout << "Down: " <<  printTile(tileDown) << std::endl;

			 std::cout << "--------------" << std::endl;
			 */

			switch (TileList[id].typeID) {
			case TILE_TYPE_GRASS:
				if (tileUp == TILE_TYPE_NONE) {
					if (tileLeft == TILE_TYPE_NONE) {
						tile_texture_rect = Tile::InTileSetPos(TILE_SHEET_SIZE, 0, 0);
					} else if (tileRight == TILE_TYPE_NONE) {
						tile_texture_rect = Tile::InTileSetPos(TILE_SHEET_SIZE, 2, 0);
					} else {
						tile_texture_rect = Tile::InTileSetPos(TILE_SHEET_SIZE, 1, 0);
					}
				} else if (tileLeft == TILE_TYPE_NONE) {
					if (tileDown == TILE_TYPE_NONE) {
						tile_texture_rect = Tile::InTileSetPos(TILE_SHEET_SIZE, 0, 2);
					} else if (tileRight == TILE_TYPE_NONE) {
						tile_texture_rect = Tile::InTileSetPos(TILE_SHEET_SIZE, 1, 1);
					} else {
						tile_texture_rect = Tile::InTileSetPos(TILE_SHEET_SIZE, 0, 1);
					}
				} else if (tileDown == TILE_TYPE_NONE) {
					if (tileRight == TILE_TYPE_NONE) {
						tile_texture_rect = Tile::InTileSetPos(TILE_SHEET_SIZE, 2, 2);
					} else {
						tile_texture_rect = Tile::InTileSetPos(TILE_SHEET_SIZE, 1, 2);
					}
				} else if (tileRight == TILE_TYPE_NONE) {
					tile_texture_rect = Tile::InTileSetPos(TILE_SHEET_SIZE, 2, 1);
				} else {
					tile_texture_rect = Tile::InTileSetPos(TILE_SHEET_SIZE, 1, 1);
				}

				break;

			default:
				tile_texture_rect = Tile::InTileSetPos(TILE_SHEET_SIZE, 7, 3); //water tile
			}

			//TileMap[id] = tile_texture_rect;
			TileMap.push_back(tile_texture_rect);
			id++;

		}
	}

}

void Map::OnRender(int mapX, int mapY) {

	if (update) {
		LayTiles();
		update = false;
	}

	int id = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {

			SDL_Rect rect_tile, rect_tileset;

			rect_tile = {
				Camera::X() + (X * TILE_SIZE),
				Camera::Y() + (Y * TILE_SIZE),
				TILE_SIZE ,
				TILE_SIZE
			};

			if (Camera::InView(&rect_tile))
				Surface::Draw(texture_tileset, &TileMap[id],
						&rect_tile);
			id++;
		}
	}
}
