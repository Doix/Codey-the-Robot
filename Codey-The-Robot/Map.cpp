#include "Map.h"
#include "Sprite.h"
#include "Graphics.h"
#include "Game.h"

#include <memory>

namespace{
	int MAP_TILE_SIZE = 48; //pixels
	int MAP_ROW_COL_FACTOR = 51; //pixels, 1 pixel border around every map tile, therefore need to adjusted col/row search
	const std::string MAP_FILE_PATH = "content/Tiles03.bmp";
}

Map::Map()
{
}


Map::~Map()
{
}

Map* Map::createTestMap(Graphics& graphics){

	Map* map = new Map();

	const int numRows = 6;	//80 * 6 = 480
	const int numCols = 8;	//80 * 8 = 640

	//ensure backgroundSprites has the correct size (i.e. numRows*numCols in size)
	map->backgroundSprites = std::vector<std::vector<std::shared_ptr<Sprite> > >(
		numRows, std::vector<std::shared_ptr<Sprite> >(
		numCols, std::shared_ptr<Sprite>()));

	std::shared_ptr<Sprite> sprite(new Sprite(graphics, MAP_FILE_PATH, 
		308, 359, 
		MAP_TILE_SIZE, MAP_TILE_SIZE));

	for (int row = 0; row < numRows; ++row){
		for (int col = 0; col < numCols; ++col){
			map->backgroundSprites[row][col] = sprite;
		}
	}

	return map;
}

void Map::update(int elapsedTimeMs){
	for (size_t row = 0; row < backgroundSprites.size(); ++row){
		for (size_t col = 0; col < backgroundSprites[row].size(); ++col){
			if (backgroundSprites[row][col]){
				backgroundSprites[row][col]->update(elapsedTimeMs);
			}
		}
	}
}

void Map::draw(Graphics& graphics) const{
	for (size_t row = 0; row < backgroundSprites.size(); ++row){
		for (size_t col = 0; col < backgroundSprites[row].size(); ++col){
			if (backgroundSprites[row][col]){
				backgroundSprites[row][col]->draw(graphics, 
					col*Game::TILE_SIZE, row*Game::TILE_SIZE,
					Game::TILE_SIZE,Game::TILE_SIZE);
			}
		}
	}
}