#ifndef CONTROLLED_SPRITE_H_
#define CONTROLLED_SPRITE_H_

#include <memory>
#include <queue>
#include "Commands.h"
#include <map>
#include "SpriteState.h"

class Sprite;
class Graphics;
class Map;
class Rectangle;

class ControlledSprite
{
public:
	ControlledSprite(Graphics& graphics, int x, int y);
	~ControlledSprite();

	void update(int elapsedTimeMs, const Map& map);
	virtual void draw(Graphics& graphics);

	void sendCommand(Command command);
	void stopMoving();
	void startCommands();
	std::deque<Command> ControlledSprite::getCommands();

protected:
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

	std::deque< Command > queuedCommands;
	std::queue< Command > commands;
	Command curCommand;

	SpriteState getSpriteState();
	MotionType currentMotion;

	Rectangle leftCollision(int delta) const;
	Rectangle rightCollision(int delta) const;
	Rectangle bottomCollision(int delta) const;
	Rectangle topCollision(int delta) const;


	void updatePos(int& PosXY, float& velocityXY, int elapsedTimeMs);

	void updateX(int elapsedTimeMs, const Map& map);
	void updateY(int elapsedTimeMs, const Map& map);

	virtual void initialiseSpriteSheets(Graphics& graphics) = 0;
	std::map<SpriteState, std::unique_ptr<Sprite>> sprites;

	//create a struct for the collision info
	struct CollisionInfo{
		bool collided;
		int row, col;
	};

	CollisionInfo getCollisionInfo(const Map& map, const Rectangle& rectangle);
};

#endif   // CONTROLLED_SPRITE_H_