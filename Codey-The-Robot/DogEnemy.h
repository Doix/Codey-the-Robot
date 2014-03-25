#ifndef DOG_ENEMY_H_
#define DOG_ENEMY_H_

#include "Enemy.h"
#include "Graphics.h"
#include "AnimatedSprite.h"
#include "Game.h"
#include "LoopCommand.h"

class DogEnemy : public Enemy
{
public:
	DogEnemy(Graphics& graphics, int PosX, int PosY);
	~DogEnemy();

	void draw(Graphics& graphics);
protected:
	void initialiseSpriteSheets(Graphics& graphics);
	void initCommands();
};

#endif //DOG_ENEMY_H_