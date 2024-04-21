#pragma once
#include <vector>
#include <string>
#include "TileType.hpp"

/**
 * Returns a 19x19 grid of tiles from a text file.
 * @param fileName the name of the file to load, from the assets/level/ directory.
 * @return a 19x19 grid representing the level tiles as a 2D vector of TileTypes.
*/
std::vector<std::vector<TileType>> LoadTileGridFromFile(std::string fileName);

/**
 * Saves the given grid of tiles to a text file.
 * @param tileGrid the 19x19 tile grid, as a 2D vector of TileTypes.
 * @param fileName the name of the file to write to.
*/
void SaveTileGridToFile(std::vector<std::vector<TileType>> tileGrid, std::string fileName);