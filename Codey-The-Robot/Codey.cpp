#include "Codey.h"
#include "Game.h"
#include "AnimatedSprite.h"

namespace{
	const int CODEY_TILE_SIZE = 80;
	const std::string CODEY_FILE_PATH = "content/codey.png";
	const std::string CODEY_REVERSE_FILE_PATH = "content/codeyReverse.png";
}

Codey::Codey(Graphics& graphics, int x, int y) : ControlledSprite(graphics, x, y)
{
	//initialise the AnimatedSprite for the player
	initialiseSpriteSheets(graphics);
}

Codey::~Codey()
{
}

void Codey::initialiseSpriteSheets(Graphics& graphics){
	sprites[SpriteState(MotionType::STANDING)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_FILE_PATH,
		0 * CODEY_TILE_SIZE, 0 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, 15, 2));

	sprites[SpriteState(MotionType::WALKING_LEFT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_REVERSE_FILE_PATH,
		2 * CODEY_TILE_SIZE, 0 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, 15, 6));

	sprites[SpriteState(MotionType::WALKING_RIGHT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_FILE_PATH,
		2 * CODEY_TILE_SIZE, 0 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, 15, 6));

	sprites[SpriteState(MotionType::WALKING_UP)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_FILE_PATH,
		0 * CODEY_TILE_SIZE, 5 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, 15, 6));

	sprites[SpriteState(MotionType::WALKING_DOWN)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_FILE_PATH,
		6 * CODEY_TILE_SIZE, 5 * CODEY_TILE_SIZE,
		CODEY_TILE_SIZE, CODEY_TILE_SIZE, 15, 2));
}

void Codey::draw(Graphics& graphics){
	sprites[getSpriteState()]->draw(graphics, PosX, PosY, CODEY_TILE_SIZE, CODEY_TILE_SIZE);
}