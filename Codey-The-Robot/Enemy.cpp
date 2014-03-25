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
	startCommands();
}


Enemy::~Enemy()
{
}
