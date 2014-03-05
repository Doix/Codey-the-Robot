#ifndef GAME_H_
#define GAME_H_


class Codey;
class Graphics;
class Hud;

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

	std::unique_ptr<Codey> player;
	std::unique_ptr<Hud> hud;
};

#endif // GAME_H_

