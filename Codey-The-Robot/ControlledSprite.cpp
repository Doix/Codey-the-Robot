#include "ControlledSprite.h"
#include "AnimatedSprite.h"
#include "Graphics.h"
#include "Game.h"

namespace{
	const float WALKING_SPEED = 0.15f; //(pixels/ms) / ms
	const float MAX_SPEED_XY = 0.325f; // pixels / ms
}

ControlledSprite::ControlledSprite(Graphics& graphics, int x, int y)
{
	//set the position of X & Y to the parameter
	PosX = x;
	PosY = y;

	//initialise velocity and acceleration of the player to 0
	velocityX = 0.0f;
	velocityY = 0.0f;
	
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
						velocityX = -WALKING_SPEED;
					}
					else {
						busy = false;
						velocityX = 0;
					}
					break;
				case Command::RIGHT:
					if (PosX < DestX) {
						velocityX = WALKING_SPEED;
					}
					else {
						busy = false;
						velocityX = 0;
					}
					break;
				case Command::DOWN:
					if (PosY < DestY) {
						velocityY = WALKING_SPEED;
					}
					else {
						busy = false;
						velocityY = 0;
					}
					break;
				case Command::UP:
					if (PosY > DestY) {
						velocityY = -WALKING_SPEED;
					}
					else {
						busy = false;
						velocityY = 0;
					}
					break;
			}
		}
	}

	updatePos(PosX, velocityX, elapsedTimeMs);
	updatePos(PosY, velocityY, elapsedTimeMs);
}

//draw the sprite at the relevant position
void ControlledSprite::draw(Graphics& graphics){
	sprites[getSpriteState()]->draw(graphics, PosX, PosY,Game::TILE_SIZE,Game::TILE_SIZE);
}

//Functions for each of the different movements player can do
void ControlledSprite::sendCommand(Command command){
	queuedCommands.push_back(command);
}

void ControlledSprite::startCommands(){
	started = true;
	// create a copy of queuedCommands so that we don't modify the original whilst executing
	// i wonder if this causes a memory leak?
	commands = std::queue<Command>(queuedCommands);
}

std::deque<Command> ControlledSprite::getCommands() {
	return queuedCommands;
}

//helper function to calculate the speed and acceleration of the player for both X and Y axis.
void ControlledSprite::updatePos(int& PosXY,float& velocityXY, int elapsedTimeMs){
	//calculate the position of X / Y based on the speed and the time elapsed since last called
	//(also round as int * float to ensure it doesn't truncate data)
	PosXY += round(velocityXY * elapsedTimeMs);
}

SpriteState ControlledSprite::getSpriteState(){
	return SpriteState(currentMotion);
}
