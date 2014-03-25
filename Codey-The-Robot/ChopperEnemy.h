#ifndef CHOPPER_ENEMY_H_
#define CHOPPER_ENEMY_H_

#include "Enemy.h"

class ChopperEnemy : public Enemy
{
public:
	ChopperEnemy(Graphics& graphics, int PosX, int PosY);
	~ChopperEnemy();

	void draw(Graphics& graphics);
protected:
	void initialiseSpriteSheets(Graphics& graphics);
	void initCommands();
};

#endif // CHOPPER_ENEMY_H_