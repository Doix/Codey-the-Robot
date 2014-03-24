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
	//set the position of X & Y to the parameter
	PosX = x;
	PosY = y;

	//remember the initial position of codey
	originX = x;
	originY = y;
	
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

void ControlledSprite::resetSprite(){
	PosX = originX;
	PosY = originY;
	DestX = PosX;
	DestY = PosY;
	velocityX = 0;
	velocityY = 0;
}
//update the player position
void ControlledSprite::update(int elapsedTimeMs, const Map& map){
	sprites[getSpriteState()]->update(elapsedTimeMs);
	if (started) {
		if (!busy) {
			if (!commands.isFinished()) {
				curCommand = commands.getCommand();
				executeCommand(curCommand);
				busy = true;						
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
	return SpriteState(currentMotion);
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
		switch (curCommand){
		case CommandAction::LEFT:
			DestX = static_cast<int>(round((PosX - Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE);
			currentMotion = MotionType::WALKING_LEFT;
			velocityX = -WALKING_SPEED;
			break;
		case CommandAction::RIGHT:
			DestX = static_cast<int>(round((PosX + Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE);
			currentMotion = MotionType::WALKING_RIGHT;
			velocityX = WALKING_SPEED;
			break;
		case CommandAction::DOWN:
			DestY = static_cast<int>(round((PosY + Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE);
			currentMotion = MotionType::WALKING_DOWN;
			velocityY = WALKING_SPEED;
			break;
		case CommandAction::UP:
			DestY = static_cast<int>(round((PosY - Game::TILE_SIZE) / Game::TILE_SIZE)*Game::TILE_SIZE);
			currentMotion = MotionType::WALKING_UP;
			velocityY = -WALKING_SPEED;
			break;
		}
	}
	else{
		switch (curCommand){
		case CommandAction::LEFT:
			if (PosX <= DestX) {
				busy = false;
				if (PosX < DestX) {
					PosX = DestX;
				}
				velocityX = 0;
			}
			break;
		case CommandAction::RIGHT:
			if (PosX >= DestX) {
				busy = false;
				if (PosX > DestX) {
					PosX = DestX;
				}
				velocityX = 0;
			}
			break;
		case CommandAction::DOWN:
			if (PosY >= DestY) {
				busy = false;
				if (PosY > DestY) {
					PosY = DestY;
				}
				velocityY = 0;
			}
			break;
		case CommandAction::UP:
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

bool ControlledSprite::isBusy() {
	return busy;
}