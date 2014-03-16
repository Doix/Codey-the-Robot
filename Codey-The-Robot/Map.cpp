#include "Map.h"
#include "Sprite.h"
#include "Graphics.h"
#include "Game.h"
#include "Rectangle.h"

#include <memory>
#include <stdexcept> 

using std::vector;

namespace{
	int MAP_TILE_SIZE = 48; //pixels
	int MAP_ROW_COL_FACTOR = 51; //pixels, 1 pixel border around every map tile, therefore need to adjusted col/row search
	const std::string MAP_FILE_PATH = "content/Tiles03.bmp";
	const int numRows = 6;	//80 * 6 = 480
	const int numCols = 8;	//80 * 8 = 640

	//calculate x or Y co-ordinates 
	int getMapTileXY(int col_Or_Row){
		return col_Or_Row * MAP_ROW_COL_FACTOR + 2;

	}
}

Map::Map()
{
}


Map::~Map()
{
}

Map* Map::createTestMap(Graphics& graphics){

	Map* map = new Map();
	
	//ensure Tiles has the correct size (i.e. numRows*numCols in size)
	map->tiles = vector<vector<Tile> >(
		numRows, vector<Tile >(
		numCols, Tile()));

	std::shared_ptr<Sprite> sprite(new Sprite(graphics, MAP_FILE_PATH, 
		getMapTileXY(6), getMapTileXY(7), 
		MAP_TILE_SIZE, MAP_TILE_SIZE));

	Tile tile(GROUND_TILE, sprite);

	for (int row = 0; row < numRows; ++row){
		for (int col = 0; col < numCols; ++col){

			map->tiles[row][col] = tile;

		}
	}



	return map;
}

vector<Map::CollisionTile> Map::getCollidingTiles(const Rectangle& rectangle) const{

	//Get co-ordinates of the collision tile
	const int firstRow = rectangle.getTop() / Game::TILE_SIZE;
	const int lastRow = rectangle.getBottom() / Game::TILE_SIZE;
	const int firstCol = rectangle.getLeft() / Game::TILE_SIZE;
	const int lastCol = rectangle.getRight() / Game::TILE_SIZE;


	vector<CollisionTile> collisionTiles;


	for (int row = firstRow; row <= lastRow; ++row){
		for (int col = firstCol; col <= lastCol; ++col){
			try{
				collisionTiles.push_back(CollisionTile(row, col, tiles.at(row).at(col).tileType));
			}
			catch (std::out_of_range& oor){
				collisionTiles.push_back(CollisionTile(row, col, TILE_OUT_OF_BOUNDS));
			}			
		}
	}

	return collisionTiles;
}


void Map::update(int elapsedTimeMs){
	for (size_t row = 0; row < tiles.size(); ++row){
		for (size_t col = 0; col < tiles[row].size(); ++col){
			if (tiles[row][col].sprite){
				tiles[row][col].sprite->update(elapsedTimeMs);
			}
		}
	}
}

void Map::draw(Graphics& graphics) const{
	for (size_t row = 0; row < tiles.size(); ++row){
		for (size_t col = 0; col < tiles[row].size(); ++col){
			if (tiles[row][col].sprite){
				tiles[row][col].sprite->draw(graphics,
					col*Game::TILE_SIZE, row*Game::TILE_SIZE,
					Game::TILE_SIZE,Game::TILE_SIZE);
			}
		}
	}
}



