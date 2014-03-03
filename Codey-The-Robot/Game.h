#ifndef GAME_H_
#define GAME_H_


class Sprite;
class Graphics;

#include <memory>

class Game
{
public:
	Game();
	~Game();

private:
	void eventLoop();
	void update();
	void draw(Graphics& graphics);

	std::unique_ptr<Sprite> sprite;
};

#endif // GAME_H_

