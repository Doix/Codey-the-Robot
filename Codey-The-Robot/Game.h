#ifndef GAME_H_
#define GAME_H_


class Codey;
class Graphics;
class Hud;
class Map;
class Enemy;

#include <memory>

class Game
{
public:
	Game();
	~Game();

	static int TILE_SIZE;

private:
	void eventLoop();
	void update(int elapsedTimeInMs);
	void draw(Graphics& graphics);

	std::unique_ptr<Map> map;
	std::shared_ptr<Codey> player;
	std::shared_ptr<Enemy> firstEnemy;
	std::unique_ptr<Hud> hud;
};

#endif // GAME_H_

