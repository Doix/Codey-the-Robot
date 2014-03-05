#include "Hud.h"
#include "AnimatedSprite.h"
#include "Game.h"
#include <iostream>

Hud::Hud(Graphics& graphics, int x, int y)
{
	//set the position of X & Y to the parameter
	PosX = x;
	PosY = y;

	//initialise the AnimatedSprite for the player
	//should remove magic numbers eventually
	sprite.reset(new Sprite(graphics, "content/hud.png", 0, 0, Game::TILE_SIZE*4, Game::TILE_SIZE*6));
}

//Destructor - release the sprite
Hud::~Hud()
{
	sprite.release();
}
void Hud::draw(Graphics& graphics){
	sprite->draw(graphics, PosX, PosY);
}

void Hud::click(std::tuple<int, int> clicked) {
	int x, y;
	std::tie(x, y) = clicked;
	std::cout << x << ' ' << y << '\n';

}