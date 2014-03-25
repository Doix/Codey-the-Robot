#include "LoopyLeo.h"
#include "AnimatedSprite.h"

namespace{
	const int LOOPY_TILE_SIZE = 80;
	const int LOOPY_HEIGHT = 60;
	const int LOOPY_WIDTH = 44;
	const std::string LOOPY_FILE_PATH = "content/loopy.png";
	const std::string LOOP_REVERSE_FILE_PATH = "content/loopy.png";
	const int FPS = 10;
	const int DEATH_SEQ_TIME = 1500;
}

LoopyLeo::LoopyLeo(Graphics& graphics, int x, int y) : Codey(graphics, x, y)
{
	//initialise the AnimatedSprite for the player
	initialiseSpriteSheets(graphics);
}


LoopyLeo::~LoopyLeo()
{
}


void LoopyLeo::initialiseSpriteSheets(Graphics& graphics){


	sprites[SpriteState(MotionType::WALKING, DirectionFacing::LEFT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		LOOP_REVERSE_FILE_PATH,
		18, 944,
		LOOPY_WIDTH, LOOPY_HEIGHT, FPS, 2));

	sprites[SpriteState(MotionType::WALKING, DirectionFacing::RIGHT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		LOOPY_FILE_PATH,
		150, 944,
		LOOPY_WIDTH, LOOPY_HEIGHT, FPS, 3));

	sprites[SpriteState(MotionType::WALKING, DirectionFacing::UP)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		LOOPY_FILE_PATH,
		19, 1003,
		LOOPY_WIDTH, LOOPY_HEIGHT, FPS, 3));

	sprites[SpriteState(MotionType::WALKING, DirectionFacing::DOWN)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		LOOP_REVERSE_FILE_PATH,
		18, 944,
		LOOPY_WIDTH, LOOPY_HEIGHT, FPS, 2));

	sprites[SpriteState(MotionType::DEAD)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		LOOPY_FILE_PATH,
		284, 1003,
		48 /*Random height*/, LOOPY_HEIGHT, FPS, 1));

	sprites[SpriteState(MotionType::DYING)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		LOOPY_FILE_PATH,
		314, 884,
		LOOPY_WIDTH, LOOPY_HEIGHT, FPS, 2));

	sprites[SpriteState(MotionType::STANDING, DirectionFacing::RIGHT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		LOOPY_FILE_PATH,
		150, 944,
		LOOPY_WIDTH, LOOPY_HEIGHT, FPS, 3));

	sprites[SpriteState(MotionType::STANDING, DirectionFacing::LEFT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		LOOP_REVERSE_FILE_PATH,
		18, 944,
		LOOPY_WIDTH, LOOPY_HEIGHT, FPS, 2));

	sprites[SpriteState(MotionType::STANDING, DirectionFacing::DOWN)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		LOOP_REVERSE_FILE_PATH,
		18, 944,
		LOOPY_WIDTH, LOOPY_HEIGHT, FPS, 2));

	sprites[SpriteState(MotionType::STANDING, DirectionFacing::UP)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		LOOPY_FILE_PATH,
		19, 1003,
		LOOPY_WIDTH, LOOPY_HEIGHT, FPS, 3));

}

void LoopyLeo::draw(Graphics& graphics){
	sprites[getSpriteState()]->draw(graphics, PosX+10, PosY, LOOPY_TILE_SIZE-20, LOOPY_TILE_SIZE);
}
