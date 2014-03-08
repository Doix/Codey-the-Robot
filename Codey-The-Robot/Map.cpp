#include "Map.h"
#include "Sprite.h"
#include "Graphics.h"
#include "Game.h"
#include "Rectangle.h"

#include <memory>

using std::vector;

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

	//ensure Tiles has the correct size (i.e. numRows*numCols in size)
	map->tiles = vector<vector<Tile> >(
		numRows, vector<Tile >(
		numCols, Tile()));

	std::shared_ptr<Sprite> sprite(new Sprite(graphics, MAP_FILE_PATH, 
		308, 359, 
		MAP_TILE_SIZE, MAP_TILE_SIZE));

	Tile tile(GROUND_TILE, sprite);

	for (int row = 0; row < numRows; ++row){
		for (int col = 0; col < numCols; ++col){

			map->tiles[row][col] = tile;
			if (row == 3 && col == 3){
				map->tiles[row][col] = Tile(BARRIER_TILE, std::shared_ptr<Sprite> (new Sprite(graphics, MAP_FILE_PATH,
					104,155,
					MAP_TILE_SIZE, MAP_TILE_SIZE)));
			}
		}
	}

	return map;
}

vector<Map::CollisionTile> Map::getCollidingTiles(const Rectangle& rectangle) const{

	const int firstRow = rectangle.getTop() / Game::TILE_SIZE;
	const int lastRow = rectangle.getBottom() / Game::TILE_SIZE;
	const int firstCol = rectangle.getLeft() / Game::TILE_SIZE;
	const int lastCol = rectangle.getRight() / Game::TILE_SIZE;
	vector<CollisionTile> collisionTiles;

	for (int row = firstRow; row <= lastRow; ++row){
		for (int col = firstCol; col <= lastCol; ++col){
			collisionTiles.push_back(CollisionTile(row, col, tiles[row][col].tileType));
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