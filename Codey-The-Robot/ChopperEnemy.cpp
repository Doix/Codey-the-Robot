#include "ChopperEnemy.h"
#include "AnimatedSprite.h"
#include "LoopCommand.h"
#include "SpriteState.h"
#include "Game.h"

namespace{
	const std::string ENEMY_FILE_PATH = "content/robotEnemies.png";
	const std::string ENEMY_REVERSE_FILE_PATH = "content/robotEnemiesReverse.png";

	const int ENEMY_WIDTH = 30;
	const int ENEMY_HEIGHT = 30;
	const int FPS = 8;
}

ChopperEnemy::ChopperEnemy(Graphics& graphics, int x, int y) : Enemy(graphics, x, y)
{
	//initialise the AnimatedSprite for the player
	initialiseSpriteSheets(graphics);
	initCommands();
}


ChopperEnemy::~ChopperEnemy()
{
}
void ChopperEnemy::initialiseSpriteSheets(Graphics& graphics){

	
	//need to hardcode numbers as sprite sheet has an inconsistent grid!

	sprites[SpriteState(MotionType::STANDING, DirectionFacing::RIGHT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_FILE_PATH,
		0, 214,
		ENEMY_WIDTH, ENEMY_HEIGHT, FPS, 2));

	sprites[SpriteState(MotionType::WALKING, DirectionFacing::LEFT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_REVERSE_FILE_PATH,
		422 - (ENEMY_WIDTH * 2), 214,
		ENEMY_WIDTH, ENEMY_HEIGHT, FPS, 2));

	sprites[SpriteState(MotionType::WALKING, DirectionFacing::RIGHT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_FILE_PATH,
		0, 214,
		ENEMY_WIDTH, ENEMY_HEIGHT, FPS, 2));
	
	sprites[SpriteState(MotionType::WALKING, DirectionFacing::DOWN)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_FILE_PATH,
		0, 214,
		ENEMY_WIDTH, ENEMY_HEIGHT, FPS, 2));

	sprites[SpriteState(MotionType::STANDING, DirectionFacing::DOWN)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_FILE_PATH,
		0, 214,
		ENEMY_WIDTH, ENEMY_HEIGHT, FPS, 2));

	sprites[SpriteState(MotionType::STANDING, DirectionFacing::LEFT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_REVERSE_FILE_PATH,
		422 - (ENEMY_WIDTH * 2), 214,
		ENEMY_WIDTH, ENEMY_HEIGHT, FPS, 2));

	sprites[SpriteState(MotionType::STANDING, DirectionFacing::UP)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_REVERSE_FILE_PATH,
		422 - (ENEMY_WIDTH * 2), 214,
		ENEMY_WIDTH, ENEMY_HEIGHT, FPS, 2));

	sprites[SpriteState(MotionType::WALKING, DirectionFacing::UP)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_REVERSE_FILE_PATH,
		422 - (ENEMY_WIDTH * 2), 214,
		ENEMY_WIDTH, ENEMY_HEIGHT, FPS, 2));
}

void ChopperEnemy::initCommands(){
	std::shared_ptr<LoopCommand>loop;
	loop.reset(new LoopCommand(CommandAction::LOOP, -1));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::MOVE_FORWARD)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::TURN_RIGHT)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::TURN_RIGHT)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::MOVE_FORWARD)));
	sendCommand(loop);
}

void ChopperEnemy::draw(Graphics& graphics){
	sprites[getSpriteState()]->draw(graphics, PosX+10, PosY+10, Game::TILE_SIZE*0.7, Game::TILE_SIZE*0.7);
}