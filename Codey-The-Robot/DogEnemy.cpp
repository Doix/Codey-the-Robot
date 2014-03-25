#include "DogEnemy.h"

namespace{
	const std::string ENEMY_FILE_PATH = "content/robotEnemies.png";
	const std::string ENEMY_REVERSE_FILE_PATH = "content/robotEnemiesReverse.png";
	const int FPS = 8;
}


DogEnemy::DogEnemy(Graphics& graphics, int x, int y) : Enemy(graphics, x, y)
{
	//sprite = std::shared_ptr<Sprite>(new AnimatedSprite(graphics, "content/robotEnemies.png", 0, 35, 36, 35, 1, 4));
	initialiseSpriteSheets(graphics);
	initCommands();
}


DogEnemy::~DogEnemy()
{
}

void DogEnemy::initialiseSpriteSheets(Graphics& graphics){

	//need to hardcode numbers as sprite sheet has an inconsistent grid!
	sprites[SpriteState(MotionType::STANDING, DirectionFacing::RIGHT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_FILE_PATH,
		0, 35,
		36, 35, FPS, 1));

	sprites[SpriteState(MotionType::WALKING, DirectionFacing::LEFT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_REVERSE_FILE_PATH,
		422 - (36 * 4), 35,
		36, 35, FPS, 4));

	sprites[SpriteState(MotionType::WALKING, DirectionFacing::RIGHT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_FILE_PATH,
		0, 35,
		36, 35, FPS, 4));

	sprites[SpriteState(MotionType::WALKING, DirectionFacing::DOWN)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_FILE_PATH,
		0, 35,
		36, 35, FPS, 4));

	sprites[SpriteState(MotionType::STANDING, DirectionFacing::DOWN)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_FILE_PATH,
		0, 35,
		36, 35, FPS, 4));

	sprites[SpriteState(MotionType::STANDING, DirectionFacing::LEFT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_REVERSE_FILE_PATH,
		422 - (36 * 4), 35,
		36, 35, FPS, 1));

	sprites[SpriteState(MotionType::STANDING, DirectionFacing::UP)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_REVERSE_FILE_PATH,
		422 - (36 * 4), 35,
		36, 35, FPS, 1));

	sprites[SpriteState(MotionType::WALKING, DirectionFacing::UP)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_FILE_PATH,
		0, 35,
		36, 35, FPS, 4));
}


//make sure the dog does not go up or down!!
void DogEnemy::initCommands(){
	std::shared_ptr<LoopCommand>loop;
	loop.reset(new LoopCommand(CommandAction::LOOP, -1));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::MOVE_FORWARD)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::MOVE_FORWARD)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::MOVE_FORWARD)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::TURN_RIGHT)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::TURN_RIGHT)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::MOVE_FORWARD)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::MOVE_FORWARD)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::MOVE_FORWARD)));
	sendCommand(loop);
}

void DogEnemy::draw(Graphics& graphics){
	sprites[getSpriteState()]->draw(graphics, PosX+5, PosY+5, Game::TILE_SIZE*.9, Game::TILE_SIZE*0.9);
}
