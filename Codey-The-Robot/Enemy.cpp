#include "Enemy.h"
#include "Graphics.h"
#include "AnimatedSprite.h"
#include "Game.h"



Enemy::Enemy(Graphics& graphics, int x, int y) : PosX(x), PosY(y)
{
	sprite = std::shared_ptr<Sprite>(new AnimatedSprite(graphics, "content/robotEnemies.png", 0, 35, 36, 35, 1, 4));
}


Enemy::~Enemy()
{
}

void Enemy::draw(Graphics& graphics) const{
	sprite->draw(graphics, PosX, PosY, Game::TILE_SIZE, Game::TILE_SIZE);
}

void Enemy::update(const int elapsed_time_ms){
	sprite->update(elapsed_time_ms);
}
