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
	virtual void draw(Graphics& graphics) = 0;

protected:
	virtual void initialiseSpriteSheets(Graphics& graphics) = 0;
	bool checkFinished();
	virtual void initCommands() = 0;
};

#endif // ENEMY_H_