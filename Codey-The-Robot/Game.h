#ifndef GAME_H_
#define GAME_H_


class Player;
class Graphics;

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

	std::unique_ptr<Player> player;
};

#endif // GAME_H_

