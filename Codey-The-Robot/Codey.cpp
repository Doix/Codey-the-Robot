#include "Codey.h"
#include "Game.h"
#include "AnimatedSprite.h"



Codey::Codey(Graphics& graphics, int x, int y) : ControlledSprite(graphics, x, y)
{
}


Codey::~Codey()
{
}

void Codey::initialiseSpriteSheets(Graphics& graphics){
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
