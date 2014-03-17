#ifndef ENEMY_H_
#define ENEMY_H_

#include <memory>
#include "ControlledSprite.h"

class Graphics;
class Sprite;

class Enemy : public ControlledSprite
{
public:
	Enemy(Graphics& graphics, int PosX, int PosY);
	~Enemy();

protected:
	void initialiseSpriteSheets(Graphics& graphics);
	bool checkFinished();
	void initCommands();
};

#endif // ENEMY_H_