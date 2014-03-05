#include "ControlledSprite.h"
#include "AnimatedSprite.h"
#include "Graphics.h"
#include "Game.h"

namespace{
	const float WALKING_ACCELERATION = 0.0012f; //(pixels/ms) / ms
	const float MAX_SPEED_XY = 0.325f; // pixels / ms
}

ControlledSprite::ControlledSprite(Graphics& graphics, int x, int y)
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
	initialiseSpriteSheets(graphics);

	//initialise state
	currentMotion = MotionType::STANDING;
}

//Destructor - release the sprite not necessary, scoped pointers!
ControlledSprite::~ControlledSprite()
{
}

//update the player position
void ControlledSprite::update(int elapsedTimeMs){
	sprites[getSpriteState()]->update(elapsedTimeMs);

	if (started) {
		if (!busy) {
			if (commands.size() > 0) {
				curCommand = commands.front();
				commands.pop();
				busy = true;

				switch (curCommand){
				case Command::LEFT:
					DestX = PosX - Game::TILE_SIZE;
					currentMotion = MotionType::WALKING_LEFT;
					break;
				case Command::RIGHT:
					DestX = PosX + Game::TILE_SIZE;
					currentMotion = MotionType::WALKING_RIGHT;
					break;
				case Command::DOWN:
					DestY = PosY + Game::TILE_SIZE;
					currentMotion = MotionType::WALKING_DOWN;
					break;
				case Command::UP:
					DestY = PosY - Game::TILE_SIZE;
					currentMotion = MotionType::WALKING_UP;
					break;
				}
			}
			else {
				started = false;

				currentMotion = MotionType::STANDING;
			}
		}
		else {
			switch (curCommand){
				case Command::LEFT:
					if (PosX > DestX) {
						accelerationX = -WALKING_ACCELERATION;
					}
					else {
						busy = false;
						accelerationX = 0;
					}
					break;
				case Command::RIGHT:
					if (PosX < DestX) {
						accelerationX = WALKING_ACCELERATION;
					}
					else {
						busy = false;
						accelerationX = 0;
					}
					break;
				case Command::DOWN:
					if (PosY < DestY) {
						accelerationY = WALKING_ACCELERATION;
					}
					else {
						busy = false;
						accelerationY = 0;
					}
					break;
				case Command::UP:
					if (PosY > DestY) {
						accelerationY = -WALKING_ACCELERATION;
					}
					else {
						busy = false;
						accelerationY = 0;
					}
					break;
			}
		}
	}

	updatePosAndAcceleration(PosX, accelerationX, velocityX, elapsedTimeMs);
	updatePosAndAcceleration(PosY, accelerationY, velocityY, elapsedTimeMs);
}

//draw the sprite at the relevant position
void ControlledSprite::draw(Graphics& graphics){
	sprites[getSpriteState()]->draw(graphics, PosX, PosY);
}

//Functions for each of the different movements player can do
void ControlledSprite::startMovingLeft(){
	commands.push(Command::LEFT);
}
void ControlledSprite::startMovingRight(){
	commands.push(Command::RIGHT);
}
void ControlledSprite::startMovingUp(){
	commands.push(Command::UP);
}
void ControlledSprite::startMovingDown(){
	commands.push(Command::DOWN);
}

void ControlledSprite::startCommands(){
	started = true;
}
void ControlledSprite::stopMoving(){
	accelerationX = 0.0f;
	accelerationY = 0.0f;
}


//helper function to calculate the speed and acceleration of the player for both X and Y axis.
void ControlledSprite::updatePosAndAcceleration(int& PosXY, float& accelerationXY, float& velocityXY, int elapsedTimeMs){
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
		velocityXY = 0;
	}
}

void ControlledSprite::initialiseSpriteSheets(Graphics& graphics){
	sprites[SpriteState(MotionType::STANDING)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		"content/codey.png",
		0 * Game::TILE_SIZE, 0 * Game::TILE_SIZE,
		Game::TILE_SIZE, Game::TILE_SIZE, 15, 2));

	sprites[SpriteState(MotionType::WALKING_LEFT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		"content/codeyReverse.png",
		2 * Game::TILE_SIZE, 0 * Game::TILE_SIZE,
		Game::TILE_SIZE, Game::TILE_SIZE, 15, 6));

	sprites[SpriteState(MotionType::WALKING_RIGHT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		"content/codey.png",
		2 * Game::TILE_SIZE, 0 * Game::TILE_SIZE,
		Game::TILE_SIZE, Game::TILE_SIZE, 15, 6));

	sprites[SpriteState(MotionType::WALKING_UP)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		"content/codey.png",
		0 * Game::TILE_SIZE, 5 * Game::TILE_SIZE,
		Game::TILE_SIZE, Game::TILE_SIZE, 15, 6));

	sprites[SpriteState(MotionType::WALKING_DOWN)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		"content/codey.png",
		6 * Game::TILE_SIZE, 5 * Game::TILE_SIZE,
		Game::TILE_SIZE, Game::TILE_SIZE, 15, 2));
}

SpriteState ControlledSprite::getSpriteState(){
	return SpriteState(currentMotion);
}
