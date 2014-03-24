#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <memory>
#include <map>

class Sprite;
class Graphics;
class Tile;
class Rectangle;


class Map
{
public:
	Map(Graphics & graphics);
	~Map();
	// needed for angelscript
	void AddRef() { /* do nothing */ }
	void ReleaseRef() { /* do nothing */ }

	enum TileType{ GROUND_TILE = 0, BARRIER_TILE = 1, TILE_OUT_OF_BOUNDS = 2, YELLOW_TILE = 3, GREEN_TILE = 4, VICOTRY_TILE = 5 };
	class CollisionTile
	{
	public:
		CollisionTile(int row, int col, TileType tileType) : 
			row(row), 
			col(col), 
			tileType(tileType) {}

		int row, col;
		TileType tileType;
	};

	std::vector<CollisionTile> getCollidingTiles(const Rectangle& rectangle) const;

	static Map* createTestMap(Graphics& graphics);
	static Map* createMapFromFile(Graphics& graphics, std::string filePath);

	void update(int elapsedTimeMs);
	void draw(Graphics& graphics) const;
	void Map::setTile(int row, int col, TileType tileType);
private:
	void initializeSprites(Graphics& graphics);
	std::map<TileType, std::shared_ptr<Sprite>> tileSprites;

	class Tile
	{
	public:
		Tile(TileType tileType = TileType::GROUND_TILE, 
			std::shared_ptr<Sprite> sprite = std::shared_ptr<Sprite>()) :
			tileType(tileType), 
			sprite(sprite){}

		TileType tileType;
		std::shared_ptr<Sprite> sprite;
	};

	std::vector<std::vector<Tile> >  tiles;
	int getColRow(const int pos) const;
};
#endif MAP_H_