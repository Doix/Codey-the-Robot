#include "Player.h"
#include "AnimatedSprite.h"
#include "Graphics.h"
#include "Game.h"

namespace{
	const float WALKING_ACCELERATION = 0.0012f; //(pixels/ms) / ms
	const float MAX_SPEED_XY = 0.325f; // pixels / ms
	const float SLOW_DOWN_FACTOR = 0.8f;
}

Player::Player(Graphics& graphics, int x, int y)
{
	//set the position of X & Y to the parameter
	PosX = x;
	PosY = y;

	//initialise velocity and acceleration of the player to 0
	velocityX = 0.0f;
	accelerationX = 0.0f;
	velocityY = 0.0f;
	accelerationY = 0.0f;

	//initialise the AnimatedSprite for the player
	sprite.reset(new AnimatedSprite(graphics, "content/codey.png", 0, 0, Game::TILE_SIZE, Game::TILE_SIZE, 15, 9));
}

//Destructor - release the sprite
Player::~Player()
{
	sprite.release();
}

//update the player position
void Player::update(int elapsedTimeMs){
	sprite->update(elapsedTimeMs);

	updatePosAndAcceleration(PosX, accelerationX, velocityX, elapsedTimeMs);
	updatePosAndAcceleration(PosY, accelerationY, velocityY, elapsedTimeMs);
}

//draw the sprite at the relevant position
void Player::draw(Graphics& graphics){
	sprite->draw(graphics, PosX, PosY);
}

//Functions for each of the different movements player can do
void Player::startMovingLeft(){
	accelerationX = -WALKING_ACCELERATION;
}
void Player::startMovingRight(){
	accelerationX = WALKING_ACCELERATION;
}
void Player::startMovingUp(){
	accelerationY = -WALKING_ACCELERATION;
}
void Player::startMovingDown(){
	accelerationY = WALKING_ACCELERATION;
}
void Player::stopMoving(){
	accelerationX = 0.0f;
	accelerationY = 0.0f;
}


//helper function to calculate the speed and acceleration of the player for both X and Y axis.
void Player::updatePosAndAcceleration(int& PosXY, float& accelerationXY, float& velocityXY, int elapsedTimeMs){
	//calculate the position of X / Y based on the speed and the time elapsed since last called
	//(also round as int * float to ensure it doesn't truncate data)
	PosXY += round(velocityXY * elapsedTimeMs);

	//calculate the new velocity for the next update
	velocityXY += accelerationXY * elapsedTimeMs;

	//check that the speed never gets higher than the max for left/right and up/down movements
	if (accelerationXY < 0.0f){
		velocityXY = std::fmax(velocityXY, -MAX_SPEED_XY);
	}
	else if (accelerationXY > 0.0f){
		velocityXY = std::fmin(velocityXY, MAX_SPEED_XY);
	}
	else{
		velocityXY *= SLOW_DOWN_FACTOR;
	}
}