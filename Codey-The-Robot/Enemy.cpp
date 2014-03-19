#include "Enemy.h"
#include "Graphics.h"
#include "AnimatedSprite.h"
#include "Game.h"
#include "LoopCommand.h"

namespace{
	const std::string ENEMY_FILE_PATH = "content/robotEnemies.png";
	const std::string ENEMY_REVERSE_FILE_PATH = "content/robotEnemiesReverse.png";
	const int FPS = 8;
}

Enemy::Enemy(Graphics& graphics, int x, int y) : ControlledSprite(graphics, x, y)
{
	//sprite = std::shared_ptr<Sprite>(new AnimatedSprite(graphics, "content/robotEnemies.png", 0, 35, 36, 35, 1, 4));
	initialiseSpriteSheets(graphics);
	initCommands();
	startCommands();
}


Enemy::~Enemy()
{
}

void Enemy::initialiseSpriteSheets(Graphics& graphics){
	//need to hardcode numbers as sprite sheet has an inconsistent grid!
	sprites[SpriteState(MotionType::STANDING)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_FILE_PATH,
		0, 35,
		36, 35, FPS, 1));

	sprites[SpriteState(MotionType::WALKING_LEFT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_REVERSE_FILE_PATH,
		422-(36*4), 35,
		36, 35, FPS, 4));

	sprites[SpriteState(MotionType::WALKING_RIGHT)] =
		std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		ENEMY_FILE_PATH,
		0, 35,
		36, 35, FPS, 4));
}

void Enemy::initCommands(){
	std::shared_ptr<LoopCommand>loop;
	loop.reset(new LoopCommand(CommandAction::LOOP, -1));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::RIGHT)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::RIGHT)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::RIGHT)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::LEFT)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::LEFT)));
	loop->addCommand(std::shared_ptr<Command>(new Command(CommandAction::LEFT)));
	sendCommand(loop);
}