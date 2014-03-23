#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <memory>

class Sprite;
class Graphics;
class Tile;
class Rectangle;


class Map
{
public:
	Map();
	~Map();

	enum TileType{ GROUND_TILE, BARRIER_TILE, TILE_OUT_OF_BOUNDS };

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
private:
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