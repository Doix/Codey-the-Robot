#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <memory>

class Sprite;
class Graphics;


class Map
{
public:
	Map();
	~Map();

	static Map* createTestMap(Graphics& graphics);

	void update(int elapsedTimeMs);
	void draw(Graphics& graphics) const;
private:
	std::vector<std::vector<std::shared_ptr<Sprite> > >  backgroundSprites;
};

#endif MAP_H_