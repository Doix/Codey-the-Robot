#include "ControlledSprite.h"
#include "AnimatedSprite.h"
#include "Graphics.h"
#include "Game.h"
#include "Map.h"
#include "Rectangle.h"

#include <assert.h>

namespace{
	const float WALKING_SPEED = 0.15f; //(pixels/ms) / ms
	const float MAX_SPEED_XY = 0.325f; // pixels / ms

	//Collision Rectangle
	const Rectangle COLLISION_RECTANGLE_X(0, Game::TILE_SIZE/2, Game::TILE_SIZE, 2); // x, y, width, height
	const Rectangle COLLISION_RECTANGLE_Y(Game::TILE_SIZE / 2, 0, 2, Game::TILE_SIZE);
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
void ControlledSprite::update(int elapsedTimeMs, const Map& map){
	sprites[getSpriteState()]->update(elapsedTimeMs);
	if (started) {
		if (!busy) {
			if (commands.size() > 0) {
				curCommand = commands.front();
				commands.pop();
				busy = true;

				switch (curCommand){
				case Command::LEFT:
					DestX = round((PosX - Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE;
					currentMotion = MotionType::WALKING_LEFT;
					velocityX = -WALKING_SPEED;
					break;
				case Command::RIGHT:
					DestX = round((PosX + Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE;
					currentMotion = MotionType::WALKING_RIGHT;
					velocityX = WALKING_SPEED;
					break;
				case Command::DOWN:
					DestY = round((PosY + Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE;
					currentMotion = MotionType::WALKING_DOWN;
					velocityY = WALKING_SPEED;
					break;
				case Command::UP:
					DestY = round((PosY - Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE;
					currentMotion = MotionType::WALKING_UP;
					velocityY = -WALKING_SPEED;
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
					if (PosX <= DestX) {
						busy = false;
						if (PosX < DestX) {
							PosX = DestX;
						}
						velocityX = 0;
					}
					break;
				case Command::RIGHT:
					if (PosX >= DestX) {
						busy = false;
						if (PosX > DestX) {
							PosX = DestX;
						}
						velocityX = 0;
					}
					break;
				case Command::DOWN:
					if (PosY >= DestY) {
						busy = false;
						if (PosY > DestY) {
							PosY = DestY;
						}
						velocityY = 0;
					}
					break;
				case Command::UP:
					if (PosY <= DestY) {
						busy = false;
						if (PosY < DestY) {
							PosY = DestY;
						}
						velocityY = 0;
					}
					break;
			}
		}
	}

	updateX(elapsedTimeMs, map);
	updateY(elapsedTimeMs, map);
}

//draw the sprite at the relevant position 
//This is virtual and can be overidden in any inherited classes to a different width/height
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
	PosXY += (int)round(velocityXY * elapsedTimeMs);
}

SpriteState ControlledSprite::getSpriteState(){
	return SpriteState(currentMotion);
}


//Get collision rectangles for distance travelled delta
Rectangle ControlledSprite::leftCollision(int delta) const{
	assert(delta <= 0);

	return Rectangle(
		PosX + COLLISION_RECTANGLE_X.getLeft() + delta, 
		PosY + COLLISION_RECTANGLE_X.getTop(), 
		COLLISION_RECTANGLE_X.getWidth() / 2 - delta,
		COLLISION_RECTANGLE_X.getHeight());
}

Rectangle ControlledSprite::rightCollision(int delta) const{
	assert(delta >= 0);

	return Rectangle(
		PosX + COLLISION_RECTANGLE_X.getLeft() + COLLISION_RECTANGLE_X.getWidth() / 2,
		PosY + COLLISION_RECTANGLE_X.getTop(),
		COLLISION_RECTANGLE_X.getWidth() / 2 + delta,
		COLLISION_RECTANGLE_X.getHeight());
}

Rectangle ControlledSprite::topCollision(int delta) const{
	assert(delta <= 0);

	return Rectangle(
		PosX + COLLISION_RECTANGLE_Y.getLeft(),
		PosY + COLLISION_RECTANGLE_Y.getTop() + delta,
		COLLISION_RECTANGLE_Y.getWidth(),
		COLLISION_RECTANGLE_Y.getHeight() / 2 - delta);
}

Rectangle ControlledSprite::bottomCollision(int delta) const{
	assert(delta >= 0);

	return Rectangle(
		PosX + COLLISION_RECTANGLE_Y.getLeft(),
		PosY + COLLISION_RECTANGLE_Y.getTop() + COLLISION_RECTANGLE_Y.getHeight() / 2,
		COLLISION_RECTANGLE_Y.getWidth(),
		COLLISION_RECTANGLE_Y.getHeight() / 2 + delta);
}

void ControlledSprite::updateX(int elapsedTimeMs, const Map& map){
	const int delta = (int)round(velocityX * elapsedTimeMs);
	
	if (delta > 0){
		//check collision in direction of delta
		CollisionInfo info = getCollisionInfo(map, rightCollision(delta));
		//React to collision
		if (info.collided){
			PosX = info.col* Game::TILE_SIZE - COLLISION_RECTANGLE_X.getRight();
			velocityX = 0.0f;
			busy = false;
		}
		else{
			PosX += delta;
		}

		//Check collision in other direction
		info = getCollisionInfo(map, leftCollision(0));
		if (info.collided){
			PosX = info.col * Game::TILE_SIZE + COLLISION_RECTANGLE_X.getRight();
			velocityX = 0.0f;
			busy = false;
		}
	}
	else if(delta < 0){
		//check collision in direction of delta
		CollisionInfo info = getCollisionInfo(map, leftCollision(delta));

		//React to collision
		if (info.collided){
			PosX = info.col * Game::TILE_SIZE + COLLISION_RECTANGLE_X.getRight();
			velocityX = 0.0f;
			busy = false;
		}
		else{
			PosX += delta;
		}

		//Check collision in other direction
		info = getCollisionInfo(map, rightCollision(0));
		if (info.collided){
			PosX = info.col* Game::TILE_SIZE - COLLISION_RECTANGLE_X.getRight();
			velocityX = 0.0f;
			busy = false;
		}
	}
}

void ControlledSprite::updateY(int elapsedTimeMs, const Map& map){
	const int delta = (int)round(velocityY * elapsedTimeMs);

	if (delta > 0){
		//check collision in direction of delta
		CollisionInfo info = getCollisionInfo(map, bottomCollision(delta));

		//React to collision
		if (info.collided){
			PosY = info.row * Game::TILE_SIZE - COLLISION_RECTANGLE_Y.getBottom();
			velocityY = 0.0f;
			busy = false;
		}
		else{
			PosY += delta;
		}

		//Check collision in other direction
		info = getCollisionInfo(map, topCollision(0));
		if (info.collided){
			PosY = info.row * Game::TILE_SIZE + COLLISION_RECTANGLE_Y.getHeight();
			velocityY = 0.0f;
			busy = false;
		}
	}
	else if(delta < 0){
		//check collision in direction of delta
		CollisionInfo info = getCollisionInfo(map, topCollision(delta));

		//React to collision
		if (info.collided){
			PosY = info.row * Game::TILE_SIZE + COLLISION_RECTANGLE_Y.getHeight();
			velocityY = 0.0f;
			busy = false;
		}
		else{
			PosY += delta;
		}

		//Check collision in other direction
		info = getCollisionInfo(map, bottomCollision(0));
		if (info.collided){
			PosY = info.row * Game::TILE_SIZE - COLLISION_RECTANGLE_Y.getBottom();
			velocityY = 0.0f;
			busy = false;
		}
	}
}

ControlledSprite::CollisionInfo ControlledSprite::getCollisionInfo(const Map& map, const Rectangle& rectangle){
	CollisionInfo info = { false, 0, 0 };

	std::vector<Map::CollisionTile> tiles(map.getCollidingTiles(rectangle));
	for (size_t i = 0; i < tiles.size(); ++i){
		if (tiles[i].tileType == Map::BARRIER_TILE || tiles[i].tileType == Map::TILE_OUT_OF_BOUNDS){
			info.collided = true;
			info.row = tiles[i].row;
			info.col = tiles[i].col;
			break;
		}
	}
	return info;
}
