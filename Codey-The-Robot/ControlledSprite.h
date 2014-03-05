#ifndef CONTROLLED_SPRITE_H_
#define CONTROLLED_SPRITE_H_

#include <memory>
#include <queue>
#include "Commands.h"
#include <map>
#include "SpriteState.h"

class Sprite;
class Graphics;

class ControlledSprite
{
public:
	ControlledSprite(Graphics& graphics, int x, int y);
	~ControlledSprite();

	void update(int elapsedTimeMs);
	void draw(Graphics& graphics);

	void startMovingLeft();
	void startMovingRight();
	void startMovingUp();
	void startMovingDown();
	void stopMoving();
	void startCommands();

private:
	int PosX;
	int PosY;
	int DestX;
	int DestY;

	bool started;
	bool busy;

	float velocityX;
	float accelerationX;
	float velocityY;
	float accelerationY;

	
	std::queue< Command > commands;
	Command curCommand;

	SpriteState getSpriteState();
	MotionType currentMotion;

	void updatePosAndAcceleration(int& PosXY, float& acclerationXY, float& velocityXY, int elapsedTimeMs);

protected:	
	virtual void initialiseSpriteSheets(Graphics& graphics) = 0;
	std::map<SpriteState, std::unique_ptr<Sprite>> sprites;
};

#endif   // CONTROLLED_SPRITE_H_