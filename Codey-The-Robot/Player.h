#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
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

private:
	int PosX;
	int PosY;
	float velocityX;
	float accelerationX;
	float velocityY;
	float accelerationY;
	std::unique_ptr<Sprite> sprite;

	void updatePosAndAcceleration(int& PosXY, float& acclerationXY, float& velocityXY, int elapsedTimeMs);
};

#endif   // PLAYER_H_