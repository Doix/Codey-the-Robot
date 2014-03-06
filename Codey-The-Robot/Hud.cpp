#include "Hud.h"
#include "AnimatedSprite.h"
#include "Game.h"
#include <iostream>

namespace{
	const int BUTTON_SIZE = 32;
}


Hud::Hud(Graphics& graphics, int x, int y, std::shared_ptr<ControlledSprite> player)
{
	//set the position of X & Y to the parameter
	PosX = x;
	PosY = y;

	//initialise the AnimatedSprite for the player
	sprite.reset(new Sprite(graphics, "content/hud.png", 0, 0, Game::TILE_SIZE*4, Game::TILE_SIZE*6));
	initializeSprites(graphics);
	
	// lets just hardcode this for now
	availableCommands = std::vector<Command>{Command::LEFT, Command::DOWN, Command::UP, Command::RIGHT};
	setPlayer(player);
}

//Destructor - release the sprite
Hud::~Hud()
{
	sprite.release();
}
void Hud::draw(Graphics& graphics){
	sprite->draw(graphics, PosX, PosY,Game::TILE_SIZE*4,Game::TILE_SIZE*6);

	int x = 656;
	const int y = 374;

	for (const auto& command : availableCommands) {
		buttons[command]->draw(graphics, x, y, BUTTON_SIZE, BUTTON_SIZE);
		x += BUTTON_SIZE + 10;
	}
}

void Hud::click(std::tuple<int, int> clicked) {
	int x, y;
	std::tie(x, y) = clicked;
	if (x > 655 && x < 926 && y >375 && y < 470) {
		x -= 655;
		y -= 375;
		int col = x / (BUTTON_SIZE+10);
		int row = y / BUTTON_SIZE;
		//TODO:: will need to be updated to handle multiple rows
		//when we have enough commands
		Command command = availableCommands.at(col);
		player->sendCommand(command);
	}
}

void Hud::initializeSprites(Graphics& graphics) {
	// very very very ugly
	// need a better solution for this
	buttons[Command::RIGHT] = std::unique_ptr<Sprite>(new Sprite(graphics, "content/buttons.png", BUTTON_SIZE*0, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[Command::DOWN] = std::unique_ptr<Sprite>(new Sprite(graphics, "content/buttons.png", BUTTON_SIZE * 1, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[Command::UP] = std::unique_ptr<Sprite>(new Sprite(graphics, "content/buttons.png", BUTTON_SIZE * 2, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[Command::LEFT] = std::unique_ptr<Sprite>(new Sprite(graphics, "content/buttons.png", BUTTON_SIZE * 3, 0, BUTTON_SIZE, BUTTON_SIZE));
	buttons[Command::NONE] = std::unique_ptr<Sprite>(new Sprite(graphics, "content/buttons.png", BUTTON_SIZE * 4, 0, BUTTON_SIZE, BUTTON_SIZE));

}

void Hud::setPlayer(std::shared_ptr<ControlledSprite> player) {
	this->player = player;
}