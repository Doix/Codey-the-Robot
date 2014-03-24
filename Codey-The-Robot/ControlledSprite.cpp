#include "ControlledSprite.h"
#include "AnimatedSprite.h"
#include "Graphics.h"
#include "Game.h"
#include "Map.h"
#include "Rectangle.h"

#include <assert.h>

namespace{
	const float WALKING_SPEED = 0.15f; //(pixels/ms) / ms

	//Collision Rectangle
	const Rectangle COLLISION_RECTANGLE_X(0, Game::TILE_SIZE/2, Game::TILE_SIZE, 2); // xPos, yPos, width, height
	const Rectangle COLLISION_RECTANGLE_Y(Game::TILE_SIZE / 2, 0, 2, Game::TILE_SIZE);
}

ControlledSprite::ControlledSprite(Graphics& graphics, int x, int y)
{
	//remember the initial position of codey
	originX = x;
	originY = y;
	
	resetSprite();

}

//Destructor - release the sprite not necessary, scoped pointers!
ControlledSprite::~ControlledSprite()
{
}

void ControlledSprite::resetSprite(){
	PosX = originX;
	PosY = originY;
	DestX = PosX;
	DestY = PosY;
	velocityX = 0.0f;
	velocityY = 0.0f;
	currentMotion = MotionType::STANDING;
	currentDirection = DirectionFacing::RIGHT;
}
//update the player position
void ControlledSprite::update(int elapsedTimeMs, const Map& map){
	sprites[getSpriteState()]->update(elapsedTimeMs);
	if (started) {
		if (!busy) {
			if (!commands.isFinished()) {
				curCommand = commands.getCommand();
				executeCommand(curCommand);
									
			}
			else {
				started = false;
				currentMotion = MotionType::STANDING;
			}
		}
		else {
			executeCommand(curCommand);
		}
		updateX(elapsedTimeMs, map);
		updateY(elapsedTimeMs, map);
	}

	
}

//draw the sprite at the relevant position 
//This is virtual and can be overidden in any inherited classes to a different width/height
void ControlledSprite::draw(Graphics& graphics){
	sprites[getSpriteState()]->draw(graphics, PosX, PosY, Game::TILE_SIZE,Game::TILE_SIZE);
}

//Functions for each of the different movements player can do
void ControlledSprite::sendCommand(std::shared_ptr<Command> command){
	//TODO: make an if statement if there is a loop command
	commands.addCommand(command);
}

void ControlledSprite::removeCommand(int index){
	//TODO: make an if statement if there is a loop command
	commands.deleteCommand(index);
}

void ControlledSprite::startCommands(){
	if (!busy) {
		resetSprite();
		started = true;
		commands.restart();
	}
}

std::list < std::shared_ptr<Command>>* ControlledSprite::getCommands() {
	return commands.getList();
}

SpriteState ControlledSprite::getSpriteState(){
	return SpriteState(currentMotion, currentDirection);
}

//get Damage rectangle

Rectangle ControlledSprite::damageRectangle() const{
	return Rectangle(PosX + Game::TILE_SIZE / 2,
		PosY + Game::TILE_SIZE / 2,
		Game::TILE_SIZE / 2,
		Game::TILE_SIZE / 2);
}

Rectangle ControlledSprite::clickRectangle() const{
	return Rectangle(PosX,
		PosY,
		Game::TILE_SIZE,
		Game::TILE_SIZE);
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

//Update the x / y co-ordinates as applicable
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

void ControlledSprite::executeCommand(CommandAction command){
	if (!busy){
		busy = true;
		switch (curCommand){
		case CommandAction::MOVE_FORWARD:
			currentMotion = MotionType::WALKING;
			switch (currentDirection){
			case DirectionFacing::LEFT:
				DestX = static_cast<int>(round((PosX - Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE);
				velocityX = -WALKING_SPEED;
				break;
			case DirectionFacing::RIGHT:
				DestX = static_cast<int>(round((PosX + Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE);
				velocityX = WALKING_SPEED;
				break;
			case DirectionFacing::DOWN:
				DestY = static_cast<int>(round((PosY + Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE);
				velocityY = WALKING_SPEED;
				break;
			case DirectionFacing::UP:
				DestY = static_cast<int>(round((PosY - Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE);
				velocityY = -WALKING_SPEED;
				break;
			}
			break;
		case CommandAction::TURN_LEFT:
			switch (currentDirection){
			case DirectionFacing::LEFT:
				currentDirection = DirectionFacing::DOWN;
				break;
			case DirectionFacing::RIGHT:
				currentDirection = DirectionFacing::UP;
				break;
			case DirectionFacing::DOWN:
				currentDirection = DirectionFacing::RIGHT;
				break;
			case DirectionFacing::UP:
				currentDirection = DirectionFacing::LEFT;
				break;
			}
			stopMoving();
			break;
		case CommandAction::TURN_RIGHT:
			switch (currentDirection){
			case DirectionFacing::LEFT:
				currentDirection = DirectionFacing::UP;
				break;
			case DirectionFacing::RIGHT:
				currentDirection = DirectionFacing::DOWN;
				break;
			case DirectionFacing::DOWN:
				currentDirection = DirectionFacing::LEFT;
				break;
			case DirectionFacing::UP:
				currentDirection = DirectionFacing::RIGHT;
				break;
			}
			stopMoving();
			break;
		}
	}
	else{
		if (currentMotion == MotionType::WALKING){
		
			switch (currentDirection){
			case DirectionFacing::LEFT:
				if (PosX <= DestX) {
					stopMoving();
					if (PosX < DestX) {
						PosX = DestX;
					}
				}
				break;
			case DirectionFacing::RIGHT:
				if (PosX >= DestX) {
					stopMoving();
					if (PosX > DestX) {
						PosX = DestX;
					}
				}
				break;
			case DirectionFacing::DOWN:
				if (PosY >= DestY) {
					stopMoving();
					if (PosY > DestY) {
						PosY = DestY;
					}
				}
				break;
			case DirectionFacing::UP:
				if (PosY <= DestY) {
					stopMoving();
					if (PosY < DestY) {
						PosY = DestY;
					}
				}
				break;
			}
		}
	}
}

bool ControlledSprite::isBusy() {
	return busy;
}

void ControlledSprite::stopMoving(){
	busy = false;
	velocityX = 0;
	velocityY = 0;
	currentMotion = MotionType::STANDING;
}

int ControlledSprite::getCol() {
	return round(PosX / Game::TILE_SIZE);
}

int ControlledSprite::getRow() {
	return round(PosY / Game::TILE_SIZE);
}