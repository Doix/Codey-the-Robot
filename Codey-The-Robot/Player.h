#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <queue>
#include "Commands.h"
class Sprite;
class Graphics;

class Player
{
public:
	Player(Graphics& graphics, int x, int y);
	~Player();

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
	std::unique_ptr<Sprite> sprite;
	std::queue< Command > commands;
	Command curCommand;

	void updatePosAndAcceleration(int& PosXY, float& acclerationXY, float& velocityXY, int elapsedTimeMs);
};

#endif   // PLAYER_H_