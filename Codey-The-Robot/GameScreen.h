#ifndef GAME_SCREEN_H_
#define GAME_SCREEN_H_

#include "Screen.h"
#include "Map.h"
#include "Codey.h"
#include "Enemy.h"
#include "Hud.h"

class GameScreen : public Screen
{
public:
	GameScreen(Game* game);
	~GameScreen();
	virtual void draw();
	virtual void update(int elapsedTimeInMs);

private:
	std::unique_ptr<Map> map;
	std::shared_ptr<Codey> player;
	std::shared_ptr<Enemy> firstEnemy;
	std::unique_ptr<Hud> hud;
};

#endif //GAME_SCREEN_H_

