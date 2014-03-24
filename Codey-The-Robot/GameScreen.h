#ifndef GAME_SCREEN_H_
#define GAME_SCREEN_H_

#include "Screen.h"
#include "Map.h"
#include "Codey.h"
#include "Enemy.h"
#include "Hud.h"
#include "Level.h"

class GameScreen : public Screen
{
public:
	GameScreen(Game* game, std::shared_ptr<Level> level);
	~GameScreen();
	virtual void draw();
	virtual void update(int elapsedTimeInMs);

private:
	std::unique_ptr<Hud> hud;
	std::shared_ptr<Level> level;
};

#endif //GAME_SCREEN_H_

